#ifndef ROADMAP_H
#define ROADMAP_H
#include <map>
#include "vertex.h"
#include "edge.h"
#include <memory>

using edge_ptr = std::shared_ptr<Edge<Vertex> >;
using vertex_ptr = std::shared_ptr<Vertex>;

class RoadMap //Graf reprezentujący autostrady łączące miasta w państwie
{
    std::vector<vertex_ptr > m_cities;
    std::vector<edge_ptr > m_roads;
    std::map<std::string, vertex_ptr > m_mapCityNameToPointer;
public:
    vertex_ptr getVertex(std::string name);
    RoadMap();
    void addCity(vertex_ptr city);
    void buildAirport(edge_ptr highway);
    int connectCities(std::string name1, std::string name2, int distance);


    std::vector<vertex_ptr > getCities() const;
    std::vector<edge_ptr > getRoads() const;
};

#endif // ROADMAP_H
