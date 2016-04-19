# Debug flag
DEBUG = -g
# Flags for compiling classes
CFLAGS = -ansi -Wall -c -w $(DEBUG)
# Flags for linking
LFLAGS = -ansi -Wall $(DEBUG)
# Base classes header files
BASECS = game.h card.h player.h
# Base classes compiled objects
BASEOS = game.o card.o player.o
# Cruno classes header files
CRUNCS = CrunoDraw2.h CrunoGame.h Cruno8.h CrunoSkip.h
# Cruno classes compiled objects
CRUNOO = CrunoDraw2.o CrunoGame.o Cruno8.o CrunoSkip.o
# Which test object to run.
TESTO = mytest.o

# Base files
game.o: game.cpp $(BASECS)
	g++ $(CFLAGS) game.cpp

player.o: player.cpp $(BASECS)
	g++ $(CFLAGS) player.cpp

card.o: card.cpp $(BASECS)
	g++ $(CFLAGS) card.cpp

CrunoDraw2.o: CrunoDraw2.cpp CrunoDraw2.h $(BASECS)
	g++ $(CFLAGS) CrunoDraw2.cpp

CrunoSkip.o: CrunoSkip.cpp CrunoSkip.h $(BASECS)
	g++ $(CFLAGS) CrunoSkip.cpp

Cruno8.o: Cruno8.cpp Cruno8.h $(BASECS)
	g++ $(CFLAGS) Cruno8.cpp

CrunoGame.o: CrunoGame.cpp CrunoGame.h $(BASECS)
	g++ $(CFLAGS) CrunoGame.cpp

proj4.o: proj4.cpp $(BASECS)
	g++ $(CFLAGS) proj4.cpp

mytest.o: mytest.cpp $(BASECS) $(CRUNCS)
	g++ $(CFLAGS) mytest.cpp

test: $(BASEOS) $(CRUNOO) $(TESTO)
	g++ $(LFLAGS) $(BASEOS) $(CRUNOO) $(TESTO) -o test

all: $(BASEOS) $(CRUNOO) $(TESTO)