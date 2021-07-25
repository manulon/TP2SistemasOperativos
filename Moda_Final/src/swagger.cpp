#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include "../utils/utils.h"
#include <iostream>

int main(int argc, const char *argv[]) {
	print_names();

	sv_sem mutex {"Mutex"};
	sv_sem influencer {"Influencer"};
	sv_sem swagger {"Swagger"};
	
	sv_shm mesa {"Mesa"};
	mesa_status_t *mesa_status;
	mesa_status = reinterpret_cast<mesa_status_t*>(mesa.map(sizeof(mesa_status_t)));

	mutex.wait();
	if (mesa_status->grungers_sentados <= 2) {
		std::cout << "Swagger esperando a sentarse..." << std::endl;
		++(mesa_status->swaggers_esperando);
		influencer.post();
		mutex.post();	
		swagger.wait();
		std::cout << "Swagger sentado" << std::endl;
	} else {
		std::cout << "Mesa ocupada el swagger no se puede sentar, esperando lugar..." << std::endl;
		++(mesa_status->swaggers_esperando);
		influencer.post();
		mutex.post();
		swagger.wait();
		std::cout << "Swagger sentado" << std::endl;
	}
	return 0;
}
