/*
Name: Ethan Childress
Professor: Turini
Project Title: Project 1 - A* Search Algorithm
Year: 2024
*/ 

typedef struct AStarTile tile;

typedef struct AStarTile {
    int x; //x coordinate
    int y; //y coordinate
    struct AStarTile *parentTile;  
    int indexInSet; //from min-heap
    double costValues[4]; //G,C,H,F
    bool isPath;
    bool isObstacle;
    bool isGoal;
    bool isStart;
    bool evaluated;
    double (*heuristicFunction)(int, int, int, int);
} tile; 

//mapInit function
tile** mapInit(double (*DistanceFuncPtr)(int, int, int, int)) {
    
    //Initialize random seed based on time
    srand(time(0));

    //make 10x10 map. Populate each cell with coordinates.
    tile** map = (tile**)malloc(10 * sizeof(tile*));
    
    for (int i=0; i<10; i++) {
        //Allocate mem for each tile
        map[i] = (tile*)malloc(10 * sizeof(tile));
        for (int j=0; j<10; j++) {
            //init static variables
            map[i][j].x = i;
            map[i][j].y = j;
            map[i][j].parentTile = NULL;
            map[i][j].indexInSet = 0;
            map[i][j].isObstacle = false;
            map[i][j].isStart = false;
            map[i][j].isGoal = false;
            map[i][j].evaluated = false;
            map[i][j].heuristicFunction = DistanceFuncPtr;
    
            //init costValues array
            for (int k=0; k<sizeof(map[i][j].costValues)/sizeof(map[i][j].costValues[0]); k++) {
                if (k == 1) {
                    //generate random number for the cost of the tile. C of gchf.
                    int randCost = rand() % 10;
                    map[i][j].costValues[k] = randCost;

                }
                else if (k == 3) {
                    //full cost
                    map[i][j].costValues[k] = map[i][j].costValues[0] + map[i][j].costValues[1] + map[i][j].costValues[2];
                }
                else {
                    //Set default to 0 for ghf
                    map[i][j].costValues[k] = 0;
                }    
            }

            if (map[i][j].costValues[1] == 0) {
                map[i][j].isObstacle = true;
            }
        }
    }

    return map;
}

//mapPrint function 
void mapPrint(tile** map, int mode, int destination[]) {
    printf("\n");
    switch(mode) {
        case 1:
            printf("Pathing after A*: \n");
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (map[i][j].isStart == true) {
                        printf("( S ) ");
                    }
                    else if (map[i][j].isPath == true) {
                        printf("(***) ");
                    }
                    else if (map[i][j].isGoal == true) {
                        printf("( G ) ");
                    }
                    else if (map[i][j].isObstacle == true) {
                        printf("(XXX) ");
                    }
                    else if (map[i][j].evaluated == false) {
                        printf("( ? ) ");
                    }
                    else  {
                        printf("( - ) ");
                    }
                }
                printf("\n");
            }
        break;
        
        case 2:
            printf("A* computed weights: \n");
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (map[i][j].isObstacle == true) {
                        printf("(  X  ) ");
                    }
                    else if (map[i][j].evaluated == false) {
                        printf("(  ?  ) ");
                    }
                    else  {
                        printf("(%.2f) ", map[i][j].costValues[3]);
                    }
                }
                printf("\n");
            }
        break;
        case 3:
            printf("Map before A*: \n");
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    printf("(%.2f) ", map[i][j].costValues[1]);
                }
                printf("\n");
            }
        break;
    }
}
