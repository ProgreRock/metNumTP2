#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
using namespace std;

int getdir (string dir, vector<string> &files){
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main(int argc, char **argv){
    int numero;
    string nombre("./main ");
    if(argc<1){
        cout<<"faltan parametros"<<endl;
        cout<<"modo de ejecucion: ./probador <directorio>"<<endl;
        cout<<" poner \".\" para realizarlo sobre el directorio actual"<<endl;
        exit(-1);
    }
    string dir = string(argv[1]);
    vector<string> files;
    getdir(dir,files);
    size_t pos = dir.find_last_of("/\\");
    string directorio=dir.substr(0,pos+1);
    int i;
    int j=0;
    cout<<"Inicio de las pruebas"<<endl;
    for(i=0;i<files.size();i++){
        string comando;
        size_t found = files[i].find_last_of(".");
        string nombre= files[i].substr(0,found+1);
        if(0==(files[i].substr(found+1)).compare ("in") ){
            cout<<"Prueba numero: "<<j<<endl;
            comando=string("./main ")+directorio+files[i]+string(" ")+directorio+nombre+string("out");
            //cout<<comando<<endl;
            system(comando.c_str());
            j++;
        }
    }
    cout<<"Fin de Pruebas"<<endl;
    return 0;

}
