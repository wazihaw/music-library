#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *artist;
    char *songName;
    char *genre;
    struct node *next;
} Node;

typedef struct linkedList {
    Node *head;
} LinkedList;

// Declarations of linked list functions

Node *createNode(char *sName, char *sArtist, char *sGenre);
void initList(LinkedList *list);
bool isEmpty(LinkedList *list);
bool insertAtFront(LinkedList *list, char *sName, char *sArtist, char *sGenre);
bool insertTitleOrdered(LinkedList *list, char *sName, char *sArtist, char *sGenre);
void printList(LinkedList *list);
bool searchName(LinkedList *list, char *sName);
bool deleteSong(LinkedList *list, char *sName);
void deleteFront(LinkedList *list);
void deleteAllNodes(LinkedList *list);


// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser(char *prompt, char *s, int arraySize);
void songNameDuplicate(char *songName);
void songNameFound(char *songName);
void songNameNotFound(char *songName);
void songNameDeleted(char *songName);
void artistFound(char *artist);
void artistNotFound(char *artist);
void printMusicLibraryEmpty(void);
void printMusicLibraryTitle(void);


const int MAX_LENGTH = 1024;

int main(void) {
    // Declare the head of the linked list.
    LinkedList musicLibrary;
    initList(&musicLibrary);

    // Announce the start of the program
    printf("Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
           "P (print), Q (quit).\n");

    char response;
    char input[MAX_LENGTH + 1];
    do {
        inputStringFromUser("\nCommand", input, MAX_LENGTH);

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I') {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.

                char *promptName = "Song name" ;
                char *promptArtist =  "Artist" ;
                char *promptGenre = "Genre" ;
                
                char inputName[MAX_LENGTH+1];
                char inputArtist[MAX_LENGTH+1];
                char inputGenre[MAX_LENGTH+1];
                
                inputStringFromUser(promptName, inputName, MAX_LENGTH);
                inputStringFromUser(promptArtist, inputArtist, MAX_LENGTH);
                inputStringFromUser(promptGenre, inputGenre, MAX_LENGTH);
                //printf("%s\n%s\n%s\n", inputName, inputArtist, inputGenre);
                
                insertTitleOrdered(&musicLibrary, inputName, inputArtist, inputGenre);
                
                

        }
        else if (response == 'D') {
            // Delete a song from the list.

            char *prompt = "\nEnter the name of the song to be deleted" ;
            
            char deleteThisSong[MAX_LENGTH + 1];
            
            inputStringFromUser(prompt, deleteThisSong, MAX_LENGTH);
            deleteSong(&musicLibrary, deleteThisSong);

        }
        else if (response == 'S') {
            // Search for a song by its name.

            char *prompt = "\nEnter the name of the song to search for" ;

            
            char searchThisName[MAX_LENGTH + 1];
            
            inputStringFromUser(prompt, searchThisName, MAX_LENGTH);
            searchName(&musicLibrary, searchThisName);

        }
        else if (response == 'P') {
            // Print the music library.

            
            if(isEmpty(&musicLibrary) == true){
                printMusicLibraryEmpty();
            } else {
                printMusicLibraryTitle();
                printList(&musicLibrary);
            }

        }
        else if (response == 'Q') {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf ("\nInvalid command.\n");
        }
    } while (response != 'Q');

    // Delete the entire linked list.
    
    deleteAllNodes(&musicLibrary);

    // Print the linked list to confirm deletion.
    if(isEmpty(&musicLibrary) == true){
                printMusicLibraryEmpty();
            } else {
                printMusicLibraryTitle();
                printList(&musicLibrary);
            }

    return 0;
}




// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char *prompt, char *s, int maxStrLength) {
    int i = 0;
    char c;

    printf("%s --> ", prompt);
    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    s[i] = '\0';
}

// Function to call when the user is trying to insert a song name
// that is already in the personal music library.
void songNameDuplicate(char *songName) {
    printf("\nA song with the name '%s' is already in the music library.\n"
           "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound(char *songName) {
    printf("\nThe song name '%s' was found in the music library.\n",
           songName);
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound(char *songName) {
    printf("\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted(char *songName) {
    printf("\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf("\nThe music library is empty.\n");
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf("\nMy Personal Music Library: \n");
}

// Add your functions below this line.

//   ADD STATEMENT(S) HERE


// Initialize list.
void initList(LinkedList *list){
    list->head = NULL;
}

// Validate if list is empty.
bool isEmpty(LinkedList *list){
    if(list->head == NULL){
        return true;
    }
    
    return false;
}

// Create a new node with the necessary parameters.
Node *createNode(char *sName, char *sArtist, char *sGenre){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->songName = malloc(sizeof(char)*(strlen(sName)+1));
    newNode->artist = malloc(sizeof(char)*(strlen(sArtist)+1));
    newNode->genre = malloc(sizeof(char)*(strlen(sGenre)+1));
    
    if(newNode != NULL && newNode->songName != NULL && newNode->artist != NULL && newNode->genre != NULL){
        strcpy(newNode->songName, sName);
        strcpy(newNode->artist, sArtist);
        strcpy(newNode->genre, sGenre);
        newNode->next = NULL;
    }
    
    return newNode;
    
}

// Insert node at front of list.
bool insertAtFront(LinkedList *list, char *sName, char *sArtist, char *sGenre){
    if(isEmpty(list) == true){
        list->head = createNode(sName,sArtist,sGenre);
        return list->head != NULL;
    }
    
    
    Node *temp = createNode(sName, sArtist, sGenre);
    if(temp == NULL){
       return false; 
    } 
    
    temp->next = list->head;
    list->head = temp;
    return true;
    
}


// Insert nodes in lexicographic order.
bool insertTitleOrdered(LinkedList *list, char *sName, char *sArtist, char *sGenre){
    if(isEmpty(list)==true){
        return insertAtFront(list, sName, sArtist, sGenre);
        
    }
    
    if(strcmp(sName,list->head->songName) == 0){
        songNameDuplicate(sName);
        return false;
    }
    
    if((strcmp(sName, list->head->songName) < 0)) { 
       return insertAtFront(list, sName, sArtist, sGenre); 
    }
    
    
    Node *current = list->head;
    while (current->next != NULL && (strcmp(sName, current->next->songName) > 0)){
        current = current->next;
    }
    
    
    
    Node *newNode = createNode(sName, sArtist, sGenre);
    if(newNode == NULL){
        return false;
    }
    
    
    newNode->next = current->next;
    current->next = newNode;
    
    if(current->next->next!=NULL){
        if(strcmp(newNode->songName, current->next->next->songName) == 0){
            Node *temp = current->next->next;
            current->next->next = temp->next;
            free(temp->artist);
            free(temp->genre);
            free(temp->songName);
            free(temp);
            songNameDuplicate(sName);
            return false;
        }
    }
    
    return true;
    
}


// Print all the nodes in the music library.
void printList(LinkedList *list){
    Node *current = list->head;
    while(current != NULL){
        printf("\n%s\n", current->songName);
        printf("%s\n", current->artist);
        printf("%s\n", current->genre);
        current = current->next;
    }
    
}

// Search for a specific song name in list.
bool searchName(LinkedList *list, char *sName){
    Node *current = list->head;
    while(current != NULL){
        if(strcmp(current->songName,sName)==0){
            songNameFound(sName);
            printf("\n%s\n", current->songName);
            printf("%s\n", current->artist);
            printf("%s\n", current->genre);
            return true;
        }
        
        current = current->next;
    }
    
    songNameNotFound(sName);
    return false;
}

// Delete specific song title.
bool deleteSong(LinkedList *list, char *sName){
    if(isEmpty(list) == true){
        return false;
    }
    
    if(strcmp(list->head->songName,sName)==0){
        Node *temp = list->head->next;
        free(list->head->artist);
        free(list->head->genre);
        free(list->head->songName);
        free(list->head);
        list->head = temp;
        songNameDeleted(sName);
        return true;
    }
    
    Node *current = list->head;
    while(current->next != NULL && (strcmp(current->next->songName, sName) != 0)){
        current = current->next;
    }
    
    if(current->next != NULL){
        Node *temp = current->next;
        
        free(temp->artist);
        free(temp->genre);
        free(temp->songName);
        free(temp);
        
        current->next = temp->next;
        songNameDeleted(sName);
        return true;
    }
    
    songNameNotFound(sName);
    return false;
}


// Delete front of list (first node).
void deleteFront(LinkedList *list){
    if(isEmpty(list)==true){
        return ;
    }
    
    Node *newHead = list->head->next;
    free(list->head->artist);
    free(list->head->genre);
    free(list->head->songName);
    free(list->head);
    list->head = newHead;
}


// Delete all nodes in the list.
void deleteAllNodes(LinkedList *list){
    while(isEmpty(list)==false){
        songNameDeleted(list->head->songName); 
        deleteFront(list); 
    }
    
    list->head = NULL;
}
