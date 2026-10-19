#include "menu.h"

const std::string HELP_MESSAGE = "Available commands:\n"
                             "Exit - Exit the program\n"
                             "Help - Display this help message\n"
                                "Print - Print the graph in its current representation\n"
                                "Export - Export the graph to TickZPicture\n"
                                "Euler - Check if the graph has an Euler Cycle\n"
                                "Hamilton - Check if the graph has a Hamilton Cycle\n"; 

Menu::Menu(message& msg){
    #ifdef DEBUG
        std::cout<<"Menu constructor called"<<std::endl;
    #endif
    messageParser = &msg;
    graphHandle = new Graph(0, 0.0f); // Placeholder, will be properly initialized later
}

Menu::~Menu() {
    #ifdef DEBUG
        std::cout<<"Menu destructor called"<<std::endl;
    #endif
    delete graphHandle;
}

int64_t Menu::InputNumData(std::string message, int64_t left, int64_t right, int64_t default_num ) {
    int64_t num = default_num;
    while (num == default_num) {
        std::cout<<message+">";
        if (messageParser->isTokenQueueEmpty()) {
            messageParser->getInputStdin();
        }
        Token token = messageParser->getToken();
        try{
            size_t count;
            num = std::stoll(token.token, &count);
            if (count != token.token.length()) throw std::invalid_argument("Invalid argument");
           // num = static_cast<float>(conn) / 100.0f; // Assuming the input is a percentage
            if (num <= left || num > right) {
                throw std::out_of_range("Input out of range");
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout<<"Invalid argument."<<std::endl;
            num = default_num;
        }
        catch (const std::out_of_range& e) {
            std::cout<<"Number out of range."<<std::endl;
            num = default_num;
        }
    }
    return num;
}

double Menu::InputFloatData(std::string message, double left, double right, double default_num ) {
    double num = default_num;
    while (num == default_num) {
        std::cout<<"message>";
        if (messageParser->isTokenQueueEmpty()) {
            messageParser->getInputStdin();
        }
        Token token = messageParser->getToken();
        try{
            size_t count;
            num = std::stod(token.token, &count);
            if (count != token.token.length()) throw std::invalid_argument("Invalid argument");
           // num = static_cast<float>(conn) / 100.0f; // Assuming the input is a percentage
            if (num <= left || num > right) {
                throw std::out_of_range("Input out of range");
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout<<"Invalid argument."<<std::endl;
            num = default_num;
        }
        catch (const std::out_of_range& e) {
            std::cout<<"Number out of range."<<std::endl;
            num = default_num;
        }
    }
    return num;
}

int Menu::processIO() {
    #ifdef DEBUG
        std::cout<<"Menu processIO called"<<std::endl;
    #endif
    if (messageParser->isTokenQueueEmpty() && !initialized) {
        std::cout<<"No arguments provided, program will now exit."<<std::endl;
        return 0; // No tokens to process, wait for more input
    }
    if (!initialized && messageParser->tokenQueueSize() > 1) {
        std::cout<<"Too many arguments provided, program will now exit."<<std::endl;
        return 0; // No tokens to process, wait for more input
    }
    int nodes = 0;
    float connectivity = 0.0f;
    if (!initialized) {
        Token currentToken = messageParser->getToken();
        if (currentToken.origin != Args) {
            std::cout<<"Expected arguments from command line, but got input from stdin. Please provide the necessary arguments."<<std::endl;
            return 0; // Wait for more input
        }
        // Process command line arguments
        if (currentToken.token == "--hamilton"){
            Representation rep = none; // Default representation
            nodes = InputNumData("nodes", 0, 1000000, 0);
            int connectiv = InputNumData("connectivity",0,100,0);
            connectivity = connectiv/100.0f;
            delete graphHandle; // Delete the placeholder graph
            graphHandle = new Graph(nodes, connectivity,false,true); // Create the actual graph with the provided parameters
            rep = list;
            graphHandle->graphRepresentation = rep; // Set the graph representation
           // graphHandle->createRepStructure(); // Creates selected structure (if its not a list) 
            initialized = true;
            std::cout<<"Graph generated successfully with "<<nodes<<" nodes and "<<graphHandle->getConnectivityNumber()*100<<"% connectivity."<<std::endl;
        }
        else if (currentToken.token == "--non-hamilton"){
            Representation rep = list; // Default representation
            nodes = InputNumData("nodes", 0, 1000000, 0);
            delete graphHandle; // Delete the placeholder graph
            graphHandle = new Graph(nodes, 0.5f, false, false); // Create the actual graph with the provided parameters
            graphHandle->graphRepresentation = rep; // Set the graph representation
        //    graphHandle->createRepStructure(); // Creates selected structure (if its not a list) 
            initialized = true;
            std::cout<<"Graph generated successfully with "<<nodes<<" nodes and "<<graphHandle->getConnectivityNumber()*100<<"% connectivity."<<std::endl;
        }
    }
    if (initialized) {
            std::cout<<"action>";
            if (messageParser->isTokenQueueEmpty()) {
                messageParser->getInputStdin();
            }
            Token actionToken = messageParser->getToken();
            #ifdef DEBUG
            std::cout<<actionToken.token<<std::endl;
            #endif
            if (actionToken.token == "Exit") {
                std::cout<<"Exiting program."<<std::endl;
                return 0; // Exit the program
            }
            else if (actionToken.token == "Help"){
                std::cout<<HELP_MESSAGE;
            }
            else if (actionToken.token == "Export"){
                GraphAlgos::exportTickZ(*graphHandle);
            }
            else if (actionToken.token == "Euler"){
                GraphAlgos::ifGraphHasEulerCycle(*graphHandle);
            }
            else if (actionToken.token == "Hamilton"){
                GraphAlgos::ifGraphHasHamiltonCycle(*graphHandle);
            }
            else if (actionToken.token == "Print") {
                std::cout<<"Graph has: "<<graphHandle->sizeOfGraph<<" nodes."<<std::endl;
                GraphAlgos::printRepresentation(*graphHandle, graphHandle->graphRepresentation);
            }
            else {
                std::cout<<"Unknown command. Type 'Help' for a list of available commands."<<std::endl;
            }

    }
    return 1; // Indicate that processing should continue
}