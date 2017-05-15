#include "matriz.h"
#include "vector.h"
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
#include <sys/time.h>

void guardar_norma_manhattan(vector<double> a,vector<double> b){
  ofstream myfile("Norma.txt", std::ofstream::app);
  if (myfile.good()){   
    myfile<<std::fixed<<std::setprecision(6)<<calcular_manhattan(a,b)<<endl;
    myfile.close();
  }
}

vector<double> INDEG(matrix a){
	return a.suma_columnas();	
}

vector<double> teletransportar(vector<double> P_prima_por_X,double c,vector<double> X){
	vector<double> res;
	res.resize(P_prima_por_X.size());
	//Equivale a X'=P''=c*P'*X+(1-c)* E * X
	double Eb=0;
	for(int i=0;i<X.size();i++){
		Eb+=X[i];
	}
	Eb=Eb/X.size();
 	for(int i=0;i<P_prima_por_X.size();i++){
		res[i]=P_prima_por_X[i]*c+(1-c)*Eb;
	}
	return res;
}

//segun aritucilo KAMVAR
vector<double> PageRank(matrix a,double c,double tol,const char * archivo){
	vector<double> res;
	vector<double> paso_anterior;
	ofstream myfile(archivo);
	clock_t ti;
	clock_t tf;
	ti=clock();
	time_t timer;
	time_t timer2;
	double seconds;
	time(&timer);
	if (myfile.is_open()){
		double prom = 1/(double)a.tamanio;
		paso_anterior.resize(a.tamanio,0);
		res.resize(a.tamanio,prom);
		a.normalizar_filas();
		int i=0;
		while(!vectores_iguales(paso_anterior,res,tol)){
			myfile<<"Norma paso "<<i<<": "<<std::fixed<<std::setprecision(6)<<calcular_manhattan(res,paso_anterior)<<endl;
			paso_anterior=res;
			//Multiplicar pagerank= P'*X
			res=teletransportar(a.multiplicar_PAGERANK(paso_anterior),c,paso_anterior);
			i++;
			cout<<"Iteracion "<<i<<endl;
		}
		tf=clock();
		time(&timer2);
		cout<<"Numero de iteraciones: "<<i<<endl;
		myfile<<"Numero de iteraciones: "<<i<<endl;
		myfile<<"Tiempo de ejecucion en segundos(clock): "<<(double)(tf-ti)/CLOCKS_PER_SEC<<endl;
		myfile<<"Tiempo de ejecucion en segundos(time): "<<difftime(timer2,timer)<<endl;
		myfile.close();
	}
	return res;
}

int main(int argc, char *argv[]){
	int algoritmo;
	int tipo;
	double c;
	double tol;
	string path;
	// Cargo los parametros
	ifstream myfile(argv[1]);
	string line;
	if(argc<=1){
		cout<<"Faltan parametros de entrada"<<endl;
		cout<<"Modo de ejecucion:"<<endl;
		cout<<"./main <archivo de entrada> <archivo resultado -- opcional>"<<endl;
		exit(-1);
	}
	//0 0.85 0 tests/test1.txt 0.00001
	//cout<<"cargando archivo de entrada"<<argv[1]<<endl;
	if (myfile.is_open()){
		getline (myfile,line);
		string substr;
		stringstream ss(line);
		getline (ss,substr,' ');
		algoritmo=atoi(substr.c_str());
		getline (ss,substr,' ');
		c=atof(substr.c_str());
		getline (ss,substr,' ');
		tipo=atoi(substr.c_str());
		getline (ss,substr,' ');
		path=substr;
		getline (ss,substr,' ');
		tol=atof(substr.c_str());
		myfile.close();
	}
	// Dependiendo del algoritmo requerido me fijo que quiero

	//cout<<"Datos del archivo: "<<endl;
	//cout<<"Algoritmo: "<<algoritmo<<"\tC: "<<c<<" tipo: "<<tipo<<endl;
	//cout<<"Path: "<<path<<"\ttolerancia: "<<tol<<endl;

	matrix mat1;
	string nombre(argv[1]);
	size_t pos=nombre.find_last_of(".in");
	nombre=nombre.substr(0,pos-string(".in").size()+1);
	nombre+=string(" Norma.txt");
	cout<<"carga de matriz";
	int error=0;
	if(tipo==0){
		//carga tipo Pagerank
		cout<<" SNAP"<<endl;
		error=mat1.cargar_SNAP(path.c_str());
	}
	else{
		//carga tipo deporte
		cout<<" deporte"<<endl;
		error=mat1.cargar_deporte(path.c_str());
	}
	if (error==0){
		cout<<"Termino de Cargar"<<endl;
	}
	else{
		cout<<"Error en la Carga"<<endl;
		return 1;
	}
	//mat1.mostrar_matriz();
	vector <double> res;
	switch(algoritmo){
		//page rank
		case 0 :
			cout<<endl<<"Page Rank"<<endl;
			cout<<endl<<"con c: "<<c<<" con tol: "<<tol<<endl;
			cout<<"Calculando... "<<endl;	
			res=PageRank(mat1,c,tol,nombre.c_str());		
		break;
		//INDEG
		case 1:
			cout<<endl<<"IN-DEG"<<endl;
			res = INDEG(mat1);
		break;

		default : /* opcion no valida */
				abort ( );
	}
	cout<<"Termino de calcular el ranking"<<endl;
	if(argc>2){	
		cout<<"guardando resultado"<<endl;
		guardar_vector(res,argv[2]);
	}
	cout<<"Termino"<<endl<<endl;
	return 0;
}
