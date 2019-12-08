
#include "piMusicBox_1.h"
#include <wiringPi.h>
#include <softTone.h>
#include <stdio.h>
#include <string.h>

int frecuenciaDespacito[160] = {0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,0,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318,659,659,659,659,659,659,659,659,554,587,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318};
int tiempoDespacito[160] = {1200,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,800,300,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,450,1800,150,150,150,150,300,150,300,150,150,150,300,150,300,450,450,300,150,150,225,75,150,150,300,450,800,150,150,300,150,150,300,450,150,150,150,150,150,150,150,150,300,300,150,150,150,150,150,150,450,150,150,150,300,150,300,450,450,300,150,150,150,300,150,300,450,800,150,150,300,150,150,300,450};

int frecuenciaGOT[518] = {1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,1175,0,1397,0,932,0,1244,0,1175,0,1397,0,932,0,1244,0,1175,0,1046,0,831,0,698,0,523,0,349,0,784,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,587,0,622,0,587,0,523,0,587,0,784,0,880,0,932,0,1046,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1046,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,880,0,784,0,932,0,1244,0,0,1397,0,0,932,0,0,1175,0,0,1244,0,0,1175,0,0,932,0,0,1046,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,0,0,0,2794,0,0,0,0,3136,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,1397,0,0,0,2350,0,0,0,2489,0,0,0,2350,0,0,0,0,2093,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865};
int tiempoGOT[518] = {900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1400,1400,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,116,267,28,267,28,267,28,900,89,900,89,1400,89,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,69,7,69,7,69,7,69,7,267,28,400,45,133,13,267,28,267,28,267,28,300,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,900,89,900,133,13,150,133,13,150,1200,1800,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,267,28,1200,400,133,13,133,13,150,900,89,900,900,89,900,600,59,600,267,28,300,600,59,600,267,28,300,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,133,13,267,28,267,28,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,900,89,900,900,900,900,89,900,900,900,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,600,212,133,13,150,150,267,28,300,300,400,45,450,450,133,13,150,150,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400,116,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400};

int frecuenciaTetris[55] = {1319,988,1047,1175,1047,988,880,880,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,1175,1397,1760,1568,1397,1319,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,659,523,587,494,523,440,415,659,523,587,494,523,659,880,831};
int tiempoTetris[55] = {450,225,225,450,225,225,450,225,225,450,225,225,450,225,225,450,450,450,450,450,675,450,225,450,225,225,675,225,450,225,225,450,225,225,450,450,450,450,450,450,900,900,900,900,900,900,1800,900,900,900,900,450,450,900,1800};

int frecuenciaStarwars[59] = {523,0,523,0,523,0,698,0,1046,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,1760,0,0,784,0,523,0,0,523,0,0,523,0};
int tiempoStarwars[59] = {134,134,134,134,134,134,536,134,536,134,134,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,429,357,1071,268,67,67,268,67,67,67,67,67};


volatile int flags = 0;

// Metodo espera hasta la proxima activacion del reloj
void delay_until (unsigned int next) {
	unsigned int now = millis();

	if (next > now) {
		delay (next - now);
	}
}

// FUNCIONES DE ENTRADA. Estos metodos se encargan de comprobar la activacion de los diferentes flags
// que componen el programa.

int CompruebaPlayerStart(fsm_t* this) {    // Metodo que comprueba la inicializacion del reproductor.
	int result;

	piLock (FLAGS_KEY);                       // Bloqueamos el flag para que nadie mas lo pueda usar a la vez
	result = (flags & FLAG_PLAYER_START);     // Comprobamos la activacion del flag y la guardamos en la variable result
	piUnlock (FLAGS_KEY);                     // Desbloqueamos de nuevo el flag.

	return result;
}

int CompruebaPlayerStop(fsm_t* this) {    // Metodo que comprueba si hay que parar el reproductor.
	int result;

	piLock (FLAGS_KEY);                    // Bloqueamos el flag para que nadie mas lo pueda usar a la vez
	result = (flags & FLAG_PLAYER_STOP);   // Comprobamos la activacion del flag y la guardamos en la variable result
	piUnlock (FLAGS_KEY);                  // Desbloqueamos de nuevo el flag.

	return result;
}

int CompruebaNuevaNota(fsm_t* this) {      // Metodo que comprueba si hay que pasar a la siguiente nota
	int result;

	piLock (FLAGS_KEY);                    // Bloqueamos el flag para que nadie mas lo pueda usar a la vez
	result = (flags & FLAG_PLAYER_END);    // Comprobamos la activacion del flag y la guardamos en la variable result
	piUnlock (FLAGS_KEY);                  // Desbloqueamos de nuevo el flag.

	return !result;
}

int CompruebaNotaTimeout(fsm_t* this) {    // Metodo que comprueba si ha acabado la reprodcucción de una nota.
	int result;

	piLock (FLAGS_KEY);                    // Bloqueamos el flag para que nadie mas lo pueda usar a la vez
	result = (flags & FLAG_NOTA_TIMEOUT);  // Comprobamos la activacion del flag y la guardamos en la variable result
	piUnlock (FLAGS_KEY);                  // Desbloqueamos de nuevo el flag.


	return result;
}

int CompruebaFinalMelodia(fsm_t* this) {   // Metodo que comprueba si ha acabado la reproducción de la melodía
	int result;

	piLock (FLAGS_KEY);                    // Bloqueamos el flag para que nadie mas lo pueda usar a la vez
	result = (flags & FLAG_PLAYER_END);    // Comprobamos la activacion del flag y la guardamos en la variable result
	piUnlock (FLAGS_KEY);                   // Desbloqueamos de nuevo el flag.

	return result;
}



// Este metodo se encarga de inicializar cada una de las melodias, introduciendo todos los datos necesarios para ello:
// nombre, array de frecuencias, array de duraciones y numero de notas.
int InicializaMelodia (TipoMelodia *melodia, char *nombre, int *array_frecuencias, int *array_duraciones, int num_notas) {
	int i;

	for(i=0; i<num_notas; i++){                 // Introducimos las frecuencias y duraciones una a una recorriendo el array.
		melodia->frecuencias[i] = array_frecuencias[i];
		melodia->duraciones[i] = array_duraciones[i];
	}

	strcpy(melodia->nombre , nombre);       //copiamos el nombre de la melodia haciendo una copia de strings.


	melodia -> num_notas = num_notas;       // Introducimos el numero de notas

	return melodia->num_notas;              // Devuelve melodía
}

// Metodo que se encarga de inicializar el reproductor.
void InicializaPlayer (fsm_t* this){
	TipoPlayer *p_player;                         // Inicializamos el reproductor.
	p_player = (TipoPlayer*) (this->user_data);

	piLock (FLAGS_KEY);                          // Bloqueamos los flags para se interrumpan durante la ejecución de un proceso.
	flags &= ~FLAG_PLAYER_END;                   // Ponemos los flags de nuevo a 0 y desbloqueamos de nuevo
	flags &= ~FLAG_PLAYER_STOP;
	flags &= ~FLAG_NOTA_TIMEOUT;
	flags &= ~FLAG_PLAYER_START;
	piUnlock (FLAGS_KEY);


	p_player -> posicion_nota_actual = 0;               // Inicializamos poniendo al reproductor en la primera posicion de las notas.
	p_player -> duracion_nota_actual = p_player->melodia->duraciones[0];
	p_player -> frecuencia_nota_actual = p_player->melodia->frecuencias[0];

	tmr_startms(p_player->tmr, p_player->duracion_nota_actual);   // comprueba cuanto debe durar la reproduccion de cada nota
	softToneWrite(18, p_player->frecuencia_nota_actual);      // produce onda cuadrada con la frecuencia correspondiente a cada nota.
	softToneWrite(22, 0);
	softToneWrite(23, 500);
	softToneWrite(24, 0);

	piLock (STD_IO_BUFFER_KEY);                                // Bloquea el buffer para que solo este proceso pueda escribir por pantalla
	printf("\n[PLAYER][InicializaPlayer]\n");
	printf("[PLAYER][InicializaPlayer][NOTA %i][FREC %i][DURA %i]\n",p_player->posicion_nota_actual + 1, p_player->frecuencia_nota_actual, p_player->duracion_nota_actual);
	fflush(stdout);
	piUnlock (STD_IO_BUFFER_KEY);                             // Desbloquea el buffer
}

// metodo que se encarga de actualizar el reproductor a la posicion de la siguiente nota que debe reproducir
void ActualizaPlayer (fsm_t* this){
	TipoPlayer *p_player;
	p_player = (TipoPlayer*) (this->user_data);

	if (p_player->posicion_nota_actual >= p_player->melodia->num_notas - 1) {  // comprueba si se ha acabado la melodia comparando la nota actual con la ultima nota de la melodia
		piLock(FLAGS_KEY);               // Si se acaba la melodia activamos el flag de finalizacion de melodia bloqueando y desbloqueando antes y despues respectivamente
		flags |= FLAG_PLAYER_END;
		piUnlock(FLAGS_KEY);
		piLock(STD_IO_BUFFER_KEY);
		printf("[PLAYER][ActualizaPlayer][REPRODUCIDAS TODAS LAS NOTAS]\n");
		fflush(stdout);
		piUnlock(STD_IO_BUFFER_KEY);
	} else {
		p_player->posicion_nota_actual += 1;     // pasamos a la siguiente nota
		p_player->frecuencia_nota_actual = p_player->melodia->frecuencias[p_player->posicion_nota_actual];
		p_player->duracion_nota_actual = p_player->melodia->duraciones[p_player->posicion_nota_actual];
		piLock(STD_IO_BUFFER_KEY);
		printf("[PLAYER][ActualizaPlayer][NUEVA NOTA ([%i] DE [%i])]\n", p_player->posicion_nota_actual + 1, p_player->melodia->num_notas);
		fflush(stdout);
		piUnlock(STD_IO_BUFFER_KEY);
		softToneWrite(18, p_player->frecuencia_nota_actual);   // Desbloqueamos de nuevo el flag.
	}
	softToneWrite(22, 0);
	softToneWrite(23, 0);
	softToneWrite(24, 500);

	piLock(FLAGS_KEY);
	flags &= ~FLAG_NOTA_TIMEOUT;   // Ponemos el flag de final de nota a 0 bloqueando y desbloqueando antes y despues
	piUnlock (FLAGS_KEY);

}

// metodo encargado de pasar del estado WAIT_END a WAIT_NEXT para pasar a la siguiente nota
void ComienzaNuevaNota (fsm_t* this){
	TipoPlayer *p_player;
	p_player = (TipoPlayer*) (this->user_data);


	tmr_startms(p_player->tmr, p_player->duracion_nota_actual);
	piLock (FLAGS_KEY);
	flags &= ~FLAG_PLAYER_END;                              // Bloqueamos los flags para se interrumpan durante la ejecución de un proceso.
	flags &= ~FLAG_PLAYER_STOP;                             // Ponemos los flags de nuevo a 0 y desbloqueamos de nuevo
	flags &= ~FLAG_NOTA_TIMEOUT;
	flags &= ~FLAG_PLAYER_START;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);
	printf("\n[PLAYER][ComienzaNuevaNota][NOTA %i] [FREC %i][DURA %i]\n", p_player->posicion_nota_actual+1, p_player->frecuencia_nota_actual, p_player->duracion_nota_actual);
	fflush(stdout);
	piUnlock (STD_IO_BUFFER_KEY);
	softToneWrite(22, 0);
	softToneWrite(23, 500);
	softToneWrite(24, 0);
}

// Metodo encargado de detener la reproduccion de la melodia al quitar la tarjeta del detector
void StopPlayer (fsm_t* this){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_PLAYER_END;                            // Bloqueamos los flags para se interrumpan durante la ejecución de un proceso.
	flags &= ~FLAG_PLAYER_STOP;                           // Ponemos los flags de nuevo a 0 y desbloqueamos de nuevo
	flags &= ~FLAG_NOTA_TIMEOUT;
	flags &= ~FLAG_PLAYER_START;
	piUnlock (FLAGS_KEY);

	softToneWrite(18, 0);    // Crea una onda cuadrada de frecuencia 0

	softToneWrite(22, 500);
	softToneWrite(23, 0);
	softToneWrite(24, 0);
	piLock (STD_IO_BUFFER_KEY);
	printf("\n[PLAYER][StopPlayer]\n");
	fflush(stdout);
	piUnlock (STD_IO_BUFFER_KEY);

}

// Metodo que se encarga de la finalizacion de la melodia cuando ya no quedan notas por reproducir
// y asi pasar de nuevo al estado de inicio
void FinalMelodia (fsm_t* this){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_PLAYER_END;
	piUnlock (FLAGS_KEY);

	softToneWrite(18, 0);  // Crea una onda cuadrada de frecuencia 0.

	softToneWrite(22, 500);
	softToneWrite(23, 0);
	softToneWrite(24, 0);

	piLock (STD_IO_BUFFER_KEY);
	printf("\n[PLAYER][FinalMelodia][REPRODUCIDAS TODAS LAS NOTAS]\n");
	fflush(stdout);
	piUnlock (STD_IO_BUFFER_KEY);

}


// Metodo que lee la entrada proviniente de el detector de tarjetas
// y activa un flag u otro dependiendo de la salida del mismo.
void Flanco (void){
	int estado = digitalRead(5);
	if(estado == 0){      // Si el estado es 0 empieza la melodia
		piLock (FLAGS_KEY);
		flags |= FLAG_PLAYER_START;
		piUnlock (FLAGS_KEY);
	} else {              // si el estado es 1 la detiene.
		piLock (FLAGS_KEY);
		flags |= FLAG_PLAYER_STOP;
		piUnlock (FLAGS_KEY);
	}
}




//------------------------------------------------------
// FUNCIONES DE INICIALIZACION
//------------------------------------------------------

// int systemSetup (void): procedimiento de configuracion del sistema.
// RealizarÃ¡, entra otras, todas las operaciones necesarias para:
// configurar el uso de posibles librerÃ­as (e.g. Wiring Pi),
// configurar las interrupciones externas asociadas a los pines GPIO,
// configurar las interrupciones periÃ³dicas y sus correspondientes temporizadores,
// crear, si fuese necesario, los threads adicionales que pueda requerir el sistema
int systemSetup (void) {
	// A completar por el alumno...
	// ...

	int x = 0;

	// sets up the wiringPi library
	if (wiringPiSetupGpio () < 0) {
		piLock (STD_IO_BUFFER_KEY);
		printf ("Unable to setup wiringPi\n");
		piUnlock (STD_IO_BUFFER_KEY);
		return -1;
	}

	pinMode(18, OUTPUT);
	softToneCreate(18);
	pinMode(22, OUTPUT);
	softToneCreate(22);
	pinMode(23, OUTPUT);
	softToneCreate(23);
	pinMode(24, OUTPUT);
	softToneCreate(24);


	// Lanzamos thread para exploracion del teclado convencional del PC
	x = piThreadCreate (thread_explora_teclado);

	if (x != 0) {
		piLock(STD_IO_BUFFER_KEY);
		printf ("it didn't start!!!\n");
		piUnlock (STD_IO_BUFFER_KEY);
		return -1;
	}
	return 1;
}

// Metodo que configura la maquina de estados. Dentro del método llamamos a FinalMelodia
// para asegurarnos de que el estado inicial del reprdocutor es WAIT_START y
// no hay nada reproduciéndose.

void fsm_setup(fsm_t* reproductor_fsm) {
	piLock (FLAGS_KEY);
	flags = 0;
	piUnlock (FLAGS_KEY);

	FinalMelodia(reproductor_fsm);

	piLock (STD_IO_BUFFER_KEY);
	printf("\nInserte tarjeta para comenzar la reproduccion y retirela para terminarla.\n");
	fflush(stdout);
	piUnlock (STD_IO_BUFFER_KEY);
}

// función para emplear temporizadores
void timer_isr(union sigval value) {
	piLock(FLAGS_KEY);
	flags |= FLAG_NOTA_TIMEOUT;
	piUnlock(FLAGS_KEY);
}


PI_THREAD (thread_explora_teclado) {
	int teclaPulsada;


	while(1) {
		delay(10); // Wiring Pi function: pauses program execution for at least 10 ms



		if(kbhit()) {
			teclaPulsada = kbread();
			//printf("Tecla %c\n", teclaPulsada);

			switch(teclaPulsada) {
			case 's':


				break;

			case 't':

				break;

			case 'p':
					piLock (FLAGS_KEY);
					flags |= FLAG_PLAYER_STOP;
					piUnlock (FLAGS_KEY);
					piLock(STD_IO_BUFFER_KEY);
					printf("Tecla Pulsada 'p'\n");
					fflush(stdout);
					piUnlock(STD_IO_BUFFER_KEY);
					break;

				case 'q':
					exit(0);
					break;

				default:
					piLock(STD_IO_BUFFER_KEY);
					printf("INVALID KEY!!!\n");
					fflush(stdout);
					piUnlock(STD_IO_BUFFER_KEY);
					break;
			}
		}
	}
}

//Metodo principal del programa que lo inicializa y comienza la maquina de estados.
int main () {
	unsigned int next;
	TipoSistema sistema;

	TipoMelodia melodiaTetris;
	//TipoMelodia melodiaGOT;
	//TipoMelodia melodiaStarwars;
	//TipoMelodia melodiaDespacito;
	//melodiaSeleccionada = melodiaTetris;
	//seleccion = InicializaMelodia(&melodiaTetris, "Tetris", frecuenciaTetris, tiempoTetris, 55);

	sistema.player.melodia = &melodiaTetris;
	sistema.player.tmr = tmr_new(timer_isr);
	if(InicializaMelodia(&melodiaTetris, "Tetris", frecuenciaTetris, tiempoTetris, 55)<0) {
		piLock(STD_IO_BUFFER_KEY);
		printf("[ERROR!!!][InicializaMelodia]\n");
		fflush(stdout);
		piUnlock(STD_IO_BUFFER_KEY);
	}



	// Maquina de estados: lista de transiciones
	// {EstadoOrigen, Funciï¿½nDeEntrada,EstadoDestino,Funciï¿½nDeSalida}

	fsm_trans_t reproductor[] = {
			{ WAIT_START, CompruebaPlayerStart, WAIT_PUSH, InicializaPlayer },
			{ WAIT_PUSH, CompruebaPlayerStop, WAIT_START, StopPlayer },
			{ WAIT_PUSH, CompruebaNotaTimeout, WAIT_END, ActualizaPlayer },
			{ WAIT_END, CompruebaFinalMelodia, WAIT_START, FinalMelodia },
			{ WAIT_END, CompruebaNuevaNota, WAIT_PUSH, ComienzaNuevaNota },
			{-1, NULL, -1, NULL },
	};

	fsm_t* player_fsm = fsm_new (WAIT_START, reproductor, &(sistema.player));

	// Configuracion e inicializacion del sistema

	systemSetup();

	fsm_setup(player_fsm);

	pinMode (5, INPUT);
	wiringPiISR (5, INT_EDGE_BOTH, Flanco);


	next = millis();
	while (1) {
		fsm_fire (player_fsm);
		next += CLK_MS;
		delay_until (next);
	}
	fsm_destroy (player_fsm);
}
