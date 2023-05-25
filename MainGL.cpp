#include <iostream>
#include <vector>
#include <list>
#include <utility>        // Para std::pair
#include "GrafoLista.hxx" // Incluir el archivo de encabezado con la definición de Grafo

int main()
{
    // Crear un objeto de la clase Grafo
    Grafo<int, int> grafo;

    // Insertar vértices
    grafo.insertarVertice(1);
    grafo.insertarVertice(2);
    grafo.insertarVertice(3);
    grafo.insertarVertice(4);
    grafo.insertarVertice(5);

    // Insertar aristas
    grafo.insertarArista(1, 2, 10);
    grafo.insertarArista(1, 3, 5);
    grafo.insertarArista(2, 4, 7);
    grafo.insertarArista(3, 4, 2);
    grafo.insertarArista(4, 5, 1);

    // Obtener y mostrar los vértices y aristas del grafo
    std::vector<int> vertices = grafo.getVertices();
    std::vector<std::list<std::pair<int, int>>> aristas = grafo.getAristas();

    std::cout << "Vertices: ";
    for (const auto &vertice : vertices)
    {
        std::cout << vertice << " ";
    }
    std::cout << std::endl;

    // Obtener la cantidad de vértices y aristas del grafo
    int cantVertices = grafo.cantVertices();
    int cantAristas = grafo.cantAristas();

    std::cout << "Cantidad de vértices: " << cantVertices << std::endl;
    std::cout << "Cantidad de aristas: " << cantAristas << std::endl;

    // Buscar un vértice y una arista en el grafo
    int verticeBuscado = 3;
    int aristaBuscada = grafo.buscarArista(2, 4);

    if (aristaBuscada != -1)
    {
        std::cout << "La arista entre los vértices 2 y 4 tiene un costo de: " << aristaBuscada << std::endl;
    }
    else
    {
        std::cout << "No se encontró la arista entre los vértices 2 y 4" << std::endl;
    }

    // Eliminar un vértice y una arista del grafo
    bool verticeEliminado = grafo.eliminarVertice(3);
    bool aristaEliminada = grafo.eliminarArista(2, 4);

    if (verticeEliminado)
    {
        std::cout << "Se eliminó el vértice 3 del grafo" << std::endl;
    }
    else
    {
        std::cout << "No se encontró el vértice 3 en el grafo" << std::endl;
    }

    if (aristaEliminada)
    {
        std::cout << "Se eliminó la arista entre los vértices 2 y 4 del grafo" << std::endl;
    }
    else
    {
        std::cout << "No se encontró la arista entre los vértices 2 y 4 en el grafo" << std::endl;
    }

    return 0;
}
