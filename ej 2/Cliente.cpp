#include <iostream>
#include <unistd.h>
#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"
#define CAP 3
/* Cliente */

using namespace std;
int main(int argc, char *argv[]) {
	int * en_espera,yo;
	yo=getpid();
	sv_shm sillas_ocup("Sillas");
	en_espera=static_cast<int *> (sillas_ocup.map(sizeof (int)));
	sv_sem mutex("Mutex",1);
	sv_sem figaro("Barbero",0);
	sv_sem cliente ("Cliente",0);
	sv_sem salida ("Salida",0);
	string rta;
	
	cout<<"Cliente "<<yo<<" quiere afeitarse"<<endl;
	mutex.wait();
	if ((*en_espera)<CAP){
		*en_espera=(*en_espera)+1;
		cliente.post();
		mutex.post();
		cout<<"Cliente "<<yo<<" esperando barbero. Posicion "<<(*en_espera)<<endl;
		figaro.wait();
		cout<<" Afeitandose ... "<<endl;
		salida.wait();
		cout<<"Adios"<<endl;
     }
	else {
		cout<<"No hay lugar."<<endl;
		mutex.post();
	}
}	
