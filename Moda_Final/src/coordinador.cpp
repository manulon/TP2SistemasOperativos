#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include "../utils/utils.h"
#include <iostream>

bool should_wait_for_influencer(mesa_status_t& mesa_status) {
	bool is_there_someone_waiting = mesa_status.swaggers_esperando > 0 ||
								    mesa_status.grungers_esperando > 0;

	bool is_grunger_trying_join = mesa_status.grungers_esperando > 0;
	bool can_grunger_join = is_table_valid(mesa_status.grungers_sentados + 1, 
										   mesa_status.swaggers_sentados);

	bool is_swagger_trying_join = mesa_status.swaggers_esperando > 0;

	bool can_swagger_join = is_table_valid(mesa_status.grungers_sentados, 
										   mesa_status.swaggers_sentados + 1);

	return !is_there_someone_waiting ||
     		is_grunger_trying_join && !can_grunger_join ||
	     	is_swagger_trying_join && !can_swagger_join;
}

void restart_mesa(mesa_status_t& mesa_status) {
	mesa_status.sillas_disponibles = MAX_SILLAS;
	mesa_status.swaggers_sentados = 0;
	mesa_status.grungers_sentados = 0;
}

void update_counters(mesa_status_t& mesa_status, int& waiting, int& seated, 
					 sv_sem& semaphore) {
	for (int i = 0; i < waiting; i++) {
		--(waiting);
		++(seated);

		--(mesa_status.sillas_disponibles);
		semaphore.post();
		if (mesa_status.sillas_disponibles == 0)
			restart_mesa(mesa_status);
	}
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

		if (should_wait_for_influencer(*mesa_status)) 
			influencer.wait();

		mutex.wait();

		if (mesa_status->grungers_esperando > 0 && 
		    is_table_valid(mesa_status->grungers_sentados + 1, 
						   mesa_status->swaggers_sentados)) {

			update_counters(*mesa_status, mesa_status->grungers_esperando, 
							mesa_status->grungers_sentados, grunger);

		} else if (mesa_status->swaggers_esperando > 0 && 
				  is_table_valid(mesa_status->grungers_sentados, 
				                 mesa_status->swaggers_sentados + 1)) {

			update_counters(*mesa_status, mesa_status->swaggers_esperando, 
							mesa_status->swaggers_sentados, swagger);
		}
		mutex.post();
	}
	return 0;
}
