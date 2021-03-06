#include<bits/stdc++.h>
#include <iostream>
#include <chrono>
 
using namespace std;
/*
* Clase: NodoLuz
* Funcion: Representa cada uno de los nodos de luz del sistema de alumbrado de la red WiSun
* nodo: se almacena el identificador del nodo
* grado: se almacena el grado del vertice
* cubierto: true -> nodo cubierto; false -> nodo no cubierto
* vecinos: vector de enteros donde se almacenan los identificadores de los vecinos
**/
class NodoLuz {
private:
	int nodo;
	int grado;
	bool cubierto;
	vector<int> vecinos;
	//Greedy vote	
	int vote;
	int weight;
public:
	/*Constructor vacio*/
	NodoLuz();

	/*Constructor de un nodoLuz*/
	NodoLuz(int n, int deg, vector<int> v, bool cov): nodo(n),grado(deg),vecinos(v), cubierto(cov){
		vote = -1;
		weight = -1;
	}

	/*
	* changeGrado: actualiza el grado del nodo
	**/
	void changeGrado(int newGrado){
		grado = newGrado;
	}

	/*
	* changeVecinos: actualiza los vecinos del nodo
	**/
	void changeVecinos(vector<int> newVec){
		vecinos = newVec;
	}

	/*
	* notCovered: devuelve verdad si el nodo no esta cubierto
	**/
	bool notCovered(){
		return !cubierto;
	}
	/*
	* getGrado: devuelve el grado del nodo
	**/
	int getGrado(){
		return grado;
	}

	/*
	* setCovered: actualiza el valor de cubierto del nodo
	**/
	void setCovered(bool cov){
		cubierto = cov;
	}

	/*
	* getVecinos: devuelve los vecinos del nodo
	**/
	vector<int> getVecinos(){
		return vecinos;
	}

	/*
	* yo: devuelve el identificador del nodo
	**/
	int yo(){
		return nodo;
	}

	/*
	* setVote: actualiza el valor de vote
	**/
	void setVote(int v){
		vote = v;
	}

	/*
	* getVote: devuelve el valor de vote
	**/
	int getVote(){
		return vote;
	}

	/*
	* setWeight: actualiza el valor de weight
	**/
	void setWeight(int w) {
		weight = w;
	}

	/*
	* getWeight: devuelve el valor de weight
	**/
	int getWeight(){
		return weight;
	}

	/* (DEBUG)
	* printNodoLuz: muestra todos los campos del nodo
	**/
	void printNodoLuz(){
		cout << nodo << " - " << grado << " - " << vote << " - " << weight << " - ";
		for (int a : vecinos){
			cout << a << " ";
		}
		cout << endl;
	}

	/* (DEBUG)
	* info: muesta el identificador del nodo y si esta cubierto o no
	**/
	void info(){
		string cub = "NO";
		if (cubierto) {
			cub = "SI";
		}
		cout << nodo << "-" << cub << " "; 
	}
};

/*
* Clase: WiSun
* Funcion: Representa la red de nodos de luz
* _size: numero de nodos de la red
* lights: vector de enteros que representan el grafo de conexiones entre
* 		  los nodos del sistema 
**/
class WiSun {
private:
	int _size;
	vector<NodoLuz> lights;
public:
	/*
	* Constructor encargado de leer el grafo de conexiones del fichero e
	* instanciar la clase WiSun
	**/
	WiSun(string path){
		ifstream f;
		f.open(path);
		if(f.is_open()){
			f >> _size;

			//cout << endl << path << endl;
			//cout << "El tamanio es de: " << _size << endl;
			
			int light = 0;
			vector<int> vecinos;
			int idNodo = 0;
			while(!f.eof()){
				vecinos.clear();
				for (int i = 0; i < _size; i++){
					f >> light;
					if (light == 1 && i != idNodo){
						vecinos.push_back(i);
					}
				}
				lights.push_back(NodoLuz(idNodo,vecinos.size(),vecinos,false));
				idNodo++;
			}
			f.close();
		}
	}

	/* (DEBUG)
	* printWiSun: muestra el grafo de conexiones
	**/
	void printWiSun(){
		for (int i = 0; i < _size; i ++) {
			lights[i].printNodoLuz();
    	}
	}

	/* (DEBUG)
	* checkAllCovered: muestra un mensaje por pantalla con los nodos que no 
	* han sido cubiertos. Se ha utilizado para el debug de los algoritmos.
	**/
	void checkAllCovered() {
		for (int i = 0; i< _size; i++){
			if (lights[i].notCovered()){
				cout << "El nodo " << i << " no se ha cubierto" << endl;
			}
		}
	}

	/*
	* conjuntoDominante: devuelve sol, siendo el conjunto dominante del 
	* 	grafo de conexiones cargado.
	**/
	vector<int> conjuntoDominante(){
		vector<int> D;
		int v = 0;
		do{
			v = elegirNodo();
			if (v != -1){
				D.push_back(v);
				ajustarGrado(v);
			}
		}while(v != -1);
		//checkAllCovered();
		return D;
	}

	/*
	* elegirNodo: devuelve el identificador del nodo no cubierto de mayor grado
	**/
	int elegirNodo() {
		int max = 0;
		int nodo = -1;
		for(int i = 0; i < _size; i++){
			if (lights[i].getGrado() + 1 > max && lights[i].notCovered()){
				max = lights[i].getGrado() + 1;
				nodo = i;
			}	
		}
		if (max == 0){
			return -1;
		}else {
			return nodo;
		}
	}

	/*
	* ajustarGrado: decrementa el grado de los vecinos de cada nodo cubierto
	**/
	void ajustarGrado(int i){
		vector<int> vecinos = lights[i].getVecinos();
		for (int j : vecinos) {
			if (lights[j].notCovered()){
				vector<int> vecinosJ = lights[j].getVecinos();
				for (int k : vecinosJ) {
					lights[k].changeGrado((lights[k].getGrado() -1));
				}
				lights[j].setCovered(true);
			}
		}
		lights[i].setCovered(true);
	}

	/*
	* chooseVertex: devuelve el nodo de mayor peso
	**/
	int chooseVertex(){
		int max = 0;
		int nodo = -1;
		for(int i = 0; i < _size; i++){
			if (lights[i].getWeight() > max){
				max = lights[i].getWeight();
				nodo = i;
			}
		}
		if (max == 0){
			return -1;
		}else {
			return nodo;
		}
	}

	/*
	* AdjustWeights: marca el nodo i como cubierto y todos sus vecinos.
	* Ademas, se encarga de ajustar los pesos de todos los nodos vecinos a los 
	* marcados como cubiertos restando el vote del nodo cubierto a su peso. 
	**/
	void AdjustWeights(int i) {
		lights[i].setWeight(0);
		int voteI = lights[i].getVote();
		vector<int> vecinos = lights[i].getVecinos();
		for (int j : vecinos) {
			if (lights[j].getWeight() > 0) {
				if (lights[i].notCovered()){
					lights[j].setWeight((lights[j].getWeight() - lights[i].getVote()));
				}
				if(lights[j].notCovered()){
					lights[j].setCovered(true);
					lights[j].setWeight((lights[j].getWeight() - lights[j].getVote()));
					vector<int> vecinosJ = lights[j].getVecinos();
					int voteJ = lights[j].getVote();
					for (int k : vecinosJ) {
						if (lights[k].getWeight() > 0) {
							lights[k].setWeight((lights[k].getWeight() - lights[j].getVote()));
						}
					}
				}
			}
		}
		lights[i].setCovered(true);
	}
	
	/*
	* GreedyVote: resuelve el conjunto dominante utilizando una heuristica voraz
	**/
	vector<int> GreedyVote() {
		vector<int> D;
		for (int i = 0; i < _size; i++){
			lights[i].setVote(1 + lights[i].getGrado());
			lights[i].setWeight(lights[i].getVote());
		}
		for (int i = 0; i < _size; i++){
			vector<int> vecinos = lights[i].getVecinos();
			for (int j : vecinos){
				lights[i].setWeight(lights[i].getWeight() + lights[j].getVote());
			}
		}
		int v = 0;
		do{
			v = chooseVertex();
			if (v != -1){
				D.push_back(v);
				AdjustWeights(v);
			}
		}while(v != -1);
		//checkAllCovered();
		return D;
	}

};

int main(int argc, char *argv[]){
	if (argc != 3){
		cout << "USAGE ERROR" << endl;
		cout << "Usage: ./practica1 <mode> <path to file>" << endl;
		exit(1);
	}
	string mode = argv[1];
	string path = argv[2];
	WiSun luces = WiSun(path);
	vector<int> sol;
	chrono::steady_clock::time_point begin;
	chrono::steady_clock::time_point end;
	if (mode == "R"){
		begin = chrono::steady_clock::now();
		sol = luces.conjuntoDominante();
		end = chrono::steady_clock::now();
	}else if (mode == "H"){
		begin = chrono::steady_clock::now();
		sol = luces.GreedyVote();
		end = chrono::steady_clock::now();
	}
	int elapsed = chrono::duration_cast<chrono::microseconds>(end - begin).count();

	//cout << mode << "," << path << "," << sol.size() << "," << elapsed << "us"<< endl;
	cout << "La solucion es de tama??o: " << sol.size() << endl;
	for (int s : sol){
		cout << s << " ";
	}
	cout << endl;
	
	cout << "Tiempo de ejecucion: " <<  elapsed << " us" << endl;

	return 0;
}