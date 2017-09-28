#include<error.h>

void Error( std::string msg ){
    std::cerr << " Error " << msg << "---EXIT " << std::endl;
    exit(1);
}

void Warning( std::string msg ){
    std::cerr << " Warning "<< msg << "---EXIT " << std::endl;
}
