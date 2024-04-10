// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

int get_length(list *lst) 
{
    
    if (lst->head == NULL) { //Checking Whether the list is empty
        return 0;
    }
    
    node *current = lst->head->next; // Start from the next node after the head
    int count = 1; // Initializing count to 1 since head already exists)
    
    while (current != lst->head) { // Traversing the list until reach the head again
        count++; 
        current = current->next; 
    }
    return count; 
}

node *create_node(char *word) 
{
    node *new_node = (node *)malloc(sizeof(node)); // Allocating memory for the new node
    new_node->prev = NULL; // Setting the previous pointer of the new node to NULL
    new_node->next = NULL; // Setting the next pointer of the new node to NULL

    new_node->word = (char *)malloc(strlen(word) + 1); // Allocating memory for the word
    strcpy(new_node->word,word); // Copy the word into the new node

    return new_node; 
}


//-------------------node.c------------------------------

// implementation
void insert_node_before(list *lst, int index, char *word)
{	
	node *new_node = create_node(word); // Creating a new node with the given word
	
    // If the list is empty
    if (lst->head == NULL) { 
        
        lst->head = new_node; 
        lst->head->next = lst->head; 
        lst->head->prev = lst->head; 
        return; 
    }

    node *current = lst->head; // Starting from the head of the list
    
    for (int i = 0; i < abs(index); i++) { // Traversing to the required position in the list
    
        if (index < 0) {
            current = current->prev; 
        } 
        else {
            current = current->next ; 
        }
    }
    
    new_node->prev = current->prev; // Setting the previous pointer of the new node
    new_node->next = current; // Setting the next pointer of the new node
    current->prev->next = new_node; // Setting the next pointer of the previous node
    current->prev = new_node; // Setting the previous pointer of the current node

    if (index == 0) { // If the index is 0, updating the head of the list
    
        lst->head = new_node;
    }
}


void insert_node_after(list *lst, int index, char *word)
{
	if (index < 0) {
        index = get_length(lst) +  index; // Converting negative index to positive index
    }
    insert_node_before(lst, index + 1,word); // Inserting the node before the next position
}


char *list_to_sentence(list *lst)
{
	if (lst->head ==NULL) { // If the list is empty
        return NULL; 
    }

    int total_length = 0; // Initializing the total length
    node *current = lst->head; // Starting from the head of the list
    
    do {
        total_length +=strlen(current->word) + 1; // Calculating the total length of the sentence including spaces
        current = current->next; 
    } 
    
    while (current != lst->head); // Traversing until reach the head again

    char *sentence = (char *)malloc(total_length); // Allocating memory for the sentence
    if (sentence == NULL) { // Checking whether the memory allocation failed
        fprintf(stderr,"Memory allocation failed\n"); 
        exit(1);
    }

    sentence[0] = '\0'; // Initialize the sentence as an empty string
    current =lst->head; // Start from the head of the list 
    
    do {
        strcat(sentence, current->word); // Concatenating the word to the sentence
        strcat(sentence, " "); // Concatenating a space after the word
        current = current->next; 
    } 
    
    while (current != lst->head);

    return sentence; 
}

void delete_node(list *lst, int index)
{
	if (lst->head == NULL) { // If the list is empty
        return; 
    }

    node *current= lst->head; 

    if (index >= 0) { // If the index is positive or zero
        for (int i = 0; i < index; i++) {
            current = current->next; 
        }
    } 
    else if (index < 0) { // If the index is negative
    
        for (int j = 0; j > index; j--) { 
            current =current->prev; 
        }
    }

    if (current->next == current) { // If the list has only one node
        lst->head = NULL; 
    }
    
    else {
        current->prev->next = current->next; // Setting the next pointer of the previous node
        current->next->prev = current->prev; // Setting the previous pointer of the next node

        if (current == lst->head) { // If the deleted node is the head of the list
            lst->head = current->next; // Updating the head of the list to the next node
        }
    }

    free(current->word); // Freeing the memory allocated for the word
    
    free(current); // Freeing the memory allocated for the node
}

void delete_list(list *lst)
{
	node *current = lst->head; 

    while (current->next != lst->head) { 
        
        node *temp = current; 
        current =current->next; 
        free(temp->word); // Free the memory allocated for the word
        free(temp); 
    }

    free(current->word); // Freeing the memory allocated for the word of the last node
    free(current); // Freeing the memory allocated for the last node
    lst->head = NULL; // Setting the head to NULL

}

//Copy any additional functions you have written here
