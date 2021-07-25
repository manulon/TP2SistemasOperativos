#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"
#include "../utils/utils.h"
#include <iostream>

int main(int argc, const char *argv[]) {
	print_names();

	sv_sem mutex {"Mutex"};
	sv_sem influencer {"Influencer"};
	sv_sem coordinador {"Coordinador"};
	sv_shm mesa {"Mesa"};

	std::cout << "Liberando semaforos..." << std::endl;	
	mesa.del();
	coordinador.del();
	influencer.del();
	mutex.del();
	std::cout << "Semaforos liberados" << std::endl;

	return 0;
}

