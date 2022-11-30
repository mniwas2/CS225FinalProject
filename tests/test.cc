#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"
#include "../src/flightgraph.h"
#include "../src/Flight.h"
#include "../src/Airport.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>



using namespace std;

TEST_CASE("BFS1", "[BFS]") {
    Graph test = Graph("data/airports.txt","data/routes.txt");
    vector<int> expected = vector<int>({2811, 2833});
    vector<Flight> actual = test.getTraversal(2811, 2833);
    REQUIRE(compareVects(expected, actual)==true);
}

bool compareVects(const vector<int>& v1, const vector<Flight>& v2) {
    if (v1.size() + 1 != v2.size()) {
        return false;
    }
    for (unsigned i = 0; i<v2.size(); i++) {
        if (!(v1.at(i) == v2.at(i).getStartID()) && v1.at(i + 1) == v2.at(i).getDestinationID()) {
            return false;
        }
    }
    return true;
}