#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iomanip>
#include <map>
#include <climits>

using namespace std;
class matrix{
	public:
		matrix();
		void mostrar_matriz();
		int cargar_SNAP (const char * archivo);
		int cargar_deporte(const char * archivo);
		vector<double> multiplicar_PAGERANK  (vector<double> vec);
		void normalizar_filas();
		vector<double> suma_columnas();
		long tamanio;
		vector<int> equivalencia();

	private:
		vector<double> _valores;	// valor del elemento A[i][j]
		vector<int> _columnaElem; // columna del elemento dentro de la fila
		vector<int> _elemsFila; 	// # elementos por filas
		map<int, int> claves;
		void convertir_dokey(vector < multimap<int, double> > dokey);
		void mostrar(const vector<int> v);

};


matrix::matrix(){}

void reemplazar_espacios(string &str){
	size_t found = str.find_first_of("\t");
	while (found!=string::npos){
	    str[found]=' ';
	    found=str.find_first_of("\t");
	}
}

void matrix::mostrar(const vector<int> v){
	for(int i=0;i<v.size();i++){
		cout<<v[i];
		if(i+1<v.size())
			cout<<" ";
	}
}

void matrix::convertir_dokey(vector < multimap<int, double> > dokey){
	int acum=0;
	for(int fila=0;fila<dokey.size();fila++ ){
		for(multimap<int,double>::iterator it=dokey[fila].begin();it!=dokey[fila].end();++it){
			_columnaElem[acum]=it->first;
			_valores[acum]=it->second;
			acum++;
		}
		_elemsFila[fila]=acum;
	}
}

vector<int> matrix::equivalencia(){
	vector<int> res;
	res.resize(tamanio);	
	for(map<int,int>::iterator it=claves.begin();it!=claves.end();++it){
		res[it->second-1]=it->first;
	}
	return res;
}

int matrix::cargar_SNAP(const char * archivo){
	string line;
	ifstream myfile(archivo);
	vector < multimap<int, double> > auxiliar;
	if (myfile.is_open()){
		getline (myfile,line);
		getline (myfile,line);
		getline (myfile,line);
		//Veo cuantos nodos y arustas sdebo recuperar
		line=line.substr(string("# Nodes: ").size());
		size_t pos=line.find(" ");
		tamanio=atoi(line.substr(0,pos).c_str());
		pos=line.find_first_of("Edges: ");
		line=line.substr(pos+string("Edges: ").size()+1);
		int edges=atoi(line.c_str());	
		_valores.resize(edges,0);
		_columnaElem.resize(edges,0);
		auxiliar.resize(tamanio+1);
		_elemsFila.resize(tamanio+1,0);
		getline( myfile, line);
		int i=0;
		int claves_definidas=0;
		while(getline (myfile,line)){
			reemplazar_espacios(line);
			stringstream ss(line);
			string valores;
			getline( ss, valores, ' ' );
			int fila=atoi(valores.c_str());
			getline( ss, valores, ' ' );
			while(valores.length()==0){
				getline( ss, valores, ' ' );
			}
			int columna=atoi(valores.c_str());
			if(claves.count (fila) ==0){
				claves_definidas++;
				claves.insert( std::pair<int,int> (fila,claves_definidas));
			//	cout<<"claves_definidas: "<<claves_definidas<<endl;
			}
			if(claves.count (columna) ==0){
				claves_definidas++;
				claves.insert( std::pair<int,int> (columna,claves_definidas));
			//	cout<<"claves_definidas: "<<claves_definidas<<endl;
			}
			map<int, int>::iterator it =claves.find (columna);
			map<int, int>::iterator it2=claves.find (fila);
			auxiliar[it2->second].insert( std::pair<int,double> (it->second,1));
			//auxiliar[fila].insert( std::pair<int,double> (columna,1));
			i++;
		}	
		convertir_dokey(auxiliar);
		myfile.close();
		if(_elemsFila[tamanio]!=edges){
			cout<<"error en la inserccion de un elemento, faltan: "<<_elemsFila[tamanio]-edges<<endl;
			return 1;
		}
	}
	else{
		cout<<"No se pudo abrir el archivo: "<<archivo<<endl;
		return 1;
	}
	return 0;
}

int matrix::cargar_deporte(const char * archivo){
	
	string line;
	size_t pos;
	ifstream myfile(archivo);
	vector < multimap<int, double> > auxiliar;
	if (myfile.is_open()){
		getline (myfile,line);
		pos=line.find_first_of(" ");
		tamanio=atoi(line.substr(0,pos).c_str());
		line=line.substr(pos+1);
		int edges = atoi(line.c_str());		
		_valores.resize(edges,0);
		_columnaElem.resize(edges,0);
		auxiliar.resize(tamanio+1);
		_elemsFila.resize(tamanio+1,0);
		
		while(getline (myfile,line)){
			//leo la linea del archivo
			pos=line.find_first_of(" ");
			line=line.substr(pos+1);
			int equipo1=atoi(line.substr(0,pos).c_str());
			pos=line.find_first_of(" ");
			line=line.substr(pos+1);
			pos=line.find_first_of(" ");
			int resultado1=atof(line.substr(0,pos).c_str());
			pos=line.find_first_of(" ");	
			line=line.substr(pos+1);
			int equipo2=atoi(line.substr(0,pos).c_str());
			pos=line.find_first_of(" ");
			line=line.substr(pos+1);
			pos=line.find_first_of(" ");
			int resultado2=atof(line.substr(0,pos).c_str());
			int i=equipo1;
			int j=equipo2;
			if(resultado1!=resultado2){
				if(resultado1>resultado2){
					i=equipo2;
					j=equipo1;
				}
				//cout<<"equipo "<<equipo1<<": "<<resultado1<<" vs equipo "<<equipo2<<": "<<resultado2<<endl;
				multimap<int, double>::iterator it=auxiliar[i].find (j);
				if(it==auxiliar[i].end()){
					auxiliar[i].insert( std::pair<int,double> (j,fabs(resultado2-resultado1)));
				}
				else{
					it->second+=fabs(resultado2-resultado1);
				}
			}
			//insertion_sorting(i,j,fabs(resultado2-resultado1));
			
		}	
		convertir_dokey(auxiliar);
		myfile.close();
	}
	else{
		cout<<"No se pudo abrir el archivo: "<<archivo<<endl;
		return 1;
	}
	return 0;
}

void matrix::mostrar_matriz(){
	for (int fila_actual = 1; fila_actual < _elemsFila.size(); fila_actual++){	
		for(int indice=_elemsFila[fila_actual-1];indice <_elemsFila[fila_actual];indice++){
			cout << "fila : "<< fila_actual <<" _ " << "columna: "<< _columnaElem[indice]<<" valor: "<<_valores[indice]<< endl;		
		}
	}
}

vector<double> matrix::multiplicar_PAGERANK(const vector<double> vec){
	//completa la fila n con 1/n
	vector<double> res;
	res.resize(tamanio,0);
	double prom=1/(double) tamanio;
	for (int fila = 1; fila <=tamanio; fila++){	
		if(_elemsFila[fila-1]==_elemsFila[fila]){
			for(int i=0;i<tamanio;i++){
				res[i]+=prom*vec[fila-1];
			}
		}
		else{
			for(int i=_elemsFila[fila-1];i<_elemsFila[fila];i++){
				res[_columnaElem[i]-1]+=_valores[i]*vec[fila-1];
			}
		}
	}
	return res;
}

void matrix::normalizar_filas(){
	for (int fila_actual = 1; fila_actual < _elemsFila.size(); fila_actual++){	
		double sumatoria=0;
		for(int indice=_elemsFila[fila_actual-1];indice <_elemsFila[fila_actual];indice++){
			sumatoria+=_valores[indice];			
		}
		for(int indice=_elemsFila[fila_actual-1];indice <_elemsFila[fila_actual];indice++){
			_valores[indice]=_valores[indice]/sumatoria;			
		}
	}
}

vector<double> matrix::suma_columnas(){
	vector<double> res;
	res.resize(tamanio,0);
	for(int i=0;i<_valores.size();i++){
		res[_columnaElem[i]-1]=res[_columnaElem[i]-1]+_valores[i];
		
	}
	return res;
}

