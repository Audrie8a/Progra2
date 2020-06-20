#include <iostream>
#include "Arbol_AVL.h"
#include "Metodos.h"
#include <algorithm>
using namespace std;


NodoArbol* Arbol_AVL::InsertarAVl(NodoArbol* Nuevo, NodoArbol* Nodo)
{
	Metodos* m = new Metodos();
	NodoArbol* nuevoPadre = Nodo;
	//m->Mayor_Menor(Nuevo->ID , Nodo->ID) == "Menor"
	//m->Mayor_Menor(Nuevo->ID,Nodo->derecha->ID)=="Mayor"
	if (m->Mayor_Menor(Nuevo->ID, Nodo->ID) == "Menor") {			 //Si es menor, insertar a la izquierda
		if (Nodo->izquierda == nullptr) {
			Nodo->izquierda = Nuevo;
		}
		else {
			Nodo->izquierda = InsertarAVl(Nuevo, Nodo->izquierda);
			if ((obtenerFe(Nodo->izquierda) - obtenerFe(Nodo->derecha)) == 2) {
				if (Nuevo->ID < Nodo->izquierda->ID) {
					nuevoPadre = SRL(Nodo);
				}
				else {
					nuevoPadre = DRL(Nodo);
				}
			}
		}
	}
	else if (m->Mayor_Menor(Nuevo->ID, Nodo->ID) == "Mayor") {		//Si es menor, insertar a la izquierda
		if (Nodo->derecha == nullptr) {
			Nodo->derecha = Nuevo;
		}
		else {
			Nodo->derecha = InsertarAVl(Nuevo, Nodo->derecha);
			if ((obtenerFe(Nodo->derecha) - obtenerFe(Nodo->izquierda)) == 2) {
				if (m->Mayor_Menor(Nuevo->ID, Nodo->derecha->ID) == "Mayor") {
					nuevoPadre = SRR(Nodo);
				}
				else {
					nuevoPadre = DRR(Nodo);
				}
			}
		}
	}
	else {		//Aceptamos duplicados
		if (Nodo->derecha == nullptr) {
			Nodo->derecha = Nuevo;
		}
		else {
			Nodo->derecha = InsertarAVl(Nuevo, Nodo->derecha);
			if ((obtenerFe(Nodo->derecha) - obtenerFe(Nodo->izquierda)) == 2) {
				if (m->Mayor_Menor(Nuevo->ID, Nodo->derecha->ID) == "Mayor") {
					nuevoPadre = SRR(Nodo);
				}
				else {
					nuevoPadre = DRR(Nodo);
				}
			}
		}
	}

	ActualizarAltura(Nodo);
	return nuevoPadre;
}

void Arbol_AVL::InsertarNodoAVL(string Nombre, string Descripcion,bool estado)
{
	Metodos* m = new Metodos();
	string ID_Activo;
	ID_Activo = m->generarID();
	NodoArbol* nuevo = new NodoArbol(ID_Activo, Nombre, Descripcion,estado);
	if (Raiz == nullptr) {
		Raiz = nuevo;
	}
	else {
		Raiz = InsertarAVl(nuevo, Raiz);
	}
}

NodoArbol* Arbol_AVL::BuscarNodoAVL(string dato, NodoArbol* Raiz)
{
	Metodos* metodo = new Metodos();
	NodoArbol* aux = Raiz;
	if (aux == nullptr) {
		return nullptr;
	}
	else if (aux->ID == dato) {
		return aux;
	}
	else if (metodo->Mayor_Menor(aux->ID,dato)=="Menor") {
		return BuscarNodoAVL(dato, aux->derecha);
	}
	else {
		return BuscarNodoAVL(dato, aux->izquierda);
	}
}

int Arbol_AVL::obtenerFe(NodoArbol* Nodo)
{
	if (Nodo == nullptr) {
		return -1;
	}
	else {
		return Nodo->FE;
	}
}

void Arbol_AVL::ActualizarAltura(NodoArbol* Nodo)
{
	if ((Nodo->izquierda == nullptr) && (Nodo->derecha != nullptr)) {
		Nodo->FE = Nodo->derecha->FE + 1;
	}
	else if ((Nodo->derecha == nullptr) && (Nodo->izquierda != nullptr)) {
		Nodo->FE = Nodo->izquierda->FE + 1;
	}
	else {
		Nodo->FE = max(obtenerFe(Nodo->izquierda), obtenerFe(Nodo->derecha)) + 1;
	}
}



NodoArbol* Arbol_AVL::getRaiz()
{
	return Raiz;
}



NodoArbol* Arbol_AVL::SRL(NodoArbol* Nodo)
{
	NodoArbol* aux = Nodo->izquierda;
	Nodo->izquierda = aux->derecha;
	aux->derecha = Nodo;
	Nodo->FE = max(obtenerFe(Nodo->izquierda), obtenerFe(Nodo->derecha)) + 1;
	aux->FE = max(obtenerFe(aux->izquierda), obtenerFe(aux->derecha)) + 1;

	return aux;
}

NodoArbol* Arbol_AVL::SRR(NodoArbol* Nodo)
{
	NodoArbol* aux = Nodo->derecha;
	Nodo->derecha = aux->izquierda;
	aux->izquierda = Nodo;
	Nodo->FE = max(obtenerFe(Nodo->izquierda), obtenerFe(Nodo->derecha)) + 1;
	aux->FE = max(obtenerFe(aux->izquierda), obtenerFe(aux->derecha)) + 1;

	return aux;
}

NodoArbol* Arbol_AVL::DRR(NodoArbol* Nodo)
{
	NodoArbol* aux;
	Nodo->derecha = SRL(Nodo->derecha);
	aux = SRR(Nodo);
	return aux;
}

NodoArbol* Arbol_AVL::DRL(NodoArbol* Nodo)
{
	NodoArbol* aux;
	Nodo->izquierda = SRR(Nodo->izquierda);
	aux = SRL(Nodo);
	return aux;
}

void Arbol_AVL::MostrarArbol(NodoArbol* arbol, int cont) {
	if (arbol == nullptr) {
		return;
	}
	else {
		MostrarArbol(arbol->izquierda, cont + 1);
		for (int i = 0; i < cont; i++) {
			cout << "   	";
		}
		cout << arbol->ID << endl;
		MostrarArbol(arbol->derecha, cont + 1);
	}
}

void Arbol_AVL::MostrarActivosArbol(NodoArbol* arbol)
{	
	if (arbol == nullptr) {
		return;
	}
	else {
		if (arbol->Estado == true) {

			cout << arbol->ID + "; " + arbol->Nombre + "; " + arbol->Descripcion << endl;
		}
		MostrarActivosArbol(arbol->izquierda);
		
		MostrarActivosArbol(arbol->derecha);
	}
}

void Arbol_AVL::MisActivos(NodoArbol* arbol)
{
	
	if (arbol == nullptr) {
		return;
	}
	else {
		if (arbol->Estado == false) {

			cout << arbol->ID + "; " + arbol->Nombre + "; " + arbol->Descripcion << endl;
		}
		MisActivos(arbol->izquierda);

		MisActivos(arbol->derecha);
	}
}

void Arbol_AVL::CambiarEstadoNodo(string dato, NodoArbol* arbol, int numero)
{
	if (arbol == nullptr) {
		return;
	}
	else {
		if (numero==1) {
			if (arbol->ID == dato) {

				arbol->setEstado(false);
				return;
			}
		}
		else if (numero ==2) {
			if (arbol->ID == dato) {

				arbol->setEstado(true);
				return;
			}
		}
		
		
		CambiarEstadoNodo(dato, arbol->izquierda, numero);
		CambiarEstadoNodo(dato,arbol->derecha, numero);
	}
}



void Arbol_AVL::graficar()
{
	FILE* file;
	errno_t err;
	err = fopen_s(&file, "AVL.dot", "w+");
	if (err != 0) {
		printf("Archivo no Abierto \n");
	}
	else {
		if (!file) {
			cout << "Error al escribir dot" << endl;
		}
		else {
			fprintf(file, "digraph G{\n");
			fprintf(file, "node [shape = record, style=filled, fillcolor=seashell2];");
			getDot(file, Raiz);
			fprintf(file, "}");
			fclose(file);

			system("dot -Tpng AVL.dot -o AVLI.jpg");

			system("start cmd /c \"AVLI.jpg \"");
		}
	}
}

void Arbol_AVL::getDot(FILE* file, NodoArbol* Raiz)
{
	NodoArbol* aux = Raiz;
	if (aux == nullptr) {
		return;
	}
	else {
		string estructura = CuerpoDot(aux);
		const char* cEstructura= estructura.c_str();
		fprintf(file, cEstructura);
	}
		
}

string Arbol_AVL::CuerpoDot(NodoArbol* Nodo)
{
	string label;
	const string espacio = ", ";
	string Estado;
	if (Nodo->getEstaod()==true) {
		Estado = "Sin Rentar";
	}else{
		Estado = "Rentado";
	}

	if (Nodo->izquierda == nullptr && Nodo->derecha == nullptr) {		
		label += "nodo"+ Nodo->ID + " [ label=\"" + Nodo->ID + espacio + Nodo->Nombre + espacio + Estado+ "\"]; \n";
	}
	else {
		label += "nodo" + Nodo->ID+" [ label=\"<C0>|"+ Nodo->ID + espacio + Nodo->Nombre + espacio + Estado + "|<C1>\"]; \n";
	}
	if (Nodo->izquierda != nullptr) {
		label += CuerpoDot(Nodo->izquierda)+ "nodo" + Nodo->ID+ ":C0->"+ "nodo" + Nodo->izquierda->ID+"\n";
	}
	if (Nodo->derecha != nullptr) {
		label += CuerpoDot(Nodo->derecha) + "nodo" + Nodo->ID + ":C1->" + "nodo" + Nodo->derecha->ID + "\n";
	}
	return label;
}
