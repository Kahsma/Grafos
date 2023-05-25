#include <iostream>
#include <vector>
#include <queue>

template <class T, class U>
class Grafo
{
public:
    Grafo()
    {
        aristas.resize(0);
    }

    void setVertices(std::vector<T> v)
    {
        vertices = v;
        aristas.resize(vertices.size(), std::vector<U>(vertices.size(), 0));
    }

    void setAristas(std::vector<std::vector<U>> a)
    {
        aristas = a;
    }

    std::vector<T> getVertices()
    {
        return vertices;
    }

    std::vector<std::vector<U>> getAristas()
    {
        return aristas;
    }

    int cantVertices()
    {
        return vertices.size();
    }

    int cantAristas()
    {
        int suma = 0;
        for (int i = 0; i < cantVertices(); i++)
        {
            for (int j = 0; j < cantVertices(); j++)
            {
                if (aristas[i][j] != 0)
                    suma++;
            }
        }
        return suma;
    }

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

    bool insertarVertice(T vert)
    {
        bool res = false;
        if (buscarVertice(vert) == -1)
        {
            vertices.push_back(vert);
            aristas.resize(cantVertices(), std::vector<U>(cantVertices(), 0));
            res = true;
        }
        return res;
    }

    bool eliminarVertice(T vert)
    {
        int ind = buscarVertice(vert);
        if (ind != -1)
        {
            vertices.erase(vertices.begin() + ind);
            aristas.erase(aristas.begin() + ind);
            for (auto &fila : aristas)
            {
                fila.erase(fila.begin() + ind);
            }
            return true;
        }
        return false;
    }

    bool insertarArista(T ori, T des, U cos)
    {
        int i_ori = buscarVertice(ori);
        int i_des = buscarVertice(des);
        if (i_ori != -1 && i_des != -1)
        {
            if (aristas[i_ori][i_des] == 0)
            {
                aristas[i_ori][i_des] = cos;
                return true;
            }
        }
        return false;
    }

    U buscarArista(T ori, T des)
    {
        int i_ori = buscarVertice(ori);
        int i_des = buscarVertice(des);
        if (i_ori != -1 && i_des != -1)
        {
            return aristas[i_ori][i_des];
        }
        return -1;
    }

    bool eliminarArista(T ori, T des)
    {
        int i_ori = buscarVertice(ori);
        int i_des = buscarVertice(des);
        if (i_ori != -1 && i_des != -1)
        {
            aristas[i_ori][i_des] = 0;
            return true;
        }
        return false;
    }

    void recorridoPlano()
    {
        for (const T &vertice : vertices)
        {
            std::cout << vertice << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < cantVertices(); i++)
        {
            std::cout << vertices[i] << " ";
            for (int j = 0; j < cantVertices(); j++)
            {
                std::cout << aristas[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void recorridoAnchura(T vert)
    {
        int origen = buscarVertice(vert);
        if (origen == -1)
            return;

        std::vector<bool> visitados(cantVertices(), false);
        std::queue<int> cola;
        visitados[origen] = true;
        cola.push(origen);

        while (!cola.empty())
        {
            int actual = cola.front();
            cola.pop();
            std::cout << vertices[actual] << " ";

            for (int i = 0; i < cantVertices(); i++)
            {
                if (aristas[actual][i] != 0 && !visitados[i])
                {
                    visitados[i] = true;
                    cola.push(i);
                }
            }
        }
        std::cout << std::endl;
    }

private:
    std::vector<T> vertices;
    std::vector<std::vector<U>> aristas;
};

int main()
{
    // Crear un grafo de tipo Grafo<int, int>
    Grafo<int, int> miGrafo;

    // Insertar vértices
    miGrafo.insertarVertice(1);
    miGrafo.insertarVertice(2);
    miGrafo.insertarVertice(3);
    miGrafo.insertarVertice(4);
    miGrafo.insertarVertice(5);

    // Insertar aristas
    miGrafo.insertarArista(1, 2, 10);
    miGrafo.insertarArista(1, 3, 5);
    miGrafo.insertarArista(2, 4, 8);
    miGrafo.insertarArista(3, 5, 3);
    miGrafo.insertarArista(4, 5, 2);

    // Imprimir los vértices y aristas del grafo
    std::cout << "Vertices y aristas del grafo:" << std::endl;
    miGrafo.recorridoPlano();
    std::cout << std::endl;

    // Recorrido en anchura desde el vértice 1
    std::cout << "Recorrido en anchura desde el vertice 1:" << std::endl;
    miGrafo.recorridoAnchura(1);
    std::cout << std::endl;

    // Eliminar un vértice y una arista
    miGrafo.eliminarVertice(3);
    miGrafo.eliminarArista(2, 4);

    // Imprimir los vértices y aristas actualizados del grafo
    std::cout << "Vertices y aristas del grafo actualizados:" << std::endl;
    miGrafo.recorridoPlano();
    std::cout << std::endl;

    return 0;
}

