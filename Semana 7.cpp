//Declaración de bibliotecas
#include <iostream>
#include <conio.h>
#include <string.h>
 

using namespace std;

 

//Estructura para control de libros
struct libros{
	char nombre[30];
	char autor[30];
	int edicion;
}libros;

 

//Funciones (SON VACIAS)
void iLibro();//Función para registrar los libros
void sLibro();//Función para ver los registros
void uLibro();//Función para actualizar los datos
void dLibro();//Función para eliminar los libros

 

//Función principal (LA DE SIEMPRE)
int main() {

	cout<<"\n\n\n\t\tBienvenidos";
	cout<<"\n\n\n\t\tPulsa ENTER para ingresar";
	getch();
	system("cls");//Es un comando usado para limpiar la pantalla

	int op; //Para almacenar la opción del usuario
	//Estructura del Menú
	do{
		cout<<"\n\n\t\tBilbioteca San Juan";
		cout<<"\n\n\t1. Registrar Libros";
		cout<<"\n\n\t2. Registro de Libros";
		cout<<"\n\n\t3. Actualizar Datos";
		cout<<"\n\n\t4. Eliminar Libro";
		cout<<"\n\n\t5. Salir";
		cout<<"\n\n\tElija una opción:";
		cin>>op;
		//Programación de la funcionalidad del menú
		switch(op){
			case 1:{
				iLibro();//Llamada a la función
				getch();
				system("cls");
				break;
			}
            case 2:{
				sLibro();//Llamando a la función
				getch();
				system("cls");
				break;
		}
		case 3:{
			uLibro();
			getch();
			system("cls");
			break;
		}
	}
	}while(op !=5);
    
	return 0;
}

 

//Funcionalidad de la función del Registro de los libros
void iLibro(){
	char s; //Variable para finalizar el ingreso de los libros
	FILE *fp; //Variableque solo maneja archivos
	do{
		fp = fopen("Biblioteca.txt","a+b");//Parametro a para agregar texto, y el parametro b, para guardar en binario
		system("cls");
		cout<<"\n\n\n\t\tRegistrar Libro\n";
		cout<<"\n\tNombre del Libro: ";
		cin.ignore();
		cin.getline(libros.nombre, sizeof(libros.nombre));
		cout<<"\n\tNombre del Autor: ";
		cin.getline(libros.autor, sizeof(libros.autor));
		cout<<"\n\tEditorial: ";
		cin>>libros.edicion;
		fwrite(&libros, sizeof(libros),1,fp);//Para escribir los daos
		fclose(fp);//Cerrar conexión con el .txt

		cout<<"\n\n\n\t\tIngrese un 1 para resitrar otro libro, 0 para salir";
		cin>>s;
	}while(s !='0');
}

void sLibro(){
	FILE *fp;
	fp = fopen("Biblioteca.txt","r+b");
	system("cls");
	cout<<"\n\n\n\t\tLibros Registrados\n";
	while(!feof(fp)){
		fread(&libros, sizeof(libros),1,fp);
		cout<<"\nNombre del libro: ";
		cout<<libros.nombre;
		cout<<"\nNombre del autor: ";
		cout<<libros.autor;
		cout<<"\nAño de Edición; ";
		cout<<libros.edicion;
		cout<<"\n\n";
	}
	fclose(fp);
	cout<<"Preciones cuaquier tecla para salir: ";
}

void uLibro(){
	char buscarnombre[30];
	bool encontrado = false;
	FILE *fp;
	FILE *tempFile;
	
	system("cls");
	cout<<"\n\n\n\n\t\tActualizar Datos de un Libro\n";
	cout<<"\n\tIngrese el nombre del libro a actualizar ";
	cin.ignore();
	cin.getline(buscarnombre, sizeof(buscarnombre));
	fp = fopen("Biblioteca.txt","r+b");
	tempFile = fopen("tempBiblioteca.txt","w+b");

	while(fread(&libros, sizeof(libros),1,fp)==1){
		if(strcmp(libros.nombre,buscarnombre)==1){
			encontrado = true;
			cout<<"\n\tNuevo nombre: ";
			cin.ignore();
			cin.getline(libros.nombre, sizeof(libros.nombre));
			cout<<"\n\tNuevo Autor: ";
			cin.getline(libros.autor, sizeof(libros.autor));
			cout<<"\n\tAño de edicion ";
			cin>>libros.edicion;
		}
		fwrite(&libros, sizeof(libros) ,1, tempFile);
	}
	fclose(fp);
	fclose(tempFile);
	if(encontrado==true){
		remove("Biblioteca.txt");
		rename("tempBiblioteca.txt","Biblioteca.txt");
		cout<<"\n\tDatos fueron actualizados...";
		
	}else{
		cout<<"\n\tDatos no fueron actualizados...";
	}
}
