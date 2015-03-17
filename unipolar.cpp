/*
 * =====================================================================================
 *
 *       Filename:  unipolar.cpp
 *
 *    Description: Clase para mover un motor PAP Unipolar por puerto paralelo 
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
#define A 1
#define B 2
#define C 4
#define D 8
#define AB 3
#define BC 6
#define CD 12
#define DA 9



using namespace std;

class motor_unipolar{

    public:


	//steps=Numero de pasos del motor,type_step[0=simple,1=double.2=half]

	motor_unipolar( int steps,  int type_step=1);


	int step( int steps = 1,  int direction = 0,  int rate_step = 25000); ///pasos a dar,direccion[0=horario,1=antihorario],tiempo entre paso y paso(microsegundos)
	
	int rotate( int angle = 1, int direction = 0,  int rate_step = 25000);///angulo a rotar (degrees),direccion[0=horario,1=antihorario],tiempo entre paso y paso(microsegundos)


	void stop(){ outb(puerto,0);} //poner a 0 el puerto


    private:

	 int motor_steps;
	 int step_type;
	float angle_by_step;
	int sequence[8];
	int *current_step;
	void single_step( int direction);
	int forward_sequence();
	void backward_sequence();

};


motor_unipolar::motor_unipolar( int steps,  int type_step) : motor_steps(steps), step_type(type_step), angle_by_step(360/steps){


    if(ioperm(puerto,1,1)){ //Abrir puerto y configurar permisos
	cout << "Error de permisos" << endl << flush;
	
    }


    switch(step_type){

	case 0: 
	    sequence[0] = A; //Secuencia simple_step
	    sequence[1] = B;
	    sequence[2] = C;
	    sequence[3] = D;
	    sequence[4] = 0;
	    sequence[5] = 0;
	    sequence[6] = 0;
	    sequence[7] = 0;

	    break; 
	case 1: 
	    sequence[0] = AB; //Secuencia double_step
	    sequence[1] = BC;
	    sequence[2] = CD;
	    sequence[3] = DA;
	    sequence[4] = 0;
	    sequence[5] = 0;
	    sequence[6] = 0;
	    sequence[7] = 0;



	    break; 
	case 2: 
	    sequence[0] = A; //Secuencia half_step
	    sequence[1] = AB;
	    sequence[2] = B;
	    sequence[3] = BC;
	    sequence[4] = C;
	    sequence[5] = CD;
	    sequence[6] = D;
	    sequence[7] = DA;
	
	    break; 

    }




    current_step = sequence;//colocamos el paso actual al principio de ka secuencia

    

    
}



int motor_unipolar::step( int steps,  int  direction,  int rate_step){

    


    while(steps > 0){
    	
	single_step(direction);
	usleep(rate_step);
	steps--;

	cout << *current_step << endl << flush;
    }   

    return 0;
}


int motor_unipolar::rotate( int angle, int direction,  int rate_step){



     int steps =  int(angle/angle_by_step);


    while(steps > 0){
    	
	single_step(direction);
	usleep(rate_step);
	steps--;

    }   

    return 0;
}


int motor_unipolar::forward_sequence(){

    if(current_step==&sequence[7] || *current_step == 0){ current_step = sequence; return 0;} //reiniciamos la secuencia
    
    current_step++; //avanzamos en la secuencia

    if(*current_step == 0){ current_step = sequence; return 0;}
    return 0;
    
}

void motor_unipolar::backward_sequence(){

    if(current_step==&sequence[0]) current_step = &sequence[7]; //reiniciamos la secuencia

    
    current_step--; //avanzamos en la secuencia
    
    if(*current_step==0) backward_sequence();

}

void motor_unipolar::single_step( int direction){

outb(*current_step,puerto);

if(direction==0){ forward_sequence();}
else{backward_sequence();}

}



int main(){

    int opcion;
    motor_unipolar motor(200);
    int direccion;
    int valor;


    for(;;){

	cout << "\n\n\nAngulo, Pasos, Salir[0,1,2]\n >>  ";
	cin >> opcion;
	cout << "Valor (angulo o pasos)\n >>  ";
	cin >> valor;
	cout << "Direccion[0,1]\n >> ";
	cin >> direccion;
	
	if(opcion==0){

	    cout << "Rotando..." << endl;
	    motor.rotate(valor,direccion);

	}else if(opcion==1){

	    motor.step(valor,direccion);
	    cout << "Rotando..." << endl;

	}else{ motor.stop(); return 0;}

}
}


