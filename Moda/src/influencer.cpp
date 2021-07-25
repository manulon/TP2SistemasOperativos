#include <iostream>
#include <unistd.h>
#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"
#include "../utils/utils.h"

using namespace std;

int main(int argc, char *argv[]) {
	printNames();
	int yo {getpid()};

	sv_sem mutex("Mutex",1);
	sv_sem mesa("Mesa",0);
	sv_sem influencer ("Influencer",0);
	sv_sem salida ("Salida",0);
	
	mesa_status_t *mesa_status;
	sv_shm sillas_shm("Sillas");
	mesa_status = reinterpret_cast<mesa_status_t*> (sillas_shm.map(sizeof(mesa_status_t)));

	cout<<"Influencer "<<yo<<" quiere sentarse"<<endl;
	mutex.wait();

	if ((mesa_status->sillas_disponibles)>0) {
		mesa_status->influencer_espera += 1;
		cout << "Hay " << mesa_status->influencer_espera << " influencers en espera " << endl; 
		influencer.post();
		mutex.post();
		cout<<"Esperando a sentarme" << endl;
		mesa.wait();
		salida.wait();
		mesa_status->sillas_disponibles -= 1;
		cout << "Sillas sillas_disponibles" << mesa_status->sillas_disponibles << endl;
		cout<<"Influencer sentado..."<<endl;
    } else {
		cout<<"No hay lugar."<<endl;
		mutex.post();
    }
}	
