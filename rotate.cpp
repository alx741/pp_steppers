/*
 * =====================================================================================
 *
 *       Filename:  rotate.cpp
 *
 *    Description:  Ejemplo para mover un motor PAP Unipolar por puerto paralelo
 *
 *        Version:  1.0
 *        Created:  09/29/12 16:39:05
 *       Revision:  none
 *       Compiler:  gcc
 *       License:   GPLv3
 *
 *         Author:  Daniel Campoverde Carri√n
 *   Organization:  Silly Bytes
 *
 * =====================================================================================
 */

#include <iostream>
#include "unipolar.cpp"

using namespace std;

int main(int argc, char *argv[]){

    bool angulo=false;
    bool pasos=false;
    motor_unipolar motor(200);
    int direccion;
    int valor;

    if(argc < 4){ cout << "args"; return 1;}

    for(int i = 0; i<argc; i++){

	if(argv[i]=="-a"){ angulo=true; valor = int(argv[i+1]); }
	if(argv[i]=="-p"){ pasos=true; valor = int(argv[i+1]); }
	if(argv[i]=="-d"){
		if(argv[i+1]=="IZQ") direccion = 1;
		if(argv[i+1]=="DER") direccion = 0;
	}

    }
    

if(pasos){

	motor.step(valor,direccion);

}else if(angulo){

	motor.rotate(valor,direccion);
}
}

