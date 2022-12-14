#include <iostream>
#include "flightgraph.h"
#include "Flight.h"
#include "Airport.h"

using namespace std;

int main()
{
    // Write your own main here
    cout << "Welcome to the Optimal Flight Tracker Tool!" << endl;
    cout << "We will help you find the best travel path for you." << endl;
    cout << "Please enter the IATA code for your starting airport (EX: ORD for O'hare Airport): " << endl;
    std::string iata;
    std::cin >> iata;
    cout << "Please enter the IATA code for your ending airport (EX: ORD for O'hare Airport): " << endl;
    std::string destIata;
    std::cin >> destIata;
    cout << "Would you like organize flights by distance traveled or number of stops (Enter 1 for distance and 2 for stops)? " << endl;
    std::string pathType;
    std::cin >> pathType;
    vector<Flight> result;
    Graph test = Graph("data/airports.txt", "data/routes.txt");
    if (stoi(pathType) == 1)
    {

        result = test.Dijkstra(test.getAirportID(iata), test.getAirportID(destIata));
    }
    else
    {
        result = test.BFS(test.getAirportID(iata), test.getAirportID(destIata));
    }
    cout << "Here is your optimized travel Path!" << endl;

    for (unsigned i = 0; i < result.size(); i++)
    {
        Airport startAirport = test.getAirport(result[i].getStartID());
        Airport endAirport = test.getAirport(result[i].getDestinationID());
        cout << startAirport.getName() << " -> " << endAirport.getName() << endl;

    }
//unordered_map<int, vector<Flight>>::iterator it = ;
// unordered_map<int, vector<Flight>>::iterator it;
// for (it = test.getMap().begin(); it != test.getMap().end(); it++)
// {
//     for(unsigned i = 1; i < it->second.size(); i = i+2){
//         string temp = (test.getAirport(it->second[i].getStartID())).getIATA() + "-" + (test.getAirport(it->second[i].getDestinationID())).getIATA();
//         std::cout << temp << std::endl;
//     }
// }
    return 0;
}
