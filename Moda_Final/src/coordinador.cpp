#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include "../utils/utils.h"
#include <iostream>

bool is_between(int val, int min, int max) {
	return min < val && val <= max;
}


int main(int argc, const char *argv[]) {
	print_names();

	sv_sem mutex {MUTEX_ID};
	sv_sem influencer {INFLUENCER_ID};
	sv_sem grunger {GRUNGER_ID};
	sv_sem swagger {SWAGGER_ID};
	
	sv_shm mesa {MESA_ID};
	mesa_status_t *mesa_status;
	mesa_status = reinterpret_cast<mesa_status_t*>(mesa.map(sizeof(mesa_status_t)));

	while(mesa_status->sillas_disponibles > 0) {
		std::cout << "Esperando por la llegada de un influencer" << std::endl;
		show_mesa(*mesa_status);

		if (mesa_status->swaggers_esperando == 0 && 
			mesa_status->grungers_esperando == 0) {
			influencer.wait();
		} else if (mesa_status->grungers_esperando > 0 && 
				   mesa_status->swaggers_sentados > MAX_SAME_SILLAS) {
			influencer.wait();
		} else if (mesa_status->swaggers_esperando > 0 && 
				   mesa_status->grungers_sentados > MAX_SAME_SILLAS) {
			influencer.wait();
		}
		
		mutex.wait();

		if (mesa_status->grungers_esperando > 0 && 
		    mesa_status->swaggers_sentados <= MAX_SAME_SILLAS) {
			for (int i = 0; i < mesa_status->grungers_esperando; i++) {
				
				--(mesa_status->grungers_esperando);
				++(mesa_status->grungers_sentados);
				--(mesa_status->sillas_disponibles);
				grunger.post();
				if (mesa_status->sillas_disponibles == 0) {
					mesa_status->sillas_disponibles = MAX_SILLAS;
					mesa_status->swaggers_sentados = 0;
					mesa_status->grungers_sentados = 0;
				}
			}

		} else if (mesa_status->swaggers_esperando > 0 && 
				   mesa_status->grungers_sentados <= MAX_SAME_SILLAS) {	
			for (int i = 0; i < mesa_status->swaggers_esperando; i++) {
				--(mesa_status->swaggers_esperando);
				++(mesa_status->swaggers_sentados);
				--(mesa_status->sillas_disponibles);
				swagger.post();
				if (mesa_status->sillas_disponibles == 0) {
					mesa_status->sillas_disponibles = MAX_SILLAS;
					mesa_status->swaggers_sentados = 0;
					mesa_status->grungers_sentados = 0;
				}
			}
		}
		mutex.post();
	}
	return 0;
}
