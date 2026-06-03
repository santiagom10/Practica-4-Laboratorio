#include "red.h"

//Constructores

red::red()
{

}


//Metodos

void red::listar_Enrutadores()
{
    /*
     * Metodo encargado de recorrer por todo el vector de enrutadores y los muestra en pantalla
     *
     * Inputs de Argumento:
     *  - Ninguno
     *
     * Retornos:
     *  - Ninguno
     *
    */
    unsigned long long int i = 0;
    for(unsigned char elemento : enrutadores){
        cout << "Enrutador " << i+1 << ": "<< elemento << endl;
        i++;
    }
}

void red::cargar_Enrutadores(string ruta)
{
    /*
     * Metodo encargado de leer los enrutadores desde un archivo dado en la ruta
     *
     * Inputs de Argumento:
     *  - Dirección de la Ruta donde esta el archivo que contenga la topología de la red
     *
     * Retornos:
     *  - Ninguno
     *
     */
    char aux = ' ';
    enrutador archivo;
    vector<unsigned char> informacion = archivo.leerArchivo(ruta);
    vector<string> informacion_split;
    string cadenaAux = archivo.vector_String(informacion);

    informacion_split = archivo.split(cadenaAux,aux);

    for(unsigned long long int i = 0; i < informacion_split.size(); i++){

        if(buscarRed(informacion_split[i][0]) == 0){
            enrutadores.push_back(informacion_split[i][0]);
        }
        if(buscarRed(informacion_split[i][1]) == 0){
            enrutadores.push_back(informacion_split[i][1]);
        }
    }


}

bool red::buscarRed(char elemento_Buscado)
/*
     * Metodo encargado de buscar una Red en especifico
     *
     * Inputs de Argumento:
     *  - Carácter que va a ser el elemento que vamos a buscar
     *
     * Retornos:
     *  - Booliano
     */
{
    for(unsigned char elemento : enrutadores){
        if(elemento == elemento_Buscado){
            return true;
        }
    }
    return false;

}

void red::generar_VectorInstancias()
{
    /*
     * Metodo encargado de generar un vector con cada elemento de la lista de enrutadores
     *
     * Inputs de Argumento:
     *  - Ninguno
     *
     * Retornos:
     *  - Ninguno
     *
     */
    for (char& elemento : enrutadores) {
        enrutador instancia(elemento);
        vector_Instancias.push_back(instancia);
    }

}

void red::inicializar_Enrutamiento(string ruta)
{
    /*
     * Metodo encargado de generar la topologia en general de los enrutadores con sus respectivos vecinos y costos
     *
     * Inputs de Argumento:
     *  - Dirección de la Ruta donde esta el archivo que contenga la topología de la red
     *
     * Retornos:
     *  - Ninguno
     *
     */
    enrutador instancia_Auxiliar;
    map<unsigned char, map<unsigned char, int>> vecinos;
    unsigned char enrutadorActual;
    unsigned char vecinoActual;
    int costo;

    const map<unsigned char, int>* vecinosDelEnrutador;

    generar_VectorInstancias();

    for (int i = 0; i < vector_Instancias.size(); i++) {
        instancia_Auxiliar = vector_Instancias[i];
        instancia_Auxiliar.cargar_Vecinos(ruta);
        vecinos = instancia_Auxiliar.getEnrutadoresVecinos();

        for (auto& entrada : vecinos) {
            enrutadorActual = entrada.first;
            vecinosDelEnrutador = &entrada.second;

            for (auto& vecino : *vecinosDelEnrutador) {
                vecinoActual = vecino.first;
                costo = vecino.second;

                enrutadores_Vecinos[enrutadorActual][vecinoActual] = costo;
                enrutadores_Vecinos[vecinoActual][enrutadorActual] = costo;
            }
        }
    }
}

void red::inicializar_Enrutamiento()
{
    /*
     * Metodo sobrecargado encargado de generar la topologia de la red, esta tiene un uso enfocado para la red aleatoria y la
     * edición posterior a la carga del archivo
     *
     * Inputs de Argumento:
     *  - Ninguno
     *
     * Retornos:
     *  - Ninguno
     *
    */
    enrutador instancia_Auxiliar;
    map<unsigned char, map<unsigned char, int>> vecinos;
    unsigned char enrutadorActual;
    unsigned char vecinoActual;
    int costo;

    const map<unsigned char, int>* vecinosDelEnrutador;

    generar_VectorInstancias();

    for (int i = 0; i < vector_Instancias.size(); i++) {
        instancia_Auxiliar = vector_Instancias[i];
        vecinos = instancia_Auxiliar.getEnrutadoresVecinos();

        for (auto& entrada : vecinos) {
            enrutadorActual = entrada.first;
            vecinosDelEnrutador = &entrada.second;

            for (auto& vecino : *vecinosDelEnrutador) {
                vecinoActual = vecino.first;
                costo = vecino.second;

                enrutadores_Vecinos[enrutadorActual][vecinoActual] = costo;
                enrutadores_Vecinos[vecinoActual][enrutadorActual] = costo;
            }
        }
    }
}


void red::mostrar_EnrutamientoAuxiliar()
{
    /*
     * Metodo encargado de mostrar la tabla de enrutamiento auxiliar
     *
     * Inputs de Argumento:
     *  - Ninguno
     *
     * Retornos:
     *  - Ninguno
     *
     */
    unsigned long long int valor = 0;

    cout << "Tabla de enrutamiento auxiliar: " << endl;

    for (auto& parExterno : enrutamiento_Aux) {
        for (auto& parInterno : parExterno.second) {
            valor = parInterno.second;
            if(valor == INT_MAX){
                cout << -1 << " ";
            }
            else{
                cout << valor << " ";
            }


        }
        cout << endl;
    }

}

void red::mostrar_Vecinos()
{
    /*
     * Metodo encargado de mostrar los vecinos de cada enrutador
     *
     * Inputs de Argumento:
     *  - Ninguno
     *
     * Retornos:
     *  - Ninguno
     *
     */
    unsigned long long int valor = 0;

    cout << "Tabla de vecinos: " << endl;

    for (auto& parExterno : enrutadores_Vecinos) {
        for (auto& parInterno : parExterno.second) {
            valor = parInterno.second;
            cout << valor << " ";
        }
        cout << endl;
    }
}


void red::inicializarDistancias()
{
    /*
     * Metodo encargado de inicializar las distancias entre los nodos en su valor más grande del int
     * (Simulando un infinito)
     *
     * Inputs de Argumento:
     *  - Ninguno
     *
     * Retornos:
     *  - Ninguno
     *
     */
    for (unsigned char nodo : enrutadores) {
        distancias[nodo] = INT_MAX;
    }
}


int red::dijkstra(char nodoInicio, char nodoFinal)
{
    /*
     * Algoritmo encargado de calcular el camino más corto entre dos nodos en una red de enrutadores.
     *
     * Inputs de argumento:
     *  - nodoInicio (El nodo de inicio)
     *  - nodoFinal (El nodo de destino)
     *
     * Retornos:
     *  - La distancia del camino más corto entre los nodos de inicio y destino. Si no hay un camino válido, se devuelve INT_MAX.
     *
     */
    unsigned char nodo;
    unsigned long long int distancia;
    unsigned char vecino;
    string camino = "";
    char nodoActual;
    unsigned long long int peso;

    priority_queue<pair<unsigned long long int, char>, vector<pair<unsigned long long int, char>>, greater<pair<unsigned long long int, char>>> siguiente;
    map<char, char> padres;

    siguiente.push(make_pair(0, nodoInicio));
    distancias[nodoInicio] = 0;
    while (!siguiente.empty()) {
        nodo = siguiente.top().second;
        distancia = siguiente.top().first;
        siguiente.pop();

        if (nodo != nodoFinal && distancia <= distancias[nodo]) {
            for (auto& kvp : enrutadores_Vecinos[nodo]) {
                vecino = kvp.first;
                peso = kvp.second;

                if (distancias[vecino] > distancias[nodo] + peso) {
                    distancias[vecino] = distancias[nodo] + peso;
                    siguiente.push(make_pair(distancias[vecino], vecino));
                    padres[vecino] = nodo;
                }
            }
        }
    }

    if(distancias[nodoFinal] == INT_MAX){
        mapa_Caminos[nodoInicio][nodoFinal] = "-1";
    }
    else{
        nodoActual = nodoFinal;
        while (nodoActual != nodoInicio) {
            camino = nodoActual + camino;
            nodoActual = padres[nodoActual];
        }
        camino = nodoInicio + camino;
        mapa_Caminos[nodoInicio][nodoFinal] = camino;
    }

    return distancias[nodoFinal];
}



void red::gen_Enrutamiento()
{
    /*
     * Metodo encargado de tomar todas las combinaciones de nodos disponibles y encontrar la ruta más corta en base a un grafo de red
     *
     * Inputs de Argumento:
     *  - Ninguno
     *
     * Retornos:
     *  - Ninguno
     *
     */
    for(unsigned char elemento1 : enrutadores){
        for(unsigned char elemento2 : enrutadores){
            inicializarDistancias();
            enrutamiento_Aux[elemento1][elemento2] = dijkstra(elemento1,elemento2);
        }
    }
}

void red::actualizar_Enrutadores()
{
    /*
     * Metodo encargado de actualizar el vector que lleva los enrutadores
     *
     * Inputs de Argumento:
     *  - Ninguno
     *
     * Retornos:
     *  - Ninguno
     *
     */

    if (vector_Instancias.empty()) {
        cout << "El vector esta vacio" << endl;
    }
    else {
        for (int i = 0; i < vector_Instancias.size(); i++) {
            vector_Instancias.at(i).setTablaEnrutamiento(enrutamiento_Aux);

        }
    }
}

void red::generar_ListaAleatoria(int n)
{
    /*
     * Metodo encargado de generar una lista aleatoria para poder ser utilizada como nuestros nodos
     *
     * Inputs de Argumento:
     *  - Número
     *
     * Retornos:
     *  - Ninguno
     *
     */
    enrutadores.clear();
    enrutador val;
    int i = 0;
    int caracter = 0;
    while(i != n){
        caracter = val.caracter_Aleatorio();
        if(buscarRed(char(caracter)) == 0){
            enrutadores.push_back(char(caracter));
            i ++;
        }
    }
}

int red::determinar_Existencia(float k)
{
    /*
     * Metodo encargado para generar las conexiones acorde a una probabilidad dada
     *
     * Inputs de Argumento:
     *  - float k
     *
     * Retornos:
     *  - costeAleatorio para un enlace existente , -1 para un enlace no existente
     *
     */
    enrutador val;
    int numeroRandom = 0;
    int costeAleatorio = rand() % 101;


    for(list<char>::iterator it = enrutadores.begin(); it != enrutadores.end(); ++it){
        numeroRandom = val.moneda();
        if (numeroRandom < k) {
            return costeAleatorio;
        } else {
            return -1;
        }
    }
    return 0;
}

int red::buscar_Instancia(char &nombre)
{
    /*
     * Metodo encargado de buscar la instancia de un nodo.
     *
     * Inputs de Argumento:
     *  - Nombre del nodo
     *
     * Retornos:
     *  - i (posición) en caso de que exista, -1 si no existe
     *
     */
    enrutador aux;
    for (int i = 0; i < vector_Instancias.size(); i++) {
        aux = vector_Instancias.at(i);
        if (aux.getNombre() == nombre) {
            return i;
        }
    }

    return -1;
}

void red::generar_GrafoAleatorio(int n, float k)
{
    /*
     * Metodo encargado de generar un grafo aleatorio
     *
     * Inputs de Argumento:
     *  - Entero N para el número de enrutadores, Flotante K para el número de la probabilidad de entablar enlace
     *
     * Retornos:
     *  - Ninguno
     *
     */

    vector_Instancias.clear();
    map<unsigned char, map<unsigned char, int >> enrutadores_Adyacentes;
    generar_ListaAleatoria(n);
    generar_VectorInstancias();
    int existencia = 0;
    int pos = 0;

    for (list<char>::iterator it0 = enrutadores.begin(); it0 != enrutadores.end(); ++it0) {
        for (list<char>::iterator it1 = enrutadores.begin(); it1 != enrutadores.end(); ++it1) {
            existencia = determinar_Existencia(k);
            pos = buscar_Instancia(*it0);
            if(existencia != -1){
                enrutadores_Adyacentes[*it0][*it1] = existencia;
            }
        }
        vector_Instancias.at(pos).setEnrutadoresVecinos(enrutadores_Adyacentes);
        enrutadores_Adyacentes.clear();
    }


}

void red::eliminar_Instancia(char& nombre)
{
    /*
     * Metodo encargado de buscar un enrutador y de eliminarlo de nuestro vector
     *
     * Inputs de Argumento:
     *  - Carácter asociado con el nombre del enrutador
     *
     * Retornos:
     *  - Ninguno
     *
     */

    int pos = buscar_Instancia(nombre);
    list<char>::iterator it = enrutadores.begin();

    for (list<char>::iterator it0 = enrutadores.begin(); it0 != enrutadores.end(); ++it0) {
        for (list<char>::iterator it1 = enrutadores.begin(); it1 != enrutadores.end(); ++it1) {
            if (char(*it0) == nombre || char(*it1) == nombre) {
                enrutadores_Vecinos[*it0].erase(*it1);
            }
        }
    }

    vector_Instancias.erase(vector_Instancias.begin()+pos);
    advance(it,pos);
    enrutadores.erase(it);

    cout << "Se ha eliminado el enrutador " << nombre << endl;

}


template<typename T>
T red::obtener_Entrada(string mensaje, T inf, T max)
{
    T opcion;

    while (true) {
        cout << mensaje;
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "La entrada no es valida. Debe ser un numero." << endl;
        }
        else if (opcion >= inf && opcion <= max) {
            break;
        }
        else {
            cout << "Opcion invalida" << endl;
        }
    }

    return opcion;
}

void red::mostrar_Camino(char origen, char destino)
/*
     * Metodo encargado de tomar la lista en donde se va la ruta y mostrar como es.
     *
     * Inputs de Argumento:
     *  - Caracter de origen para el nodo de origen, y caracter destino para el nodo del destino.
     *
     * Retornos:
     *  - Ninguno
     *
     */
{
    if(mapa_Caminos[origen][destino] == "-1"){
        cout << "No hay ruta disponible" << endl;
    }
    else{
        cout << "La ruta es: " << mapa_Caminos[origen][destino] << endl;
    }

}

void red::cambiar_Costo(int origen, int destino, int& costo)
{
    /*
     * Metodo encargado de cambiar el costo entre enlaces
     *
     * Inputs de Argumento:
     *  - Entero para el enlace de origen y el destino, por referencia el costo entre ellos.
     *
     * Retornos:
     *  - Ninguno
     *
     */
    char origenAux = vector_Instancias.at(origen-1).getNombre();
    char destinoAux = vector_Instancias.at(destino-1).getNombre();


    if (enrutadores_Vecinos.find(origenAux) != enrutadores_Vecinos.end()) {
        if (enrutadores_Vecinos[origenAux].find(destinoAux) != enrutadores_Vecinos[origenAux].end()) {
            enrutadores_Vecinos[origenAux][destinoAux] = costo;
            enrutadores_Vecinos[destinoAux][origenAux] = costo;
        } else {
            cout << "Este enlace no existe" << endl;
        }
    } else {

        cout << "Este enlace no existe" << endl;
    }


}

void red::agregar_Enlace(int origen, int destino, int &costo)
{
    /*
     * Método para agregar un enlace entre dos enrutadores en una red.
     *
     * Inputs de Argumento:
     *  - origen Índice del enrutador de origen en el vector de instancias.
     *  - destino: Índice del enrutador de destino en el vector de instancias.
     *  - costo: Costo del enlace a agregar.
     *
     * Descripción:
     *  Este método permite agregar un enlace entre dos enrutadores en una red. Verifica si el enlace
     *  ya existe y, en caso afirmativo, muestra un mensaje de error. Si el enlace no existe, lo agrega
     *  a la estructura de datos que representa los enrutadores vecinos.
     *
     */
    char origenAux = vector_Instancias.at(origen-1).getNombre();
    char destinoAux = vector_Instancias.at(destino-1).getNombre();


    if (enrutadores_Vecinos.find(origenAux) != enrutadores_Vecinos.end()) {
        if (enrutadores_Vecinos[origenAux].find(destinoAux) != enrutadores_Vecinos[origenAux].end()) {
            cout << "Este enlace ya existe, puedes editarlo en otra opcion" << endl;
        } else {
            enrutadores_Vecinos[origenAux][destinoAux] = costo;
            enrutadores_Vecinos[destinoAux][origenAux] = costo;
        }
    } else {
        enrutadores_Vecinos[origenAux][destinoAux] = costo;
        enrutadores_Vecinos[destinoAux][origenAux] = costo;
    }
}

void red::eliminar_Enlace(int origen, int destino) {
    /*
     * Método para eliminar un enlace entre dos enrutadores en una red.
     *
     * Inputs de Argumento:
     *  - origen: Índice del enrutador de origen en el vector de instancias.
     *  - destino: Índice del enrutador de destino en el vector de instancias.
     *
     * Retornos:
     *  - Ninguno
     *
     */
    char origenAux = vector_Instancias.at(origen-1).getNombre();
    char destinoAux = vector_Instancias.at(destino-1).getNombre();


    if (enrutadores_Vecinos.find(origenAux) != enrutadores_Vecinos.end() && enrutadores_Vecinos[origenAux].find(destinoAux) != enrutadores_Vecinos[origenAux].end()) {

        enrutadores_Vecinos[origenAux].erase(destinoAux);
        enrutadores_Vecinos[destinoAux].erase(origenAux);

        cout << "Enlace eliminado entre " << origenAux << " y " << destinoAux << endl;
    } else {
        cout << "Este enlace no existe" << endl;
    }
}



void red::listar_EnlacesCambiantes()
{
    /*
     * Método para listar los enlaces cambiantes en la red.
     *
     * Inputs de Argumento:
     *  - Ninguno
     *
     * Retornos:
     *  - Ninguno
     *
     */
    unsigned char claveExterna;
    unsigned char claveInterna;
    int valor = 0;
    map<unsigned char, map<unsigned char, int>>::iterator itEx;
    map<unsigned char, int>::iterator itIn;
    map<unsigned char, int> mapaInterno;

    for (itEx = enrutadores_Vecinos.begin(); itEx != enrutadores_Vecinos.end(); ++itEx) {
        claveExterna = itEx->first;
        cout << "En enrutador: " << claveExterna << endl;
        mapaInterno = itEx->second;

        for (itIn = mapaInterno.begin(); itIn != mapaInterno.end(); ++itIn) {
            claveInterna = itIn->first;
            valor = itIn->second;
            cout << "Enlace: " << claveInterna << ", Valor: " << valor << endl;
        }
    }
}


void red::menu(string ruta)
{
    /*
     * La principal funcion encargada de llamar al menu y a todos nuestros metodos para comenzar con la simulación
     *
     * Inputs de Arugmento:
     *  - Ruta del archivo de la topologia
     *
     * Retornos:
     *  - Ninguno
     *
     */
    int opcion = 0;
    int opcion2 = 0;
    int costoAux = 0;
    int enrutadorDestino = 0;
    float probabilidad = 0;
    char aux;
    map<unsigned char, map<unsigned char, int >> adyacentes_Aux;

    do{

        cout << "Menu Principal" << endl;
        cout << "1. Cargar Red Desde Un Archivo" << endl;
        cout << "2. Generar y Visualizar Tabla de Enrutamiento" << endl;
        cout << "3. Agregar Enrutador" << endl;
        cout << "4. Eliminar Enrutador" << endl;
        cout << "5. Cambiar Costo Entre Nodos" << endl;
        cout << "6. Eliminar Conexion Entre Nodos" << endl;
        cout << "7. Agregar Enlace Entre Nodos" << endl;
        cout << "8. Consultar Costo de Envio" << endl;
        cout << "9. Consultar Camino a Seguir" << endl;
        cout << "10. Generar Red Aleatoria" << endl;
        cout << "11. Listar Enrutadores Activos" << endl;
        cout << "12. Listar Enrutadores Conectados" << endl;
        cout << "13. Limpiar Contenido de Pantalla " << endl;
        cout << "14. Salir" << endl;
        opcion = obtener_Entrada<int>("Ingrese una opcion:", 0, 14);

        switch(opcion){
        case 1:
            cargar_Enrutadores(ruta);
            cout << "Se han cargado estos enrutadores del archivo ubicado en: " << ruta << endl;
            inicializar_Enrutamiento(ruta);
            listar_Enrutadores();
            break;

        case 2:
            enrutamiento_Aux.clear();
            gen_Enrutamiento();
            mostrar_Vecinos();
            cout << "\n" << endl;
            mostrar_EnrutamientoAuxiliar();
            actualizar_Enrutadores();
            break;

        case 3:
            cout << "Ingrese el nombre del enrutador:" << endl;
            cin >> aux;
            if(buscar_Instancia(aux) != -1){
                cout << "No se puede agregar algo que ya existe" << endl;
                break;
            }
            else{
                enrutadores.push_back(aux);
                vector_Instancias.push_back(enrutador(aux));
                adyacentes_Aux[aux][aux] = 0;
                vector_Instancias.at(vector_Instancias.size()-1).setEnrutadoresVecinos(adyacentes_Aux);
                adyacentes_Aux.clear();
            }

            break;

        case 4:
            listar_Enrutadores();
            opcion2 = obtener_Entrada<int>("Ingrese el numero del enrutador:",0,vector_Instancias.size());
            aux = vector_Instancias.at(opcion2-1).getNombre();
            eliminar_Instancia(aux);
            actualizar_Enrutadores();
            break;

        case 5:
            if(enrutadores.empty()){
                cout << "No hay enrutadores disponibles" << endl;
            }
            else{
                cout << "Estos son los enlaces que pueden ser cambiados:" << endl;
                listar_EnlacesCambiantes();
                listar_Enrutadores();
                opcion2 = obtener_Entrada<int>("Ingrese el numero del enrutador de origen:",0,vector_Instancias.size());
                enrutadorDestino = obtener_Entrada<int>("Ingrese el numero del enrutador destino:",0,vector_Instancias.size());
                costoAux = obtener_Entrada<int>("Ingrese el nuevo costo:",0,INT_MAX);
                cambiar_Costo(opcion2,enrutadorDestino,costoAux);
            }
            break;

        case 6:
            cout << "Estos son los enlaces que pueden ser eliminados:" << endl;
            listar_EnlacesCambiantes();
            listar_Enrutadores();
            opcion2 = obtener_Entrada<int>("Ingrese el numero del enrutador de origen:",0,vector_Instancias.size());
            enrutadorDestino = obtener_Entrada<int>("Ingrese el numero del enrutador destino:",0,vector_Instancias.size());
            eliminar_Enlace(opcion2,enrutadorDestino);
            break;

        case 7:
            cout << "Estos son los enlaces que ya existen:" << endl;
            listar_EnlacesCambiantes();
            listar_Enrutadores();
            opcion2 = obtener_Entrada<int>("Ingrese el numero del enrutador de origen:",0,vector_Instancias.size());
            enrutadorDestino = obtener_Entrada<int>("Ingrese el numero del enrutador destino:",0,vector_Instancias.size());
            costoAux = obtener_Entrada<int>("Ingrese el nuevo costo:",0,INT_MAX);
            agregar_Enlace(opcion2,enrutadorDestino,costoAux);
            break;

        case 8:
            if(vector_Instancias.empty()){
                cout << "El vector esta vacio" << endl;
                break;
            }
            listar_Enrutadores();
            opcion2 = obtener_Entrada<int>("Ingrese el enrutador de origen:",0,vector_Instancias.size());
            enrutadorDestino = obtener_Entrada<int>("Ingrese el enrutador de destino:",0,vector_Instancias.size());
            aux = vector_Instancias.at(enrutadorDestino-1).getNombre();
            cout << "El coste de envio del enrutador " << vector_Instancias.at(opcion2-1).getNombre() << " a " << vector_Instancias.at(enrutadorDestino-1).getNombre() << " es: ";
            vector_Instancias.at(opcion2-1).mostrar_Coste(aux);
            break;

        case 9:
            if(vector_Instancias.empty()){
                cout << "El vector esta vacio" << endl;
                break;
            }
            listar_Enrutadores();
            opcion2 = obtener_Entrada<int>("Ingrese el enrutador de origen:",0,vector_Instancias.size());
            enrutadorDestino = obtener_Entrada<int>("Ingrese el enrutador de destino:",0,vector_Instancias.size());
            aux = vector_Instancias.at(enrutadorDestino-1).getNombre();
            mostrar_Camino(vector_Instancias.at(opcion2-1).getNombre(),aux);
            break;

        case 10:
            opcion2 = obtener_Entrada<int>("Ingrese la cantidad de enrutadores:",0,INT_MAX);
            probabilidad = obtener_Entrada<float>("Ingrese la probalidad:",0,1);
            generar_GrafoAleatorio(opcion2,probabilidad);
            inicializar_Enrutamiento();
            break;

        case 11:
            cout << "Los Enrutadores Activos Son:" << endl;
            listar_Enrutadores();
            break;

        case 12:
            cout << "Los Enrutadores Cambiantes Son:" << endl;
            listar_EnlacesCambiantes();
            break;

        case 13:
            system("cls");
            break;
        }

    } while(opcion != 14);
}


//Metodos getter y setter

vector<enrutador> red::getVector_Instancias() const
{
    return vector_Instancias;
}

void red::setVector_Instancias(const vector<enrutador> &newVector_Instancias)
{
    vector_Instancias = newVector_Instancias;
}

list<char> red::getEnrutadores() const
{
    return enrutadores;
}

void red::setEnrutadores(const list<char> &newEnrutadores)
{
    enrutadores = newEnrutadores;
}

map<unsigned char, map<unsigned char, int> > red::getEnrutadores_Vecinos() const
{
    return enrutadores_Vecinos;
}

void red::setEnrutadores_Vecinos(const map<unsigned char, map<unsigned char, int> > &newEnrutadores_Vecinos)
{
    enrutadores_Vecinos = newEnrutadores_Vecinos;
}

map<unsigned char, map<unsigned char, int> > red::getEnrutamiento_Aux() const
{
    return enrutamiento_Aux;
}

void red::setEnrutamiento_Aux(const map<unsigned char, map<unsigned char, int> > &newEnrutamiento_Aux)
{
    enrutamiento_Aux = newEnrutamiento_Aux;
}

map<unsigned char, int> red::getDistancias() const
{
    return distancias;
}

void red::setDistancias(const map<unsigned char, int> &newDistancias)
{
    distancias = newDistancias;
}

map<unsigned char, map<unsigned char, string> > red::getMapa_Caminos() const
{
    return mapa_Caminos;
}

void red::setMapa_Caminos(const map<unsigned char, map<unsigned char, string> > &newMapa_Caminos)
{
    mapa_Caminos = newMapa_Caminos;
}

