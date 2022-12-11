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

bool compareVects(const vector<int>& v1, const vector<Flight>& v2) {

    REQUIRE (v1.size() - 1 == v2.size());
    for (unsigned i = 0; i<v2.size(); i++) {
        if (!(v1.at(i) == v2.at(i).getStartID()) && v1.at(i + 1) == v2.at(i).getDestinationID()) {
            return false;
        }
    }
    return true;
}

TEST_CASE("getAirportSmall", "[Data]") {
    Graph test = Graph("tests/testairports.txt","tests/testflights.txt");
    Airport expected = Airport(1,"A","A","A","XXX",47.808543,-111.235683);
    Airport actual = test.getAirport(1);
    REQUIRE(expected.getName() == actual.getName());
    REQUIRE(expected.getCity() == actual.getCity());
    REQUIRE(expected.getCountry() == actual.getCountry());
    REQUIRE(expected.getLatitude() == actual.getLatitude());
    REQUIRE(expected.getLongitude() == actual.getLongitude());
}

TEST_CASE("getAirport", "[Data]") {
    Graph test = Graph("data/airports.txt","data/routes.txt");
    Airport expected = Airport(3129,"Barysiai Airport","Barysiai","Lithuania", "HLJ",56.07059860229492,23.5580997467041);
    Airport actual = test.getAirport(3129);
    REQUIRE(expected.getName() == actual.getName());
    REQUIRE(expected.getCity() == actual.getCity());
    REQUIRE(expected.getCountry() == actual.getCountry());
    REQUIRE(expected.getLatitude() == actual.getLatitude());
    REQUIRE(expected.getLongitude() == actual.getLongitude());
    REQUIRE(expected.getID() == test.getAirportID("HLJ"));
}

//Was wanting to make a test case for Flights but I think we may have implemented it incorrectly.
TEST_CASE("getFlight", "[Data]") {
    Graph test = Graph("data/airports.txt","data/routes.txt");
    Airport Manits_International_Airport = test.getAirport(1683);
    Airport Anweshas_Mid_Airport = test.getAirport(1675);
    Flight actual = test.getDirectFlight(Manits_International_Airport.getID(), Anweshas_Mid_Airport.getID());
    string line = "PK,3871,PZH,2233,UET,2221,,0,ATR";  //we needed to Re-ID the airports to eliminate those without IATAs
    Flight expected = Flight(1683,1675,"PK",3871,0,0);     
    REQUIRE(expected.getAirlineID() == actual.getAirlineID());
    REQUIRE(expected.getStartID() == actual.getStartID());
    REQUIRE(expected.getDestinationID() == actual.getDestinationID());               
    REQUIRE(expected.getAirline() == actual.getAirline());
    REQUIRE(expected.getStops() == actual.getStops());
}
TEST_CASE("DetectNoFlight", "[Data]") {
    Graph test = Graph("tests/testairports.txt","tests/testflights.txt");
    Airport Manits_International_Airport = test.getAirport(1); //A
    Airport Rohans_L_Airport = test.getAirport(5); //E
    Flight actual = test.getDirectFlight(Manits_International_Airport.getID(), Rohans_L_Airport.getID());
    Flight expected = Flight(-1,-1,"",-1,0,0);  
    REQUIRE(expected.getStops() == actual.getStops());   
    REQUIRE(expected.getAirlineID() == actual.getAirlineID());
    REQUIRE(expected.getStartID() == actual.getStartID());
    REQUIRE(expected.getDestinationID() == actual.getDestinationID());               
    REQUIRE(expected.getAirline() == actual.getAirline());
}
TEST_CASE("GetFlightEasy", "[Data]") {
    Graph test = Graph("tests/testairports.txt","tests/testflights.txt");
    Airport Anweshas_Amazing_Airport = test.getAirport(1); //A
    Airport Rohans_Rowdy_Runways = test.getAirport(4); //D
    Flight actual = test.getDirectFlight(Anweshas_Amazing_Airport.getID(), Rohans_Rowdy_Runways.getID());
    Flight expected = Flight(1,4,"A",0,0,0);  
    REQUIRE(expected.getStops() == actual.getStops());   
    REQUIRE(expected.getAirlineID() == actual.getAirlineID());
    REQUIRE(expected.getStartID() == actual.getStartID());
    REQUIRE(expected.getDestinationID() == actual.getDestinationID());               
    REQUIRE(expected.getAirline() == actual.getAirline());
}
TEST_CASE("TopTenAirports", "[Data]") {
    Graph test = Graph("data/airports.txt","data/routes.txt");
    Airport Manits_International_Airport = test.getAirport(3296); //Newark
    Airport Sofias_Speedy_Planes = test.getAirport(4008); //Columbus Metropolitan Airport
    //vector<int> topten = test.getTopTen();
    //for (int i = 0; i < 10; i++) {
    //    cout<<topten[i]<<endl;
    //}
}
TEST_CASE("BFS1", "[BFS]") {
    Graph test = Graph("data/airports.txt","data/routes.txt");
    vector<int> expected = vector<int>({test.getAirportID("AER"), test.getAirportID("KZN")});
    vector<Flight> actual = test.BFS(test.getAirportID("AER"), test.getAirportID("KZN"));
    REQUIRE(compareVects(expected, actual)==true);
}

TEST_CASE("BFS2", "[BFS]") {
    Graph test = Graph("tests/testairports.txt","tests/testflights.txt");
    vector<int> expected = vector<int>({1, 3, 5});
    vector<Flight> actual = test.BFS(1, 5);
    REQUIRE(compareVects(expected, actual)==true);
}
TEST_CASE("BFSHard", "[BFS]") {
    Graph test = Graph("data/airports.txt","data/routes.txt");
    vector<int> expected = vector<int>({2651, 2873, 412, 2292, 4158}); 
    vector<Flight> actual = test.BFS(2651, 4158);  //from Trenton, New Jersey to Guwahati, Assam, India
    REQUIRE(compareVects(expected, actual)==true);
}

TEST_CASE("Dijkstra1", "[Dijkstra]") {
    Graph test = Graph("tests/testairports.txt","tests/testflights.txt");
    vector<int> expected = vector<int>({1, 4});
    vector<Flight> actual = test.Dijkstra(1, 4);
    REQUIRE(compareVects(expected, actual)==true);
    expected = vector<int>({1, 4, 2, 5});
    actual = test.Dijkstra(1, 5);
    REQUIRE(compareVects(expected, actual)==true);
}
TEST_CASE("DijkstraHard", "[Dijkstra]") {
    Graph test = Graph("data/airports.txt","data/routes.txt");
    vector<int> expected = vector<int>({2651, 2689, 188, 1665, 2371, 4158});
    vector<Flight> actual = test.Dijkstra(2651, 4158);  //from Trenton, New Jersey to Guwahati, Assam, India
    REQUIRE(compareVects(expected, actual)==true);
}