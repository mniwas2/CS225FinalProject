# CS225FinalProject

### The output and correctness of each algorithm:

1. BFS-Find
    Intended function + output: receive input of given coordinates in order to find the closest airport to location
2. Dijkstra's
    Intended function + output: take in the origin and destination longitude + latitude to return the shortest path possible between two airports
    
    The test case for this includes comparing the expected vector with the given vector of coordinates.  

3. Page Rank 
    Intended function + output: with the given 15-20 sightseeing locations scattered across the world, the algorithm will return a sorted list of the locations by proximity to the destination airport
    


### The answer to your leading question:

With our project, we wanted to assist users in their trans-atlantic commutes. We had two main questions that we wanted to answer; the first being "Can we find the nearest airport given an individual's coordinates?" and "How can we calculate the shortest path between two airports?". 

To answer the first question, we created a "Find" function. We decided to take in a set of coordinates containing longitude and latitude in order to know where the user's location was. From there, we use the BFS algorithm to find the airport closest to the nearest coordinates. Our initial plan was to use our Find function to have two functionalities: find the nearest airport to a given location and find the nearest sightseeing landmark that is closest to the destination airport.


Our next algorithm was using Dijkstra's. This algorithm takes into consideration the origin and destination airports to then calculate the shortest path between 2 airports. The nodes are coordinates containing the longitude and latitudes of airports while the edges are only the existing routes between 2 airports.  
