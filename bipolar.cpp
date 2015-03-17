/*
 * =====================================================================================
 *
 *       Filename:  bipolar.cpp
 *
 *    Description: Clase para mover un motor PAP Bipolar por puerto paralelo 
 *
 *        Version:  1.0
 *        Created:  09/28/12 11:44:21
 *       Revision:  none
 *       Compiler:  g++
 *       License:   GPLv3
 *
 *         Author:  Daniel Campoverde Carri√n
 *   Organization: Silly Bytes 
 *
 * =====================================================================================
 */

#include <iostream>
#include <sys/io.h>
#include <unistd.h>

#define puerto (0x378) //Puede ser (0x278)

//datos sacados por el nibble bajo del puerto paralelo 
//A,B,C,D son los cables del motor PAP
#define A 1 //bobina 1 polaridad 1
#define B 2 //bobina 1 polaridad 2
#define C 4 //bobina 2 polaridad 1
#define D 8 //bobina 2 polaridad 2


using namespace std;

class motor_bipolar{

    public:


	//steps=Numero de pasos del motor

	motor_bipolar( int steps);


	int step( int steps = 1,  int direction = 0,  int rate_step = 25000); ///pasos a dar,direccion[0=horario,1=antihorario],tiempo entre paso y paso(microsegundos)
	
	int rotate( int angle = 1, int direction = 0,  int rate_step = 25000);///angulo a rotar (degrees),direccion[0=horario,1=antihorario],tiempo entre paso y paso(microsegundos)

    private:

	 int motor_steps;
	 
	float angle_by_step;
	int sequence[4] = {A,B,C,D};
	int *current_step;
	void single_step( int direction);
	int forward_sequence();
	void backward_sequence();

};


motor_bipolar::motor_bipolar( int steps) : motor_steps(steps), angle_by_step(360/steps), current_step(sequence){


    if(ioperm(puerto,1,1)){ //Abrir puerto y configurar permisos
	cout << "Error de permisos" << endl << flush;
	
    }

    
}



int motor_bipolar::step( int steps,  int  direction,  int rate_step){

    


    while(steps > 0){
    	
	single_step(direction);
	usleep(rate_step);
	steps--;

	
    }   

    return 0;
}


int motor_bipolar::rotate( int angle, int direction,  int rate_step){



     int steps =  int(angle/angle_by_step);


    while(steps > 0){
    	
	single_step(direction);
	usleep(rate_step);
	steps--;

    }   

    return 0;
}


int motor_bipolar::forward_sequence(){

    if(current_step==&sequence[4]){ current_step = sequence; return 0;} //reiniciamos la secuencia
    
    current_step++; //avanzamos en la secuencia

    return 0;
    
}

void motor_bipolar::backward_sequence(){

    if(current_step==&sequence[0]) current_step = &sequence[4]; //reiniciamos la secuencia

    
    current_step--; //avanzamos en la secuencia
    

}

void motor_bipolar::single_step( int direction){

outb(*current_step,puerto);

if(direction==0){ forward_sequence();}
else{backward_sequence();}

}




