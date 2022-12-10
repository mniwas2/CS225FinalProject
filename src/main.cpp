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
        Airport endAiport = test.getAirport(result[i].getDestinationID());
        cout << startAirport.getName() << "->" << endAiport.getName() << endl;

    }

    return 0;
}
