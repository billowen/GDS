#include <iostream>
#include <fstream>
#include "src/library.h"
#include "src/exceptions.h"


int main()
{
    try
    {
        GDS::Library lib;
        
    }
    catch (GDS::FormatError &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

