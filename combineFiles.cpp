#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <random>
using namespace std;
//https://www.kaggle.com/datasets/oddrationale/mnist-in-csv?resource=download
const int INPUTS = 784;
const int OUTPUTS = 10;
const int HL_SIZE = 64;
const int HL_AMOUNT =1;
struct layerb {
    float bias[HL_SIZE];
    float weights[HL_SIZE][INPUTS];
};
struct layerc {
    float bias[HL_AMOUNT][HL_SIZE];
    float weights[HL_AMOUNT][HL_SIZE][HL_SIZE];
};
struct layerd {
    float bias[OUTPUTS];
    float weights[OUTPUTS][HL_SIZE];
};
struct nobes {
    layerb b;
    layerc c;
    layerd d;
};


nobes* fetchNobeSettings (string filename);

int main() {
    string filenames[10] = {"largerNetwork0.txt", "largerNetwork1.txt", "largerNetwork2.txt", "largerNetwork3.txt", "largerNetwork4.txt", "largerNetwork5.txt", "largerNetwork6.txt", "largerNetwork7.txt", "largerNetwork8.txt", "largerNetwork9.txt"};
    nobes** nobe = new nobes*[10];
    for(int i=0; i<10; i++) {
        nobe[i] = new nobes;
    }

    //recieving
    for(int i=0; i<10; i++) {
        nobe[i] = fetchNobeSettings(filenames[i]);
    }
    ofstream settings;
    settings.open("10NetworksCombinedLARGE.txt");
    for(int p=0; p<10; p++) {
        for(int j=0; j<HL_SIZE; j++) {
            for(int i=0; i<INPUTS; i++) {
                settings << to_string(nobe[p]->b.weights[j][i]) << " ";
            }
            settings << to_string(nobe[p]->b.bias[j]) << endl;
        }
        for(int j=0; j<HL_SIZE; j++) {
            for(int i=0; i<HL_SIZE; i++) {
                settings << to_string(nobe[p]->c.weights[0][j][i]) << " ";
            }
            settings << to_string(nobe[p]->c.bias[0][j]) << endl;
        }
        for(int j=0; j<OUTPUTS; j++) {
            for(int i=0; i<HL_SIZE; i++) {
                settings << to_string(nobe[p]->d.weights[j][i]) << " ";
            }
            settings << to_string(nobe[p]->d.bias[j]) << endl;
        }
    }
    settings.close();
}


nobes* fetchNobeSettings (string filename) {

    nobes* nobe;
    nobe = new nobes;

    ifstream settings;
    settings.open(filename);
    for(int j=0; j<HL_SIZE; j++) {
        for(int i=0; i<INPUTS; i++) {
            settings >> nobe->b.weights[j][i];
        }
        settings >> nobe->b.bias[j];
    }
    for(int p=0; p<HL_AMOUNT; p++) {
        for(int j=0; j<HL_SIZE; j++) {
            for(int i=0; i<HL_SIZE; i++) {
                settings >> nobe->c.weights[p][j][i];
            }
            settings >> nobe->c.bias[p][j];
        }
    }
    for(int j=0; j<OUTPUTS; j++) {
        for(int i=0; i<HL_SIZE; i++) {
            settings >> nobe->d.weights[j][i];
        }
        settings >> nobe->d.bias[j];
    }
    settings.close();
    return nobe;
}

