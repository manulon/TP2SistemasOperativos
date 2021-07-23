#include <iostream>
#include <unistd.h>
#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"

#define IXM 3 /* influencer por mesa */

/* Basado en el ejemplo del barbero */

using namespace std;
int main(int argc, char *argv[]) {
	int * sillas_ocupadas;
	
	int yo;
	yo=getpid();

	sv_shm sillas_shm("Sillas");
	sillas_ocupadas=static_cast<int *> (sillas_shm.map(sizeof (int)));

	sv_sem mutex("Mutex",1);
	sv_sem mesa("Barbero",0);
	sv_sem influencer ("Cliente",0);
	sv_sem salida ("Salida",0);
	
	cout<<"Influencer "<<yo<<" quiere sentarse"<<endl;
	mutex.wait();

	if ((*sillas_ocupadas)<IXM){
		*sillas_ocupadas=(*sillas_ocupadas)+1;
		influencer.post();
		mutex.post();
		cout<<"Cliente "<<yo<<" esperando a sentarme. Posicion "<<(*sillas_ocupadas)<<endl;
		mesa.wait();
		cout<<" Sentandome ... "<<endl;
		salida.wait();
		cout<<"Sentado y morfando..."<<endl;
     }
	else {
		cout<<"No hay lugar."<<endl;
		mutex.post();
	}
}	
