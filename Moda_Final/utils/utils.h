#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#define MAX_SILLAS 4
#define MAX_SAME_SILLAS 2
#define EMPTY_SEAT '.'
#define GRUNGE_SEAT 'G'
#define SWAGGER_SEAT 'S'

#define MUTEX_ID "Mutex"
#define INFLUENCER_ID "Influencer"
#define SWAGGER_ID "Swagger"
#define GRUNGER_ID "Grunger"
#define MESA_ID "Mesa"


struct mesa_status_t {
	int sillas_disponibles;
    int swaggers_esperando;
	int swaggers_sentados;
	int grungers_esperando;
	int grungers_sentados;
};

void show_mesa(mesa_status_t& mesa) {
    std::cout << "\tMesa: " 
              << std::string(mesa.grungers_sentados, GRUNGE_SEAT) 
              << std::string(mesa.swaggers_sentados, SWAGGER_SEAT) 
              << std::string(mesa.sillas_disponibles, EMPTY_SEAT) 
              << std::endl;

    std::cout << "\tEsperando: " 
              << std::string(mesa.grungers_esperando, GRUNGE_SEAT) 
              << std::string(mesa.swaggers_esperando, SWAGGER_SEAT) 
              << std::endl;
}

bool is_table_valid(int g, int s) {
	return !(g > 0                && s > MAX_SAME_SILLAS  ||
		     g > MAX_SAME_SILLAS  && s > 0);
}

void print_names() {
    std::cout<<"Grupo 4"<<std::endl<<std::endl;
    std::cout<<"102425 LONGO ELIA CATALAN, MANUEL"<<std::endl;
    std::cout<<"102914 MORE, AGUSTIN EMANUEL"<<std::endl;
    std::cout<<"103442 LOVERA LOPEZ, DANIEL ALEJANDRO"<<std::endl;
    std::cout<<"104112 BURMAN, FEDERICO "<<std::endl<<std::endl;
}



#endif //_UTILS_H_
