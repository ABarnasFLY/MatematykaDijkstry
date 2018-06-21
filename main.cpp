//Narzędzia komputerowe w rozwiązywaniu zagadnień matematyki wyższej
//Zespół: Katarzyna Kopel, Katarzyna Płaneta, Agnieszka Lupierz, Adrian Barnaś

//Temat 3:
//Lotnisko w San Escobar pęka w szwach! To oczywiście efekt ogromnego ruchu lotniczego
//z Polski, jaki nastąpił po nawiązaniu stosunków dyplomatycznych między oboma krajami. Jako
//minister transportu republiki postanowiłaś wybudować nowe lotnisko dla naszych narodowych
//linii lotniczych El Niño i to natychmiast. W tym celu na pas startowy zostanie przerobiony jeden z
//odcinków sieci autostrad w naszym kraju. Sieć autostrad na planach ma kształt grafu, a
//wierzchołkami są poszczególne miasta. Napisz algorytm, który ustali, który odcinek sieci
//autostrad należy poświęcić pod pas startowy, tak aby suma odległości ze stolicy kraju, Santo
//Subito, do pozostałych miast pozostała jak najmniejsza.

//Istotą zadania jest znalezienie krawędzi w grafie z wagami, która nie jest elementem żadnej najkrótszej
//ścieżki do Santo Subito, lub krawędzi dla której istnieje alternatywna droga tej samej długości.

//Do wykonania zadania są dwie drogi.
//>wyznaczenie najkrótszych dróg do Santo Subito i sprawdzenie które z krawędzi nie są ich częścią
//>iteracyjne usuwanie krawgędzi i liczenie sumy odległości po każdym kroku |<- wybraliśmy tą ścieżkę |


//Wejście:
//Plik Mapa.txt znajdująca się w tym samym katalo co plik wykonywalny
//W pliku lista krawędzi (autostrad) przykład:
//Kraków;Tarnów;100
//oznacza krawędź między Tarnowem a Krakowem o długości 100km

//Wyjście
//Na konsoli pojawi się informacja o tym które z autostrad można wykorzystać do budowy lotniska

#include <iostream>
#include <limits>
#include "roadmap.h"
using namespace std;

//modifikacja algorytmu Dijkstry [wyznaczamy same odległości bez najkrótszych ścierzek]
int sumOfDistancesFromSantoSubito(RoadMap& SanEscobar)
{
    bool SantoSubitoPresent = false;
    std::map<std::string, int> l;
    std::vector<std::string> cities_left_to_check;
    std::vector<std::shared_ptr<Vertex> > cities = SanEscobar.getCities();
    for(int i =0; i < cities.size(); i++) // Uzupełnienie przypisania l(city) i wektora miast do wyznaczania odległości
    {
        l.insert(std::pair<std::string, int> (cities[i]->name(),std::numeric_limits<int>::max()));
        cities_left_to_check.push_back(cities[i]->name());
        if(cities[i]->name() == "Santo Subito")
        {
            SantoSubitoPresent = true;
            l["Santo Subito"] = 0; //pierwszy krok algorytmu. Do Santo Subito przypisujemy wartość "0"
        }
    }
    if(!SantoSubitoPresent) return -1; //Na mapie nie ma Santo Subito
    for(int i = 0; i < cities.size()-1; i++) //iterator i zlicza kroki ale nie służy wskazywaniu pól w mapie
    {
        std::shared_ptr<Vertex> city;

        //Znaleźć miasto z minimalnym l nie należoącym do done
        int min = std::numeric_limits<int>::max(); // minimum na wartość maksymalną
        std::string minCity;
        std::vector<std::string>::iterator curent;
        for(std::vector<std::string>::iterator it = cities_left_to_check.begin() ; it != cities_left_to_check.end(); it++)
        {
            if(l[*it] < min)
            {
                min = l[*it];
                minCity = *it;
                curent = it;
            }
        } // found city with miniumum l
        city = SanEscobar.getVertex(minCity);
        std::vector<std::shared_ptr<Edge<Vertex> > > edges = city->getAsociateEdges();
        for(int j=0; j< edges.size(); j++)
        {
            std::shared_ptr<Vertex> neighbour = edges[j]->getSecondEnd(city.get());
            int distance = edges[j]->getDistance();
            if(l[neighbour->name()] > l[city->name()] + distance) l[neighbour->name()] = l[city->name()] + distance;
        }
        cities_left_to_check.erase(curent);// dodanie miasta do listy zrobionych
    }
    int sum = 0;

    for(std::map<std::string, int>::iterator it = l.begin(); it != l.end(); it++)
    {
        sum+= it->second;
    }
    return sum;
}

int main(int argc, char *argv[])
{
    RoadMap map;
    map.addCity(std::shared_ptr<Vertex>(new Vertex("Santiago")));
    map.addCity(std::shared_ptr<Vertex>(new Vertex("Ronaldo")));
    map.addCity(std::shared_ptr<Vertex>(new Vertex("Oranje")));
    map.addCity(std::shared_ptr<Vertex>(new Vertex("Tutto Bene")));
    map.addCity(std::shared_ptr<Vertex>(new Vertex("Loco Maroco")));
    map.addCity(std::shared_ptr<Vertex>(new Vertex("San Tana")));
    map.addCity(std::shared_ptr<Vertex>(new Vertex("Santo Subito")));
    map.connectCities("Santo Subito","Santiago", 40);
    map.connectCities("Santo Subito","Ronaldo", 20);
    map.connectCities("Santo Subito","Tutto Bene", 30);
    map.connectCities("Santo Subito","Loco Maroco", 20);
    map.connectCities("Loco Maroco","Santiago", 100);
    map.connectCities("Ronaldo","Oranje", 50);
    map.connectCities("Tutto Bene","Oranje", 30);
    map.connectCities("Loco Maroco","San Tana", 30);
    map.connectCities("Tutto Bene","San Tana", 10);
    map.connectCities("Oranje","San Tana", 80);
    int sum = sumOfDistancesFromSantoSubito(map);
    std::vector<std::shared_ptr<Edge<Vertex> > > candidates = map.getRoads();
    for(std::vector<std::shared_ptr<Edge<Vertex> > >::iterator it = candidates.begin(); it != candidates.end(); it++)
    {
        map.buildAirport(*it); //Zbudujmy lotnisko na próbę
        if(sumOfDistancesFromSantoSubito(map) == sum) //I zmierzmy odległości
            std::cout << "Highway between: " << (*it)->ends().first->name() << " and: " << (*it)->ends().second->name() << " may be an airport!\n";
        map.connectCities((*it)->ends().first->name(),(*it)->ends().second->name(), (*it)->getDistance()); //Odbuduj drogę
    }


}
