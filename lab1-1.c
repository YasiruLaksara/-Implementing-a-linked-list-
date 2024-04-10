// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <stdbool.h>
// user-defined header files
#include "node.h"

// macros 

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

// function prototypes
void print_list(list * lst); 
void run(list * lst);


int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    free(lst);
	return 0;
}

// parse the input
void run(list *lst) 
{
    char data[100];
    
    scanf("%[^\n]", data); // Reading the user input

    char newWord[20];
    int j = 0;

    for (int i = 0; data[i] != '\0'; i++) { // Iterating through each character in the data in user input
    
        if (data[i] == ',') { // If there is a comma , inserting the word into the list
        
            newWord[j] = '\0'; // Terminating the word with a null character
            insert_node_after(lst, -1, newWord); // Inserting the word after the last position
            j = 0; // Resetting the index for the new word
        } 
        else {
            newWord[j++] = data[i]; // Adding the character to the new word
        }
    }
    if (j > 0) { // If there is a remaining word to be inserted
        newWord[j] = '\0'; // Terminating the word with a null character
        insert_node_after(lst, -1, newWord); // Inserting the word after the last position
    }

    int command;
    bool flag = true;

    while (flag) { 
        scanf("%d", &command); // Reading the command from the user input

        switch (command) {
            
            case 0:
                flag = false; // Setting flag to false to exit the loop
                break;
                
            case INSERT_BEFORE: {
                int index;
                char word[20];
                scanf("%d %s",&index,word); // Reading the index and the word from the user input
                insert_node_before(lst,index,word); // Inserting the word before the specified position
                break;
            }
            
            case INSERT_AFTER: {
                int index;
                char word[20];
                scanf("%d %s", &index,word); // Reading the index and the word from the user input
                insert_node_after(lst,index,word); // Inserting the word after the specified position
                break;
            }
            
            case DELETE_NODE: {
                int index;
                scanf("%d", &index); // Reading the index from the user input
                delete_node(lst, index); // Deleting the node at the specified position
                break;
            }
            case DELETE_LIST:
                delete_list(lst); // Deleting the entire list and exiting the loop
                flag =false;
                break;
        }
    }
	
}

//Print the list contents
void print_list(list * lst)
{
   
    node *current =lst->head; // Setting the current node to the head of the list
    
   
    // Checking whether the current node is not NULL
    if (current !=  NULL)
    {
        
        printf("%s",current->word);// Printing the word of the current node

       
        current =current->next;

       
        while (current !=  lst->head)
        {
            
            printf(" %s",current->word);// Printing the word of the current node

            current = current->next;
        }
    }
    printf("\n");

}

