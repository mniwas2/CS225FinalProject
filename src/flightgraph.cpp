#include "flightgraph.h"
#include <fstream>
#include <string>
#include <iostream>

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
            if (flight.getStartID() != -1) {
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
            // vector<int> ranks;
            // int destId = flight.getDestinationID();
            // ranks.resize(airports_.size(), 0);
            // ranks[destId] = ranks[destId] + 1;
            // if (topten.size() == 0) {
            //     topten.push_back(destId);
            // }
            // for (int i = 0; i < int(topten.size()); i++) {
            //     if (topten.size() < 10) {
            //         topten.push_back(destId);
            //         break;
            //     }
            //     else if (ranks[destId] > ranks[topten[i]]) {
            //         topten[i] = destId;
            //     }
            // }
        }
        flightf.close();
    }
}
Flight Graph::getDirectFlight(int startID, int endID) {
    Flight f = Flight();
    vector<Flight> flights = getFlights(startID);
    for (size_t i = 0; i < (flights.size()); i++) {
        if (flights[i].getDestinationID() == endID) {
            return flights[i];
        }
    }
    return f;
}