#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"
#include "../utils/utils.h"
#include <iostream>

int main(int argc, const char *argv[]) {
	print_names();

	sv_sem mutex {MUTEX_ID};
	sv_sem influencer {INFLUENCER_ID};
	sv_sem grunger {GRUNGER_ID};
	sv_sem swagger {SWAGGER_ID};
	sv_shm mesa {MESA_ID};

	std::cout << "Liberando semaforos..." << std::endl;	
	mesa.del();
	swagger.del();
	grunger.del();
	influencer.del();
	mutex.del();
	std::cout << "Semaforos liberados" << std::endl;
	return 0;
}
