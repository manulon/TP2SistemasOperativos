#include <unistd.h>
#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"
#include "../utils/utils.h"

using namespace std;
int main(int argc, char *argv[]) {
	printNames();

	sv_sem mutex("Mutex");
	sv_sem mesa("Mesa");
	sv_sem influencer("Influencer");
	sv_sem salida("Salida");
	sv_shm sillas_shm("Sillas");
	
	mutex.del();
	mesa.del();
	influencer.del();
	salida.del();
	sillas_shm.del();
}
	
