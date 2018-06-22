#ifndef VERTEX_H
#define VERTEX_H
#include <vector>
#include <memory>
#include <algorithm>
#include "edge.h"



class Vertex
{
    using edge_ptr = std::shared_ptr<Edge<Vertex> >;
    using vertex_ptr = std::shared_ptr<Vertex>;
    std::string m_name;
    std::vector<edge_ptr> m_asociateEdges;
public:
    void addEdge(edge_ptr);
    void deleteEdge(edge_ptr e);
    Vertex(std::string name);
    std::string name() const;
    std::vector<vertex_ptr> getNeighbours();
    bool isNotANeighbour(std::shared_ptr<Vertex> v);
    std::vector<edge_ptr> getAsociateEdges() const;
};

#endif // VERTEX_H
