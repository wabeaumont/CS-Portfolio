OBJS = c4.o cda.o da.o queue.o stack.o cell.o board.o game.o integer.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99
EXEC = c4

c4 : c4.o game.o board.o cell.o stack.o da.o queue.o cda.o integer.o
		gcc $(LOPTS) $(OBJS) -o c4

c4.o : c4.c c4.h game.o board.o cell.o stack.o da.o queue.o cda.o integer.o
		gcc $(OOPTS) c4.c

game.o : game.c game.h board.o integer.o
		gcc $(OOPTS) game.c

integer.o : integer.c integer.h
		gcc $(OOPTS) integer.c

board.o : board.c board.h cell.o queue.o stack.o da.o cda.o
		gcc $(OOPTS) board.c

cell.o : cell.c cell.h
		gcc $(OOPTS) cell.c

queue.o : queue.c queue.h cda.o
		gcc $(OOPTS) queue.c

stack.o : stack.c stack.h da.o
		gcc $(OOPTS) stack.c

cda.o : cda.c cda.h
		gcc $(OOPTS) cda.c

da.o : da.c da.h
		gcc $(OOPTS) da.c

valgrind: c4
		valgrind --leak-check=full --show-leak-kinds=all c4

clean	:
		rm -f $(OBJS) $(EXEC)
