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

	return 0;
}
