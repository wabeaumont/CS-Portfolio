//Author: Williams Beaumont
//Purpose: Class implementing a dynamic array.

 #include "da.h"

 //Structure of the dynamic array
 typedef struct da {
   int size;
   int capacity;
   void **slots;
   void (*display)(void *value, FILE *output);
   void (*free)(void *value);
   int setFree;
   int debug;
 } DA;

 //Constructor for a dynamic array
 DA *newDA(void) {
   DA *items = malloc(sizeof(DA));
   assert(items != 0);
   items->size = 0;
   items->capacity = 1;
   items->setFree = 0;
   items->slots = malloc(sizeof(void *));
   items->debug = 0;
   return items;
 }

 //Sets a display function for the type of value stored in the array
void setDAdisplay(DA *items, void (*d)(void *,FILE *)) {
  items->display = d;
}

//Like the above function but for a freeing function
void setDAfree(DA *items, void (*f)(void *)) {
  items->free = f;
  items->setFree = 1;
}

//Allows dynamic array to double in capacity
void doubleDA(DA *items) {
  items->capacity = items->capacity * 2;
  items->slots = realloc(items->slots, sizeof(void *) * items->capacity);
}

//Allows dynamic array to halve in capacity
void halveDA(DA *items) {
    items->capacity = items->capacity / 2;
    items->slots = realloc(items->slots, sizeof(void *) * items->capacity);
}

//Allows user to insert value at certain index
void insertDA(DA *items,int index,void *value) {
  assert(index >= 0 && index <= items->size);
  assert(items != 0);
  int i = 0;

  if(items->size == items->capacity) {
    doubleDA(items);
  }

  if(index != items->size) {
    for(i = items->size - 1; i >= index; i = i - 1) {
      items->slots[i + 1] = items->slots[i];
    }
  }

  items->slots[index] = value;
  items->size = items->size + 1;
}

//Allows user to remove value at certain index
void *removeDA(DA *items,int index) {
  assert(index >= 0 && index <= items->size - 1);
  assert(items != 0);
  assert(items->size > 0);
  int i = 0;
  void *value = items->slots[index];

  if(index != items->size - 1) {
    for(i = index; i < items->size - 1; i = i + 1) {
      items->slots[i] = items->slots[i + 1];
    }
  }

  items->size = items->size - 1;
  if(items->size < items->capacity / 4)
    halveDA(items);
  if(items->size == 0) {
    items->capacity = 1;
    items->slots = realloc(items->slots, sizeof(void *));
  }
  return value;
}

//Allows user to join two dynamic arrays together
void unionDA(DA *recipient,DA *donor) {
    int i = 0;
    for(i = 0; i < donor->size; i = i + 1) {
      insertDA(recipient, recipient->size, donor->slots[i]);
    }
    donor->capacity = 1;
    donor->size = 0;
    donor->slots = realloc(donor->slots, sizeof(void *));
  }

//Allows user to get value at certain index
void *getDA(DA *items,int index) {
  assert(index >= 0 && index < items->size);
  return items->slots[index];
}

//Allows user to set value at certain index
void *setDA(DA *items,int index,void *value) {
  assert(index >= 0 && index <= items->size);
  if(index == items->size) {
    insertDA(items, index, value);
    return NULL;
  }
  else {
    void *target = items->slots[index];
    items->slots[index] = value;
    return target;
  }
}

//Allows user to get size of dynamic array
int sizeDA(DA *items) {
  return items->size;
}

//Allows user to display dynamic array
void displayDA(DA *items,FILE *fp) {
  int i = 0;
  fprintf(fp, "[");
  for(i = 0; i < items->size; i = i + 1) {
    if(items->display != 0) {
      items->display(items->slots[i], fp);
    }
    else {
      fprintf(fp, "@%p", items->slots[i]);
    }
    if(i < items->size - 1) {
      fprintf(fp, ",");
    }
  }
  if(items->debug != 0) {
    if(items->size > 0) {
      fprintf(fp, ",");
    }
    fprintf(fp, "[%d]", items->capacity - items->size);
  }
  fprintf(fp, "]");
}

//Allows user to display more specifically
int debugDA(DA *items,int level) {
  int value = items->debug;
  items->debug = level;
  return value;
}

//Allows user to free dynamic array
void freeDA(DA *items) {
  if(items->setFree != 0 && items->size != 0) {
    int i = 0;
    for(i = 0; i < items->size; i = i + 1) {
      items->free(items->slots[i]);
    }
  }
  free(items->slots);
  free(items);
}
