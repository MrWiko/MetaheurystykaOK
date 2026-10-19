#pragma once
#include <string>


enum Type {
    Stdin,
    Args,
    ERROR
}; 

struct Token { 
    std::string token;
    Type origin;
};