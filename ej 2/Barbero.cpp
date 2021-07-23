#include <iostream>
#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"
#define CAP 3
/* Barbero */

using namespace std;
int main(int argc, char *argv[]) {
	int * en_espera;
	sv_shm sillas_ocup("Sillas");
	en_espera=static_cast<int *>	(sillas_ocup.map(sizeof (int)));
	sv_sem mutex("Mutex",1);
	sv_sem figaro("Barbero",0);
	sv_sem cliente ("Cliente",0);
	sv_sem salida ("Salida",0);
	string rta="s";
	
	while (rta!="f" ){
		cout<<"Figaro listo para afeitar..."<<endl;;
		cliente.wait();
		cout<<"Hay "<<( * en_espera)<<" clientes."<<endl;
		mutex.wait();
		*en_espera=(*en_espera)-1;
		figaro.post();
		mutex.post();
		cout<<" Afeitando ... (string para seguir, f termina)"<<endl;
		cin>>rta;
		salida.post();
	}
	sillas_ocup.del();
	figaro.del();
	cliente.del();
	salida.del();
}