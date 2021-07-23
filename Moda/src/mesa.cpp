#include <iostream>
#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"
/* Basado en el ejemplo del barbero */

using namespace std;

int main(int argc, char *argv[]) {
	int * sillas_ocupadas;

	sv_shm sillas_shm("Sillas");
	sillas_ocupadas=static_cast<int *>(sillas_shm.map(sizeof (int)));

	sv_sem mutex("Mutex",1);
	sv_sem mesa("Mesa",0);
	sv_sem influencer ("Cliente",0);
	sv_sem salida ("Salida",0);
	
	while ( *sillas_ocupadas = 4 ){
		cout<<"Mesa lista para ser ocupada..."<<endl;;
		influencer.wait();
		cout<<"Hay "<<(*sillas_ocupadas)<<" sillas ocupadas."<<endl;
		mutex.wait();
		mesa.post();
		*sillas_ocupadas=(*sillas_ocupadas)+1;
		mutex.post();
		cout<<" Se ocupo una silla ahora hay"<<(*sillas_ocupadas)<<" influencers"<<endl;
		salida.post();
	}
	

	sillas_shm.del();
	mesa.del();
	influencer.del();
	salida.del();
}