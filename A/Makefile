FLAGS=-O3 -Wall -lpthread -std=c++17 -mcmodel=large

CC=g++

RM=rm -f

EXEC=optimize

all: $(EXEC)

$(EXEC): 
	$(CC) $(FLAGS) $(EXEC).cpp -o $(EXEC)

clean:
	$(RM) $(EXEC)
