#include "flightgraph.h"
#include <fstream>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

// construct graph from files
Graph::Graph(string airportFile, string flightFile)
{
    readData(airportFile, flightFile);
}
unordered_map<int, vector<Flight>> Graph::getMap(){
    return flights_;
}

// load airport and flight data information from files
void Graph::readData(string airportFile, string flightFile)
{
    string line;
    // read in airport file
    unordered_map<int, int> airportIDMap;
    ifstream airportf(airportFile);
    int linenum = 1;
    if (airportf.is_open())
    {
        while (getline(airportf, line))
        {
            // create Airport objects and populate airports_ map of airport IDs and the corresponding airport
            Airport airport = Airport(line);
            if (airport.getID() != -1) {
                airportIDMap[airport.getID()] = linenum;
                airport.setID(linenum);
                airports_[airport.getID()] = airport;
                airportsIATA_[airport.getIATA()] = airport.getID();
                linenum++;
            }
        }
        airportf.close();
    }
    else
    {
        std::cout << "airport file not open" << std::endl;
    }
    ifstream flightf(flightFile);
    if (flightf.is_open())
    {
        while (getline(flightf, line))
        {
            // create Flight objects and populate flight_ adjacency list
            Flight flight = Flight(line);

            if (flight.getStartID() != -1 && airportIDMap.find(flight.getStartID()) != airportIDMap.end() && airportIDMap.find(flight.getDestinationID()) != airportIDMap.end()) {
                flight.setStart(airportIDMap[flight.getStartID()]);
                flight.setDestination(airportIDMap[flight.getDestinationID()]);
                int flightstartID = flight.getStartID();
                flight.setDistance(airports_[flightstartID].distanceTo(airports_[flight.getDestinationID()]));
                if (!flights_[flightstartID].empty())
                {
                    vector<Flight> &flights = flights_[flightstartID];
                    if (std::find(flights.begin(), flights.end(), flight) == flights.end())
                    {
                        flights_[flightstartID].push_back(flight);
                    }
                }
                else
                {
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
    } else
    {
        std::cout << "flight file not open" << std::endl;
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


vector<Flight> Graph::Dijkstra(int source, int destination)
{
    // store the min distance to each node starting at source node
    struct Path
    {
        double mindistance;
        Flight lastflight;
    };
    vector<Path> mindistance;
    Flight default_flight = Flight();
    Path default_path = {-1, default_flight};
    mindistance.resize(airports_.size(), default_path);

    // set source airport distance to 0
    mindistance[source - 1].mindistance = 0;
    priority_queue<std::pair<double, Flight>, vector<std::pair<double, Flight>>, greater<std::pair<double, Flight>>> queue;
    for (Flight flight : flights_[source])
    {
        if (flight.getDestinationID() == destination)
        {
            return vector<Flight>({flight});
        }
        mindistance[flight.getDestinationID() - 1].mindistance = flight.getDistance();
        mindistance[flight.getDestinationID() - 1].lastflight = flight;
        std::pair<double, Flight> trip = std::make_pair(flight.getDistance(), flight);
        queue.push(trip);
    }

    // when top of queue == destination and !queue.empty
    // pop off closest node and add all adjacent nodes if not closer
    while (!queue.empty() && queue.top().second.getDestinationID() != destination)
    {
        std::pair<double, Flight> top = queue.top();
        int destID = top.second.getDestinationID();
        queue.pop();
        if (mindistance.at(destID - 1).mindistance == top.first)
        {
            for (Flight flight : flights_[destID])
            {
                double distanceToSource = top.first + flight.getDistance();
                std::pair<double, Flight> trip = std::make_pair(distanceToSource, flight);
                if (mindistance.at(flight.getDestinationID() - 1).mindistance == -1 || mindistance.at(flight.getDestinationID() - 1).mindistance > distanceToSource)
                {
                    mindistance.at(flight.getDestinationID() - 1).mindistance = distanceToSource;
                    mindistance.at(flight.getDestinationID() - 1).lastflight = flight;
                    queue.push(trip);
                }
            }
        }
        
    }

    if (!queue.empty())
    {
        vector<Flight> reverseResult;
        reverseResult.push_back(queue.top().second);
        int prevNode = reverseResult.at(0).getStartID();

        while (prevNode != source)
        {
            reverseResult.push_back(mindistance.at(prevNode - 1).lastflight);
            prevNode = mindistance.at(prevNode - 1).lastflight.getStartID();
        }
        std::reverse(reverseResult.begin(), reverseResult.end());
        return reverseResult;
    }
    return vector<Flight>();
}

std::vector<Flight> Graph::BFS(int source, int destination)
{
    Airport start = airports_[source];
    Airport end = airports_[destination];
    std::vector<Flight> visited;
    std::vector<Flight> toReturn;
    visited.resize(airports_.size(), Flight());
    std::queue<Flight> q;
    visited[start.getID()] = Flight(-2, -2, "none", 0, 0, 0);
    for (Flight f : flights_[start.getID()])
    {
        if (f.getDestinationID() == end.getID())
        {

            toReturn.push_back(f);
            return toReturn;
        }
        int id = f.getDestinationID()-1;
        q.push(f);
        visited[id] = f;
    }
    Flight v;

    while (!q.empty())
    {
        v = q.front();

        q.pop();
        // if done

        // we have reached the end of our BFS!
        for (Flight f : flights_[v.getDestinationID()])
        {
            if (f.getDestinationID() == end.getID())
            {


                // create vector of flights
                vector<Flight> reverseResult;
                reverseResult.push_back(f);
                int prevNode = reverseResult.at(0).getStartID();

                while (prevNode != start.getID())
                {
                    reverseResult.push_back(visited.at(prevNode - 1));

                    prevNode = reverseResult.at(reverseResult.size() - 1).getStartID();


                }

                std::reverse(reverseResult.begin(), reverseResult.end());



                return reverseResult;
            }
            // for all flights at airport v...

            int id = f.getDestinationID()-1;

            if (visited[id] == Flight())
            {

                // unexplored node
                visited[id] = f;
                q.push(f);
            }
        }
    }
    return toReturn;
}
