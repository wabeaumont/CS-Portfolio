//Author: Williams Beaumont
//Purpose: Class implementing a circular dynamic array

#include "cda.h"

//Structure of the circular dynamic array
typedef struct cda {
  int size;
  int capacity;
  void **slots;
  void (*display)(void *value, FILE *output);
  void (*free)(void *value);
  int setFree;
  int debug;
  int start;
  int end;
} CDA;

//Constructor for a dynamic array
CDA *newCDA(void) {
  CDA *items = malloc(sizeof(CDA));
  assert(items != 0);
  items->size = 0;
  items->capacity = 1;
  items->setFree = 0;
  items->slots = malloc(sizeof(void *));
  items->debug = 0;
  items->start = 0;
  items->end = 0;
  return items;
}

//Sets a display function for the type of value stored in the array
void setCDAdisplay(CDA *items, void (*display)(void *,FILE *)) {
  items->display = display;
}

//Like the above function but for a freeing function
void setCDAfree(CDA *items, void (*f)(void *)) {
  items->free = f;
  items->setFree = 1;
}

//Allows dynamic array to double in capacity
void doubleCDA(CDA *items) {
  int i = 0;
  void **temp = malloc(sizeof(void *) * items->capacity * 2);
  for(i = 0; i < items->size; i = i + 1) {
    temp[i] = getCDA(items, i);
  }
  items->capacity = items->capacity * 2;
  free(items->slots);
  items->slots = temp;
  items->start = 0;
  items->end = items->size - 1;
}

//Allows dynamic array to halve in capacity
void halveCDA(CDA *items) {
    int i = 0;
    void **temp = malloc(sizeof(void *) * items->capacity / 2);
    for(i = 0; i < items->size; i = i + 1) {
      temp[i] = getCDA(items, i);
    }
    items->capacity = items->capacity / 2;
    free(items->slots);
    items->slots = temp;
    items->start = 0;
    items->end = items->size - 1;
}

//Allows user to insert value at certain index
void insertCDA(CDA *items,int index,void *value) {
  assert(index >= 0 && index <= items->size);
  assert(items != 0);
  int i = 0;

  if(items->size == items->capacity) {
    doubleCDA(items);
  }

  //special case if the array is empty
  /*if(items->size == 0) {
    items->start = index;
    items->end = index;
  }*/

  if(index == 0) { //if inserting at front
    items->start = (items->start - 1 + items->capacity) % items->capacity;
    items->slots[(index + items->start) % items->capacity] = value;
    //setCDA(items, index, value);
    items->size = items->size + 1;
  }
  else if(index == items->size) { //if inserting at back
    items->slots[(index + items->start) % items->capacity] = value;
    //setCDA(items, index, value);
    items->size = items->size + 1;
    items->end = (items->end + 1) % items->capacity;
  }
  else if(index <= items->size / 2) { //if inserting in front half
    items->start = (items->start - 1 + items->capacity) % items->capacity;
    for(i = 0; i <= index; i = i + 1) {
      items->slots[(i + items->start) % items->capacity] = items->slots[(i + items->start + 1) % items->capacity];
      //setCDA(items, i, getCDA(items, i + 1));
    }
    items->slots[(index + items->start) % items->capacity] = value;
    //setCDA(items, index, value);
    items->size = items->size + 1;
  }
  else { //if inserting in back half
    for(i = items->size - 1; i >= index; i = i - 1) {
      items->slots[(i + items->start + 1) % items->capacity] = items->slots[(i + items->start) % items->capacity];
      //setCDA(items, i + 1, getCDA(items, i));
    }
    items->slots[(index + items->start) % items->capacity] = value;
    //setCDA(items, index, value);
    items->size = items->size + 1;
    items->end = (items->end + 1) % items->capacity;
  }
}

//Allows user to remove value at certain index
void *removeCDA(CDA *items,int index) {
  assert(index >= 0 && index <= items->size - 1);
  assert(items != 0);
  assert(items->size > 0);
  int i = 0;
  void *value = items->slots[(index + items->start) % items->capacity];
  //void *value = getCDA(items, index);

  if(index == 0) {
    items->start = (items->start + 1) % items->capacity;
  }
  else if(index == items->size - 1) {
    items->end = (items->end - 1) % items->capacity;
  }
  else if(index < items->size / 2) {
    for(i = index; i > 0; i = i - 1) {
      items->slots[(i + items->start) % items->capacity] = items->slots[(i + items->start - 1) % items->capacity];
      //setCDA(items, i + 1, getCDA(items, i));
    }
    items->start = (items->start + 1) % items->capacity;
  }
  else {
    for(i = index; i < items->size - 1; i = i + 1) {
      items->slots[(i + items->start) % items->capacity] = items->slots[(i + items->start + 1) % items->capacity];
      //setCDA(items, i, getCDA(items, i + 1));
    }
    items->end = (items->end - 1) % items->capacity;
  }

  items->size = items->size - 1;
  if(items->size < items->capacity / 4)
    halveCDA(items);
  if(items->size == 0) {
    void **temp = malloc(sizeof(void *));
    items->capacity = 1;
    free(items->slots);
    items->slots = temp;
    items->start = 0;
    items->end = 0;
  }
  return value;
}

//Allows user to join two dynamic arrays together
void unionCDA(CDA *recipient,CDA *donor) {
    int i = 0;
    void *j;
    for(i = 0; i < donor->size; i = i + 1) {
      j = getCDA(donor, i);
      insertCDA(recipient, recipient->size, j);
    }
    donor->capacity = 1;
    void **temp = malloc(sizeof(void *));
    free(donor->slots);
    donor->slots = temp;
    donor->start = 0;
    donor->end = 0;
    donor->size = 0;
}

//Allows user to get value at certain index
void *getCDA(CDA *items,int index) {
  assert(index >= 0 && index < items->size);
  return items->slots[(index + items->start) % items->capacity];
  //return getCDA(items, index);
}

//Allows user to set value at certain index
void *setCDA(CDA *items,int index,void *value) {
  assert(index >= -1 && index <= items->size);
  if(index == items->size) {
    insertCDAback(items, value);
    return NULL;
  }
  else if(index == -1) {
    insertCDAfront(items, value);
    return NULL;
  }
  else {
    void *target = items->slots[(index + items->start) % items->capacity];
    items->slots[(index + items->start) % items->capacity] = value;
    //setCDA(items, index, value);
    return target;
  }
}

//Allows user to get size of dynamic array
int  sizeCDA(CDA *items) {
  return items->size;
}

//Allows user to display dynamic array
void displayCDA(CDA *items,FILE *fp) {
  int i = 0;
  fprintf(fp, "(");
  for(i = 0; i < items->size; i = i + 1) {
    if(items->display != 0) {
      items->display(items->slots[(i + items->start) % items->capacity], fp);
      //items->display(getCDA(items, i), fp);
    }
    else {
      fprintf(fp, "@%p", items->slots[(i + items->start) % items->capacity]);
      //fprintf(fp, "@%p", getCDA(items, i));
    }
    if(i < items->size - 1) {
      fprintf(fp, ",");
    }
  }
  if(items->debug != 0) {
    if(items->size > 0) {
      fprintf(fp, ",");
    }
    fprintf(fp, "(%d)", items->capacity - items->size);
  }
  fprintf(fp, ")");
}

//Allows user to display more specifically
int  debugCDA(CDA *items,int level) {
  int value = items->debug;
  items->debug = level;
  return value;
}

//Allows user to free dynamic array
void freeCDA(CDA *items) {
  if(items->setFree != 0 && items->size != 0) {
    int i = 0;
    for(i = 0; i < items->size; i = i + 1) {
      items->free(getCDA(items, i));
    }
  }
  free(items->slots);
  free(items);
}
