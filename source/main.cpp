#include <iostream>
#include "message.h"
#include "menu.h"

int main(int argc, char** argv) {

    #ifdef DEBUG
        std::cout<<"Initializing menu system"<<std::endl;
    #endif

    message msg;
    Menu menu(msg);

    while (menu.processIO());

    return 0; 
}