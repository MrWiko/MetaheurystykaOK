#include <queue>
#include <iostream>
#include <sstream>
#include <vector>
#include "message.h"
#include "token-struct.h"
#ifdef _WIN32
    #include <cstdio> // for fileno
    #include <io.h>   // for isatty
    extern "C" int _fileno(FILE*);
    #define fileno _fileno
    extern "C" int _isatty(int);
    #define isatty _isatty
#else
    #include <unistd.h> // for isatty and fileno
#endif

message::message(){
    #ifdef DEBUG
        std::cout << "message class object created\n";
    #endif
}
message::~message(){
    #ifdef DEBUG
        std::cout << "message class object deleted\n";
    #endif
}
// ======================
// Functions for getting input
// ======================
void message::getInputArgs(int argc, char** argv){
    std::string tokenLine = "";

    for(int i = 1; i < argc; i++) {
        tokenLine += argv[i];
        tokenLine += ' ';
    }
    
    tokenize(tokenLine, Args);
}

void message::getInputStdin(){
    std::string line;
    std::string fullText;

    while (std::getline(std::cin, line)) {
        fullText += line + '\n';

        // If input comes from a terminal, stop after one line
        if (isatty(fileno(stdin)))
            break;
    }

    tokenize(fullText, Stdin);
}
// ======================
// Token functions
// ======================
void message::tokenize(std::string line, Type origin){
    std::stringstream ss(line);
    std::string command;

    std::vector<std::string> commands;

    while (ss >> command) // Separate input by spaces
        commands.push_back(command);
    
    for(std::string token : commands)
        tokenQueue.push({token, origin});
}

Token message::getToken(){
    if(!tokenQueue.empty()){
        Token temp = tokenQueue.front(); 
        tokenQueue.pop();
        return temp;
    }
    else
        return {"ERROR_EMPTY_TOKEN_QUEUE", ERROR};
}
// ======================
// Utility functions 
// ======================
bool message::isTokenQueueEmpty(){ return tokenQueue.empty(); }
int message::tokenQueueSize(){ return tokenQueue.size(); }
