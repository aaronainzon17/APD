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

			cout << endl << path << endl;
			cout << "El tamanio es de: " << _size << endl;
			
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

	/*
	* printWiSun: muestra el grafo de conexiones
	**/
	void printWiSun(){
		for (int i = 0; i < _size; i ++) {
			lights[i].printNodoLuz();
    	}
	}

	//SOLUCION : se coge el primero y se marcan los nodos que cubre como cubiertos y se coge el siguiente no cubierto ...
	/*
	* conjuntoDominante: devuelve sol, siendo el conjunto dominante del 
	* 	grafo de conexiones cargado.
	**/
	/*vector<int> conjuntoDominante(){
		bool covered[_size];
		for (int i = 0; i < _size; i++){covered[i]= false;}
		cout << "Pasa el vector de bool" << endl;
		vector<int> sol;
		for(int i = 0; i < _size; i++){
			if(!covered[i]){
				sol.push_back(i);
				covered[i] = true;
				for(int j = 0; j < _size; j++){
					if(!covered[j] && lights[i*_size + j] == 1){
						covered[j] = true;
					}
				}
			}
		}
		return sol;
	}*/

	/*
	* calcularGrado: calcula el grado y el vector de vecinos 
	* de cada uno de los nodos del grafo
	**/
	/*vector<NodoLuz> calcularGrado(){
		vector<NodoLuz> v;
		vector<int> vecinos;
		for (int i = 0; i < _size; i++){
			vecinos.clear();
			for (int j = 0; j < _size; j++){
				if (lights[i*_size + j] == 1) {
					vecinos.push_back(j);
				}
			}
			v.push_back(NodoLuz(i,vecinos.size(),vecinos,false));
		}
		return v;
	}*/ 

	/*
	* getMostDeg: devuelve el identificador del nodo que tiene mayor grado
	**/
	int getMostDeg(vector<NodoLuz> covered) {
		int i = 0, nodoSol;
		int maxGrado = 0;
		for (NodoLuz a : covered){
			if (a.notCovered() && a.getGrado() >= maxGrado){
				nodoSol = i; 
				maxGrado = a.getGrado();
			}
			i++;
		}
		return nodoSol;
	}

	/*
	* actualizarPesos: actualiza el grado y el numero de vecinos no cubiertos 
	* de cada nodo tras haber elegido uno para el conjnto dominante
	**/
	void actualizarPesos(int nodoC,vector<NodoLuz>& nodos, bool &fin){
		vector<int> vecinosC = nodos[nodoC].getVecinos();
		vector<int> newVecinos;
		bool found = false;
		int cubiertos = 0;
		for (int i = 0; i < nodos.size(); i++){
			newVecinos.clear();
			if (nodos[i].notCovered()){
				vector<int> vecinosA = nodos[i].getVecinos();
				for (int va : vecinosA){
					found = false;
					for (int v : vecinosC) {
						if (va == v) {
							found = true;
						}
					}
					if (found == false) {
						newVecinos.push_back(va);
					} 
				}
				nodos[i].changeVecinos(newVecinos);
				nodos[i].changeGrado(newVecinos.size());
			}else {
				cubiertos++;
			}
		}
		if (cubiertos == _size){
			fin = true;
		}else {
			fin = false;
		}
	}

	/*
	* marcarCubiertos: marca como cubiertos todos los vecinos del nodo elegido
	**/
	void marcarCubiertos(vector<NodoLuz>& nodos, int nodoC){
		vector<int> vecinosC = nodos[nodoC].getVecinos();
		for (int v : vecinosC) {
			nodos[v].setCovered(true);
		}
	}


	/*
	* GreedyAlg: resuelve el conjunto dominante utilizando una heuristica voraz
	**/
	/*vector<int> GreedyAlg() {
		vector<NodoLuz> covered = calcularGrado();
		vector<int> D;
		bool done = false;
		int i = 0;
		while (!done){
			int nodoC = getMostDeg(covered);
			marcarCubiertos(covered,nodoC);
			D.push_back(nodoC);
			actualizarPesos(nodoC, covered, done);
			i++;
		} //porque actualizar pesos puede devolver done o no 

		cout << "Resuelto en " << i << " iteraciones" << endl;
		return D;
		
	}*/

	int chooseVertex(){
		int max = 0;
		int nodo = -1;
		for(int i = 0; i < _size; i++){
			if (lights[i].getWeight() > max){
				max = lights[i].getWeight();
				nodo = i;
			}
		}
		if (max <= 0){
			return -1;
		}else {
			return nodo;
		}
	}

	void AdjustWeights(int i) {
		lights[i].setWeight(0);
		//int voteI = lights[i].getVote();
		vector<int> vecinos = lights[i].getVecinos();
		for (int j : vecinos) {
			//cout << "Trato a " << j << endl;
			if (lights[j].getWeight() > 0) {
				if (lights[i].notCovered()){
					lights[j].setWeight((lights[j].getWeight() - lights[i].getVote()));
					//cout << "actualizo el peso de "<< j <<" a " << lights[j].getWeight() << endl;
				}
				if(lights[j].notCovered()){
					//cout << "Como " << j << " no esta cubierto" << endl;
					lights[j].setCovered(true);
					lights[j].setWeight((lights[j].getWeight() - lights[j].getVote()));
					//cout << "actualizo el peso de "<< j <<" a " << lights[j].getWeight() << endl;
					vector<int> vecinosJ = lights[j].getVecinos();
					//int voteJ = lights[j].getVote();
					//cout << "Actualizo los vecinos de " << j << endl;
					for (int k : vecinosJ) {
						if (lights[k].getWeight() > 0) {
							lights[k].setWeight((lights[k].getWeight() - lights[j].getVote()));
							//cout << "actualizo el peso de"<< k <<" vecino de" << j << " a " << lights[k].getWeight() << endl;
						}
					}
				}
			}
		}
		lights[i].setCovered(true);
	}

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
		while(v != -1){
			//cout << "----------------------------------" << endl;
			//for (int i = 0; i < _size; i++){
			//	lights[i].printNodoLuz();
			//}
			v = chooseVertex();
			//cout << "El nodo elegido es: " << v << endl;
			if (v != -1){
				D.push_back(v);
				AdjustWeights(v);
			}
		}
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
		//sol = luces.conjuntoDominante();
		end = chrono::steady_clock::now();
	}else if (mode == "H"){
		begin = chrono::steady_clock::now();
		sol = luces.GreedyVote();
		end = chrono::steady_clock::now();
	}
	cout << "La solucion es de tamaño: " << sol.size() << endl;
	for (int s : sol){
		cout << s << " ";
	}
	cout << endl;
	int elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	if (elapsed > 0) {
		cout << "Tiempo de ejecucion: " <<  elapsed << " ms" << endl;
	}else {
		elapsed = chrono::duration_cast<chrono::microseconds>(end - begin).count();
		cout << "Tiempo de ejecucion: " <<  elapsed << " µs" << endl;
	}
	

	return 0;
}