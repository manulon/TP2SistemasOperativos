#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#define MAX_SILLAS 4

struct mesa_status_t {
	int sillas_disponibles;
    int swaggers_esperando;
	int swaggers_sentados;
	int grungers_esperando;
	int grungers_sentados;
};

void print_names() {
    std::cout<<"Grupo 4"<<std::endl<<std::endl;
    std::cout<<"102425 LONGO ELIA CATALAN, MANUEL"<<std::endl;
    std::cout<<"102914 MORE, AGUSTIN EMANUEL"<<std::endl;
    std::cout<<"103442 LOVERA LOPEZ, DANIEL ALEJANDRO"<<std::endl;
    std::cout<<"104112 BURMAN, FEDERICO "<<std::endl<<std::endl;
}

#endif //_UTILS_H_

