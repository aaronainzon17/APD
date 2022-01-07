#include<iostream>
#include<fstream>
#include <random>

using namespace std;  

int main(int argc, char *argv[]){
    if (argc !=3) {
        cout << "Wrong usage: ./generadorMatrices <size> <name>" << endl;
        exit(0);
    }
    default_random_engine generatorRR;
    uniform_real_distribution<double> russianRoulette(0,1);
    // Create and open a text file
    int size = atoi(argv[1]);
    string name = argv[2];
    ofstream f(name+".txt");
    // Write to the file
    f << to_string(size) << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double rr = russianRoulette(generatorRR);
            if (rr > 0.5 || i == j){
                f << "1\t" ;
            }else{
                f << "0\t" ;
            }
        }
        f << endl;
    }

    //Two Clique
    /*for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            //double rr = russianRoulette(generatorRR);
            if (i >= size/2 && j >= size/2 || i == j){
                f << "1\t" ;
            }else if(i < size/2 && j < size/2){
                f << "1\t" ;
            }else{
                f << "0\t" ;
            }
        }
        f << endl;
    }*/

    //One main node
    /*int fila = rand()%size;
    cout << fila << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            //double rr = russianRoulette(generatorRR);
            if (j == fila || i == j){
                f << "1\t" ;
            }else{
                f << "0\t" ;
            }
        }
        f << endl;
    }*/
    f.close();
}
 
