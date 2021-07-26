#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include "../utils/utils.h"
#include <iostream>

int main(int argc, const char *argv[]) {
	print_names();

	sv_sem mutex {MUTEX_ID};
	sv_sem influencer {INFLUENCER_ID};
	sv_sem swagger {SWAGGER_ID};
	
	sv_shm mesa {MESA_ID};
	mesa_status_t *mesa_status;
	mesa_status = reinterpret_cast<mesa_status_t*>(mesa.map(sizeof(mesa_status_t)));

	mutex.wait();
	if (is_table_valid(mesa_status->grungers_sentados,
					   mesa_status->swaggers_sentados + 1))
		std::cout << "Swagger esperando a sentarse..." << std::endl;
	else
		std::cout << "Mesa ocupada el swagger no se puede sentar, " 
				  << "esperando lugar..." << std::endl;

	++(mesa_status->swaggers_esperando);
	influencer.post();
	mutex.post();
	swagger.wait();
	std::cout << "Swagger sentado" << std::endl;
	return 0;
}
