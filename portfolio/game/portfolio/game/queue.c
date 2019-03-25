//Author: Williams Beaumont
//Purpose: Class implementing a queue

#include "queue.h"
#include "cda.h"

//Structure of the queue
typedef struct queue {
  CDA *cda;
  int debugLevel;
  void (*display)(void *value, FILE *output);
} QUEUE;

//Constructor for a queue
QUEUE *newQUEUE(void) {
  QUEUE *items = malloc(sizeof(QUEUE));
  assert(items != 0);
  items->cda = newCDA();
  items->debugLevel = 0;
  return items;
}

//Sets a display function for the type of value stored in the queue
void  setQUEUEdisplay(QUEUE *items,void (*d)(void *,FILE *)) {
  items->display = d;
  setCDAdisplay(items->cda, d);
}

//Like the above function but for a freeing function
void  setQUEUEfree(QUEUE *items,void (*f)(void *)) {
  setCDAfree(items->cda, f);
}

//Allows user to add an item to the end of the queue
void  enqueue(QUEUE *items,void *value) {
  insertCDAback(items->cda, value);
}

//Allows user to remove an item from the end of the queue
void *dequeue(QUEUE *items) {
  return removeCDAfront(items->cda);
}

//Allows user to see what the item at the end of the queue is
void *peekQUEUE(QUEUE *items) {
  return getCDA(items->cda, 0);
}

//Allows user to display the queue
void  displayQUEUE(QUEUE *items,FILE *fp) {
  if(items->debugLevel != 1 && items->debugLevel != 2) {
    int i = 0;
    fprintf(fp, "<");
    if(sizeCDA(items->cda) > 0) {
      for(i = 0; i < sizeCDA(items->cda); i = i + 1) {
        items->display(getCDA(items->cda, i), fp);
        if(i < sizeCDA(items->cda) - 1) {
          fprintf(fp, ",");
        }
      }
    }
    fprintf(fp, ">");
  }
  else {
    displayCDA(items->cda, fp);
  }
}

//Like the above but with more detail
int   debugQUEUE(QUEUE *items,int level) {
  items->debugLevel = level;
  if(level == 1)
    return debugCDA(items->cda, 0);
  else if(level == 2)
    return debugCDA(items->cda, 1);
  else
    return level;
}

//Allows user to free a queue
void  freeQUEUE(QUEUE *items) {
  freeCDA(items->cda);
  free(items);
}

//Allows user to see the size of the queue
int   sizeQUEUE(QUEUE *items) {
  return sizeCDA(items->cda);
}
