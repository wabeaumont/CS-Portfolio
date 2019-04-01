#ifndef __STACK_INCLUDED__
#define __STACK_INCLUDED__

    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>

    typedef struct stack STACK;

    extern STACK *newSTACK(void);
    extern void  setSTACKdisplay(STACK *items,void (*d)(void *,FILE *));
    extern void  setSTACKfree(STACK *items,void (*f)(void *));
    extern void  push(STACK *items,void *value);
    extern void *pop(STACK *items);
    extern void *peekSTACK(STACK *items);
    extern void  displaySTACK(STACK *items,FILE *fp);
    extern int   debugSTACK(STACK *items,int level);
    extern void  freeSTACK(STACK *items);
    extern int   sizeSTACK(STACK *items);

    #endif
