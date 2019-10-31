#include <iostream>
#include <fstream>
using namespace std;

void readEntry(ifstream& in, int& entry);

int main() {
    ifstream inFile;
    ofstream outFile;

    inFile.open("../array");
    outFile.open("../output");

    if(!inFile.is_open()) {
        cout << " Could not open file \n";
        return 1;
    }
    int value;
    // read table dimensions and allocate 2D array
    int nRows, nCols;
    cout<<"Enter the number of rows and columns: ";
    while ( !inFile.eof() ){
        inFile >> nRows >> nCols;
        break;
    }

    cout << nRows << " " << nCols << endl;

    int** table = new int*[nRows];
    for(int i = 0; i < nRows; i++) {
        table[i] = new int[nCols];
    }

    // read table data
    // cout<<"Enter your numbers: ";
    for(int i = 0; i < nRows; i++) {
        for(int j = 0; j < nCols; j++) {
            try {
              readEntry(inFile, table[i][j]);
            }
            catch (int x) {
                    cout << "Entry " << i << "," << j << " not an integer, was set to " << x << ", now setting it to 0" << endl;
                    table[i][j] = 0;
                    inFile.clear();
                    string tmp;
                    inFile>> tmp;
            }
            inFile.clear();
        }
    }


    // write table data to the screen in transposed order
    cout << nCols << " " << nRows << endl;
    for(int i = 0; i < nCols; i++) {
        for(int j = 0; j < nRows; j++) {
            outFile << table[j][i] << " ";
        }
        outFile << endl;
    }


    // free memory
    for(int i = 0; i < nRows; i++) {
        delete [] table[i];
    }
    delete [] table;

    inFile.close();
    outFile.close();
}

void readEntry(ifstream& in, int& entry) {

    in >> entry;
    if(in.fail()) {
        throw entry;
    }
}