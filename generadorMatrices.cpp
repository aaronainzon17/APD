#include<iostream>
#include<fstream>

using namespace std;  

int main(int argc, char *argv[]){

    // Create and open a text file
    int size = atoi(argv[1]);
    int totalSize = size * size;
    ofstream f("name.ppm");
    // Write to the file
    f << "El tamanyo" << endl;
    for (int i = 0; i < totalSize; i ++) {
        f << " Valores aleatorios ";
        //Se pone -1 porque se hace el salto de linea al final
        if ((i + 1) % size == 0){ f << endl; }
    }
    f.close();
}
 
