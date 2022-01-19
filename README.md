Course work on the discipline: "Object-oriented programming"\
"Data compression using Huffman codes"\
Druzhinin N.V. group B3530904/00030\
10.01.2022 v.1

modules used:\
input_output.h - I/O library\
encode_decode.h - encoding- decoding library\
exception.h - exception handling library


                                           Description of functions:

                                                 input_output.h:

void readFile(const char* filename)      -- read file (for encoding and decoding)

void printMap(std::map<T, N> m)          -- print dictionary (for debugging)

void writeTable(const char* filename)    -- write frequencies table in output file (for encoding)

void writeTempCode(const char* infile, const char* outfile, size_t& filesize) -- write bitcode in temporary file (for encoding)

void writeEncod(const char* infile, const char* outfile, const size_t filesize) -- write encoded data in output file (for encoding) 

void readFrecTable(const char* filename, long int& offset) -- read data from input file and make frequencies table (for decoding)

char findCharInBitcode(const std::string& str, bool& flag) -- find a character depending on the bitcode (for decoding)

void writeDecod(const char* infile, const char* outfile) -- write decoded data in output file (for decoding)

void writeTempDecode(const char* infile, const char* outfile, long int offset) -- write bitcode in temporary file (for decoding)


                                                   encode_decode.h:

void makeBitCode(structNodePtr root, std::string str) -- create bitcode and save it in dictionary (for encoding and decoding)

void printQue(T t) -- print que with priorities (fro debugging)

void makeHuffTree() -- create Huffman tree
