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

void BinaryConverter::printBinary(vector<bool> vect) {

    for (int i = 0; i < vect.size(); i++) {
        if (vect[i]) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

void BinaryConverter::printBinary(vector<int> vect) {

    for (int i = 0; i < vect.size(); i++) {

            printf("%d ", vect[i]);

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


vector<bool> BinaryConverter::normalizeBinary(vector<bool> vect, int sizeNeeded) {

    vector<bool> result;
    int vectSize = vect.size();
    int _difSize = 0;

    if (sizeNeeded < vectSize) {    // gestion du cas d'erreur
        exit(0);
    }

    _difSize = sizeNeeded - vectSize;

    int x = 0;
    for (int i = 0; i < sizeNeeded; i++) {
        if (i < _difSize) {
            result.push_back(false);
        } else {
            result.push_back(vect[x]);
            x++;
        }
    }

    return result;

}


vector<bool> BinaryConverter::toBinaryConvert(int unsigned decimalInt) {

        int unsigned valeur; // decimalInt
        vector<bool> result;
        vector<bool> reversedBin;

        int x=0;
        int i;
        int reste=0;
        int binaire=0;


        valeur = decimalInt;

        while (valeur > 0) {
            reste = valeur%2 ;//calcul le reste

            if (reste==1) {
                result.push_back(true);
            } else {
                result.push_back(false);
            }

            x++;
            valeur = valeur/2;
        }

        for (int i = (result.size() - 1); i >= 0; i--) {
            reversedBin.push_back(result[i]);
        }

        this->binaryTab = reversedBin;
        return reversedBin;


}

