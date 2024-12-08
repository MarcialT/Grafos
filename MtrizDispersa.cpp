#include <iostream>

using namespace std;

struct Arista {
    int destino;
    int peso;
};

struct Nodo {
    int id;
    Arista* aristas;
    int numAristas;
    int capacidadAristas;
};

class Grafo {
private:
    Nodo* nodos;
    int numNodos;
    int capacidadNodos;

public:
    Grafo() {
        numNodos = 0;
        capacidadNodos = 2;
        nodos = new Nodo[capacidadNodos];
    }

    ~Grafo() {
        for (int i = 0; i < numNodos; i++) {
            delete[] nodos[i].aristas;
        }
        delete[] nodos;
    }

    void agregarNodo(int id) {
        if (numNodos == capacidadNodos) {
            capacidadNodos *= 2;
            Nodo* nuevoArreglo = new Nodo[capacidadNodos];
            for (int i = 0; i < numNodos; i++) {
                nuevoArreglo[i] = nodos[i];
            }
            delete[] nodos;
            nodos = nuevoArreglo;
        }
        
        nodos[numNodos].id = id;
        nodos[numNodos].numAristas = 0;
        nodos[numNodos].capacidadAristas = 2;
        nodos[numNodos].aristas = new Arista[nodos[numNodos].capacidadAristas];
        numNodos++;
    }

    void agregarArista(int origen, int destino, int peso) {
        for (int i = 0; i < numNodos; i++) {
            if (nodos[i].id == origen) {
                if (nodos[i].numAristas == nodos[i].capacidadAristas) {
                    nodos[i].capacidadAristas *= 2;
                    Arista* nuevoArreglo = new Arista[nodos[i].capacidadAristas];
                    for (int j = 0; j < nodos[i].numAristas; j++) {
                        nuevoArreglo[j] = nodos[i].aristas[j]; 
                    }
                    delete[] nodos[i].aristas; 
                    nodos[i].aristas = nuevoArreglo;
                }
                
                nodos[i].aristas[nodos[i].numAristas].destino = destino;
                nodos[i].aristas[nodos[i].numAristas].peso = peso;
                nodos[i].numAristas++;
                break;
            }
        }
    }

    void imprimirMatrizDispersa() {
        cout << "Matriz dispersa del grafo:\n";
        for (int i = 0; i < numNodos; i++) {
            cout << "Nodo " << nodos[i].id << ": ";
            for (int j = 0; j < nodos[i].numAristas; j++) {
                cout << "(" << nodos[i].aristas[j].destino << ", " << nodos[i].aristas[j].peso << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    Grafo g;

    g.agregarNodo(1);
    g.agregarNodo(2);
    g.agregarNodo(3);

    g.agregarArista(1, 2, 5);
    g.agregarArista(1, 3, 10);
    g.agregarArista(2, 3, 2);

    g.imprimirMatrizDispersa();

    return 0;
}