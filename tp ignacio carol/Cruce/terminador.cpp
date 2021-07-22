#include <iostream>
#include "./Sem-sv/sv_sem.h"
#include "./Sem-sv/sv_shm.h"
#include "./utils/utils.cpp"
using namespace std;

int main(int argc, char * argv[]){
    printNames();
    sv_sem mutex("Mutex");
    sv_sem DI("Simio_cruzando_derecha_a_izquierda");
    sv_sem ID("Simio_cruzando_izquierda_a_derecha");
    sv_shm soga("Soga");
    mutex.del();
    DI.del();
    ID.del();
    soga.del();
}
