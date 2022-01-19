#ifndef INOUT_H
#define INOUT_H

#include <iostream>
#include <cstdio>
#include <map>
#include <bitset>
#include <string>
#include <algorithm>
#include "exception.h"


namespace inoutput
{
    union code
    {
        unsigned char chh;
        struct byte
        {
            unsigned b1:1;
            unsigned b2:1;
            unsigned b3:1;
            unsigned b4:1;
            unsigned b5:1;
            unsigned b6:1;
            unsigned b7:1;
            unsigned b8:1;
        } byte;
    };

    std::map<unsigned char, size_t> freq;
    std::map<unsigned char, std::string> bitcode;

    void readFile(const char* filename)
    {
        FILE* fp = fopen(filename, "rb");
        if (!fp)
        {
            throw Exception("Can not open file ", filename);
        }

        int ch;
        while ((ch = fgetc(fp)) != EOF)
        {
            freq[ch]++;
        }

        fclose(fp);
    }

    template<class T, class N>
    void printMap(std::map<T, N> m)
    {
        for (const auto& it : m)
        {
            std::cout << it.first << " " << std::bitset<8>(it.first) << " = "
            << std::dec << it.second << " - " << std::hex << it.second << "\n";
        }
    }

    void writeTable(const char* filename)
    {
        FILE* fp = fopen(filename, "wb");

        if (!fp)
        {
            throw Exception("Can not open file ", filename);
        }

        int numOfUnicElems = freq.size();
        fwrite(&numOfUnicElems, sizeof(int), 1, fp);
        for(const auto it : freq)
        {
            fwrite(&it.first, sizeof(char), 1, fp);
            fwrite(&it.second, sizeof(int), 1, fp);
        }

        fclose(fp);
    }

    void writeTempCode(const char* infile, const char* outfile, size_t& filesize)
    {
        FILE* outfp = fopen(outfile, "wb"); //ab

        if (!outfp)
        {
            throw Exception("Can not open file ", outfile);
        }

        FILE* infp = fopen(infile, "rb");

        if (!infp)
        {
            throw Exception("Can not open file ", infile);
        }

        int ch;
        size_t counter = 0;
        while ((ch = fgetc(infp)) != EOF)
        {
            std::string tmp = bitcode[ch];
            for (size_t i = 0; i < tmp.size(); ++i)
            {
                fputc(tmp[i], outfp);
                ++counter;
            }
        }
        filesize = counter;

        fclose(outfp);
        fclose(infp);
    }

    void writeEncod(const char* infile, const char* outfile, const size_t filesize)
    {
        FILE* outfp = fopen(outfile, "ab"); //ab

        if (!outfp)
        {
            throw Exception("Can not open file ", outfile);
        }

        FILE* infp = fopen(infile, "rb");

        if (!infp)
        {
            throw Exception("Can not open file ", infile);
        }

        char byte_[8];
        char ch;
        union code byteCode;
        for (int i = 0; i < filesize; ++i)
        {
            fread(&ch, sizeof(char), 1, infp);
            byte_[(i % 8)] = ch;
            if((i % 8) == 7)
            {
                byteCode.byte.b1 = byte_[0] - '0';
                byteCode.byte.b2 = byte_[1] - '0';
                byteCode.byte.b3 = byte_[2] - '0';
                byteCode.byte.b4 = byte_[3] - '0';
                byteCode.byte.b5 = byte_[4] - '0';
                byteCode.byte.b6 = byte_[5] - '0';
                byteCode.byte.b7 = byte_[6] - '0';
                byteCode.byte.b8 = byte_[7] - '0';
                fwrite(&byteCode.chh, sizeof(unsigned char), 1, outfp);
            }
        }

        fclose(infp);
        fclose(outfp);
    }

    void readFrecTable(const char* filename, long int& offset)
    {
        FILE* fp = fopen(filename, "rb");
        if (!fp)
        {
           throw Exception("Can not open file ", filename);
        }

        int numOfUnicElems = 0;
        fread(&numOfUnicElems, sizeof(int), 1, fp);

        inoutput::freq.clear();
        int counter = 0, frequency;
        char ch;
        while (counter < numOfUnicElems)
        {
            fread(&ch, sizeof(char), 1, fp);
            fread(&frequency, sizeof(int), 1, fp);
            inoutput::freq[ch] = frequency;
            ++counter;
        }
        offset = sizeof(char) * numOfUnicElems + sizeof(int) * numOfUnicElems + sizeof(int);
        fclose(fp);
    }

    char findCharInBitcode(const std::string& str, bool& flag)
    {
        for(auto& elem : bitcode)
        {
            if (elem.second == str)
            {
                //std::cout << "I found symbol " << elem.first << "\n";
                flag = true;
                return elem.first;
            }
        }
        return '0';
    }

    void writeDecod(const char* infile, const char* outfile)
    {
        FILE* outfp = fopen(outfile, "wb"); //ab

        if (!outfp)
        {
            throw Exception("Can not open file ", outfile);
        }

        FILE* infp = fopen(infile, "rb");

        if (!infp)
        {
            throw Exception("Can not open file ", infile);
        }

        char ch;
        std::string str;
        bool flag;
        while (!feof(infp))
        {
            flag = false;
            while(str.size() < 3)
            {
                fread(&ch, sizeof(char), 1, infp);
                str += ch;
            }

            ch = findCharInBitcode(str, flag);
            if (flag)
            {
                fputc(ch, outfp);
                str.clear();
            }
            else
            {
                while (!flag && !feof(infp))
                {
                    fread(&ch, sizeof(char), 1, infp);
                    str += ch;
                    ch = findCharInBitcode(str, flag);
                    if (flag)
                    {
                        fputc(ch, outfp);
                        str.clear();
                    }
                }
            }
        }
        fclose(infp);
        fclose(outfp);
    }

    void writeTempDecode(const char* infile, const char* outfile, long int offset)
    {
        FILE* outfp = fopen(outfile, "wb");

        if (!outfp)
        {
            throw Exception("Can not open file ", outfile);
        }

        FILE* infp = fopen(infile, "rb");

        if (!infp)
        {
            throw Exception("Can not open file ", infile);
        }

        unsigned char ch;
        if(fseek(infp, offset, 0) != 0)
        {
            throw Exception("Can not make an ofset");
        }

        union code byteCode;
        std::string strByte = "";
        while (!feof(infp))
        {
            fread(&ch, sizeof(char), 1, infp);
            byteCode.chh = ch;
            strByte += (byteCode.byte.b1 + '0');
            strByte += (byteCode.byte.b2 + '0');
            strByte += (byteCode.byte.b3 + '0');
            strByte += (byteCode.byte.b4 + '0');
            strByte += (byteCode.byte.b5 + '0');
            strByte += (byteCode.byte.b6 + '0');
            strByte += (byteCode.byte.b7 + '0');
            strByte += (byteCode.byte.b8 + '0');
            for_each (strByte.begin(), strByte.end(), [&outfp](const char& c) { fputc(c, outfp); });
            strByte.clear();
        }

        fclose(outfp);
        fclose(infp);
    }
}



#endif // INOUT_H
