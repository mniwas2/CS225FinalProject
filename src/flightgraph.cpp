#include "flightgraph.h"
#include <fstream>
#include <string>

using namespace std;

// construct graph from files
Graph::Graph(string airportFile, string flightFile) {
    readData(airportFile, flightFile);
}

// load airport and flight data information from files
void Graph::readData(string airportFile, string flightFile) {
    string line;
    // read in airport file
    ifstream airportf(airportFile);
    if (airportf.is_open()) {
        while ( getline(airportf, line) ) {
            // create Airport objects and populate airports_ map of airport IDs and the corresponding airport
            Airport airport = Airport(line);
            airports_[airport.getID()] = airport;
        }
        airportf.close();
    }

    ifstream flightf(flightFile);
    if (flightf.is_open()) {
        while ( getline(flightf, line) ) {
            // create Flight objects and populate flight_ adjacency list
            Flight flight = Flight(line);
            flight.setDistance(airports_[flight.getStartID()].distanceTo(airports_[flight.getDestinationID()]));
            if (!flights_[flight.getStartID()].empty()) {
                flights_[flight.getStartID()].push_back(flight);
            } else {
                flights_[flight.getStartID()] = vector<Flight>({flight});
            }
        }
        flightf.close();
    }
}