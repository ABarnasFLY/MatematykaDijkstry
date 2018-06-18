#ifndef VERTEX_H
#define VERTEX_H


class Vertex
{
    std::string m_name;
    std::vector<std::shared_ptr<Edge> > m_edges;
public:
    Vertex(std::string name);
};

#endif // VERTEX_H
