#include <stdio.h>
#include<string.h>
struct Book {
    int id;
    int popularity;
    int lastAccessTime;
};

// Function to find a book by ID
int findBook(struct Book shelf[], int capacity, int id) {
    for (int i = 0; i < capacity; i++) {
        if (shelf[i].id == id)
            return i;
    }
    return -1;
}


int findLRU(struct Book shelf[], int capacity) {
    int lruIndex = 0;
    for (int i = 1; i < capacity; i++) {
        if (shelf[i].lastAccessTime < shelf[lruIndex].lastAccessTime)
            lruIndex = i;
    }
    return lruIndex;
}

int main() {
    int capacity, Q;
    printf("enter the quantity and Q:");
    scanf("%d %d", &capacity, &Q);

    struct Book shelf[capacity];

    // initialize 
    for (int i = 0; i < capacity; i++) {
        shelf[i].id = -1;
        shelf[i].popularity = 0;
        shelf[i].lastAccessTime = 0;
    }

    int currentTime = 1;

    while (Q--) {
        char op[10];
        scanf("%s", op);

        if (strcmp(op, "ADD") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);

            // check if the book exits
            int index = findBook(shelf, capacity, x);

            if (index != -1) {
                // update book
                shelf[index].popularity = y;
                shelf[index].lastAccessTime = currentTime++;
            } 
            else {

                int emptySlot = -1;
                for (int i = 0; i < capacity; i++) {
                    if (shelf[i].id == -1) {
                        emptySlot = i;
                        break;
                    }
                }

                if (emptySlot != -1) {
                    shelf[emptySlot].id = x;
                    shelf[emptySlot].popularity = y;
                    shelf[emptySlot].lastAccessTime = currentTime++;
                } 
                else{
				
                    int lruIndex = findLRU(shelf, capacity);

                    shelf[lruIndex].id = x;
                    shelf[lruIndex].popularity = y;
                    shelf[lruIndex].lastAccessTime = currentTime++;
                }
            }
        }

        else if (strcmp(op, "ACCESS") == 0) {
            int x;
            scanf("%d", &x);

            int index = findBook(shelf, capacity, x);

            if (index == -1) {
                printf("-1\n");
            } else {
                printf("%d\n", shelf[index].popularity);
                shelf[index].lastAccessTime = currentTime++;
            }
        }
    }

    return 0;
}

