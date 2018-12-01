#include <stdio.h>
#include <stdlib.h>
#include <windows.h>//libreria para el color
#include <locale.h>
#include <time.h>

#define TAMANHO 8

struct Estado
{

int Num_fichas;//variable que cuenta el numero de fichas que hay en el tablero
int Cont_jugador;//variable que indica el turno del jugador
int Mov_invalidos;//variable que lleva la cuenta de movimientos invalidos
int Opcion_juego;//Variable que sirve para que si el usuario lo desea no le vuelva a aparecer el menu de guardar a lo largo de la partida
char jugador;//Variable que contiene la ficha del jugador al que le toca

	
};

struct Jugada
{
	int Fila_jugada;//variable que continene la fila introducida por el jugador
	char Columna_jugada;//variable que contiene la columna introducida por el jugador
};


//FUNCIONES

int Menu_principal();
int Menu_juego (char tablero[TAMANHO][TAMANHO],struct Estado E);
int Guardar_partida (char tablero[TAMANHO][TAMANHO],struct Estado E);
int Validar_movimientos (char tablero[TAMANHO][TAMANHO],int Movimientos_validos[TAMANHO][TAMANHO],struct Estado E);	
void Hacer_movimientos (char tablero[TAMANHO][TAMANHO],struct Jugada J,struct Estado E);
void Puntuacion (char tablero[TAMANHO][TAMANHO]);
void Turno_jugador(char tablero[TAMANHO][TAMANHO], struct Estado *E);
void Partida(char tablero[TAMANHO][TAMANHO],struct Estado E);
void Inicializar_tablero(char tablero[TAMANHO][TAMANHO],struct Estado *E);
void Cargar_partida(char tablero[TAMANHO][TAMANHO],struct Estado *E);
void SetColor(int Color);
void Visualizar_tablero(char tablero[TAMANHO][TAMANHO]);
void Tiempo_de_ejecucion();


int main()
{	
	setlocale(LC_CTYPE, "Spanish");//Función que permite que los acentos se visualicen por pantalla.
	
	struct Estado E;//Estructura estado en la que almacenamos los valores Num_Fichas,Cont_jugador,Mov_invalidos,Opcion_juego,jugador
	E.Cont_jugador= 0; 
	E.Mov_invalidos = 0;
	E.Num_fichas = 0;
	E.Opcion_juego = 0;
	E.jugador;
	char tablero[TAMANHO][TAMANHO];//Array con el tablero del juego, sirve para introducir las fichas  

    Tiempo_de_ejecucion(); //Iniciamos el reloj

	switch(Menu_principal())
	{
		case 1://Prepara la configuracion del tablero para empezar una nueva partida
			
			Inicializar_tablero(tablero,&E);
			break;
		
		case 2://funcion para cargar una partida guardada
			
			Cargar_partida(tablero,&E);
			break;
		
		case 4:	//Sale del juego
		
			printf("\n\n\n\n\n\n\t\tMUCHAS GRACIAS POR JUGAR CON NOSOTROS!!!:D\n\n\n\n\n\n");
			exit(0);//Función que hace que el programa se cierre.
			break;
			
		default: break;
	}
	
	
	
	Partida(tablero,E);
	
	Visualizar_tablero(tablero);//Muestra el tablero con posición final
		
	Puntuacion(tablero);//Imprime la puntuación de cada jugador
	
	system("cls");
			
	

	return main();//Vuelve a empezar el juego(vuelve al menu)
}

/*FUNCION DEL MENU PRINCIPAL
En esta función se imprimer las opciones que puede escoger el usuario.
Si escoge la opcion instrucciones, se le imprimirá por pantalla las 
instruciones del juego,y si escoge otra opcion esta función devolverá
el valor asociado a esa opción
*/
int Menu_principal()
{
	
	int opcion = 0;//Guarda el valor de la opcion que escoge el usuario
	
	
	SetColor(10);
	printf("\n\tBIENVENIDO AL REVERSI!UN REVERSI PUJANTE!!UN REVERSI EMPRENDEDOR! \n\n");
	SetColor(15);
	
	
	do
	{
		fflush(stdin);
		SetColor(15);
		printf("\n\n\t\t\t\t     REVERSI\n\n\n");
		printf("\t\t\t      Introduzca una opción:\n\n");
		printf("\t\t\t---------------------------------");
		printf("\n\n\t\t\t| 1.Nueva partida\t\t|\n\n\t\t\t| ");
		printf("2.Cargar partida anterior     |\n\n\t\t\t| ");
		printf("3.Instruciones\t        |\n\n\t\t\t| ");
		printf("4.Salir del juego.            |\n");
		printf("\t\t\t---------------------------------");
		SetColor(11);
		printf("\n\t\t\t     La opción escogida es: ");
		scanf("%d",&opcion);
		system("cls");//Limpiamos pantalla

		//Muestra las instruciones,y luego vuelve al menú
		if(opcion==3)
		{
			system("cls");
			SetColor(10);
			printf("Como se juega al reversi?\n\n\n");
			SetColor(12);
			printf("MOVIMIENTOS:\n\n");
			SetColor(11);
			printf("1.Solo podrá incorporarse una ficha flanquendo a una o varias fichas contrarias.\n\n");
			printf("2.Cada vez que un jugador incorpora una ficha, y por lo tanto encierra a otras\n");
			printf("del contrario, debe dar la vuelta a las fichas encerradas convirtiéndolas así \nen propias.\n\n");
			printf("3.Si en una sola incorporación se provocase esta situación de flanqueo en más deuna línea, ");
			printf("se voltearán todas las fichas contrarias que estuvieran implicadas encada uno de los flanqueos.\n\n");
			printf("4.Si no fuera posible para un jugador encerrar a ninguna ficha, deberá pasar en su turno, volviendo el mismo a su oponente.\n\n");
			SetColor(12);
			printf("AL TERMINAR LA PARTIDA:\n\n");
			SetColor(11);
			printf("\n1.La partida finaliza cuando todas las casillas del tablero son ocupadas \no ninguno de los 2 jugadores tiene posibilidad de incorpar una nueva ficha.\n\n");
			printf("2.Gana el jugador con más fichas en el tablero.\n\n");
			SetColor(15);
			system("pause");
			
			system("cls");
		}
	
	
	if(opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4)
	{	
		system("cls");
		SetColor(12);
		printf("La opción introducida es incorrecta, vuelva a introducirla: ");
	
	}
	
	}while(opcion != 1 && opcion != 2 && opcion!= 4);
	

	return opcion;//Devuelve el valor de opcion
	
}


/*Función que vacía el tablero para empezar la partida  e inicializa el numero de fichas a 4*/
void Inicializar_tablero(char tablero[TAMANHO][TAMANHO],struct Estado *E)
{
	int i = 0,j = 0;
		//el numero de fichas del tablero al principio son 4.
		
		E->Num_fichas = 4;
		//Inicializamos el array del tablero a 0, ya que este bucle se va a repetir cuando el usuario acabe la partida y quiera volver a jugar
		for(i = 0;i < TAMANHO;i++)
		{
			for(j = 0;j < TAMANHO;j++)
			{
				tablero [i][j] = ' ';
			}
		}
		
		//Ponemos las cuatro fichas que aparecen en el tablero por defecto
		tablero[(TAMANHO/2)-1][(TAMANHO/2)-1] = tablero[TAMANHO/2][TAMANHO/2] = 'O';
 		tablero[(TAMANHO/2)-1][TAMANHO/2] = tablero[TAMANHO/2][(TAMANHO/2)-1] = '#';
			
}

/*Función del tablero
En esta funcion se imprime en pantalla el tablero con la posición actual, 
pasada a través del array tablero[][], el cual tiene las fichas de cada jugador*/

void Visualizar_tablero(char tablero[TAMANHO][TAMANHO])
{
	int i = 0, j = 0;			//Contadores que se usan para los bucles anidados
	char Letra_columna = 'a';	//Letra de las columnas
	
	printf("\n\t\t");
	
	//Coloca las letras de las columnas
	
	for(i = 0;i < TAMANHO;i++)
	{
		printf("   %c",Letra_columna+i);//Va cambiando de letra(a->b->c..) mientras el valor de i sea menor que el tamaño del tablero
	}
	printf("\n\t\t");
	
	//Crea la estructura del tablero y coloca los números de las filas
	
	for(i = 0;i < TAMANHO;i++)
	{
		printf("  +");	//Introduce las esquinas izquierdas
		
		for(j = 0;j < TAMANHO;j++)
		{
			printf("---+");	//Introduce las líneas de las casillas y las esquinas
		}
		
			printf("\n\t\t%2d|", i+1);	//Introduce los números de las filas
		
		for(j = 0;j < TAMANHO;j++)
		{
			if(tablero[i][j] == 'O')
			{
				SetColor(10);
				printf(" %c ", tablero[i][j]);	//Introduce el valor que haya en la posición del tablero indicada
		
			}else 
			{
				SetColor(12);	
				printf(" %c ",tablero[i][j]);
			}
			SetColor(11);
			printf("|");
		}
		
		printf("\n\t\t");
		
	}
	
	printf("  +");	//Introduce la esquina inferior izquierda
	
	for(j = 0;j < TAMANHO;j++)
	{
		printf("---+");	//Introduce la esquina inferior derecha
	}
	
	printf("\n");
	
}


/*FUNCION QUE CARGA UNA PARTIDA GUARDADA
Esta función carga una partida guardada en un archivo .txt. Coloca las fichas
de la anterior partida en el array tablero[][],indica a que jugador le toca
a traves del puntero a la variable Turno_jugador y el modifica el numero de Fichas
que hay a traves del puntero a la variable Num_fichas
*/
void Cargar_partida(char tablero[TAMANHO][TAMANHO],struct Estado *E)
{
	
	int i = 0,j = 0; //Contadores
	char tablero_cargado [TAMANHO*TAMANHO];//Vector con el texto del archivo de la partida guardada
	char jugadorguardado; //variable que guarda e turno del jugador('0' o '1')
	
	
   	FILE *partida = fopen("partida.txt","r");
   	
	if(partida == 0)
	{
  		printf("No existe un archivo con una partida guardada\n\n");
  	 	//vuelve a ejecutarse el main, es decir, aparece el menu
		main();
   
	}else{ 
   
   
		//coge las fichas del fichero partida y las introduce en una cadena llamada tablerocargado
		fgets(tablero_cargado,(TAMANHO*TAMANHO)+1,partida);
     
     
    	for(i = 0;i < TAMANHO;i++)
     	{
       		for(j = 0;j < TAMANHO;j++)
        	{
	         	//Coloca las fichas en la matriz
	       		tablero[i][j] = tablero_cargado [(TAMANHO*i)+j];
	    
       		}
    	}
    	
		//obtiene el turno del jugador(si es un 0 le toca al jugador 1 y si es un 1 le toca al jugador 2  
		jugadorguardado = fgetc(partida);
     
    	if(jugadorguardado == '0')
		{
     		E->Cont_jugador = 0;
     	 
     	}else if(jugadorguardado == '1')
		 {
     		
     		(E->Cont_jugador) = 1;
     	 
    	 }
    	
      //contamos las fichas que hay al cargar la partida
      	E->Num_fichas = 0;
      	
		for(i = 0;i < TAMANHO;i++)
     	{
            for(j = 0;j < TAMANHO;j++)
        	{ 
            	if(tablero[i][j] == 'O' || tablero[i][j] == '#')
        		{
                	(E->Num_fichas)++;
         		}
       		}
     	} 
     	
     	if(fclose(partida) == EOF)
		{
			printf("Error al cerrar partida.txt");
			main();
		}
   
	}
	

	
	
}

//Función para guardar la partida
int Guardar_partida(char tablero[TAMANHO][TAMANHO],struct Estado E)
{
	
	int i = 0,j = 0;//contadores

	
	//abre un fichero para guardar la partida, si existe una ya guardada 
	//se sobreescribe, sino se crea un nuevo fichero
	
	FILE *partida = fopen("partida.txt","w");
	
	//Nos avisa si se abre mal la partida
	
	if(partida == NULL)
	{
		printf("Error al abrir partida.txt");
		return -1;
	}

	//Guarda el tablero en un fichero
	for(i = 0;i < TAMANHO;i++)
	{		
		for(j = 0;j < TAMANHO;j++)
		{			
			fputc (tablero[i][j],partida);						
		}
	}
	
	//Escribe el turno del jugador 2, ya que el jugador 1 ya ha hecho 
	//su movimiento	

	if(E.Cont_jugador == 1)
	{
		fputc('1',partida);
						
	}else if(E.Cont_jugador == 0)
			{
				fputc('0',partida);
			}
						
					
	//Cierra el fichero y avisa si hay un error
	
			
	if(fclose(partida) == EOF)
	{
		printf("Error al cerrar partida.txt");
		return -1;
	}
	
	printf("La partida se ha guardado correctamente");
	
	return 0;
	
}


//Función que va cambiando de jugador hasta que se llena el tablero de fichas o ninguno de los dos jugadores puede mover 
void Partida(char tablero[TAMANHO][TAMANHO],struct Estado E)
{
	
	do
	{
		if(E.Cont_jugador == 0)
		{	
			system("cls");
			SetColor(11);
			//Creamos la visualización del array del tablero
			Visualizar_tablero(tablero);
			
			E.jugador = 'O';
			SetColor(12);
			printf("\nTurno del jugador 'O':\n");
			//Se comrpueba que haya movimientos posibles, y la matriz con las casillas de las jugadas posibles(con 1) 
			//se pasa para poder comparar luego con la casilla introducida por el usuario
			SetColor(11);
			//Realiza las acciones que tienen que ver con el turno del jugador
			Turno_jugador(tablero,&E);
		
		}else if(E.Cont_jugador == 1)
		{
			system("cls");
			SetColor(11);
			Visualizar_tablero(tablero);
			E.jugador = '#';
			SetColor(12);
			printf("\nTurno del jugador '#':\n");
			SetColor(11);
			
			Turno_jugador(tablero,&E);
		}
		
	}while(E.Num_fichas < TAMANHO*TAMANHO && E.Mov_invalidos < 2);

	
	
}


//Función que realiza todo lo referente al turno del jugador
void Turno_jugador(char tablero[TAMANHO][TAMANHO],struct Estado *E)
{
	struct Jugada J;
	J.Fila_jugada = 0;
	J.Columna_jugada;
	int Movimientos_validos[TAMANHO][TAMANHO];	//Array de los movimientos que son válidos
		
		//Comprobamos que hay movimientos validos a realizar
		if(Validar_movimientos(tablero,Movimientos_validos,*E)!=0)
		{
			do
			{
				fflush(stdin);	//Limpia el buffer para evitar problemas con el retorno de carro
				printf("Introduce una jugada(FILA COLUMNA):");
				scanf("%d%c",&J.Fila_jugada,&J.Columna_jugada);	
				//Guardamos las posiciones de la jugada introducida por el usuario
				//Calcula el número de la columna
				J.Columna_jugada = tolower(J.Columna_jugada) - 'a';	
				//Restamos 1 a la fila porque la matriz empieza en 0
				J.Fila_jugada--;	
					
				//Hacemos el movimiento y aumentamos el número de fichas si el movimiento no sale del tablero 
				//y ese movimiento es válido
				
				if(J.Fila_jugada >= 0 && J.Columna_jugada >= 0 && J.Fila_jugada < TAMANHO && J.Columna_jugada < TAMANHO 
				   && (Movimientos_validos [J.Fila_jugada][J.Columna_jugada] != 0))
				{	
					//Si se ha realizado un movimiento invalido, pero el siguiente jugador puede mover se 
					//vuelve a poner el contador a 0
					
					E->Mov_invalidos = 0;
					
					//HACER MOVIMIENTO(cambia las fichas flanqueadas)
					Hacer_movimientos(tablero,J,*E);
				
					//aumenta en uno el contador del numero de fichas del tablero, 
					//para que cuando se llene el tablero, se termine la partida
					(E->Num_fichas)++;
					
					//Para cambiar de jugador en el siguiente turno
				
					if(E->jugador == 'O')
					{
						(E->Cont_jugador)++;
						
					}else{	
					
						(E->Cont_jugador)--;			
					}
						
					
					//Se abre el menu del juego si con anterioridad no se le ha dicho que no se volviese a abrir	
					if((E->Opcion_juego) == 0)
					{
						(E->Opcion_juego) = Menu_juego(tablero,*E);	
					}
					
					if((E->Opcion_juego) == 2)
					{
						//funcion para cargar una partida guardada
						Cargar_partida(tablero,E);
						(E->Opcion_juego) = 0;
					}	
						
				}else 
					{
						printf("La jugada es incorrecta\n");
					}
				}while(J.Fila_jugada < 0 || J.Columna_jugada < 0 || J.Fila_jugada >= TAMANHO || J.Columna_jugada >= TAMANHO 
					|| Movimientos_validos[J.Fila_jugada][J.Columna_jugada] != 1);	
				//Ejecutamos el bucle mientras el movimiento sea inválido(porque en la casilla introducida no tenga un 1 marcandola como movimiento valido o no esté en el tablero(no se pueda realizar el movimiento)

			}else{
					//Si el contador de movimientos inválidos es 1 implica que el jugador 1 
					//no puede hacer un movimiento válido y pasamos al jugador 2
					
					if(++(E->Mov_invalidos)< 2)
					{	
						if(E->jugador == 'O')
						{
							printf("\nEl jugador 1 no puede mover, tiene que pasar\n");
							(E->Cont_jugador)++;
							
						}else if(E->jugador == '#')
						{
							printf("\nEl jugador 2 no puede mover, ten que pasar\n");
							(E->Cont_jugador)--;	
						}
						system("pause");
					}else{
					//Si el contador es 2, ambos jugadores no pueden seguir jugando y se termina la partida
					printf("\nNinguno de losjugadores puede mover,la partida se ha terminado \n");
					}
				}
			
	
	
	
}


//FUNCIÓN DE VALIDAR EL MOVIMIENTO
/*Pasamos a esta función el array con las fichas, un array con los movimientos
 validos(que queremos que nos modifique)y pasamos la ficha que es el jugador.
Comprobamos las casillas en blanco, luego nos movemos en la dirección 
en la cual hemos encontrado una ficha del contraria hasta que encontremos 
una casilla del jugador. Entonces en esa casilla en blanco colocamos un 1 en el 
array,de movimientos validos y devolvemos si hay jugadas posibles.*/
int Validar_movimientos(char tablero[TAMANHO][TAMANHO],int Movimientos_validos[TAMANHO][TAMANHO],struct Estado E)
{

	int i = 0, j = 0; //contadores
	int fila = 0, columna = 0;	//Estas variables guardan la posición inicial de la casilla
	int Fila_lado = 0, Columna_lado = 0;	//Y estas guardan la posición de las casillas que están alrededor
	int x = 0, y = 0;	//Guarda la posición del movimiento a partir de encontra una ficha del oponente
	int Num_movimientos = 0;	//Guarda el número de movimientos(es el valor que devolvemos en la función)
	char oponente;	//Segundo jugador
	
	if (E.jugador == 'O')
	{
		oponente = '#';
		
	}else{
		
		oponente = 'O';
		
	}
	//Inicializa los movimientos válidos del jugador
	for(i = 0;i < TAMANHO;i++)
	{
		for(j = 0;j < TAMANHO;j++)
		{
			Movimientos_validos[i][j] = 0;
		}
	}
	
	for(fila = 0;fila < TAMANHO;fila++)
	{
		for(columna = 0;columna < TAMANHO;columna++)
		{
			/*Si la casilla seleccionada está ocupada, ejecuta este código
			  Localiza las casillas vacias y luego comprueba si se puede 
			  colocaruna ficha del jugador, si cumple las condiciones exigidas*/
			if(tablero[fila][columna] == ' ')
			{
				//Bucles que recorren las casillas que se encuentran alrededor de la casilla seleccionada
				for(Fila_lado = -1;Fila_lado <= 1;Fila_lado++)
				{
					for(Columna_lado =- 1;Columna_lado <= 1;Columna_lado++)
					{
						/*Comprueba que las casillas que se encuentran alrededor no estén fuera del tablero
						  ni que sea la casilla actual*/
						
						if(fila+Fila_lado >= 0 && fila+Fila_lado < TAMANHO &&
						 columna+Columna_lado >= 0 && columna+Columna_lado < TAMANHO 
						 && !(Fila_lado == 0 && Columna_lado == 0))
						{
							//Comprueba que la casilla sea del oponente
							if(tablero [fila+Fila_lado][columna+Columna_lado] == oponente)
							{
								//Guardamos la posición de la fila y la columna de la casilla del oponente
								x = fila+Fila_lado;
								y = columna+Columna_lado;
								
								/*Recorre todas las casillas en la dirección en la que está el oponente 
								  y deja de ejecutarse cuando salga la posición del tablero o cuando la casilla 
								  estea vacía o ocupada por jugador*/
							
								
					            	do{
					            		
		
					           			 x += Fila_lado;         //para dirigirse a la siguiente casilla 						 
					              		 y += Columna_lado;      //en la dirección delta
									
										/*Si la casilla tiene una ficha del jugador
										luego el movimiento es válido*/
										if(tablero[x][y] == E.jugador && x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO && tablero[x][y]!=' ') //&& tablero[x][y]!=' '&& x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO)
										{
						                 	Movimientos_validos[fila][columna] = 1;   // Marcar como válido 
						                 	Num_movimientos++;         // Incrementar el numero de movimientos validos 
						                  
								 		}
								 		
									
							 		}while(x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO && tablero[x][y]!=' ');							
							}
						}
					}
				}
			}
		}

	}
	return Num_movimientos;	//Devolvemos el número de movimientos
}

//FUNCIÓN DE HACER EL MOVIMIENTO
/*Colocamos la ficha en la casilla elegida y recorremos las casillas adyacentes
para encontrar las fichas del oponente y poder moverse en esa dirección.
Luego,si no encuentra una ficha del jugador no hace nada, y si la encuentra
hace cambiar las fichas contrarias hasta volver a la casilla inicial*/
void Hacer_movimientos (char tablero[TAMANHO][TAMANHO],struct Jugada J,struct Estado E)
{
	int Fila_lado = 0, Columna_lado = 0; //contador para recorrer las casillas colindantes
	int x = 0,y = 0;//Guarda la posición del movimiento a partir de encontra una ficha del oponente
	char oponente;	//Variable del segundo jugador
	
	//Transformamos la ficha del oponente dependiendo de como se la del jugador
	if (E.jugador == 'O')
	{
		oponente = '#';
		
	}else{
		
		oponente = 'O';	
		
		}
		
	tablero[J.Fila_jugada][J.Columna_jugada] = E.jugador; //Se coloca la ficha del jugador en la casilla introducida, previamente validada
	
	//Revisamos las casillas de alrededor para encontrar fichas del oponente(doble bucle)
	for(Fila_lado =- 1;Fila_lado <= 1;Fila_lado++)
	{
		
		for(Columna_lado =- 1;Columna_lado <= 1;Columna_lado++)
		{
			
			//si se sale de la matriz al comprobar hacemos con continue que pase a la siguiente casilla a comprobar
			if(J.Fila_jugada + Fila_lado >= 0 && J.Fila_jugada + Fila_lado < TAMANHO && J.Columna_jugada + Columna_lado >= 0 
			&& J.Columna_jugada + Columna_lado < TAMANHO && !(Fila_lado==0 && Columna_lado== 0))
			{
				//si encontramos una ficha del oponente....
				if(tablero[J.Fila_jugada + Fila_lado][J.Columna_jugada + Columna_lado] == oponente)
				{	
					//nos movemos en esa dirección...
					x = J.Fila_jugada + Fila_lado;        		
	         		y = J.Columna_jugada + Columna_lado;
	         		
					do
					{
	         			x += Fila_lado;           	      
		          		y += Columna_lado;
		          		
		          		
	         			
						if(tablero[x][y] == E.jugador)
			            {	
						//cambiamos las fichas del oponente en la direccion contraria a la dada hasta llegar a nuestra ficha
			            	while(tablero[x -= Fila_lado][y -= Columna_lado] == oponente)
						 	{
			               		tablero[x][y] = E.jugador;     
							}                         
			            } 
			           
					 }while(x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO && tablero[x][y] != ' '&& tablero[x][y] != E.jugador);
				}
			
			}
		}
	}
	
}

/*Menú que aparece durante la partida, y da la opción de guardar la partida
 cargar una anterior,no volver a mostrar el menu, continuar partida y salir del juego*/
int Menu_juego (char tablero[TAMANHO][TAMANHO],struct Estado E)
{
	int opcion = 0;
	char opcion1;
	//Pregunta si quiere abrir el menu
	system("cls");
	do
	{
		
		fflush(stdin);//Limpia el buffer
		Visualizar_tablero(tablero);
		SetColor(14);
		printf("\nPulse 's' si desea abrir el menú del juego o 'c' si quiere continuar: ");
		scanf("%c",&opcion1);
		SetColor(11);
		opcion1 = tolower(opcion1);
		if(opcion1 != 's' && opcion1 != 'c')
		{	
			system("cls");
			printf("\nLa opción introducida no es correcta, vuelva a introducirla: \n");
		}
		
	}while(opcion1 != 's' && opcion1 != 'c');
	
	SetColor(3);
	
	switch(opcion1)
	{
	
	case 's'://Abre el menu del juego
			do
			{
				//system("cls");
				//GUARDAR PARTIDA
				fflush(stdin);//Limpia el buffer					
				printf("+------------------------------------------------------------------------------+\n");
				SetColor(10);
				//printf("Quieres guardar la partida? (s/n)\nSi quieres salir de la partida, pulsa 'e'. No molestar mas(`l').cargar partida anterior ('c'): ");
				printf("1.Guardar partida\n2.Cargar partida anterior\n3.No volver a mostrar la opción de abrir el menú del juego hasta acabar el juego4.Salir del juego\n5.Continuar la partida\n");
				SetColor(3);
				printf("\nIntroduzca su opcion: ");
				scanf("%i",&opcion);
				
				if(opcion !=1 && opcion != 2 &&opcion != 3 && opcion != 4&& opcion != 5)
				{
					printf("La opción introducida no es correcta, vuelva a introducirla: ");
				}
						
			}while(opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5);
						
			SetColor(11);
						
			switch (opcion)
			{
			
				case 1://Guardar partida
				
					Guardar_partida(tablero,E);
					
					return Menu_juego(tablero,E);
					
					break;
								
				case 4://Salir del juego
						system("cls");
						printf("\n\n\n\n\n\n\t\tMUCHAS GRACIAS POR JUGAR CON NOSOTROS!!!:D\n\n\n\n\n\n");
						exit(0);
						break;
						
				case 3://No volver a molestar con el menu
						return 1;
						break;
				case 5://Continuar la partida
						return 0;
						break;
						
				case 2://Cargar partida anterior
					
						if(fopen("partida.txt","r") == 0)
						{	
							SetColor(12);
					  		printf("No existe un archivo con una partida guardada\n\n");
					  	 	//vuelve a ejecutarse el main, es decir, aparece el menu
							SetColor(15);
							system("pause");
							SetColor(11);
							return Menu_juego(tablero,E);
					   
						}else{
							return 2;
						}
						break;
						
				default:break; //no realiza ninguna opcion
			}	
							
	case 'c'://Sigue la partida sin abrir el menu del juego
			return 0;
	}	
		
}


//Función para contar la puntuación y lo imrpime por pantalla
void Puntuacion(char tablero[TAMANHO][TAMANHO])
{
	clock_t start;
	
	int Puntuacion_jugador1 = 0;
	int Puntuacion_jugador2 = 0;
	int i = 0,j = 0;//Contadores
	float fin,inicio; //Variables para el funcionamiento del reloj de ejecución.
	
	/*Bucle que recorre el tablero y cuenta las fichas de ambos jugadores*/
	for(i = 0; i < TAMANHO; i++)
	{
       	for(j = 0; j < TAMANHO; j++)
       	{
         	if(tablero [i][j] == 'O')
			{
         		Puntuacion_jugador1++;
         		
			}else if(tablero [i][j] == '#')
				{
      		 
					Puntuacion_jugador2++;
			   	
				}
		}
	}
	system("cls");
	Visualizar_tablero(tablero); 
	SetColor(10);
	printf("\nLA PUNTUACION FINAL ES: \n\n");

	printf("JUGADOR 1 ('O') -------> %i\nJUGADOR 2 ('#')-------> %i\n\n\n",Puntuacion_jugador1,Puntuacion_jugador2);
	SetColor(7);
	fin=clock();
	printf("Tiempo transcurrido: %.2f segundos\n", (fin-inicio)/(double)CLOCKS_PER_SEC);
	
	SetColor(12);
	printf("\nCOMENZANDO UNA NUEVA PARTIDA...\n");
	SetColor(8);
	printf("+------------------------------------------------------------------------------+");
	SetColor(7);
	system("pause");

}

/*Función que inicia un reloj y que usamos para calcular el tiempo desde que inicia
 el programa hasta que se termina la última partida que se juega.Devuelve el  tiempo
usado en la funcion puntuacion.*/
void Tiempo_de_ejecucion()
{
	
	clock_t inicio=0,fin=0;
	inicio=clock();
	fin=clock();
	
	
}

/*Función para poner colores en el texto que sale por pantalla
,usa la librería <windows.h>*/

void SetColor(int Color)
{
	WORD wColor;

 	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	 CONSOLE_SCREEN_BUFFER_INFO csbi;

 	if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 	{
   		wColor = (csbi.wAttributes & 0xF0) + (Color & 0x0F);
      	SetConsoleTextAttribute(hStdOut, wColor);
 	}
 return;
}

