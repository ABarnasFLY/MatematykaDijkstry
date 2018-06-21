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
#include <fstream>
#include "roadmap.h"

//modifikacja algorytmu Dijkstry [wyznaczamy same odległości bez najkrótszych ścierzek]
int sumOfDistancesFromSantoSubito(RoadMap& SanEscobar)
{
    bool SantoSubitoPresent = false;
    std::map<std::string, int> l;
    std::vector<std::string> cities_left_to_check;
    std::vector<std::shared_ptr<Vertex> > cities = SanEscobar.getCities();
    for(size_t i =0; i < cities.size(); i++) // Uzupełnienie przypisania l(city) i wektora miast do wyznaczania odległości
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
    for(size_t i = 0; i < cities.size()-1; i++) //iterator i zlicza kroki ale nie służy wskazywaniu pól w mapie
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
        } // znaleziono miasto z najmniejszym l
        city = SanEscobar.getVertex(minCity);
        std::vector<std::shared_ptr<Edge<Vertex> > > edges = city->getAsociateEdges();
        for(size_t j=0; j< edges.size(); j++)
        {
            std::shared_ptr<Vertex> neighbour = edges[j]->getSecondEnd(city.get());
            int distance = edges[j]->getDistance();
//l(v) przypisujemy wartość odległości od San Tana przez badany wierzchołek jeśli jest mniejsza dotychczas przypisana wierzchołkowi
            l[neighbour->name()] = std::min(l[neighbour->name()], l[city->name()] + distance);
        }
        cities_left_to_check.erase(curent);// usunięcie z listy niezbadanych wierzchołków
    }
    int sum = 0;
//suma odległości
    for(std::map<std::string, int>::iterator it = l.begin(); it != l.end(); it++)
    {
        sum+= it->second;
    }
    return sum;
}

void readFromFile(RoadMap& map)
{
    std::string line;
    std::ifstream myfile ("mapa.txt");
    std::vector<std::string> cities1, cities2, distance, added;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cities1.push_back(line.substr(0,line.find(";")));
            line.erase(0,line.find(";")+1);
            cities2.push_back(line.substr(0, line.find(";")));
            line.erase(0,line.find(";")+1);
            distance.push_back(line);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file\n";

    for(size_t i = 0; i < cities1.size(); i++)
    {
        if(find(added.begin(),added.end(),cities1[i])==added.end())
        {
            map.addCity(std::shared_ptr<Vertex>(new Vertex(cities1[i])));
            added.push_back(cities1[i]);
        }

        if(find(added.begin(),added.end(),cities2[i])==added.end())
        {
            map.addCity(std::shared_ptr<Vertex>(new Vertex(cities2[i])));
            added.push_back(cities2[i]);
        }
        map.connectCities(cities1[i],cities2[i],std::stoi(distance[i]));
    }

}

int main()
{
    RoadMap map;
    readFromFile(map);
/*    map.addCity(std::shared_ptr<Vertex>(new Vertex("Santiago")));
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
*/    int sum = sumOfDistancesFromSantoSubito(map);
    std::vector<std::shared_ptr<Edge<Vertex> > > candidates = map.getRoads();
    for(std::vector<std::shared_ptr<Edge<Vertex> > >::iterator it = candidates.begin(); it != candidates.end(); it++)
    {
        map.buildAirport(*it); //Zbudujmy lotnisko na próbę
        if(sumOfDistancesFromSantoSubito(map) == sum) //I zmierzmy odległości
            std::cout << "Highway between: " << (*it)->ends().first->name() << " and: " << (*it)->ends().second->name() << " may be an airport!\n";
        map.connectCities((*it)->ends().first->name(),(*it)->ends().second->name(), (*it)->getDistance()); //Odbuduj drogę
    }


}
