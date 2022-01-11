#include<bits/stdc++.h>
#include <iostream>
#include <chrono>

using namespace std;
class Carretera{
private:
    int u;
    int v;
    int t_uv;
    float p_uv;
    float p_vu;
public:
    Carretera(int ini, int fin, int tiempo, float prob_uv, float prob_vu):
        u(ini),v(fin),t_uv(tiempo),p_uv(prob_uv), p_vu(prob_vu){}

    Carretera(){}

    int getU(){
        return u;
    }

    int getV(){
        return v;
    }

    int getTuv(){
        return t_uv;
    }

    float getPuv(){
        return p_uv;
    }

    float getPvu(){
        return p_vu;
    }

    void printCarretera(){
        //cout << "-----------------------------------------------------------" << endl;
        cout << "Une " << u << " con " << v << " en tiempo " << t_uv << endl;
        cout << "Probabilidad de " << u << " a " << v << " " << p_uv << endl;
        cout << "Probabilidad de " << v << " a " << u << " " << p_vu << endl << endl;
    }
};

class Interseccion {
private:
    int idInterseccion;
    int nCruce; 
    vector<Carretera*> carreteras;
public:

    Interseccion(int i): idInterseccion(i){
        carreteras.clear(); 
    }   

    Interseccion(int id, int n, vector<Carretera*> cruce):
        idInterseccion(id),nCruce(n),carreteras(cruce){}

    void setId(int id){
        idInterseccion = id;
    }

    void setN(int n){
        nCruce = n;
    }

    void setCarreteras(vector<Carretera*> carr){
        carreteras = carr;
    }

    void addCarretera(Carretera* carr){
        nCruce++;
        carreteras.push_back(carr);
    }

    int getId(){
        return idInterseccion;
    }

    int getN(){
        return nCruce;
    }

    vector<Carretera*> getCarreteras(){
        return carreteras;
    } 

    void printInterseccion(){
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "Interseccion: " << idInterseccion + 1 << " con " << nCruce << " carreteras " << endl;
        for (Carretera *c : carreteras){
            c->printCarretera();
        }
    }   
};

class Almacen {
private:
    int nIntersecciones;
    int mCarreteras;
    int cVivienda;
    int almacenA;
    int almacenB;
    vector<Carretera*> carreteras;
    vector<Interseccion> intersecciones;
public:
    Almacen(){}

    Almacen(string path){
        ifstream f;
		f.open(path);
		if(f.is_open()){
			f >> nIntersecciones >> mCarreteras >> cVivienda >> almacenA >> almacenB;
			//cout << endl << path << endl;
			//cout << "El tamanio es de: " << _size << endl;
            for (int i = 0; i < nIntersecciones; i++){
                intersecciones.push_back(Interseccion(i));
            }
			int ini, fin, tiempo; 
            float prob_uv, prob_vu;
            int indexRoad = 0;
            carreteras.clear();
			while(!f.eof()){
                //Leer las M carreteras
                f >> ini >> fin >> tiempo >> prob_uv >> prob_vu;
                
                carreteras.push_back(new Carretera(ini,fin,tiempo,prob_uv,prob_vu));
                cout << "Anyado nueva carretera" << endl;
                carreteras[indexRoad]->printCarretera();
                //Crear las N intersecciones
                intersecciones[ini-1].addCarretera(carreteras[indexRoad]);
                intersecciones[fin-1].addCarretera(carreteras[indexRoad]);
                indexRoad++;
			}
			f.close();
		}
    }

    void printAlmacen(){
        cout << "N: " << nIntersecciones << ", M: " << mCarreteras << ", C: " << cVivienda;
        cout << ", A: " << almacenA << ", B: " << almacenB << endl;
        for (Interseccion i : intersecciones){
            i.printInterseccion();
        }
    }
};

int main(int argc, char *argv[]){
	if (argc != 2){
		cout << "USAGE ERROR" << endl;
		cout << "Usage: ./practica1 <mode> <path to file>" << endl;
		exit(1);
	}
    string path = argv[1];
    Almacen a = Almacen(path);
    a.printAlmacen();
}