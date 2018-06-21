#ifndef EDGE_H
#define EDGE_H

#include <utility>
#include <memory>
template <class T>
class Edge
{
    std::pair<std::shared_ptr<T> , std::shared_ptr<T> > m_ends;
    int distance;
public:
    Edge(std::shared_ptr<T> V1, std::shared_ptr<T> V2, int s)
    :m_ends(V1,V2), distance(s)
    {

    }

    std::shared_ptr<T> getSecondEnd(auto end)
    {
        if(m_ends.first.get() == end) return m_ends.second;
        else if(m_ends.second.get() == end) return m_ends.first;
        else return nullptr;
    }
    std::pair<std::shared_ptr<T>, std::shared_ptr<T> > ends() const
    {
        return m_ends;
    }
    int getDistance() const
    {
        return distance;
    }
};



#endif // EDGE_H
