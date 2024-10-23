FLAGS=-O3 -std=c++17 -mcmodel=large

CC=g++

RM=rm -f

EXEC=Aexec

all: $(EXEC)

$(EXEC): $(EXEC).cpp
	$(CC) $(FLAGS) $(EXEC).cpp -o $(EXEC)

clean:
	$(RM) $(EXEC)
