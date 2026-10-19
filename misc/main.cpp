#include <iostream>
#include "graph.h"
#include "message.h"
#include "menu.h"

int main(int argc, char** argv) {

    #ifdef DEBUG
        std::cout<<"Initializing menu system"<<std::endl;
    #endif

    message msg;
    Menu menu(msg);
    
    msg.getInputArgs(argc, argv);

    while (menu.processIO());

    return 0; 
}