#ifndef VERTEX_H
#define VERTEX_H
#include <vector>
#include <memory>
#include <algorithm>
#include "edge.h"
class Vertex
{
    std::string m_name;
    std::vector<std::shared_ptr<Edge<Vertex> > > m_asociateEdges;
public:
    void addEdge(std::shared_ptr<Edge<Vertex> >);
    void deleteEdge(std::shared_ptr<Edge<Vertex> > e);
    Vertex(std::string name);
    std::string name() const;
    std::vector<std::shared_ptr<Vertex> > getNeighbours();
    bool isNotANeighbour(std::shared_ptr<Vertex> v);
    std::vector<std::shared_ptr<Edge<Vertex> > > getAsociateEdges() const;
};

#endif // VERTEX_H
