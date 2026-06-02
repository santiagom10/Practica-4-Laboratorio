#include "enrutador.h"

//Constructores

enrutador::enrutador()
{

}

enrutador::enrutador(char& _nombre)
{
    nombre = _nombre;
}

enrutador::enrutador(char& _nombre, map<unsigned char, map<unsigned char, int >> _tablaEnrutamiento)
{
    nombre = _nombre;
    tablaEnrutamiento = _tablaEnrutamiento;
}

enrutador::enrutador(char& _nombre, map<unsigned char, map<unsigned char, int> > _tablaEnrutamiento, map<unsigned char, map<unsigned char, int> > _enrutadoresVecinos)
{
    nombre = _nombre;
    tablaEnrutamiento = _tablaEnrutamiento;
    enrutadoresVecinos = _enrutadoresVecinos;
}

//Metodos

void enrutador::cargar_Vecinos(string& ruta)
{

    /*
     * Metodo encargado de cargar todos los enrutadores adyacentes con sus respectivos costos a su respectivo enrutador.
     *
     * Inputs de Argumento:
     *  - ruta
     *
     * Retornos:
     *  - Ninguno
     *
     */

    char aux = ' ';
    enrutador archivo;
    vector<unsigned char> informacion_Archivo = archivo.leerArchivo(ruta);
    vector<string> informacion_Split;
    string cadenaAuxiliar = "";
    char nombre = getNombre();

    cadenaAuxiliar = archivo.vector_String(informacion_Archivo);
    informacion_Split = archivo.split(cadenaAuxiliar,aux);

    for(unsigned long long int i = 0; i <informacion_Split.size(); i++){
        if(informacion_Split[i][0] == nombre){
            enrutadoresVecinos[informacion_Split[i][0]][informacion_Split[i][1]] = stoi(informacion_Split[i].substr(2,informacion_Split[i].length()-2));
        }
    }

}

void enrutador::mostrar_EnrutadoresVecinos()
{

    /*
     * Metodo encargado de mostrar todos los enrutadores adyacentes almacenados en el mapa anidado.
     *
     * Inputs de Argumento:
     * ninguno
     *
     * Retornos:
     *  - Ninguno
     *
     */

    int valor = 0;

    for (auto& parExterno : enrutadoresVecinos) {
        for (auto& parInterno : parExterno.second) {
            valor = parInterno.second;
            cout << valor << " ";
        }
        cout << endl;
    }

}

void enrutador::mostrar_Coste(char& destino)
{
    /*
     * Metodo encargado de imprimir en pantalla una posición de un mapa adyacente dado únicamente el destino.
     *
     * Inputs de Argumento:
     *  - ruta
     *
     * Retornos:
     *  - Ninguno
     *
     */

    cout << tablaEnrutamiento[this->nombre][destino] << endl;

}

void enrutador::mostrar_Enrutamiento()
{
    /*
     * Metodo encargado de imprimir en pantalla la tabla de enrutamiento completa.
     *
     * Inputs de Argumento:
     *  - ruta
     *
     * Retornos:
     *  - Ninguno
     *
     */

    int valor = 0;

    for (auto& parExterno : tablaEnrutamiento) {
        for (auto& parInterno : parExterno.second) {
            valor = parInterno.second;
            cout << valor << " ";
        }
        cout << endl;
    }

}

//Metodos complementarios de la clase que no se relacionan con los atributos

unsigned long long int enrutador::obtenerLongitud(string& ruta)
{
    unsigned long long int size = 0;
    fstream archivo;

    archivo.open(ruta,ios::in | ios::ate);
    if(archivo.is_open()){
        size = archivo.tellg();
        archivo.close();
        return size;
    }
    else{
        cout << "Error al leer el archivo: ";
        return 1;
    }

}

unsigned long long enrutador::obtenerLongitud(const vector<unsigned char> &miVector)
{
    /*
    * Método para obtener la longitud de un archivo.
    *
    * Argumentos de Entrada:
     *  - ruta: Ruta al archivo del que se desea conocer la longitud.
     *
    * Retorno:
    *  - Longitud del archivo(unsigned long long int).
    *  - 1 si se produce un error al abrir el archivo.
    */

    unsigned long long int size = 0;

    while(miVector[size]!='\0'){
        size += 1;
    }
    return size;

}

vector<unsigned char>enrutador::leerArchivo(string& rutaArchivo)
{
    /*
     * Método para leer un archivo y almacenar su contenido en un vector de caracteres.
     *
     * Argumentos de Entrada:
     *  - rutaArchivo: Ruta al archivo que se desea leer.
     *
     * Retorno:
     *  - Vector de caracteres que contiene el contenido del archivo.
     *  - Vector vacío si se produce un error al abrir el archivo.
     */

    fstream archivo;
    unsigned long long int size = 0;
    vector<unsigned char> datos;

    archivo.open(rutaArchivo,ios::in|ios::ate);


    if(archivo.is_open()){
        size = obtenerLongitud(rutaArchivo);
        datos.reserve(size);
        archivo.seekg(0);
        for(unsigned long long i = 0; i < size; i++){
            datos.push_back(static_cast<unsigned char>(archivo.get()));
        }
        datos.push_back('\0');
    }
    else{
        cout << "Error al leer el archivo";
        return {};
    }

    archivo.close();

    return datos;
}

vector<string> enrutador::split(const string &entrada, char& delimitador)
{

    /*
     * Método para dividir una cadena en subcadenas utilizando un delimitador.
     *
     * Argumentos de Entrada:
     *  - entrada: Cadena que se desea dividir.
     *  - delimitador: Carácter utilizado como delimitador.
     *
     * Retorno:
     *  - Vector de subcadenas resultantes.
     */

    vector<string> subcadenas;
    string subcadena;
    int inicio = 0;
    int fin = entrada.find(delimitador);

    while(fin != string::npos){
        subcadena = entrada.substr(inicio,fin-inicio);
        subcadenas.push_back(subcadena);
        inicio = fin + 1;
        fin = entrada.find(delimitador,inicio);

    }

    subcadena = entrada.substr(inicio);
    subcadenas.push_back(subcadena);


    return subcadenas;
}

string enrutador::vector_String(vector<unsigned char>&miVector)
{

    /*
     * Método para convertir un vector de caracteres en una cadena de texto.
     *
     * Argumentos de Entrada:
     *  - miVector: Vector de caracteres que se desea convertir.
     *
     * Retorno:
     *  - Cadena de texto resultante.
     */

    enrutador archivo;
    string cadena = "";
    unsigned long long int cont_Saltos = 1;

    for(unsigned long long int i = 0; i < miVector.size(); i++){
        if(miVector[i] != ' ' && miVector[i] != '\n'){
            cadena.push_back(miVector[i]);
        }
        else if(miVector[i] == '\n'){
            cont_Saltos ++;
            cadena += " ";
        }
    }

    cadena = cadena.substr(0,cadena.length()-cont_Saltos);

    return cadena;

}

int enrutador::caracter_Aleatorio()
{
    /*
     * Método para generar un número aleatorio entre 65 y 90 (correspondiente a caracteres ASCII mayúsculos).
     *
     * Retorno:
     *  - Número aleatorio entre 65 y 90.
     */

    int numeroAleatorio = 0;
    do {
        numeroAleatorio = rand() % 58 + 65;
    } while (numeroAleatorio > 90 && numeroAleatorio < 97);

    return numeroAleatorio;
}

int enrutador::moneda()
{
    /*
     * Método para simular una moneda.
     *
     * Retorno:
     *  - 0.
     *  - 1.
     */

    int numeroAleatorio = rand() % 2;

    return numeroAleatorio;
}


// Sobrecarga de operadores

ostream& operator<<(ostream& os, const vector<unsigned char>& vec)
{

    /*
     * Sobrecarga del operador << para imprimir un vector de caracteres en un flujo de salida.
     *
     * Argumentos de Entrada:
     *  - os: Flujo de salida.
     *  - vec: Vector de caracteres a imprimir.
     *
     * Retorno:
     *  - Flujo de salida actualizado.
     */

    for (int i = 0; i < vec.size(); ++i) {
        os << vec[i];
    }
    return os;
}

//Metodos getter y setter

char enrutador::getNombre() const
{
    return nombre;
}

void enrutador::setNombre(char& newNombre)
{
    nombre = newNombre;
}

map<unsigned char, map<unsigned char, int> > enrutador::getTablaEnrutamiento() const
{
    return tablaEnrutamiento;
}

map<unsigned char, map<unsigned char, int> > enrutador::getEnrutadoresVecinos() const
{
    return enrutadoresVecinos;
}

void enrutador::setTablaEnrutamiento(const map<unsigned char, map<unsigned char, int> > &newTablaEnrutamiento)
{
    tablaEnrutamiento = newTablaEnrutamiento;
}

void enrutador::setEnrutadoresVecinos(const map<unsigned char, map<unsigned char, int> > &newEnrutadoresVecinos)
{
    enrutadoresVecinos = newEnrutadoresVecinos;
}
