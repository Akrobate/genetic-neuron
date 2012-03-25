#include "../include/BinaryConverter.h"

BinaryConverter::BinaryConverter()
{
    //ctor
}

BinaryConverter::~BinaryConverter()
{
    //dtor
}


void BinaryConverter::printBinary() {

    for (int i = 0; i < this->binaryTab.size(); i++) {
        if (this->binaryTab[i]) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}


void BinaryConverter::setDecimalInt(int dec){
    this->decimalInt = dec;
}


void BinaryConverter::setBinaryTab(vector<bool> bin) {
    this->binaryTab = bin;
}


void BinaryConverter::toDecimalConvert() {
    this->decimalInt = 0;
    for (int i = 0; i < this->binaryTab.size(); i++) {
        if (this->binaryTab[i]) {
            this->decimalInt = this->decimalInt * 2 + 1;
        } else {
            this->decimalInt = this->decimalInt * 2;
        }
    }
}

int BinaryConverter::toDecimalConvert(vector<bool> bin) {
    this->binaryTab = bin;
    this->decimalInt = 0;
    for (int i = 0; i < this->binaryTab.size(); i++) {
        if (this->binaryTab[i]) {
            this->decimalInt = this->decimalInt * 2 + 1;
        } else {
            this->decimalInt = this->decimalInt * 2;
        }
    }
    return decimalInt;
}


vector<bool> BinaryConverter::toBinaryConvert(int decimalInt) {

}

