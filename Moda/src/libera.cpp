#include <unistd.h>
#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"

/* Basado en ejemplo de la barberia */

using namespace std;
int main(int argc, char *argv[]) {
	sv_shm sillas_shm("Sillas");
	sillas_shm.del();

	sv_sem mutex("Mutex");
	mutex.del();

	sv_sem mesa("Barbero");
	mesa.del();

	sv_sem influencer("Cliente");
	influencer.del();

	sv_sem salida("Salida");
	salida.del();
}
	