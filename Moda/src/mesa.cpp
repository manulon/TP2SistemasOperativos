#include <iostream>
#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"
#include "../utils/utils.h"

using namespace std;

int main(int argc, char *argv[]) {
	printNames();

	sv_sem mutex("Mutex", 1);
	sv_sem mesa("Mesa", 0);
	sv_sem influencer ("Influencer", 0);
	sv_sem salida ("Salida", 0);

	mesa_status_t* mesa_status;
	sv_shm sillas_shm("Sillas");
	mesa_status = reinterpret_cast<mesa_status_t*>(sillas_shm.map(sizeof(mesa_status_t)));
	mesa_status->sillas_disponibles = INFLUENCERS_MESA;
	mesa_status->influencer_espera = 0;

	std::cout<<"Las sillas disponibles son "<<mesa_status->sillas_disponibles<<std::endl;
	string coordinador {""};

	while (coordinador != "f") {
		cout<<"Mesa lista para ser ocupada..."<<endl;
		cout <<"Hay "<< mesa_status->sillas_disponibles <<" sillas disponibles."<<endl;
		influencer.wait();
		cout << "Sentando a influencer... (String para seguir o f para terminar)" << endl;
		cin >> coordinador;
		mutex.wait();
		mesa_status->influencer_espera -= 1;
		mesa.post();
		mutex.post();
		salida.post();
		cout << "Se ocupo una silla ahora hay "<< INFLUENCERS_MESA - mesa_status->sillas_disponibles << " influencers sentados" <<endl;
	}
	
	mutex.del();
	mesa.del();
	influencer.del();
	salida.del();
	sillas_shm.del();
}
