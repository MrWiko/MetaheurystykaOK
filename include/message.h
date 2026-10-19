#pragma once

#include <queue>
#include "token-struct.h"

class message {
    private:
        std::queue<Token> tokenQueue;

    public:
        message();
        ~message();

        void getInputArgs(int argc, char** argv);
        void getInputStdin();

        void tokenize(std::string line, Type origin); 
        Token getToken();

        bool isTokenQueueEmpty();
        int tokenQueueSize();
};