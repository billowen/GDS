#include <iostream>
#include <fstream>
#include "library.h"
#include "exceptions.h"


int main()
{
    try
    {
        GDS::Library lib1;
		std::ifstream in;
		std::ofstream out;
		in.open("rotate_90_test.ics.db", std::ios_base::binary);
		lib1.read(in);
		in.close();
		out.open("origin.txt");
		lib1.printASCII(out);
		out.close();
		out.open("tmp.db", std::ios_base::binary);
		lib1.write(out);
		out.close();

		GDS::Library lib2;
		in.open("tmp.db", std::ios_base::binary);
		lib2.read(in);
		in.close();
		out.open("after.txt");
		lib2.printASCII(out);
		out.close();
        
    }
    catch (GDS::FormatError &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

