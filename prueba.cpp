/* This is the class for controlling stepper motors (unipolar and bipolar), this is free software, can be redistributed or modified under the terms of the GNU General Public License (GPL)


*/


#include <iostream> 
#include <sys/io.h> //para comunicar con el puerto 
#include <unistd.h>
#define puerto (0x378) /* Notense los parentesis, son importantes, pues en este declaramos el puerto, tambien podria ser (0x278), si no funciona el 378 */ 
#define seconds 25000 

using namespace std; // Para el Iostream

int main(){

if(ioperm(puerto,1,1)){ // Abrimos el puerto, y verificamos permisos de abrir el puerto
cout << "Hubo un error de permisos" << endl << flush;// Se da si no tenemos permisos
return 1; // Devuelve error 1 y finaliza
}



while(true){
usleep(seconds); //0.2 Seconds
outb(3,puerto); 
usleep(seconds);
outb(6,puerto); 
usleep(seconds);
outb(12,puerto); 
usleep(seconds);
outb(9,puerto); 
}





return 0;
}
