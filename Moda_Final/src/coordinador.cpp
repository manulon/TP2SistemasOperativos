#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include "../utils/utils.h"
#include <iostream>

int main(int argc, const char *argv[]) {
	print_names();

	sv_sem mutex {"Mutex"};
	sv_sem influencer {"Influencer"};
	sv_sem grunger {"Grunger"};
	sv_sem swagger {"Swagger"};
	
	sv_shm mesa {"Mesa"};
	mesa_status_t *mesa_status;
	mesa_status = reinterpret_cast<mesa_status_t*>(mesa.map(sizeof(mesa_status_t)));

	while(mesa_status->sillas_disponibles > 0) {
		std::cout << "Esperando por la llegada de un influencer" << std::endl;
		if (mesa_status->swaggers_esperando == 0 && mesa_status->grungers_esperando == 0) {
			influencer.wait();
		} else if (mesa_status->grungers_esperando > 0 && mesa_status->swaggers_sentados >= 3) {
			influencer.wait();
		} else if (mesa_status->swaggers_esperando > 0 && mesa_status->grungers_sentados >= 3) {
			influencer.wait();
		}
		mutex.wait();

		if (mesa_status->grungers_esperando > 0 && mesa_status->swaggers_sentados <= 2) {
			for (int i = 0; i < mesa_status->grungers_esperando; i++) {
				--(mesa_status->grungers_esperando);
				++(mesa_status->grungers_sentados);
				--(mesa_status->sillas_disponibles);
				grunger.post();
				if (mesa_status->sillas_disponibles == 0) {
					mesa_status->sillas_disponibles = 4;
					mesa_status->swaggers_sentados = 0;
					mesa_status->grungers_sentados = 0;
				}
			}

		} else if (mesa_status->swaggers_esperando > 0 && mesa_status->grungers_sentados <= 2) {	
			for (int i = 0; i < mesa_status->swaggers_esperando; i++) {
				--(mesa_status->swaggers_esperando);
				++(mesa_status->swaggers_sentados);
				--(mesa_status->sillas_disponibles);
				swagger.post();
				if (mesa_status->sillas_disponibles == 0) {
					mesa_status->sillas_disponibles = 4;
					mesa_status->swaggers_sentados = 0;
					mesa_status->grungers_sentados = 0;
				}
			}
		}
		mutex.post();
	}
	return 0;
}
