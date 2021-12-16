#include <iostream>

#define COUNT 10

using namespace std;

/*
    Fecha de Inicio: 2 - 11 - 2021

    Fecha de Entrega: 11 - 11 - 2021

    Grupo #02

    * Christopher Tineo
    * Camilo Maria
    * Lya Sanchez
    * Sahira Tejada
    * Taiyab Gillani
    * José Fernandez

    * Instrucciones

    Construir un algoritmo que sea capaz de manejar árboles binarios donde se pueda:

    1. Insertar un nodo.
    2. Eliminar un nodo
    3. Mostrar el árbol

    Identifica las reglas para eliminar un nodo que tiene hojas como hijo

    Sobre cual es el prococeso que se sigue para insertar un nuevo nodo
*/

// Crear un árbol de segundo orden (max. 2 hijos o árbol binario)

struct Nodo {
    // Declarando un nodo de segundo orden
    int numero;
    Nodo* izquierda, * derecha;
};

Nodo* arbol = NULL; // Declaramos el árbol binario

Nodo* crearNodo(int);
Nodo* insertar(Nodo*, int);
Nodo* minimoNodo(Nodo*);
Nodo* eliminar(Nodo*, int);
void mostrarArbol(Nodo*, int);
void menu();

// 1. Insertar un nodo

Nodo* crearNodo(int valor) {
    Nodo* nuevo_nodo = new Nodo;

    nuevo_nodo->numero = valor;
    // Inicializar en NULL referencias de sus hijos 
    nuevo_nodo->izquierda = NULL;
    nuevo_nodo->derecha = NULL;

    return nuevo_nodo;
}

Nodo* insertar(Nodo* nodo, int valor) {

    if (nodo == NULL) return crearNodo(valor); // Si el arbol esta vacio

    if (valor < nodo->numero) {
        // Si el valor que se quiere insertar
        // Es menor al valor del nodo actual
        // Se coloca en el lado izquierdo
        nodo->izquierda = insertar(nodo->izquierda, valor);
    }
    else {
        // Si el valor que se quiere insertar
        // Es mayor o igual al valor del nodo actual
        // Se coloca en el lado derecho
        nodo->derecha = insertar(nodo->derecha, valor);
    }

    return nodo; // Retornar el nodo
}

// 2. Eliminar un nodo

Nodo* minimoNodo(Nodo* nodo) {
    Nodo* actual = nodo;

    // Encontrar el nodo más a la izquierda dado un nodo
    while (actual && actual->izquierda != NULL) {
        actual = actual->izquierda;
    }

    return actual; // Devolver el nodo minimo a la izquierda
}

Nodo* eliminar(Nodo* root, int valor) {
    if (root == NULL) return root;

    if (valor < root->numero) {
        // Si el valor a eliminar
        // Es menor al que tiene el nodo actual
        // Sigue buscando por la izquierda
        root->izquierda = eliminar(root->izquierda, valor);
    }
    else if (valor > root->numero) {
        // Si el valor a eliminar
        // Es mayor o igual al que tiene el nodo actual
        // Sigue buscando por la derecha
        root->derecha = eliminar(root->derecha, valor);
    }
    else {
        // Si el nodo tiene cero o un hijo
        // Busca en que posicion esta, en el segundo caso.

        if (root->izquierda == NULL) {
            // Si el hijo izquierdo está vacio
            Nodo* derecha = root->derecha;
            free(root);
            return derecha;
        }
        else if (root->derecha == NULL) {
            // Si el hijo derecho está vacío
            Nodo* izquierda = root->izquierda;
            free(root);
            return izquierda;
        }

        // Si el nodo tiene dos hijos

        // Se eliminará el nodo y lo reemplazará el nodo más a la izquierda del hijo derecho.

        Nodo* minimo = minimoNodo(root->derecha); // Encuentra el nodo más a la izquierda en el hijo derecho del nodo.

        root->numero = minimo->numero; // Poner el valor del mínimo en el nodo a eliminar

        root->derecha = eliminar(root->derecha, minimo->numero); // Elimina el mínimo nodo de su posición anterior
    }

    return root;
}

// 3. Mostrar el árbol

void mostrarArbol(Nodo* root, int space)
{
    // Base case
    if (root == NULL)
        // Si el arbol está vacío
        return;

    space += COUNT;

    // Imprimir lado derecho primero
    mostrarArbol(root->derecha, space);

    cout << endl;

    for (int i = COUNT; i < space; i++) {
        cout << " ";
    }

    cout << root->numero << endl;

    // Process lado derecho
    mostrarArbol(root->izquierda, space);
}

int main() {
    system("cls");

    menu();

    return 0;
}

void menu() {
    int opcion, dato, contador = 0;
    do {
        cout << "Menu:" << endl;
        cout << "1. Insertar nodo" << endl;
        cout << "2. Eliminar nodo" << endl;
        cout << "3. Mostrar arbol" << endl;
        cout << "4. Salir" << endl;

        cout << "Elige una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
        case 1:
            cout << "Digite un numero entero: ";
            cin >> dato;
            arbol = insertar(arbol, dato);
            cout << "\n";
            system("pause");
            break;
        case 2:
            if (arbol != NULL) {
                cout << "Escriba el valor de un nodo: ";
                cin >> dato;
                arbol = eliminar(arbol, dato);
            }
            else {
                cout << "ERROR: EL ARBOL ESTA VACIO" << endl;
            }
            cout << "\n";
            system("pause");
            break;
        case 3:
            if (arbol != NULL) {
                cout << "Mostrando arbol: " << endl;
                mostrarArbol(arbol, 0);
            }
            else {
                cout << "ERROR: EL ARBOL ESTA VACIO" << endl;
            }

            cout << "\n";
            system("pause");
            break;

        }
        system("cls");
    } while (opcion != 4);
}