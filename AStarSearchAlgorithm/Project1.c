/*
Name: Ethan Childress
Professor: Turini
Project Title: Project 1 - A* Search Algorithm
Year: 2024
*/ 

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "AStarTileMap.h"
#include "AStarTileHeap.h"
#include "AStarTileStack.h"
#include "AStarAlgorithm.h"

//Compute Euclidian distance betwwen two tiles function
double calcEuclidianDistance(int aX, int aY, int bX, int bY) {
    // [(aX-bX)^2 + (aY-bY)^2]^.5
    double verticalDist = bY - aY;
    double lateralDist = bX - aX;
    lateralDist *= lateralDist;
    verticalDist *= verticalDist;
    return sqrt(lateralDist + verticalDist);
}

//Manhattan distance function
double calcManhattanDistance(int aX, int aY, int bX, int bY) {
    // |aX-bX| + |aY-bY|
    double verticalDist = bY - aY;
    double lateralDist = bX - aX;
    return abs(verticalDist) + abs(lateralDist);
}

int main() {
    //Map Initialization
    tile** map = mapInit(calcEuclidianDistance);

    //Call to A* search algorithm
    int source[] = {0, 0};
    int destination[] = {9, 9};
    aStarRunSearch(map, source, destination);
    
    //Print on console: 
    mapPrint(map, 1, destination);
    mapPrint(map, 2, destination);
    mapPrint(map, 4, destination);
    
    return 0;
} 