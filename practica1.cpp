#include<bits/stdc++.h>
 
using namespace std;
class NodoLuz {
private:
	int _pos;
	int _deg;

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
	//SOLUCIOON : se coge el primero y se marcan los nodos que cunbre como cubiertos y se coge el siguiente no cubierto ...
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
};
 


int main(int argc, char *argv[]){
	if (argc != 2){
		cout << "USAGE ERROR" << endl;
		cout << "Usage: ./practica1 <path to file>" << endl;
		exit(1);
	}

	string path = argv[1];
	WiSun luces = WiSun(path);
	vector<int> sol = luces.solve_dominant();
	cout << "La solucion es de tamaño: " << sol.size() << endl;
	for (int s : sol){
		cout << s << " ";
	}
	cout << endl;

	return 0;
}