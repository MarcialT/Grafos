#include <iostream>

using namespace std;

struct Arista {
    int destino;
    Arista* siguiente;
};

struct Nodo {
    int id;
    Arista* listaAdyacente;
};

class Grafo {
private:
    Nodo* nodos;
    int numNodos;
    int capacidadNodos; 

    bool dfs(int origen, int destino, bool* visitado) {
        if (origen == destino) return true; 

        visitado[origen] = true;

        Arista* actual = nodos[origen].listaAdyacente;
        while (actual != nullptr) {
            int siguiente = actual->destino;
            if (!visitado[siguiente]) {
                if (dfs(siguiente, destino, visitado)) {
                    return true;
                }
            }
            actual = actual->siguiente;
        }
        return false;
    }

public:
    Grafo() {
        numNodos = 0;
        capacidadNodos = 2;
        nodos = new Nodo[capacidadNodos];
    }

    ~Grafo() {
        for (int i = 0; i < numNodos; i++) {
            Arista* actual = nodos[i].listaAdyacente;
            while (actual != nullptr) {
                Arista* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
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
        nodos[numNodos].listaAdyacente = nullptr;
        numNodos++;
    }

    void agregarArista(int origen, int destino) {
        for (int i = 0; i < numNodos; i++) {
            if (nodos[i].id == origen) {
                Arista* nuevaArista = new Arista();
                nuevaArista->destino = destino;
                nuevaArista->siguiente = nodos[i].listaAdyacente;
                nodos[i].listaAdyacente = nuevaArista; 

                break;
            }
        }
    }

    void imprimirListaAdyacencia() {
        cout << "Lista de adyacencia del grafo:\n";
        for (int i = 0; i < numNodos; i++) {
            cout << "Nodo " << nodos[i].id << ": ";
            Arista* actual = nodos[i].listaAdyacente;
            while (actual != nullptr) {
                cout << actual->destino << " ";
                actual = actual->siguiente;
            }
            cout << endl;
        }
    }

    bool existeCamino(int origen, int destino) {
        if (origen >= numNodos || destino >= numNodos) return false;

        bool* visitado = new bool[numNodos];
        for (int i = 0; i < numNodos; i++) visitado[i] = false;

        bool resultado = dfs(origen, destino, visitado);
        
        delete[] visitado;
        return resultado;
    }
};

int main() {
    Grafo g;

    g.agregarNodo(0);
    g.agregarNodo(1);
    g.agregarNodo(2);
    
    g.agregarArista(0, 1);
    g.agregarArista(1, 2);
    
    g.imprimirListaAdyacencia();

    int origen = 0, destino = 2;
    if (g.existeCamino(origen, destino)) {
        cout << "Existe un camino desde " << origen << " hasta " << destino << ".\n";
    } else {
        cout << "No existe un camino desde " << origen << " hasta " << destino << ".\n";
    }

    return 0;
}