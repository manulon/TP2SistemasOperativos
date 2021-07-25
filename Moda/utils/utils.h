#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#define INFLUENCERS_MESA 4

void printNames() {
    std::cout<<"Grupo 4"<<std::endl<<std::endl;
    std::cout<<"102425 LONGO ELIA CATALAN, MANUEL"<<std::endl;
    std::cout<<"102914 MORE, AGUSTIN EMANUEL"<<std::endl;
    std::cout<<"103442 LOVERA LOPEZ, DANIEL ALEJANDRO"<<std::endl;
    std::cout<<"104112 BURMAN, FEDERICO "<<std::endl<<std::endl;
}

struct mesa_status_t {
	int sillas_disponibles = INFLUENCERS_MESA;
    int influencer_espera = 0;
};

#endif

