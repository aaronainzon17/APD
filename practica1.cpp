#include<bits/stdc++.h>
#include <iostream>
#include <chrono>
 
using namespace std;
class NodoLuz {
private:
	int nodo;
	int grado;
	bool cubierto;
	vector<int> vecinos;
public:

	NodoLuz();
	NodoLuz(int n, int deg, vector<int> v, bool cov): nodo(n),grado(deg),vecinos(v), cubierto(cov){}

	void changeGrado(int newGrado){
		grado = newGrado;
	}

	void changeVecinos(vector<int> newVec){
		vecinos = newVec;
	}

	void printNodoLuz(){
		cout << nodo << " - " << grado << " - ";
		for (int a : vecinos){
			cout << a << " ";
		}
		cout << endl;
	}

	bool notCovered(){
		return !cubierto;
	}

	int getGrado(){
		return grado;
	}

	void markAsCovered(){
		cubierto = true;
	}

	vector<int> getVecinos(){
		return vecinos;
	}

	int me(){
		return nodo;
	}

	void info(){
		string cub = "NO";
		if (cubierto) {
			cub = "SI";
		}
		cout << nodo << "-" << cub << " "; 
	}

	int yo(){
		return nodo;
	}

};
class WiSun {
private:
	int _size;
	vector<int> lights;
public:
	WiSun(string path){
		ifstream f;
		f.open(path);
		if(f.is_open()){
			f >> _size;

			cout << endl << path << endl;
			cout << "El tamanio es de: " << _size << endl;
			
			int light = 0;
			while(!f.eof()){
				f >> light;
				lights.push_back(light);
			}
			f.close();
		}
	}

	void printWiSun(){
		for (int i = 0; i < _size; i ++) {
			for (int j =0; j< _size; j++){
				cout << lights[_size*i+j] << " ";
			}
			cout << endl;
    	}
	}

	//SOLUCION : se coge el primero y se marcan los nodos que cubre como cubiertos y se coge el siguiente no cubierto ...
	vector<int> solve_dominant(){
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
	}

	vector<NodoLuz> calcularGrado(){
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
	} 

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

	void actualizarPesos(int nodoC,vector<NodoLuz>& nodos, bool &fin){
		vector<int> vecinosC = nodos[nodoC].getVecinos();
		vector<int> newVecinos;
		bool found = false;
		int cubiertos = 0;
		for (int i = 0; i < nodos.size(); i++){
			newVecinos.clear();
			if (nodos[i].notCovered()){
				//cout << "NODO: " << nodos[i].yo() << endl;
				vector<int> vecinosA = nodos[i].getVecinos();
				for (int va : vecinosA){
					found = false;
					for (int v : vecinosC) {
						//cout << "comparo: " << va << " con " << v << endl;
						if (va == v) {
							found = true;
						}
					}
					if (found == false) {
						//cout << "Meto en newVecinos de " << nodos[i].yo() << " " << va << endl;
						newVecinos.push_back(va);
					} 
				}
				nodos[i].changeVecinos(newVecinos);
				nodos[i].changeGrado(newVecinos.size());
			}else {
				cubiertos++;
			}
		}
		/*for (NodoLuz a : nodos){
			newVecinos.clear();
			if (a.notCovered()){
				cout << "NODO: " << a.yo() << endl;
				vector<int> vecinosA = a.getVecinos();
				for (int va : vecinosA){
					found = false;
					for (int v : vecinosC) {
						//cout << "comparo: " << va << " con " << v << endl;
						if (va == v) {
							found = true;
						}
					}
					if (found == false) {
						cout << "Meto en newVecinos de " << a.yo() << " " << va << endl;
						newVecinos.push_back(va);
					} 
				}
				a.changeVecinos(newVecinos);
				a.changeGrado(newVecinos.size());
			}else {
				cubiertos++;
			}
		}*/
		if (cubiertos == _size){
			fin = true;
		}else {
			fin = false;
		}
	}

	void marcarCubiertos(vector<NodoLuz>& nodos, int nodoC){
		vector<int> vecinosC = nodos[nodoC].getVecinos();
		for (int v : vecinosC) {
			nodos[v].markAsCovered();
		}
	}

	vector<int> GreedyAlg() {
		vector<NodoLuz> covered = calcularGrado();
		vector<int> D;
		bool done = false;
		while (!done){
			int nodoC = getMostDeg(covered);
			marcarCubiertos(covered,nodoC);
			D.push_back(nodoC);
			actualizarPesos(nodoC, covered, done);
			/*for (NodoLuz a : covered){
				a.printNodoLuz();
			}
			cout << endl;*/
		} //porque actualizar pesos puede devolver done o no 
		//for (int i = 0; i < _size; i++) {
			
		//}
		return D;
		
	}

};

int main(int argc, char *argv[]){
	if (argc != 2){
		cout << "USAGE ERROR" << endl;
		cout << "Usage: ./practica1 <path to file>" << endl;
		exit(1);
	}

	string path = argv[1];
	WiSun luces = WiSun(path);
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	//vector<int> sol = luces.solve_dominant();
	vector<int> sol = luces.GreedyAlg();
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	cout << "La solucion es de tamaño: " << sol.size() << endl;
	for (int s : sol){
		cout << s << " ";
	}
	cout << endl;
	cout << "Tiempo de ejecucion: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << " µs" << endl;

	return 0;
}