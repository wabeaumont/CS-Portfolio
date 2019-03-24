//Author: Williams Beaumont
//Purpose: Class implementing a stack

#include "stack.h"
#include "da.h"

//Structure of the stack
typedef struct stack {
  DA *da;
  int debugLevel;
  void (*display)(void *value, FILE *output);
} STACK;

//Constructor for a stack
STACK *newSTACK(void) {
  STACK *items = malloc(sizeof(STACK));
  assert(items != 0);
  items->da = newDA();
  items->debugLevel = 0;
  return items;
}

//Sets a display function for the type of value stored in the stack
void  setSTACKdisplay(STACK *items,void (*d)(void *,FILE *)) {
  items->display = d;
  setDAdisplay(items->da, d);
}

//Like the above function but for a freeing function
void  setSTACKfree(STACK *items,void (*f)(void *)) {
  setDAfree(items->da, f);
}

//Allows user to add an item to the end of the stack
void  push(STACK *items,void *value) {
  insertDAback(items->da, value);
}

//Allows user to remove an item from the end of the stack
void *pop(STACK *items) {
  assert(sizeDA(items->da) > 0);
  return removeDAback(items->da);
}

//Allows user to see what the item at the end of the stack is
void *peekSTACK(STACK *items) {
  assert(sizeDA(items->da) > 0);
  return getDA(items->da, sizeDA(items->da) - 1);
}

//Allows user to display the stack
void  displaySTACK(STACK *items,FILE *fp) {
  if(items->debugLevel != 1 && items->debugLevel != 2) {
    int i = 0;
    fprintf(fp, "|");
    if(sizeDA(items->da) > 0) {
      for(i = sizeDA(items->da) - 1; i >= 0; i = i - 1) {
        items->display(getDA(items->da, i), fp);
        if(i > 0) {
          fprintf(fp, ",");
        }
      }
    }
    fprintf(fp, "|");
  }
  else {
    displayDA(items->da, fp);
  }
}

//Like the above but with more detail
int   debugSTACK(STACK *items,int level) {
  items->debugLevel = level;
  if(level == 1)
    return debugDA(items->da, 0);
  else if(level == 2)
    return debugDA(items->da, 1);
  else
    return level;
}

//Allows user to free a stack
void  freeSTACK(STACK *items) {
  freeDA(items->da);
  free(items);
}

//Allows user to see the size of the stack
int   sizeSTACK(STACK *items) {
  return sizeDA(items->da);
}
