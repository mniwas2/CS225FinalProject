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
    unordered_map<int, int> airportIDMap;
    ifstream airportf(airportFile);
    int linenum = 1;
    if (airportf.is_open()) {
        while ( getline(airportf, line) ) {
            // create Airport objects and populate airports_ map of airport IDs and the corresponding airport
            Airport airport = Airport(line);
            airportIDMap[airport.getID()] = linenum;
            airport.setID(linenum);
            airports_[airport.getID()] = airport;
            linenum++;
        }
        airportf.close();
    }

    ifstream flightf(flightFile);
    if (flightf.is_open()) {
        while ( getline(flightf, line) ) {
            // create Flight objects and populate flight_ adjacency list
            Flight flight = Flight(line);
            flight.setStart(airportIDMap[flight.getStartID()]);
            flight.setDestination(airportIDMap[flight.getDestinationID()]);
            int flightstartID = flight.getStartID();
            flight.setDistance(airports_[flightstartID].distanceTo(airports_[flight.getDestinationID()]));
            if (!flights_[flightstartID].empty()) {
                vector<Flight>& flights = flights_[flightstartID];
                if (std::find(flights.begin(), flights.end(), flight) == flights.end()) {
                    flights_[flightstartID].push_back(flight);
                }
            } else {
                flights_[flightstartID] = vector<Flight>({flight});
            }
        }
        flightf.close();
    }
}