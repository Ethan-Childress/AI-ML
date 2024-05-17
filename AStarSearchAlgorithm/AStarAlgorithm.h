/*
Name: Ethan Childress
Professor: Turini
Project Title: Project 1 - A* Search Algorithm
Year: 2024
*/ 

Node* tileStack;

//aStarTracePath function
//build path once A* reaches destination
void aStarTracePath(tile** map, tile currentTile) { 
    
    Node* current = tileStack;

    //Clear the tile stack
    while (tileStack != NULL) {
        Node* temp = tileStack;
        tileStack = tileStack->next;
        free(temp);
    }

    // Traverse from destination to start, pushing tiles onto the stack
    while (currentTile.parentTile != NULL) {
        stackPush(&tileStack, &currentTile);
        currentTile = *(map[currentTile.x][currentTile.y].parentTile);
        map[currentTile.x][currentTile.y].isPath = true;
    }

    // Push the start currentTile onto the stack
    stackPush(&tileStack, &currentTile);

    printf("Tile Stack (top to bottom): \n");
    while (tileStack != NULL) {
        tile poppedTile = stackPop(&tileStack);
        printf("(%d, %d) ", poppedTile.x, poppedTile.y);
    }
    printf("\n");
}

void aStarProcessNeighborTile(Heap* heap, tile** map, tile neighbor, tile parent, int destination[]) {
    //Update tile inputs G H and F
    neighbor.evaluated = true;
    neighbor.costValues[0] += parent.costValues[3];
    neighbor.costValues[2] = neighbor.heuristicFunction(neighbor.x,neighbor.y,destination[0],destination[1]);
    neighbor.costValues[3] = neighbor.costValues[0] + neighbor.costValues[1] + neighbor.costValues[2];

    map[neighbor.x][neighbor.y] = neighbor;

    heapInsert(heap, &neighbor);
}

int aStarRunSearch(tile** map, int source[], int destination[]) {
    
    //define source and destination tile
    map[source[0]][source[1]].isStart = true;
    map[source[0]][source[1]].costValues[3] = 0;
    map[destination[0]][destination[1]].isGoal = true;

    //Create an open and closed list
    Heap openHeap;
    heapInit(&openHeap);
    tile closedList[1000];
    int closedCounter = 0;

    //Insert source into the open list 
    heapInsert(&openHeap, &map[source[0]][source[1]]);

    while (openHeap.size != 0) {  
        tile minTile = openHeap.array[0]; 
        closedList[closedCounter] = minTile; 
        closedCounter++;
        heapExtractMin(&openHeap);
    
        if (minTile.isGoal == true) {
            aStarTracePath(map, map[minTile.x][minTile.y]);
            return 1;
        }

        //Generate neighbors of minTile NESW
        tile neighbors[4];

        //South
        if (minTile.x != 0) {
            neighbors[2] = map[minTile.x-1][minTile.y];
        }

        //North
        if (minTile.x != 9) {
            neighbors[0] = map[minTile.x+1][minTile.y];
        }

        //West
        if (minTile.y != 0) {
            neighbors[3] = map[minTile.x][minTile.y-1];
        }

        //East
        if (minTile.y != 9) {
            neighbors[1] = map[minTile.x][minTile.y+1];
        }

        for (int i=0; i<4; i++) {
            //Check if neighbor is not NULL
            if (neighbors[i].x < 0 || neighbors[i].x > 9 || neighbors[i].isObstacle || neighbors[i].isStart) {
                // Skip processing this neighbor
                continue;
            }

            bool isClosed = false;
            // Check if neighbor is already in closed list
            for (int k=0; k<closedCounter; k++) {
                if (neighbors[i].x == closedList[k].x && neighbors[i].y == closedList[k].y) {
                    // Skip processing this neighbor
                    isClosed = true;
                }
            }


            bool inOpenList = false;
            int openIndex;
            // Check if neighbor is already in open list
            for (int j=0; j<openHeap.size; j++) {
                if (neighbors[i].x == openHeap.array[j].x && neighbors[i].y == openHeap.array[j].y) {
                    inOpenList = true;
                    openIndex = j;
                }
            }

            if (inOpenList) {
                //if new g is better than old g
                double newG = neighbors[i].costValues[0] + minTile.costValues[3];
                double oldG = openHeap.array[openIndex].costValues[0];

                if (newG < oldG) {
                    //Recalc GFH
                    openHeap.array[openIndex].costValues[0] = newG;
                    openHeap.array[openIndex].costValues[2] = openHeap.array[openIndex].heuristicFunction(openHeap.array[openIndex].x,openHeap.array[openIndex].y,destination[0],destination[1]);
                    openHeap.array[openIndex].costValues[3] = openHeap.array[openIndex].costValues[0] + openHeap.array[openIndex].costValues[1] + openHeap.array[openIndex].costValues[2];
                    map[openHeap.array[openIndex].x][openHeap.array[openIndex].y] = openHeap.array[openIndex];
                    heapSwapUpTile(&openHeap, openIndex);
                }

                inOpenList = false;
            }
            else if (isClosed) {
                break;
            }

            else {
                
                // Dynamically allocate memory for the parent tile
                neighbors[i].parentTile = malloc(sizeof(tile));
                // Check if memory allocation was successful

                if (neighbors[i].parentTile != NULL) {
                    // Copy the contents of minTile to the allocated memory
                    *(neighbors[i].parentTile) = minTile;
                    // Process the neighbor tile
                    aStarProcessNeighborTile(&openHeap, map, neighbors[i], minTile, destination);
                } 
                else {
                    printf("Memory allocation failed.\n");
                }
            }
        }
    }
    return 0;
}





