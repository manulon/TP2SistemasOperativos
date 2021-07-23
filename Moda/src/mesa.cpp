#include <iostream>
#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"
/* Basado en el ejemplo del barbero */

using namespace std;

int main(int argc, char *argv[]) {
	int* sillas_disponibles;

	sv_shm sillas_shm("Sillas");
	sillas_disponibles=static_cast<int *>(sillas_shm.map(sizeof(int)));

	sv_sem mutex("Mutex",1);
	sv_sem mesa("Mesa",0);
	sv_sem influencer ("Influencer",0);
	sv_sem salida ("Salida",0);
	
	std::cout<<"Las sillas disponibles son "<<*sillas_disponibles<<std::endl;

	while ( *sillas_disponibles != 0 ){
		cout<<"Mesa lista para ser ocupada..."<<endl;;
		influencer.wait();
		cout<<"Hay "<<(*sillas_disponibles)<<" sillas disponibles."<<endl;
		mutex.wait();
		mesa.post();
		mutex.post();
		cout<<" Se ocupo una silla ahora hay "<<4-(*sillas_disponibles)<<" influencers"<<endl;
		cout<<"--------------------------------------"<<endl;
		salida.post();
	}
	
	sillas_shm.del();
	mesa.del();
	influencer.del();
	salida.del();
}