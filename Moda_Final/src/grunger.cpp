#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include "../utils/utils.h"
#include <iostream>

int main(int argc, const char *argv[]) {
	print_names();

	sv_sem mutex {"Mutex"};
	sv_sem influencer {"Influencer"};
	sv_sem grunger {"Grunger"};
	
	sv_shm mesa {"Mesa"};
	mesa_status_t *mesa_status;
	mesa_status = reinterpret_cast<mesa_status_t*>(mesa.map(sizeof(mesa_status_t)));

	mutex.wait();
	if (mesa_status->swaggers_sentados <= 2) {
		std::cout << "Grunger esperando a sentarse..." << std::endl;
		++(mesa_status->grungers_esperando);
		influencer.post();
		mutex.post();	
		grunger.wait();
		std::cout << "Grunger sentado" << std::endl;
	} else {
		std::cout << "Mesa ocupada el grunger no se puede sentar, esperando lugar..." << std::endl;
		++(mesa_status->grungers_esperando);
		influencer.post();
		mutex.post();
		grunger.wait();
		std::cout << "Grunger sentado" << std::endl;
	}
	return 0;
}
