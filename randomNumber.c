#include <stdio.h>
#include<stdlib.h>
#define TABLE_SIZE 101

struct NodeI {
    int key;
    int count;
    struct NodeI* next;
};

int hash(int key) {
    return (key % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
}
void insertOrUpdate(struct NodeI* table[], int key) {
    int index = hash(key);

    // Search for the key in the linked list at the calculated index
    struct NodeI* current = table[index];
    while (current != NULL) {
        if (current->key == key) {
            // Key found, update count
            current->count++;
            return;
        }
        current = current->next;
    }

    // Key not found, insert a new node at the beginning of the linked list
    struct NodeI* newNode = (struct NodeI*)malloc(sizeof(struct NodeI));
    newNode->key = key;
    newNode->count = 1;
    newNode->next = table[index];
    table[index] = newNode;
}
// Function to print the counts in the hash table
void printCounts(struct NodeI* table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct NodeI* current = table[i];
        while (current != NULL) {
            printf("Value %d occurs %d times\n", current->key, current->count);
            current = current->next;
        }
        if(current != NULL) free(current);
    }
}

// Function to free memory allocated for the linked lists
void freeTable(struct NodeI* table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct NodeI* current = table[i];
        while (current != NULL) {
            struct NodeI* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int customRandom() {
    static unsigned int seed = 42;
    seed ^= (seed << 13);
    seed ^= (seed >> 17);
    seed ^= (seed << 6);
    return seed;
}
int randI(int lower_limit, int upper_limit) {
    
    static unsigned int seed = 42;
    seed ^= (seed << 13);
    seed ^= (seed >> 17);
    seed ^= (seed << 6);

    return lower_limit + (seed % (upper_limit - lower_limit + 1));
}
double randF() {
    unsigned int randomInt = customRandom();
    double randomFloat = (double)randomInt / 0xFFFFFFFF;

    return randomFloat;
}
float custom_rand_float(unsigned int seed) {
    unsigned int int_value = randI(0,0);
    float result = (float)int_value / 0xFFFFFFFF;
    return result;
}
int main() {
    struct NodeI* hashTable[TABLE_SIZE] = {NULL}; // Initialize the hash table

    int choice, lower, upper; 
    printf("1. Generate random integer number between two numbers.\n2. Generate floating point numbers between 0 and 1.\n \tEnter your choice - ");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:        
            printf("Enter the lower bound: ");
            scanf("%d", &lower);
            printf("Enter the upper bound: ");
            scanf("%d", &upper);
            
            if (upper < lower) {
                printf("Error: Upper bound must be greater than or equal to the lower bound.\n");
                return -1; 
            }

            int randomNum = 0;
            for (int i = 0; i < 10000; i++)
            {
                randomNum = randI(lower, upper);
                if (randomNum != -1) {
                    // printf("Random number between %d and %d: %d\n", lower, upper, randomNum);
                    insertOrUpdate(hashTable, randomNum);
                }
            }
            printCounts(hashTable);
            freeTable(hashTable);   
            break;
        case 2:
            for (int j = 0; j < 1000; j++) {
                float custom_rand_float = randF();
                printf("Random float between 0 and 1: %f\n", custom_rand_float);
            }   
        break;
        
        default:
            printf("Wrong Input chap!!")
        break;
    }

    return 0;
}
