#ifndef BINARYCONVERTER_H
#define BINARYCONVERTER_H

#include <cstdlib>
#include <math.h>
#include <vector>
#include <stdio.h>

using namespace std;

class BinaryConverter
{
    public:
        vector<bool> binaryTab;
        char binaryChar;
        int decimalInt;

        BinaryConverter();
        virtual ~BinaryConverter();
        void printBinary();
        void printBinary(vector<bool> vect);
        void printBinary(vector<int> vect);
        void setDecimalInt(int dec);
        void setBinaryTab(vector<bool> bin);
        void toDecimalConvert();
        int toDecimalConvert(vector<bool> bin);
        vector<bool> toBinaryConvert(int unsigned decimalInt);
        vector<bool> normalizeBinary(vector<bool> vect, int sizeNeeded);
    protected:
    private:
};

#endif // BINARYCONVERTER_H
