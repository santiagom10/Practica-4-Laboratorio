#ifndef RED_H
#define RED_H

#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <fstream>
#include <enrutador.h>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cstdlib>
using namespace std;

class red
{

    /*
 * Clase red
 *
 * Atributos:
 * vector_Instancias: Vector que almacena los enrutadores pertenecientes a la clase con el mismo nombre.
 * enrutadores: Lista con los nombres de los enrutadores activos en la red.
 * enrutadores_vecinos: Mapa con todos los enrutadores que tienen conexión directa con sus respectivos costos.
 * enrutamiento_Aux: Tabla de enrutamiento con todos los costes cálculados.
 * distancias: Mapa en el que se guardan las distancias correspondientes a los enlaces.
 *
 */

private:

    vector<enrutador> vector_Instancias;
    list<char>enrutadores;
    map<unsigned char, map<unsigned char, int >> enrutadores_Vecinos;
    map<unsigned char, map<unsigned char, string >> mapa_Caminos;
    map<unsigned char, map<unsigned char, int >> enrutamiento_Aux;
    map<unsigned char, int> distancias;


public:

    //Constructores
    red();

    //Metodos
    void listar_Enrutadores();
    void cargar_Enrutadores(string ruta);
    bool buscarRed(char elemento_Buscado);
    void inicializar_Enrutamiento(string ruta);
    void inicializar_Enrutamiento();
    void mostrar_EnrutamientoAuxiliar();
    void mostrar_Vecinos();
    void inicializarDistancias();
    int dijkstra(char nodoInicio, char nodoFinal);
    void gen_Enrutamiento();
    void actualizar_Enrutadores();
    void generar_GrafoAleatorio(int n, float k);
    void generar_ListaAleatoria(int n);
    void generar_VectorInstancias();
    int determinar_Existencia(float k);
    int buscar_Instancia(char& nombre);
    void eliminar_Instancia(char& nombre);
    void menu(string ruta);
    void listar_EnlacesCambiantes();
    void mostrar_Camino(char origen, char destino);
    void cambiar_Costo(int origen, int destino, int& costo);
    void agregar_Enlace(int origen, int destino, int& costo);
    void eliminar_Enlace(int origen, int destino);


    //Métodos getter y setter
    vector<enrutador> getVector_Instancias() const;
    void setVector_Instancias(const vector<enrutador> &newVector_Instancias);
    list<char> getEnrutadores() const;
    void setEnrutadores(const list<char> &newEnrutadores);
    map<unsigned char, map<unsigned char, int> > getEnrutadores_Vecinos() const;
    void setEnrutadores_Vecinos(const map<unsigned char, map<unsigned char, int> > &newEnrutadores_Vecinos);
    map<unsigned char, map<unsigned char, int> > getEnrutamiento_Aux() const;
    void setEnrutamiento_Aux(const map<unsigned char, map<unsigned char, int> > &newEnrutamiento_Aux);
    map<unsigned char, int> getDistancias() const;
    void setDistancias(const map<unsigned char, int> &newDistancias);
    map<unsigned char, map<unsigned char, string> > getMapa_Caminos() const;
    void setMapa_Caminos(const map<unsigned char, map<unsigned char, string> > &newMapa_Caminos);
    template <typename T>
    T obtener_Entrada(string mensaje, T inf, T max);
};

ostream& operator<<(ostream& os, const vector<unsigned char>& vec);

#endif // RED_H
