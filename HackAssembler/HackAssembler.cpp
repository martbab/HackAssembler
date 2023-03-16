// HackAssembler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "../LibHackAssembler/LibHackAssembler.h"

int main(int argc, char **argv)
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [ASM FILE] [OUTPUT FILE]" << std::endl;
        return 1;
    }
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    if (!input) {
        std::cerr << "Can not open file \"" << argv[1] << "\" for reading." << std::endl;
        return 2;
    }

    if (!output) {
        std::cerr << "Can not open file \"" << argv[2] << "\" for writing." << std::endl;
        return 2;
    }

    std::cout << "Assembling ASM file \""
        << argv[1] << "\" to machine code file \"" << argv[2] << "\"..." << std::endl;

    try {
        compileAsmToMachineCode(input, output);
    } catch (const std::exception& ex) {
        std::cerr << "An error occured during assembly: " << ex.what() << std::endl;
        return 3;
    }

    std::cout << "Completed." << std::endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
