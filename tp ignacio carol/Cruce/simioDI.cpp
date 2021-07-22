#include <iostream>
#include "./Sem-sv/sv_sem.h"
#include "./Sem-sv/sv_shm.h"
#include "./utils/utils.cpp"
using namespace std;

int main(int argc, char * argv[]){
    printNames();
	if (argc<2) {
	    cerr<<"Usar "<<argv[0]<<" indicando el <id del simioDI> como parámetro."<<endl;
	    exit(2);
	}
	
	string nombreSimio="SimioDI_"+string(argv[1]);
	sv_sem mutex("Mutex");
	sv_sem DI("Simio_cruzando_derecha_a_izquierda");
	sv_sem ID("Simio_cruzando_izquierda_a_derecha");
	shared_status * status;
	sv_shm soga("Soga");
	status= reinterpret_cast<shared_status *> (soga.map(sizeof (shared_status)));
	
	cout<<nombreSimio<<" (pid: "<<getpid()<<") a punto de ingresar a la soga..."<<endl;
	cin.ignore();
	cout<<nombreSimio<<" (pid: "<<getpid()<<") prueba ingreso a la soga... \n";
	
	if (status->simios_cruzando_ID > 0){
	    /*Caso en el que hay simios cruzando de izquierda a derecha*/
	    cout<<nombreSimio<<" (pid: "<<getpid()<<") va a esperar."<<endl;
	    cout<<"Hay "<<status->simios_cruzando_ID<<" simio/s cruzando de izquierda a derecha."<<endl;
	    status->simios_esperando_DI++;
	    DI.wait();
	} else {
	    /*Caso en el que se puede cruzar*/
	    cout<<nombreSimio<<" (pid: "<<getpid()<<") va a cruzar."<<endl;
	    if (status->simios_cruzando_DI == 0) cout<<"Es el primer simio cruzando de derecha a izquierda."<<endl;
	    else cout<<"Hay "<<status->simios_cruzando_DI<<" simio/s yendo en la misma dirección."<<endl;
	    status->simios_cruzando_DI++;
	}
	
	mutex.wait();	
	
	/*El simio entra a la sección crítica*/
	cout<<nombreSimio<<" (pid: "<<getpid()<<") cruzando..."<<endl;
	cin.ignore();
	
	status->simios_cruzando_DI--;
	
	if (status->simios_esperando_DI > 0){
	    /*Caso en el que hay más simios cruzando de derecha a izquierda*/
	    status->simios_cruzando_DI++;
	    status->simios_esperando_DI--;
	    DI.post();
	} else if (status->simios_esperando_ID > 0 and status->simios_cruzando_DI == 0) {
	    /*Caso en el que terminaron de cruzar los simios*/
	    int simios_que_empiezan_a_cruzar=status->simios_esperando_ID;
	    status->simios_esperando_ID=0;
	    status->simios_cruzando_ID=status->simios_cruzando_ID+simios_que_empiezan_a_cruzar;
	    for(int i=0; i<simios_que_empiezan_a_cruzar; i++) {
	        ID.post();
	    }
	}
	
	if (status->simios_cruzando_DI == 0) cout<<nombreSimio<<" es el último simio cruzando de derecha a izquierda."<<endl;
	else cout<<"Queda/n "<<status->simios_cruzando_DI<<" simio/s cruzando de derecha a izquierda."<<endl;
	
	cout<<nombreSimio<<" "<<" terminó de cruzar."<<endl;
    mutex.post();   
}
