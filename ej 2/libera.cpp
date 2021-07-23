#include <unistd.h>
#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"
/* libera */

using namespace std;
int main(int argc, char *argv[]) {
	sv_shm sillas_ocup("Sillas");
	sillas_ocup.del();
	sv_sem mutex("Mutex");
	mutex.del();
	sv_sem figaro("Barbero");
	figaro.del();
	sv_sem cliente ("Cliente");
	cliente.del();
	sv_sem salida ("Salida");
	salida.del();
}
	
