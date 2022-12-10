#include "BFS.h"
#include <unordered_map>
#include "Airport.h"
#include "Flight.h"
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

std::vector<Flight> getTraversal(unordered_map<int, Airport> airports_, unordered_map<int, vector<Flight>> flights_, Airport start, Airport end)
{
    std::vector<Flight> visited;
    std::vector<Flight> toReturn;
    visited.resize(airports_.size(), Flight());
    std::queue<Flight> q;
    for (Flight f : flights_[start.getID()]){
        if(f.getDestinationID() == end.getID()){
            toReturn.push_back(f);
            return toReturn;
        }
        int id = f.getDestinationID();
        q.push(f);
        visited[id] = f;
    }
    Flight v;
    
    while (!q.empty())
    {
        v = q.front();
        q.pop();
        if (v.getDestinationID() == end.getID()) {

            if (!q.empty()) {
        // create vector of flights
        vector<Flight> reverseResult;
        reverseResult.push_back(q.front());
        int prevNode = reverseResult.at(0).getStartID();
        while (prevNode != start.getID()) {
            reverseResult.push_back(visited.at(prevNode - 1));
            prevNode = reverseResult.at(reverseResult.size() - 1).getStartID();
        }
        // for (unsigned i = 0; i < reverseResult.size(); i++) {
        //     std::cout<<reverseResult.at(i)<<", ";
        // }
        // std::cout<<std::endl;
        std::reverse(reverseResult.begin(), reverseResult.end());
        return reverseResult;
            break;

            //we have reached the end of our BFS!
        }
        for (Flight f : flights_[v.getDestinationID()])
        {
            // for all flights at airport v...
            int id = f.getDestinationID();
            Airport dest = airports_[f.getDestinationID()];
            if (visited[id] == Flight())
            {
                // unexplored node
                visited[id] = v;                    
                q.push(f);
    
            }
        }
    }
    return toReturn;
}
