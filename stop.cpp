#include <iostream> // Se puede poner la de printf
#include <sys/io.h> // Esta nos da los comandos
#include <unistd.h>
#define puerto (0x378)

/* Notense los parentesis, son importantes, pues en este declaramos el puerto, tambien podria ser (0x278), si no les funciona el 378 */

using namespace std; // Para el Iostream

int main(){
if(ioperm(puerto,1,1)){ // Abrimos el puerto, y verificamos permisos de abrir el puerto
cout << "Hubo un error de permisos";// Se da si no tenemos permisos
//sleep(5);
return 1; // Devuelve error 1 y finaliza
}






outb(0,puerto); 

outb(0,0x379); 

outb(0,0x37A); 


//outb(255,puerto); //Prendemos los primeros 5 pines, mandando una salida de 5V
if(ioperm(puerto,1,0)){ // Cerramos el puerto, y verificamos permisos del puerto
cout << "Hubo un error de permisos, ERROR 2";
//sleep(5);
return 2; // Devuelve error 2 y finaliza
}
return 0;
}
