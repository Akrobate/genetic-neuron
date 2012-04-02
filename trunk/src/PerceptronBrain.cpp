#include "../include/PerceptronBrain.h"

PerceptronBrain::PerceptronBrain() {
    // a basculer dans un constructeur plus sexy avec parametres
    this->in.assign(6,0);
    this->out.assign(6,0);

    vector<int> _tmp;
    this->nbIn = this->in.size();
    this->nbOut = this->out.size();

    _tmp.assign(this->nbIn,0);
    this->poids.assign(this->nbOut, _tmp);
}

void PerceptronBrain::drawBrainConsole() {
    int inSize = this->in.size();
    int outSize = this->out.size();


    for (int i = 0; i < outSize; i++) {
        for (int j = 0; j < inSize; j++) {
            printf("%d ", this->poids[i][j]);
        }
        printf("\n");
    }

}

void PerceptronBrain::initRandomPoids() {
    for (int i=0; i < nbOut; i++) {
        for (int j=0; j < nbIn; j++) {
            this->poids[i][j] = ((rand()%256) - 128);
        }
    }
}

void PerceptronBrain::think() {

    int _total = 0;

    for (int i = 0; i < nbOut; i++) {
        for (int j = 0; j < nbIn; j++) {
            if (this->in[j]) {
                _total += this->poids[i][j];
            }
        }
        if (_total > 0) {
            this->out[i] = 1;
        } else {
            this->out[i] = 0;
        }
        _total = 0;
    }
}

PerceptronBrain::~PerceptronBrain() {
    //dtor
}

vector<int> PerceptronBrain::exportVectorPoids() {
    int inSize = this->in.size();
    int outSize = this->out.size();

    vector<int> result;
    for (int i = 0; i < outSize; i++) {
        for (int j = 0; j < inSize; j++) {
            result.push_back(this->poids[i][j]);
        }
    }
    return result;
}

void PerceptronBrain::importVectorPoids(vector<int> import) {
    int inSize = this->in.size();
    int outSize = this->out.size();

    int x = 0;
    for (int i = 0; i < outSize; i++) {
        for (int j = 0; j < inSize; j++) {
            this->poids[i][j] = import[x];
            x++;
        }
    }
}


string PerceptronBrain::exportStringVector(vector<int> vect, int normValue) {

    string result="";
    BinaryConverter bin;
    vector<bool> localBinary;


    for (int i = 0; i < vect.size(); i ++ ) {
        localBinary = bin.toBinaryConvert((unsigned int)(vect[i]+128));
        localBinary = bin.normalizeBinary(localBinary, normValue);

        for (int j = 0; j < localBinary.size(); j++) {
            if (localBinary[j]) {
                result.push_back('1');
            } else {
                result.push_back('0');
            }

        }
    }
    return result;

}


vector<int> PerceptronBrain::importStringVector(string import, int normValue) {

    vector<int> result;
    vector<bool> localBinary;
    int j = 0;
    BinaryConverter bin;
    int tmpV;

    for (int i = 0; i < import.size(); i++) {
        if (import[i] == '1') {
            localBinary.push_back(true);
        } else {
            localBinary.push_back(false);
        }

        if ((((i+1) % normValue) == 0) && (i != 0)) {
            tmpV = bin.toDecimalConvert(localBinary);
            tmpV -= 128;

            printf("\n val:%d", tmpV);
            bin.printBinary(localBinary);

            result.push_back(tmpV);
            localBinary.clear();
        }
    }
    return result;
}

string PerceptronBrain::exportStringBrain(int normValue) {

    vector<int> brain = this->exportVectorPoids();
    string result = this->exportStringVector(brain,normValue);
    return result;
}


void PerceptronBrain::importStringBrain(string import, int normValue) {

    vector<int> brain = this->importStringVector(import, normValue);
    this->importVectorPoids(brain);
}

