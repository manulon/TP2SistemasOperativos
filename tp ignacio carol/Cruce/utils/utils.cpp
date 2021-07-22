void printNames() {
    cout<<"Grupo 2"<<endl<<endl;
    cout<<"99599    MININO, ALAN NAHUEL         nminino@fi.uba.ar"<<endl;
    cout<<"99846    TORRESETTI, LISANDRO        ltorresetti@fi.uba.ar"<<endl;
    cout<<"100073   CAROL LUGONES, LUIS IGNACIO icarol@fi.uba.ar"<<endl<<endl;
}

typedef struct {
    int simios_cruzando_DI=0;
    int simios_cruzando_ID=0;
    int simios_esperando_DI=0;
    int simios_esperando_ID=0;
} shared_status;