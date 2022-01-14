#include<bits/stdc++.h>
#include <iostream>
#include <chrono>

using namespace std;

default_random_engine generator;
uniform_real_distribution<double> distribution(0.0,1.0);

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
        cout << "Interseccion: " << idInterseccion << " con " << nCruce << " carreteras " << endl;
        for (Carretera *c : carreteras){
            c->printCarretera();
        }
    }   
};

class Ruta {
private:
    int nIntersecciones;
    int mCarreteras;
    int cVivienda;
    int almacenA;
    int almacenB;
    vector<Carretera*> carreteras;
    vector<Interseccion> intersecciones;
public:
    Ruta(){}

    Ruta(string path){
        ifstream f;
		f.open(path);
		if(f.is_open()){
			f >> nIntersecciones >> mCarreteras >> cVivienda >> almacenA >> almacenB;
			cout << endl << path << endl;
			//cout << "El tamanio es de: " << _size << endl;
            for (int i = 0; i < nIntersecciones; i++){
                intersecciones.push_back(Interseccion(i+1));
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

    void printRuta(){
        cout << "N: " << nIntersecciones << ", M: " << mCarreteras << ", C: " << cVivienda;
        cout << ", A: " << almacenA << ", B: " << almacenB << endl;
        for (Interseccion i : intersecciones){
            i.printInterseccion();
        }
    }

    int caminoA(){
        srand(time(NULL));
        bool caminoEncontrado = false, perdido = false;
        Interseccion estoy = intersecciones[almacenA - 1];
        cout << "Estoy en: " << estoy.getId() << endl;
        //estoy.printInterseccion();
        int tiempo = 0;
        int i = 0;
        while(!caminoEncontrado && !perdido && i < 1000000){
            float prob = rand()%10000;
            prob /= 10000;
            float acum = 0.0;
            vector<Carretera *> carrEstoy = estoy.getCarreteras();
            for (Carretera *c : carrEstoy){
                if (c->getU() == estoy.getId() && prob < c->getPuv()+acum){
                    estoy = intersecciones[c->getV()-1];
                    //cout << "Avanzo a " << c->getV() << ", ";
                    tiempo += c->getTuv();
                    acum += c->getPuv();
                    break;
                }else if (c->getV() == estoy.getId() && prob < c->getPvu()+acum){
                    estoy = intersecciones[c->getU()-1];
                    //cout << "Retrocedo a " << c->getU() << ", ";
                    tiempo += c->getTuv();
                    acum += c->getPvu();
                    break;
                }else if (c->getU() == estoy.getId()){
                    acum += c->getPuv();
                }else if (c->getV() == estoy.getId()){
                    acum += c->getPvu();
                }
            }
            if (casi_iguales(acum,0.0)) {
                    perdido = true;
                    tiempo =-1;
                    cout << "ME HE PERDIDO" << endl;
                }
            if (estoy.getId() == cVivienda) {
                caminoEncontrado = true;
                cout << "PONGO ENCONTRADO A TRUE" << endl;
            }
            i++;
        }
        return tiempo;
    }

    int caminoB(){
        srand(time(NULL));
        bool caminoEncontrado = false, perdido = false;
        Interseccion estoy = intersecciones[almacenB - 1];
        cout << "Estoy en: " << estoy.getId() << endl;
        //estoy.printInterseccion();
        int tiempo = 0;
        int i = 0;
        while(!caminoEncontrado && !perdido && i < 1000000){
            float prob = rand()%10000;
            prob /= 10000;
            float acum = 0.0;
            vector<Carretera *> carrEstoy = estoy.getCarreteras();
            for (Carretera *c : carrEstoy){
                if (c->getU() == estoy.getId() && prob < c->getPuv()+acum){
                    estoy = intersecciones[c->getV()-1];
                    //cout << "Avanzo a " << c->getV() << ", ";
                    tiempo += c->getTuv();
                    acum += c->getPuv();
                    break;
                }else if (c->getV() == estoy.getId() && prob < c->getPvu()+acum){
                    estoy = intersecciones[c->getU()-1];
                    //cout << "Retrocedo a " << c->getU() << ", ";
                    tiempo += c->getTuv();
                    acum += c->getPvu();
                    break;
                }else if (c->getU() == estoy.getId()){
                    acum += c->getPuv();
                }else if (c->getV() == estoy.getId()){
                    acum += c->getPvu();
                }
            }
            if (casi_iguales(acum,0.0)) {
                    perdido = true;
                    tiempo =-1;
                    cout << "ME HE PERDIDO" << endl;
                }
            if (estoy.getId() == cVivienda) {
                caminoEncontrado = true;
                cout << "HE ENCONTRADO EL CAMINO" << endl;
            }
            i++;
        }
        return tiempo;
    }

    bool casi_iguales(float izquierda, float derecha){
        return fabs(izquierda - derecha) <= FLT_EPSILON;
    }

    float rand0_1(){
        return distribution(generator);
    }

    
};

int main(int argc, char *argv[]){
	if (argc != 2){
		cout << "USAGE ERROR" << endl;
		cout << "Usage: ./practica2 <path to file>" << endl;
		exit(1);
	}
    string path = argv[1];
    Ruta a = Ruta(path);
    int tiempoA, tiempoB;
    //a.printAlmacen();
    tiempoA = a.caminoA();
    tiempoB = a.caminoB();
    if (tiempoA == -1) {
        cout << "Intentamos entregar tu paquete, pero no estabas" << endl;
    }else {
        cout << "El tiempo que le cuesta al repartidor del camino A es: " << tiempoA << " minutos" << endl;
    }
    if (tiempoB == -1) {
        cout << "Intentamos entregar tu paquete, pero no estabas" << endl;
    }else {
        cout << "El tiempo que le cuesta al repartidor del camino B es: " << tiempoB << " minutos" << endl;
    }
    
    return 0;
}