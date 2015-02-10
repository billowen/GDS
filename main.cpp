#include <fstream>
#include <iostream>
#include <string>
#include "library.h"
#include "exceptions.h"
#include "log.h"

int main(int argc, char** argv)
{
    std::string name;    
    if (argc < 2)
    {
        std::cout << "Please input a gds file.\n";
        return 1;
    }
    else
    {
        name = argv[1];
    }

    try
    {
        GDS::Library* lib = GDS::Library::getInstance();
        std::ifstream in(name, std::ios::binary);
        GDS::LogIO* log = GDS::LogIO::getInstance();
        log->open("log.txt");
        lib->read(in);
    }
    catch (GDS::FormatError e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
