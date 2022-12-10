# CS225FinalProject

### The output and correctness of each algorithm:
We have test cases for our dataset which are shown below. 
<img width="856" alt="Screen Shot 2022-12-10 at 2 17 07 PM" src="https://user-images.githubusercontent.com/90567203/206873743-cab4a9de-499e-49ee-b381-579d90d66b6a.png">

1. BFS-Find
    Intended function + output: receive input of given coordinates in order to find the closest airport to location
    
    <img width="553" alt="Screen Shot 2022-12-10 at 2 17 50 PM" src="https://user-images.githubusercontent.com/90567203/206873778-d0ddafd2-07dd-4f03-846b-eb7aff4b2b39.png">
2. Dijkstra's
    Intended function + output: take in the origin and destination longitude + latitude to return the shortest path possible between two airports
    
    The test case for this includes comparing the expected vector with the given vector of coordinates.  
    
    <img width="548" alt="Screen Shot 2022-12-10 at 2 20 04 PM" src="https://user-images.githubusercontent.com/90567203/206873832-82f17892-3836-44e4-896e-1096a5eabbd7.png">
    
    The run time of our algorithm is O(|E|+|V|log(|V|)).

3. Page Rank 
    Intended function + output: with the given 15-20 sightseeing locations scattered across the world, the algorithm will return a sorted list of the locations by proximity to the destination airport
    
    We faced issues in implementing this aspect of our project due to a time constraint and switching our project 1.5 weeks into the term. This algorithm is built off of completing BFS and Dijkstra's so we found it imperative to first complete our Find function and Dijkstra's.
    


### The answer to your leading question:

With our project, we wanted to assist users in their trans-atlantic commutes. We had two main questions that we wanted to answer; the first being "Can we find the nearest airport given an individual's coordinates?" and "How can we calculate the shortest path between two airports?". 

To answer the first question, we created a "Find" function. We decided to take in a set of coordinates containing longitude and latitude in order to know where the user's location was. From there, we use the BFS algorithm to find the airport closest to the nearest coordinates. Our initial plan was to use our Find function to have two functionalities: find the nearest airport to a given location and find the nearest sightseeing landmark that is closest to the destination airport.


Our next algorithm was using Dijkstra's. This algorithm takes into consideration the origin and destination airports to then calculate the shortest path between 2 airports. The nodes are coordinates containing the longitude and latitudes of airports while the edges are only the existing routes between 2 airports.  


Our last algorithm uses PageRank. We decided to input 15-20 locations that are known as popular sightseeing locations across the world. With that, we would produce a ranked list of these locations based on their proximity to the final destination.
