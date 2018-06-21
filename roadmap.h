#ifndef ROADMAP_H
#define ROADMAP_H
#include <map>
#include "vertex.h"
#include "edge.h"
#include <memory>

class RoadMap //Graf reprezentujący autostrady łączące miasta w państwie
{
    std::vector<std::shared_ptr<Vertex> > m_cities;
    std::vector<std::shared_ptr<Edge<Vertex> > > m_roads;
    std::map<std::string, std::shared_ptr<Vertex> > m_mapCityNameToPointer;
public:
    std::shared_ptr<Vertex> getVertex(std::string name);
    RoadMap();
    void addCity(std::shared_ptr<Vertex> city);
    void buildAirport(std::shared_ptr<Edge<Vertex> > highway);
    int connectCities(std::string name1, std::string name2, int distance);


    std::vector<std::shared_ptr<Vertex> > getCities() const;
    std::vector<std::shared_ptr<Edge<Vertex> > > getRoads() const;
};

#endif // ROADMAP_H
