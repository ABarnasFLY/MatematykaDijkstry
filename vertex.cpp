#include "vertex.h"

std::string Vertex::name() const
{
    return m_name;
}

std::vector<std::shared_ptr<Vertex> > Vertex::getNeighbours()
{
    std::vector<std::shared_ptr<Vertex> > temporary;
    for(int i = 0; i< m_asociateEdges.size(); i++)
    {
        temporary.push_back(m_asociateEdges[i]->getSecondEnd(this));
    }
}

bool Vertex::isNotANeighbour(std::shared_ptr<Vertex> v)
{
    bool temporary = true;
    for(int i = 0; i < m_asociateEdges.size(); i++)
    {
        if(m_asociateEdges[i]->getSecondEnd(this) == v) temporary = false;
    }
    return temporary;
}

std::vector<std::shared_ptr<Edge<Vertex> > > Vertex::getAsociateEdges() const
{
    return m_asociateEdges;
}

void Vertex::addEdge(std::shared_ptr<Edge<Vertex> > e)
{
    m_asociateEdges.push_back(e);
}

void Vertex::deleteEdge(std::shared_ptr<Edge<Vertex> > e)
{
    m_asociateEdges.erase(std::find(m_asociateEdges.begin(),m_asociateEdges.end(), e));
}

Vertex::Vertex(std::string name)
    :m_name(name)
{

}

