#include <iostream>
#include <fstream>
#include "library.h"
#include "exceptions.h"


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

