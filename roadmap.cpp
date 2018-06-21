#include "roadmap.h"
#include <iostream>
RoadMap::RoadMap()
{

}

void RoadMap::addCity(std::shared_ptr<Vertex> city)
{
    m_cities.push_back(city);
    m_mapCityNameToPointer.insert(std::pair<std::string, std::shared_ptr<Vertex> >(city->name(), city) );
}

void RoadMap::buildAirport(std::shared_ptr<Edge<Vertex> > highway)
{
    highway->ends().first->deleteEdge(highway);
    highway->ends().second->deleteEdge(highway);
    m_roads.erase(std::find(m_roads.begin(), m_roads.end(), highway));
}

int RoadMap::connectCities(std::string name1, std::string name2, int distance)
{
    try
    {
        if(getVertex(name2)->isNotANeighbour(getVertex(name2)))
        {
            std::shared_ptr<Edge<Vertex> > edge_ptr((new Edge<Vertex>(getVertex(name1),getVertex(name2), distance)));
            m_roads.push_back(edge_ptr);
            getVertex(name1)->addEdge(edge_ptr);
            getVertex(name2)->addEdge(edge_ptr);
        }
        else return 1; //Already Connected
    }
    catch(std::exception)
    {
        std::cout << "City not found!\n";
        return 2; //City not found
    }
}

std::vector<std::shared_ptr<Vertex> > RoadMap::getCities() const
{
    return m_cities;
}

std::vector<std::shared_ptr<Edge<Vertex> > > RoadMap::getRoads() const
{
    return m_roads;
}

std::shared_ptr<Vertex> RoadMap::getVertex(std::string name)
{
    return m_mapCityNameToPointer.at(name);
}
