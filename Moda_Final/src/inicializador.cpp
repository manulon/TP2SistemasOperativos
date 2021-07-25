#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"
#include "../utils/utils.h"
#include <iostream>

int main(int argc, const char *argv[]) {
	print_names();

	std::cout << "Inicializando semaforos..." << std::endl;
	
	sv_sem mutex {"Mutex", 1};
	std::cout << "Mutex:" << std::endl;
	std::cout << "\t- " << mutex << std::endl;

	sv_sem influencer {"Influencer", 0};
	std::cout << "Influencer:" << std::endl;
	std::cout << "\t- " << influencer << std::endl;
	
	sv_sem grunger {"Grunger", 0};
	std::cout << "Grunger:" << std::endl;
	std::cout << "\t- " << grunger << std::endl;

	sv_sem swagger {"Swagger", 0};
	std::cout << "Swagger:" << std::endl;
	std::cout << "\t- " << swagger << std::endl;
	
	std::cout << "Inicializando memoria compartida..." << std::endl;
	sv_shm mesa {"Mesa"};
	mesa_status_t *mesa_status;
	mesa_status = reinterpret_cast<mesa_status_t*>(mesa.map(sizeof(mesa_status_t)));
	mesa_status->sillas_disponibles = MAX_SILLAS;
	mesa_status->grungers_sentados = 0;
	mesa_status->grungers_esperando = 0;
	mesa_status->swaggers_sentados = 0;
	mesa_status->swaggers_esperando = 0;

	std::cout << "Mesa: " << std::endl;
	std::cout << "\t- " << mesa << std::endl;
	return 0;
}
