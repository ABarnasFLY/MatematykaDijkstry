#include "vertex.h"

using edge_ptr = std::shared_ptr<Edge<Vertex> >;
using vertex_ptr = std::shared_ptr<Vertex>;

std::string Vertex::name() const
{
    return m_name;
}

std::vector<Vertex::vertex_ptr> Vertex::getNeighbours()
{
    std::vector<vertex_ptr > temporary;
    for(int i = 0; i< m_asociateEdges.size(); i++)
    {
        temporary.push_back(m_asociateEdges[i]->getSecondEnd(this));
    }
}

bool Vertex::isNotANeighbour(vertex_ptr v)
{
    bool temporary = true;
    for(int i = 0; i < m_asociateEdges.size(); i++)
    {
        if(m_asociateEdges[i]->getSecondEnd(this) == v) temporary = false;
    }
    return temporary;
}

std::vector<Vertex::edge_ptr> Vertex::getAsociateEdges() const
{
    return m_asociateEdges;
}

void Vertex::addEdge(edge_ptr e)
{
    m_asociateEdges.push_back(e);
}

void Vertex::deleteEdge(edge_ptr e)
{
    m_asociateEdges.erase(std::find(m_asociateEdges.begin(),m_asociateEdges.end(), e));
}

Vertex::Vertex(std::string name)
    :m_name(name)
{

}

