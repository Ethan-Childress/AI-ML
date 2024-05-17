/*
Name: Ethan Childress
Professor: Turini
Project Title: Project 1 - A* Search Algorithm
Year: 2024
*/ 

typedef struct Heap{
    tile *array; // Array of tiles
    int capacity; // Maximum size of the heap
    int size; // Current number of elements in the heap
} Heap;

void heapInit(Heap *heap) {
    // Check if input heap pointer is valid.
    if (heap != NULL) {
        // Initialize size and capacity
        heap->size = 0;
        heap->capacity = 10; //FIX THIS

        // Allocate memory for the array
        heap->array = (tile*)malloc(heap->capacity * sizeof(tile));

    }
}

void heapSwapDownTile(Heap *heap, int index) {
    int leftChildIndex = 2 * index + 1;    
    int rightChildIndex = 2 * index + 2;   
    int smallest = index;             

    if (leftChildIndex < heap->size && heap->array[leftChildIndex].costValues[3] < heap->array[smallest].costValues[3]) {
        smallest = leftChildIndex;
    }

    if (rightChildIndex < heap->size && heap->array[rightChildIndex].costValues[3] < heap->array[smallest].costValues[3]) {
        smallest = rightChildIndex;
    }

    if (smallest != index) {
        //Swap the nodes
        tile temp = heap->array[index];
        heap->array[index] = heap->array[smallest];
        heap->array[smallest] = temp;

        //Update parentTile of the swapped nodes
        heap->array[index].parentTile = &heap->array[(index - 1) / 2];
        heap->array[smallest].parentTile = &heap->array[index];

        //call heapSwapDownTile on the child
        heapSwapDownTile(heap, smallest);
    }
}


void heapSwapUpTile(Heap *heap, int index) {
    int parentIndex = (index - 1) / 2;  // Index of the parent node

    // Keep swapping with parent as long as the current node is smaller than its parent
    while (index > 0 && heap->array[index].costValues[3] < heap->array[parentIndex].costValues[3]) {
        // Swap the nodes
        tile temp = heap->array[index];
        heap->array[index] = heap->array[parentIndex];
        heap->array[parentIndex] = temp;

        // Move up to the parent node
        index = parentIndex;
        parentIndex = (index - 1) / 2;
    }
}

void heapExtractMin(Heap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty\n");
        return;
    }

    // Move the last element to the root
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    // Fix the heap 
    heapSwapDownTile(heap, 0);
}

void heapInsert(Heap *heap, tile* tile) {
    if (heap->size < heap->capacity) {
        //Insert tile into heap
        heap->array[heap->size] = *tile;
        //Check if tile needs to be moved up the heap
        heapSwapUpTile(heap, heap->size);
        heap->size++;
    }
}

//heapPrint
void heapPrint(Heap* heap) {
    if (heap != NULL) {
        printf("Heap Contents:\n");
        for (int i = 0; i < heap->size; i++) {
            // Check if parentTile is not NULL before dereferencing it
            if (heap->array[i].parentTile != NULL) {
                
                tile parentTile = *(heap->array[i].parentTile);
                //heap->array[i].parentTile.x

                printf("%d: %d, %d | %f | %d, %d\n", i, heap->array[i].x, heap->array[i].y, heap->array[i].costValues[3], parentTile.x, parentTile.y);
            } else {
                printf("%d: %d, %d | %f | No parent\n", i, heap->array[i].x, heap->array[i].y, heap->array[i].costValues[3]);
            }
        }
    }
}