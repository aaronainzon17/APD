#include<iostream>
#include<fstream>
#include <random>

using namespace std;  

int main(int argc, char *argv[]){
    if (argc !=4) {
        cout << "Wrong usage: ./generadorPruebas <name> <nIntersecciones> <densidad>" << endl;
        exit(0);
    }
    random_device num;
    uniform_real_distribution<double> generator(0,1);
    // Create and open a text file
    
    string name = argv[1];
    int nIntersecciones = atoi(argv[2]);
    string den = argv[3];
    int nCarreteras = 4*stof(den);
    ofstream f(name+".txt");

    int totCarreteras = nCarreteras* (nIntersecciones-2) + 2;
    int almacen1 = nIntersecciones*generator(num);
    while ( almacen1 == 0){
        almacen1 = nIntersecciones*generator(num);
    }
    int almacen2 = nIntersecciones*generator(num);
    while (almacen2 == almacen1 || almacen2 == 0){
        almacen2 = nIntersecciones*generator(num);
    }
    int casa = nIntersecciones*generator(num);
    cout << "el numero de carreteras es " << nCarreteras << endl;
    while (casa == almacen1 || casa == almacen2){
        casa = nIntersecciones*generator(num);
        cout << "La casa coincide con un almacen" << endl;
    }
    
    bool nCI[nIntersecciones][nIntersecciones] = {false};
    // Write to the file
    f << to_string(nIntersecciones) << " " << to_string(totCarreteras) << " " << casa << " " << almacen1 << " " << almacen2 << endl;
    int unidoA = rand()%(nIntersecciones-1) + 1;
    while (unidoA == almacen1){
        unidoA = rand()%(nIntersecciones-1) + 1;
    }
    f << to_string(almacen1) << " " << to_string(unidoA) << " " << to_string((int)(30*generator(num))) << " " << "1" << " "  << "0" << endl;
    unidoA = rand()%(nIntersecciones-1) + 1;
    while (unidoA == almacen2){
        unidoA = rand()%(nIntersecciones-1) + 1;
    }
    f << to_string(almacen2) << " " << to_string(unidoA) << " " << to_string((int)(30*generator(num))) << " " << "1" << " "  << "0" << endl;
    
    for (int i = 1; i <= nIntersecciones; i++) {
        if (i != almacen1 && i != almacen2){
            float totPuv = 0;
            for (int j = 0; j < nCarreteras-1; j++){
                int unidoA = rand()%(nIntersecciones-1) + 1;
                while (nCI[i - 1][unidoA - 1] == true || unidoA == almacen1 || unidoA == almacen2 || unidoA == i){
                    unidoA = rand()%(nIntersecciones-1) + 1;
                }
                    
                float puv = generator(num);
                while (puv > (1 - totPuv)){
                    puv = generator(num);
                }
                totPuv += puv;
                float pvu = generator(num);
                if (i == casa) {
                    pvu = 0;
                }
                f << to_string(i) << " " << to_string(unidoA) << " " << to_string((int)(30*generator(num))) << " " << to_string(puv) << " "  << to_string(pvu) << endl;
                nCI[i - 1][unidoA - 1] = true;
                nCI[unidoA - 1][i - 1] = true;
            }
            
            int unidoA = rand()%(nIntersecciones-1) + 1;
            while (nCI[i - 1][unidoA - 1] == true || unidoA == almacen1 || unidoA == almacen2 || unidoA == i){
                unidoA = rand()%(nIntersecciones-1) + 1;
            }
            float pvu = generator(num);
                if (i == casa) {
                    pvu = 0;
                }
            f << to_string(i) << " " << to_string(unidoA) << " " << to_string((int)(30*generator(num))) << " " << to_string(1- totPuv) << " " << to_string(pvu) << endl;
            nCI[i - 1][unidoA - 1] = true;   
            nCI[unidoA - 1][i - 1] = true;
        }
    }
    f.close();
}
 
