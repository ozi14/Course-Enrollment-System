COURSE = cs240
SEMESTER = spring2023
CP_NUMBER = 1
LASTNAME = Ucar
GITUSERID = ozi14
EXE = scheduler_cp1

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/scheduler_cp1.o
	$(CC) $(FLAGS) $(OBJ)/scheduler_cp1.o -o $@

$(OBJ)/scheduler_cp1.o: scheduler_cp1.cpp 
	$(CC) $(FLAGS) -c scheduler_cp1.cpp -o $@

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz

