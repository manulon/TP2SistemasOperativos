#include <iostream>
#include <unistd.h>
#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"

#define IXM 4 /* influencer por mesa */

/* Basado en el ejemplo del barbero */

using namespace std;
int main(int argc, char *argv[]) {
	int* sillas_disponibles;
	
	int yo;
	yo=getpid();

	sv_shm sillas_shm("Sillas2");
	sillas_disponibles=static_cast<int *> (sillas_shm.map(sizeof (int)));

	sv_sem mutex("Mutex",1);
	sv_sem mesa("Mesa",0);
	sv_sem influencer ("Influencer",0);
	sv_sem salida ("Salida",0);
	
	cout<<"Influencer "<<yo<<" quiere sentarse"<<endl;
	mutex.wait();

	if ((*sillas_disponibles)>0){
		*sillas_disponibles=(*sillas_disponibles)-1;
		influencer.post();
		mutex.post();
		cout<<"Esperando a sentarme";
		mesa.wait();
		salida.wait();
		cout<<" morfando..."<<endl;
     }
	else {
		cout<<"No hay lugar."<<endl;
		mutex.post();
	}
}	
