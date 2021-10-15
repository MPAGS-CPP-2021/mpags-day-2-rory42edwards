#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "TransformChar.hpp"
#include "processCommandLine.hpp"

int main(int argc, char* argv[])
{
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};
    const bool cmdLineStatus{processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile)};

    if (!cmdLineStatus){
        return 1;
    }

   // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Read in user input from stdin/file
    std::ifstream in_file{inputFile};
    // Check if input file was correctly opened, warn if not
    bool ok_to_read{in_file.good()};
    if (!ok_to_read){
        std::cerr << "[warning] input file ('" << inputFile << "') not opened successfully" << std::endl;
        return 0;
    }

    // loop over each character from user input
    char in_char{'x'};
    std::string outputText{""};
    while (in_file >> in_char) {
        outputText += transformChar(in_char);
    }

    // Open output file as specified in arguments
    std::ofstream out_file{outputFile};
    // Check if output file was correctly opened, warn if not
    bool ok_to_write{out_file.good()};
    if (!ok_to_write){
        std::cerr << "[warning] output file ('" << outputFile << "') not opened successfully" << std::endl;
        return 0;
    }

    // Write to output file
    out_file << outputText << std::endl;

    // Print out transliterated text
    std::cout << outputText << std::endl;

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}