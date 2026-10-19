#pragma once
#include "message.h"
#include <iostream>
#include "token-struct.h"
#include "represenation-struct.h"
#include "graph.h"
#include "graph-algos.h"
#include "graph-algos-2.h"

class Menu {
    private:
        message *messageParser;
        Graph *graphHandle;
        bool initialized = false;
        int64_t InputNumData(std::string message, int64_t left, int64_t right, int64_t default_num);
        double InputFloatData(std::string message, double left, double right, double default_num);

    public:
        Menu(message& msg);
        virtual ~Menu();
        
        int processIO();
      //  void displayMenu();

};