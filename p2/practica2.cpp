#include<bits/stdc++.h>
#include <iostream>
#include <chrono>

using namespace std;

/*
* Clase: Carretera
* Funcion: Representa cada una de las carreteras del mapa
* u,v: intersecciones que une 
* t_uv: tiempo de recorrer la carretera en minutos
* p_uv: probabilidad de ir de u a v
* p_vu: probabilidad de ir de v a u
**/
class Carretera{
private:
    int u;
    int v;
    int t_uv;
    float p_uv;
    float p_vu;

public:

    //Constructor de la clase
    Carretera(int ini, int fin, int tiempo, float prob_uv, float prob_vu):
        u(ini),v(fin),t_uv(tiempo),p_uv(prob_uv), p_vu(prob_vu){}

    //Constructor vacio
    Carretera(){}

    /*
	* getU: Devuelve la interseccion origen
	**/
    int getU(){
        return u;
    }

    /*
	* getV: Devuelve la interseccion destino
	**/
    int getV(){
        return v;
    }

    /*
	* getTuv: Devuelve el tiempo de recorrer la carretera
	**/
    int getTuv(){
        return t_uv;
    }

    /*
	* getPuv: Devuelve la probabilidad de ir de u a v
	**/
    float getPuv(){
        return p_uv;
    }

    /*
	* getPvu: Devuelve la probabilidad de ir de v a u
	**/
    float getPvu(){
        return p_vu;
    }

    /*(DEBUG)
	* printCarretera: Imprime por pantalla toda la informacion de una carretera
	**/
    void printCarretera(){
        cout << "Une " << u << " con " << v << " en tiempo " << t_uv << endl;
        cout << "Probabilidad de " << u << " a " << v << " " << p_uv << endl;
        cout << "Probabilidad de " << v << " a " << u << " " << p_vu << endl << endl;
    }
};

/*
* Clase: Interseccion
* Funcion: Representa cada una de las intersecciones del mapa
* idInterseccion: identificador de la interseccion
* nCruce: numero de carreteras que tiene el cruce
* carreteras: vector que apunta a todas las carreteras del cruce 
**/
class Interseccion {
private:
    int idInterseccion;
    int nCruce; 
    vector<Carretera*> carreteras;

public:

    //Constructor de la clase
    Interseccion(int i): idInterseccion(i){
        carreteras.clear(); 
    }   

    //Constructor de la clase
    Interseccion(int id, int n, vector<Carretera*> cruce):
        idInterseccion(id),nCruce(n),carreteras(cruce){}

    /*
	* setId: modifica el id de la interseccion
	**/
    void setId(int id){
        idInterseccion = id;
    }

    /*
	* setN: modifica el numero de carreteras de la interseccion
	**/
    void setN(int n){
        nCruce = n;
    }

    /*
	* setCarreteras: establece las carreteras de la interseccion
    **/
    void setCarreteras(vector<Carretera*> carr){
        carreteras = carr;
    }

    /*
	* addCarretera: añade una carretera a la interseccion
    **/
    void addCarretera(Carretera* carr){
        nCruce++;
        carreteras.push_back(carr);
    }

    /*
	* getId: devuelve el identificador de la interseccion
    **/
    int getId(){
        return idInterseccion;
    }

    /*
	* getN: devuelve el numero de carreteras en la interseccion
    **/
    int getN(){
        return nCruce;
    }

    /*
	* getCarreteras: devuelve las carreteras de la interseccion
    **/
    vector<Carretera*> getCarreteras(){
        return carreteras;
    } 

     /*(DEBUG)
	* printInterseccion: Imprime por pantalla toda la informacion de la interseccion
	**/
    void printInterseccion(){
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "Interseccion: " << idInterseccion << " con " << nCruce << " carreteras " << endl;
        for (Carretera *c : carreteras){
            c->printCarretera();
        }
    }   
};

/*
* Clase: Mapa
* Funcion: Representa el mapa
* nIntersecciones: numero de intersecciones del mapa 
* mCarreteras: numero de carreteras del mapa
* cVivienda: interseccion en la que se encuentra la vivienda
* almacenA: interseccion en la que se encuentra el almacen A
* almacenB: interseccion en la que se encuentra el almacen B
**/
class Mapa {
private:
    int nIntersecciones;
    int mCarreteras;
    int cVivienda;
    int almacenA;
    int almacenB;
    vector<Interseccion> intersecciones;

public:

    //Constructor por defecto
    Mapa(){}

    //Constructor de la clase 
    Mapa(string path){
        ifstream f;
		f.open(path);
        vector<Carretera*> carreteras;
		if(f.is_open()){
            //Lee los datos iniciales
			f >> nIntersecciones >> mCarreteras >> cVivienda >> almacenA >> almacenB;

            //Inicializa las intersecciones
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

                //Crear las N intersecciones
                intersecciones[ini-1].addCarretera(carreteras[indexRoad]);
                intersecciones[fin-1].addCarretera(carreteras[indexRoad]);
                indexRoad++;
			}
			f.close();
		}
    }

    /*
	* numIntersecciones: devuelve el numero de intersecciones del mapa
    **/
    int numIntersecciones(){
        return nIntersecciones;
    }

     /*(DEBUG)
	* printMapa: muesta los datos y las intersecciones del mapa
    **/
    void printMapa(){
        cout << "N: " << nIntersecciones << ", M: " << mCarreteras << ", C: " << cVivienda;
        cout << ", A: " << almacenA << ", B: " << almacenB << endl;
        for (Interseccion i : intersecciones){
            i.printInterseccion();
        }
    }
    
    /*
	* elegirAlmacen: devuelve el indice de la interseccion donde se encuentra
    * el almacen en funcion de por cual se haya preguntado
    **/
    int elegirAlmacen(string almacen){
        int IDalmacen;
        if (almacen == "almacenA"){
            IDalmacen = almacenA - 1;
        }else if (almacen == "almacenB"){
            IDalmacen = almacenB - 1;
        }else {
            cout << "No se ha especificado almacen existente" << endl;
            exit(1);
        }
        return IDalmacen;
    }

    /*
	* camino: calcula el camino desde el almacen especificado hasta la vivienda
    **/
    int camino(string almacen){
        int IDalmacen = elegirAlmacen(almacen);

        random_device num;
        uniform_real_distribution<double> generator(pow(10,-4),1);

        bool caminoEncontrado = false;
        int tiempo = 0, i = 0, maxIter = 0;

        Interseccion estoy = intersecciones[IDalmacen];
        //Se define un numero maximo de iteraciones
        if(nIntersecciones <= 50){
            maxIter = 2000;
        }else {
            maxIter = 10000;
        }

        while(!caminoEncontrado && i < maxIter){
            float prob = generator(num);
            float acum = 0.0;
            vector<Carretera *> carrEstoy = estoy.getCarreteras();
            // Se decide a que interseccion debe desplazarse el repartidor
            for (Carretera *c : carrEstoy){
                if (c->getU() == estoy.getId() && prob < c->getPuv()+acum){
                    estoy = intersecciones[c->getV()-1];
                    tiempo += c->getTuv();
                    break;
                }else if (c->getV() == estoy.getId() && prob < c->getPvu()+acum){
                    estoy = intersecciones[c->getU()-1];
                    tiempo += c->getTuv();
                    break;
                }else if (c->getU() == estoy.getId()){
                    acum += c->getPuv();
                }else if (c->getV() == estoy.getId()){
                    acum += c->getPvu();
                }
            }
            if (estoy.getId() == cVivienda) {
                caminoEncontrado = true;
            }
            i++;
        }
        //Se comprueba si se ha llegado al limite de iteraciones
        if (i == maxIter){
            return 0;
        }else {
            return tiempo;
        }   
    }
};

int main(int argc, char *argv[]){
	if (argc != 2){
		cout << "USAGE ERROR" << endl;
		cout << "Usage: ./practica2 <path to file>" << endl;
		exit(1);
	}
    string path = argv[1];
    Mapa paqueteria = Mapa(path);
    
    int acumA = 0, timeA = 0,nExitoA = 0, tiempoA;
    int acumB = 0, timeB = 0, nExitoB = 0, tiempoB;
    chrono::steady_clock::time_point beginA, endA;
    chrono::steady_clock::time_point beginB, endB;

    //Se realizan 500 iteraciones de cada prueba
    for (int i = 0; i < 500; i ++){
        //Calculo del camino de A
        beginA = chrono::steady_clock::now();
		tiempoA = paqueteria.camino("almacenA");
		endA = chrono::steady_clock::now();
        timeA += chrono::duration_cast<chrono::milliseconds>(endA - beginA).count();
        acumA += tiempoA;
        if (tiempoA != 0) {
            nExitoA++;
        }
        //Calculo del camino de B
        beginB = chrono::steady_clock::now();
		tiempoB = paqueteria.camino("almacenB");
		endB = chrono::steady_clock::now();
        timeB += chrono::duration_cast<chrono::milliseconds>(endB - beginB).count();
        acumB += tiempoB;
        if (tiempoB != 0) {
            nExitoB++;
        }
    }
    if (nExitoA == 0){
        nExitoA = 1;
    }
    if (nExitoB == 0){
        nExitoB = 1;
    }
    cout << path << "," << paqueteria.numIntersecciones() << "," << acumA/nExitoA << "," << acumB/nExitoB << ","<< timeA+timeB << endl;    
    return 0;
}