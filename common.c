#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



typedef struct Node{
  char *word;
  int count;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct List{
  Node *head;
  Node *tail;
} List;

void insertNodeAtTail(List*, char **);
void printList(List*, int);
//void printlistTailToHead();
// void insertNodeAtHead();

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Please include the two input text file names and the output file name at execution time! \n");
    exit(EXIT_FAILURE);
  }

  List firstFileLinkedList;
  List secondFileLinkedList;

  firstFileLinkedList.head = NULL;
  firstFileLinkedList.tail = NULL;

  secondFileLinkedList.head = NULL;
  secondFileLinkedList.tail = NULL;

  FILE *fPtr1;
  FILE *fPtr2;
  // FILE *fPtr3;
  char *scannedWord = NULL;
  
  fPtr1 = fopen(argv[1], "r");

  if (fPtr1 == NULL) {
    printf("The file %s was not found or could not be open. Please try again!", argv[1]);
    exit(EXIT_FAILURE);
  }

  fPtr2 = fopen(argv[2], "r");

  if (fPtr2 == NULL) {
    printf("The file %s was not found or could not be open. Please try again!", argv[2]);
    exit(EXIT_FAILURE);
  }

  while(fscanf(fPtr1,"%ms", &scannedWord) != EOF) {
    insertNodeAtTail(&firstFileLinkedList, &scannedWord);
  }

  printList(&firstFileLinkedList, 0);

  fclose(fPtr1);
  fclose(fPtr2);
  //fclose(fPtr3);

  return 0;
}

void insertNodeAtTail(List *firstFileLinkedList, char **scannedWord) {

  char * wordToInsert = strndup(*scannedWord, strlen(*scannedWord));
  Node *nextTailNode = malloc(sizeof(Node));

  //could I use strndup?? Do I need to do a +1?
  //Do I even need to do malloc again?
  nextTailNode->word = wordToInsert;
  nextTailNode->count = 1;

  Node *currentNode = firstFileLinkedList->head;
  // Node *currentHeadNode = firstFileLinkedList->head;
  Node *currentTailNode = firstFileLinkedList->tail;

  if (currentNode == NULL) {

    nextTailNode->prev = NULL;
    nextTailNode->next = NULL;

    firstFileLinkedList->head = nextTailNode;
    firstFileLinkedList->tail = nextTailNode;

  } else {
 
    while(currentNode != NULL) {
      
      if (strcmp(currentNode->word, wordToInsert) == 0) {

        currentNode->count++;
        break;
        
      } else {
        currentNode = currentNode->next;
      }

      if (currentNode == NULL) {

        nextTailNode->prev = currentTailNode;
        nextTailNode->next = NULL;
        currentTailNode->next = nextTailNode;
        firstFileLinkedList->tail = nextTailNode;

      }

    }
  
  }


  printf("values are %s \n", wordToInsert);

  free(*scannedWord);
}

void printList(List *list, int reverse){
  Node *currentNode = NULL;

  if (!reverse) {
    currentNode = list->head;
    
    while (currentNode != NULL) {

      printf("WORD: %s \n COUNT: %d \n\n", currentNode->word, currentNode->count);

      currentNode = currentNode->next;
    }

  } else {
    
    currentNode = list->tail;
    
    while (currentNode != NULL) {

      printf("WORD: %s \n COUNT: %d \n\n", currentNode->word, currentNode->count);

      currentNode = currentNode->prev;
    }

  }

}