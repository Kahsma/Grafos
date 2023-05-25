#include <iostream>
#include <vector>
#include <list>
#include <queue>

// Lista de adyacencia
template <class T, class U> // T para el vertice y U para el peso
class Grafo
{

private:
    std::vector<T> vertices; // vector de vertices que me dan el indice en la multilista
    // podríamos usar otra estructura lineal (lista)
    std::vector<std::list<std::pair<int, U>>> aristas; // cuidad con el espacio (no es >>)
    // Se puede definir un TAD para el vertice o para la arista

public:
    Grafo() {} // Constructor por defecto

    void setVertices(std::vector<T> v)
    {
        vertices = v;
    }

    void setAristas(std::vector<std::list<std::pair<int, U>>> a)
    {
        aristas = a;
    }

    std::vector<T> getVertices()
    {
        return vertices;
    }

    std::vector<std::list<std::pair<int, U>>> getAristas()
    {
        return aristas;
    }

    // función que define la cantidad de vertices, retorna un entero
    int cantVertices() { return vertices.size(); }

    // función que define la cantidad de aristas, retorna un entero
    // suma el tamaño de cada lista
    int cantAristas()
    {
        int suma = 0;
        for (int i = 0; i < cantVertices(); i++)
        {
            suma += aristas[i].size();
        }
        return suma;
    }

    // función que busca un vertice retorna la posición, en el vector inicial
    // T debe poderse comparar, si es un TAD es necesario sobrecargarlo o hacer una función que compare
    int buscarVertice(T vert)
    {
        int ind = -1;
        for (int i = 0; i < cantVertices(); i++)
        {
            if (vertices[i] == vert)
                ind = i;
        }
        return ind;
    }

    // función para insertar un vertice
    // aumentar una nueva lista al vector de listas
    bool insertarVertice(T vert)
    {
        bool res = false; // dice si lo pudo insertar o si ya estaba
        if (buscarVertice(vert) == -1)
        {
            vertices.push_back(vert);                                     // aumenta el vector de vertices
            std::list<pair<int, U>> *nlist = new std::list<pair<int, U>>; // crea una nueva lista (asignando memoria)
            aristas.push_back(*nlist);                                    // inserta la nueva lista
        }
        return res;
    }

    // función que inserta una arista retora un bool
    bool insertarArista(T ori, T des, U cos)
    {
        bool res = false;
        int i_ori = buscarVertice(ori); // verificar que los vertices existan
        int i_des = buscarVertice(des);
        if (i_ori != -1 && i_des != -1)
        {
            bool esta = false;                                                 // dice si el vertice destino está en la lista
            std::list<pair<int, U>>::iterator itList = aristas[i_ori].begin(); // iterador que va sobre una lista de pares
            for (; itList != aristas[i_ori].end(); itList++)
            { // recorre la lista del vertice origen
                if (itList->first == i_des)
                    esta = true; // compara el primer dato del par y si lo encuenta dice que si estaba el destino
            }
            if (!esta)
            {                                           // si no estaba lo puedo agreagar
                pair<int, U> *n_par = new pair<int, U>; // asigna memoria para un nuevo par
                n_par->first = i_des;
                n_par->second = cos;
                aristas[i_ori].push_back(*n_par); // lo inserta en la lista
                res = true;
            }
        }
        return res;
    }

    // función que busca la arista y retornar el costo (positivo)
    U buscarArista(T ori, T des)
    {
        U res = -1;
        int i_ori = buscarVertice(ori); // busca el origen y el destino
        int i_des = buscarVertice(des);
        if (i_ori != -1 && i_des != -1)
        {
            std::list<pair<int, U>>::iterator itList = aristas[i_ori].begin(); // iterador para recorrer la lista
            for (; itList != aristas[i_ori].end(); itList++)
            {
                if (itList->first == i_des)
                    res = itList->second; // si lo encuentra guarda el costo del par
            }
        }
        return res;
    }

    // función que elimina el vertice retorna un bool
    bool eliminarVertice(T vert)
    {
        bool res = false;
        int i_vert = buscarVertice(vert); // busca el vertice y obtiene el indice
        if (i_vert != -1)
        {
            std::vector<std::list<pair<int, U>>>::iterator itA, posE; // iterador para la lista externa
            int ind = 0;
            for (itA = aristas.begin(); itA != aristas.end(); itA++, ind++)
            {
                if (ind == i_vert)
                {               // estoy en la lista a eliminar
                    posE = itA; // almacena la posicion de la lista a eliminar
                }
                else
                {
                    std::list<pair<int, U>>::iterator itList, posEE; // iterador para las listas internas
                    for (itList = itA->begin(); itList != itA->end(); itList++)
                    {
                        if (itList->first == i_vert)
                        {
                            posEE = itList; // lo almaceno si está en la lista de ese vertice
                        }
                        else if (itList->first > i_vert)
                        {
                            itList->first--; // actualiza los índices mayores que el eliminado
                        }
                    }
                    itA->erase(posEE); // elimina la posición interna
                }
            }
            aristas.erase(posE);                       // elimina la lista completa de ese vertice (origen)
            vertices.erase(vertices.begin() + i_vert); // elimina el vertice del vector de vertices
            res = true;
        }
        return res;
    }
    // función que elimina la arista retorna un bool
    bool eliminarArista(T ori, T des)
    {
        bool res = false;
        int i_ori = buscarVertice(ori); // busca los indices de los vertices
        int i_des = buscarVertice(des);
        if (i_ori != -1 && i_des != -1)
        {
            std::list<pair<int, U>>::iterator itList, posE; // iterador para recorrer la lista interna del vertice origen
            for (itList = aristas[i_ori].begin(); itList != aristas[i_ori].end(); itList++)
            {
                if (itList->first == i_des)
                    posE = itList; // si encuentra el indice destino guarda la posicion
            }
            aristas[i_ori].erase(posE); // elimina ese par de la lista del vertice origen
        }
        return res;
    }

    void recorridoPlano(std::vector<std::list<std::pair<int, U>>> &aristas, int nodo, std::vector<bool> &visitado, std::vector<int> &recorrido)
    {
        visitado[nodo] = true;
        recorrido.push_back(nodo);

        for (const auto &arista : aristas[nodo])
        {
            int vecino = arista.first;
            if (!visitado[vecino])
            {
                recorridoPlano(aristas, vecino, visitado, recorrido);
                recorrido.push_back(nodo);
            }
        }
    }

    std::vector<int> recorridoPlano(Grafo<T, U> &grafo)
    {
        std::vector<bool> visitado(grafo.cantVertices(), false);
        std::vector<int> recorrido;

        recorridoPlano(grafo.getAristas(), 0, visitado, recorrido);

        return recorrido;
    }

    void recorridoProfundidad(std::vector<std::list<pair<int, U>>> &aristas, int nodo, std::vector<bool> &visitado, std::vector<int> &recorrido)
    {
        visitado[nodo] = true;
        recorrido.push_back(nodo);

        for (const auto &arista : aristas[nodo])
        {
            int vecino = arista.first;
            if (!visitado[vecino])
            {
                recorridoProfundidad(aristas, vecino, visitado, recorrido);
            }
        }
    }

    std::vector<int> recorridoProfundidad(Grafo<T, U> &grafo)
    {
        std::vector<bool> visitado(grafo.cantVertices(), false);
        std::vector<int> recorrido;

        recorridoProfundidad(grafo.getAristas(), 0, visitado, recorrido);

        return recorrido;
    }

    void recorridoAnchura(std::vector<std::list<pair<int, U>>> &aristas, int nodo, std::vector<bool> &visitado, std::vector<int> &recorrido)
    {
        std::queue<int> cola;
        visitado[nodo] = true;
        cola.push(nodo);

        while (!cola.empty())
        {
            int actual = cola.front();
            cola.pop();
            recorrido.push_back(actual);

            for (const auto &arista : aristas[actual])
            {
                int vecino = arista.first;
                if (!visitado[vecino])
                {
                    visitado[vecino] = true;
                    cola.push(vecino);
                }
            }
        }
    }

    std::vector<int> recorridoAnchura(Grafo<T, U> &grafo)
    {
        std::vector<bool> visitado(grafo.cantVertices(), false);
        std::vector<int> recorrido;

        recorridoAnchura(grafo.getAristas(), 0, visitado, recorrido);

        return recorrido;
    }

    void recorridoAnchura(std::vector<std::list<pair<int, U>>> &aristas, int nodo, std::vector<bool> &visitado, std::vector<int> &recorrido)
    {
        std::queue<int> cola;
        visitado[nodo] = true;
        cola.push(nodo);

        while (!cola.empty())
        {
            int actual = cola.front();
            cola.pop();
            recorrido.push_back(actual);

            for (const auto &arista : aristas[actual])
            {
                int vecino = arista.first;
                if (!visitado[vecino])
                {
                    visitado[vecino] = true;
                    cola.push(vecino);
                }
            }
        }
    }

    std::vector<int> recorridoAnchura(Grafo<T, U> &grafo)
    {
        std::vector<bool> visitado(grafo.cantVertices(), false);
        std::vector<int> recorrido;

        recorridoAnchura(grafo.getAristas(), 0, visitado, recorrido);

        return recorrido;
    }

    void dfsComponentesConectados(std::vector<std::list<pair<int, U>>> &aristas, int nodo, std::vector<bool> &visitado, std::list<int> &componente)
    {
        visitado[nodo] = true;
        componente.push_back(nodo);

        for (const auto &arista : aristas[nodo])
        {
            int vecino = arista.first;
            if (!visitado[vecino])
            {
                dfsComponentesConectados(aristas, vecino, visitado, componente);
            }
        }
    }

    std::vector<std::list<int>> componentesConectados(Grafo<T, U> &grafo)
    {
        std::vector<bool> visitado(grafo.cantVertices(), false);
        std::vector<std::list<int>> componentes;

        for (int nodo = 0; nodo < grafo.cantVertices(); nodo++)
        {
            if (!visitado[nodo])
            {
                std::list<int> componente;
                dfsComponentesConectados(grafo.getAristas(), nodo, visitado, componente);
                componentes.push_back(componente);
            }
        }

        return componentes;
    }

    void dfsAristasPuente(std::vector<std::list<pair<int, U>>> &aristas, int nodo, int padre, std::vector<bool> &visitado, std::vector<int> &tiempoDescubrimiento, std::vector<int> &tiempoMenorDescubrimiento, std::vector<bool> &esAristaPuente, int &tiempo)
    {
        visitado[nodo] = true;
        tiempo++;
        tiempoDescubrimiento[nodo] = tiempo;
        tiempoMenorDescubrimiento[nodo] = tiempo;

        for (const auto &arista : aristas[nodo])
        {
            int vecino = arista.first;
            if (!visitado[vecino])
            {
                dfsAristasPuente(aristas, vecino, nodo, visitado, tiempoDescubrimiento, tiempoMenorDescubrimiento, esAristaPuente, tiempo);
                tiempoMenorDescubrimiento[nodo] = std::min(tiempoMenorDescubrimiento[nodo], tiempoMenorDescubrimiento[vecino]);
                if (tiempoDescubrimiento[nodo] < tiempoMenorDescubrimiento[vecino])
                {
                    esAristaPuente[arista.second] = true;
                }
            }
            else if (vecino != padre)
            {
                tiempoMenorDescubrimiento[nodo] = std::min(tiempoMenorDescubrimiento[nodo], tiempoDescubrimiento[vecino]);
            }
        }
    }

    std::vector<bool> aristasPuente(Grafo<T, U> &grafo)
    {
        int n = grafo.cantAristas();
        std::vector<bool> esAristaPuente(n, false);

        std::vector<bool> visitado(grafo.cantVertices(), false);
        std::vector<int> tiempoDescubrimiento(grafo.cantVertices());
        std::vector<int> tiempoMenorDescubrimiento(grafo.cantVertices());
        int tiempo = 0;

        dfsAristasPuente(grafo.getAristas(), 0, -1, visitado, tiempoDescubrimiento, tiempoMenorDescubrimiento, esAristaPuente, tiempo);

        return esAristaPuente;
    }

    bool esPonte(std::vector<std::list<pair<int, U>>> &aristas, int origen, int destino)
    {
        if (aristas[origen].size() == 1)
        {
            return true;
        }

        std::vector<bool> visitado(aristas.size(), false);
        std::queue<int> cola;
        cola.push(origen);

        while (!cola.empty())
        {
            int actual = cola.front();
            cola.pop();
            visitado[actual] = true;

            if (actual == destino && aristas[actual].size() == 1)
            {
                return true;
            }

            for (const auto &arista : aristas[actual])
            {
                int vecino = arista.first;
                if (!visitado[vecino])
                {
                    cola.push(vecino);
                }
            }
        }

        return false;
    }

    void fleuryRecursivo(std::vector<std::list<pair<int, U>>> &aristas, int nodo, std::vector<int> &camino)
    {
        for (const auto &arista : aristas[nodo])
        {
            int vecino = arista.first;
            if (!esPonte(aristas, nodo, vecino))
            {
                camino.push_back(vecino);
                aristas[nodo].remove({vecino, arista.second});
                aristas[vecino].remove({nodo, arista.second});
                fleuryRecursivo(aristas, vecino, camino);
                return;
            }
        }
    }

    std::vector<int> fleury(Grafo<T, U> &grafo)
    {
        std::vector<int> camino;
        camino.push_back(0);

        std::vector<std::list<pair<int, U>>> aristas = grafo.getAristas();
        fleuryRecursivo(aristas, 0, camino);

        return camino;
    }
};
