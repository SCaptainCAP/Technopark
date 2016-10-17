CC := g++
CFLAGS := -Wall -pedantic -g3
OBJS := main.o

main : $(OBJS)
	$(CC) $^ -o main

%.o : %.cpp *.h
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(OBJS) main
