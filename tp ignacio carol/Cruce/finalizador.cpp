#include <iostream>
#include "./Sem-sv/sv_sem.h"
#include "./Sem-sv/sv_shm.h"
#include "./utils/utils.cpp"

using namespace std;

int main(int argc, char * argv[]){
    printNames();

    sv_sem mutex("Mutex");
    sv_sem DI("Simio_cruzando_derecha_a_izquierda", 0);
    sv_sem ID("Simio_cruzando_izquierda_a_derecha", 0);
    sv_shm soga("Soga");
    shared_status* ss;
    void* ptr = soga.map(sizeof(ss));
    ss = reinterpret_cast<shared_status*>(ptr);
    ss->simios_cruzando_DI=0;
    ss->simios_cruzando_ID=0;
    ss->simios_esperando_DI=0;
    ss->simios_esperando_ID=0;
    cout << endl;
    cout << "Semáforos" << endl;
    cout << "Reseteado semaforo simio DI con id: " << DI.getSem() << ", clave: " << DI.getClave() << "." << endl;
    cout << "Reseteado semaforo simio ID con id: " << ID.getSem() << ", clave: " << ID.getClave() << "." << endl;

    cout << endl;
    cout << "Simios activos (PID)" << endl;
    int status = system("pgrep -a \"simio[ID|DI]\"");
    if (WEXITSTATUS(status) != 0) {
        cout << "No se encontraron instancias activas de simios." << endl;
    }
    else {

        int status = system("pkill -f \"simio[ID|DI]\"");
        if (WEXITSTATUS(status) == 0) {
            cout << "Se finalizaron las instancias activas de simios." << endl;
        }
    }

    cout << endl;
    cout << "Finalizador terminado." << endl;

}
