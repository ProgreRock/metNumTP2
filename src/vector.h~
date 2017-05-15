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

#define Norma_1 1
#define Norma_2 2
#define Norma_infinito 0

void mostrar_vector(const vector<double> v){
	for(int i=0;i<v.size();i++){
		cout<<v[i];
		if(i+1<v.size())
			cout<<" ";
	}
}

void guardar_vector(const vector<double> v,const char * archivo){
	ofstream myfile(archivo);
	cout<<"guardando en: "<<archivo<<endl;
	if (myfile.good()){
	    for (int i=0;i < v.size();i++){
	    	myfile<<std::fixed<<std::setprecision(6)<<v[i]<<endl;
	    }
	    myfile.close();
	}
	else{
	  cout<<"No se puedo abrir el archivo: "<<archivo<<endl;
	}
}

bool vectores_iguales(const vector<double> &a,const vector<double> & b, double tol=0.00000000000001){
	bool res=true;
	int i=0;
	double parcial=0;
	while(res&&(i<a.size())){
		parcial+=(fabs(a[i]-b[i]));
		if(parcial>tol)
			res=false;
		i++;
	}
	return res;
}

double calcular_manhattan(const vector<double> a,const vector<double> b){
	double resultado=0;
	for (int i=0;i < a.size();i++){
		resultado+=fabs(a[i]-b[i]);
	}
	return resultado;
}
