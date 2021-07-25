#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include "../utils/utils.h"
#include <iostream>

int main(int argc, const char *argv[]) {
	print_names();

	sv_sem mutex {"Mutex"};
	sv_sem coordinador {"Coordinador"};
	sv_sem influencer {"Influencer"};
	
	sv_shm mesa {"Mesa"};
	mesa_status_t *mesa_status;
	mesa_status = reinterpret_cast<mesa_status_t*>(mesa.map(sizeof(mesa_status_t)));

	while(mesa_status->sillas_disponibles > 0) {
		std::cout << "Esperando por la llegada de un influencer" << std::endl;
		influencer.wait();
		
		mutex.wait();
		if (mesa_status->grungers_esperando > 0) {
			--(mesa_status->grungers_esperando);
			++(mesa_status->grungers_sentados);
		} else if (mesa_status->swaggers_esperando > 0) {	
			--(mesa_status->swaggers_esperando);
			++(mesa_status->swaggers_sentados);
		}
		--(mesa_status->sillas_disponibles);
		coordinador.post();
		mutex.post();
	}
	
	return 0;
}

