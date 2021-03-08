/* ALSE-1 ______Laboratorio 3____
 * Este laboratorio se realiza con el fin de implementar las buenas practicas,procesos, archivos y comunicacion entre ellos
 * Christian Camilo Lara ---- Daniel Eduardo Rodriguez ----Paula Andrea Melo*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define LIMITE_CADENA 100
#define LIMITE_DATOS 5


/*Prototipo*/
void tomar_valores(double *valores, char *cadena);
void cargar_datos(double *valores,double *valores2,char* path);
double promedio(double* valores);
double desviacion_estandar(double* valores);
void maximo_minimo(double* valores,FILE* arch1);
void todo(double* valores,FILE* arch1,int numero);
void comparar(double* valores,double* valores2,FILE* arch1);
void comparar_suma(double* valores,double* valores2,FILE* arch1);


int main(int argc, char *args[]){ //se reciben dos parámetros
	int menu = 0;
	double valores[LIMITE_DATOS + 1]; //arreglo 1
	double valores2[LIMITE_DATOS + 1]; //arreglo2
	double avg,desvest;
	FILE* arch1;//FILE	es el descriptor del archivo, es una referencia al archivo de salida, *arch1 abre el archivo de salida
	cargar_datos(valores,valores2,args[1]);//arg[1] manda la primera ruta que se encuentra, el .csv
    arch1 = fopen(args[2], "w"); //args[2] ruta del archivo de salida, w para borrar todo lo que hay en el .txt y escribir sobre ese archivo
    fprintf (arch1, "RESPUESTAS \n"); //fprint me imprime dentro del arch1  
	avg = promedio(valores); //se imprime dentro del archivo
	fprintf (arch1, "Promedio: %.3lf \n", avg); //igual se imprime...%.31f numeros con coma flotante con tres números después de la coma
	desvest = desviacion_estandar(valores);//igual se imprime...
	fprintf (arch1, "Desviacion estandar: %.3lf \n", desvest);
	maximo_minimo(valores,arch1); //además de la lista de los valores se envía el archivo donde se debe escribir (arch1) 
	todo(valores,arch1,1);//imprime todos los números que encuentra
	todo(valores2,arch1,2);
	comparar(valores,valores2,arch1);
	comparar_suma(valores,valores2,arch1);
	fclose(arch1); //cerrar archivo   
	
    return 0;
}

void tomar_valores(double *valores, char *cadena){
   	const char split[2] = ";";//dentro de split[2] se guarda el ; que es el separador de los números, es una cadena de solo ;
	int cont = 1;
    char *valor	 = strtok(cadena, split);// con strtok se manda una cadena con el ; y ella me devuelve un apuntador hacia los valores que va encontrando
    
    if(valor != NULL){
        while(valor != NULL && cont < LIMITE_DATOS + 1){
        	valores[cont] = atof(valor);//a valores que es el vector que llega le asigno el resultado de la funcion atof que convirte una string a un número con coma
            valor = strtok(NULL, split);
            cont++;
        }
    }
    
    valores[0] = cont - 1;// se pone la cantidad de elementos en la posicion 0
}

void cargar_datos(double *valores,double *valores2,char* path){ // se envían el arreglo1, el arreglo2 y el path que el la ruta de almacenamiento donde está el .csv
	char datos1 [LIMITE_CADENA]; //se declaran dos cadenas de texto
	char datos2 [LIMITE_CADENA];
    FILE* arch1; //arch1 es el descriptor del archivo, donde se va a escribir y leer dentro del archivo
    arch1 = fopen(path, "rt"); //fopen envío la ruta y el rt que me permite leer el archivo, se utiliza rt para abrir el archivo en modo texto
    fgets (datos1, LIMITE_CADENA, arch1); //fgets guarda los caracteres del arch1 en datos1
    fgets (datos2, LIMITE_CADENA, arch1); //lo mismo para el segundo vector a leer   
    fclose(arch1); //cierra los archivos
    
    tomar_valores(valores,datos1); //vector 1 del .csv
    tomar_valores(valores2,datos2); //vector 2 del .csv
}

double promedio(double* valores){//se envían los valores
	double cantidad = valores[0], suma = 0;//cantidad será valores[0]
	int i;
	double avg;
	
	for (i = 1; i <= cantidad;i++){//se hace un ciclo por toda la cadena hasta la cantidad se inicia desde 1 porque la vector[0] es la canrtidad y no se necesita
		suma += valores[i];//suma de valores
	}
	
	avg = (double)suma/cantidad;//formula para el promedio
	
	return avg;
}

double desviacion_estandar(double* valores){//se reciben los valores
	double avg = promedio(valores),desvest,suma=0;// se guarda el primedio en un variable, se declara otra variable para guardar la desv. estándar y una variable suma
	double cantidad = valores[0];
	int i;
	
	for (i = 1; i <= cantidad;i++){
		double potencia = pow(valores[i]-avg,2);// se guarda el primedio en un variable, se declara otra variable para guardar la desv. estándar y una variable suma
		suma += potencia;//suma = suma + potencia
	}
	
	desvest = (double)suma/(cantidad-1);//division entre la cantidad de elementos menos 1 por fórmula de desv. estándar
	desvest = sqrt(desvest);
	
	return desvest;
}

void maximo_minimo(double* valores,FILE* arch1){//se empieza a comparar desde el primer elemento
	double max = valores[1], min = valores[1],cantidad = valores[0];
	int i;
	
	for (i = 1; i <= cantidad;i++){//se va modificando el máx el min dependiendo la posicion
		if(valores[i] > max){
			max = valores[i];
		}
		if(valores[i] < min){
			min = valores[i];
		}
	}
	fprintf (arch1, "Minimo: %.3lf\n",min); //en arch1 se escribe el mínimo
	fprintf (arch1, "Maximo: %.3lf\n",max); //en arch1 se escribe el máximo
	
}

void todo(double* valores,FILE* arch1,int numero){//se hacen todas la operaciones al tiempo 
	double cantidad = valores[0];
	int i;
	fprintf(arch1,"Valores del vector %d: ",numero);
	
	for (i = 1; i < cantidad;i++){
		fprintf(arch1,"%.3lf,",valores[i]);
	}
	
	fprintf(arch1,"%.3lf\n",valores[i]);
}

void comparar(double* valores,double* valores2,FILE* arch1){//compara posicion por posicion ambos vectores
	int cantidad = valores[0],i;
	int cantidad2 = valores2[0];
	fprintf(arch1,"Comparaciones: \n");
	if (cantidad!=cantidad2){//si las cantidades son diferentes no se puede hacer una comparacion posicion por posicion
		fprintf(arch1,"No se puede hacer comparacion punto a punto\n");
		
	}else{
		for (i = 1; i <= cantidad;i++){
			if(valores[i] > valores2[i]){//comparaciones si son mayores, menores o iguales posicion por posicion
				fprintf(arch1,"Para la posicion %d el valor del primer vector es mayor respecto a la misma posicion del segundo vector: %.3lf > %.3lf\n",i,valores[i],valores2[i]);
			}else if (valores[i] == valores2[i]){
				fprintf(arch1,"Para la posicion %d los valores son iguales %.3lf = %.3lf\n",i,valores[i],valores2[i]);
			}else{
				fprintf(arch1,"Para la posicion %d el valor del primer vector es menor respecto a la misma posicion del segundo vector:  %.3lf < %.3lf\n",i,valores[i],valores2[i]);
			}
		}
	}
}

void comparar_suma(double* valores,double* valores2,FILE* arch1){//comparar la suma de los valores de los dos vectores
	double cantidad = valores[0];
	double cantidad2 = valores2[0];
	double suma=0,suma2=0;// dos variables para las sumas independientes
	int i;
	
	for (i = 1; i <= cantidad;i++){//suma de los elementos cadena 1
		suma+=valores[i];
	}
	
	for (i = 1; i <= cantidad2;i++){//suma de los elementos cadena2
		suma2+=valores2[i];
	}
	
	if(suma > suma2){
		fprintf(arch1,"La suma del arreglo 1 es mayor: %.3lf > %.3lf\n",suma,suma2);//comparaciones
	}else if(suma == suma2){
		fprintf(arch1,"La suma de los arreglos es igual: %.3lf = %.3lf\n", suma,suma2);
	}else{
		fprintf(arch1,"La suma del arreglo 1 es menor: %.3lf < %.3lf\n",suma,suma2);
	}
}

