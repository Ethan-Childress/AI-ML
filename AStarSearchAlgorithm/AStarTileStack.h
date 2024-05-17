/*
Name: Ethan Childress
Professor: Turini
Project Title: Project 1 - A* Search Algorithm
Year: 2024
*/ 

typedef struct AStarTileStackNode {
    tile node;
    struct AStarTileStackNode* next;
} Node;

void stackInit(Node** top) {
    *top = NULL;
}

void stackPush(Node** top, tile* tile) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->node = *tile;
    newNode->next = *top;
    *top = newNode;
}

tile stackPop(Node** top) {
    if (*top == NULL) {
        printf("Stack underflow.\n");
        exit(1);
    }
    Node* temp = *top;
    tile poppedTile = temp->node;
    *top = temp->next;
    free(temp);
    return poppedTile;
}

void stackPrint(Node** top) {
    if (*top == NULL) {
        printf("Stack Empty.\n");
        return;
    }
    
    Node* temp = *top;
    while (temp != NULL) {
        printf("(%d, %d) ", temp->node.x, temp->node.y);
        temp = temp->next;
    }
    printf("\n");
}

void stackDelete(Node** top) {
    while (*top != NULL) {
        Node* temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}
