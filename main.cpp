// Course work on the discipline:
// "Object-oriented programming"
// Druzhinin N.V. group B3530904/00030
// 10.01.2022 v.1

// Implementation of the Huffman algorithm for encoding and decoding files of any type

#include "input_output.h"
#include "encode_decode.h"

using namespace inoutput;
using namespace encode_decode;

int main()
{
    try
    {

        char oper;
        std::string inFile, outFile, tempFile{"temp.txt"}, suff;
        std::cout << "To archivate press 1, to unzip press 2\n";
        std::cin >> oper;
        switch (oper)
        {
        case '1':
            {
                //getfilename
                std::cout << "Please enter file name ";
                std::cin >> inFile;
                outFile = inFile;
                suff = "_encode";
                outFile.insert(outFile.begin() + outFile.find_last_of('.'), std::begin(suff), std::end(suff));

                //open and read input file
                size_t filesize;
                readFile(inFile.c_str());

                //write frequencies table
                writeTable(outFile.c_str());
                printMap(freq);

                //make Huffman tree
                makeHuffTree();
                printMap(bitcode);

                //write bit codes in temporary file
                writeTempCode(inFile.c_str(), tempFile.c_str(), filesize); //pif.txt

                //get encode file
                writeEncod(tempFile.c_str(), outFile.c_str(), filesize);
                break;
            }
        case '2':
            {
                //getfilename
                std::cout << "Please enter file name ";
                std::cin >> inFile;
                outFile = inFile;
                suff = "_decode";
                outFile.insert(outFile.begin() + outFile.find_last_of('.'), std::begin(suff), std::end(suff));

                //decode
                //get frquencies table
                long int offset;
                readFrecTable(inFile.c_str(), offset);
                //printMap(freq);

                //create Huffman tree
                makeHuffTree();
                //printMap(bitcode);

                writeTempDecode(inFile.c_str(), tempFile.c_str(), offset);
                writeDecod(tempFile.c_str(), outFile.c_str());
                break;
            }

        }

        return 0;
    }
    catch (Exception* e)
    {
        std::cout << e->what() << "\n";
    }
    catch (...)
    {
        std::cout << "Unknown error \n";
    }
}
