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
CRUNCS = CrunoDraw2.h CrunoGame.h Cruno8.h CrunoSkip.h CrunoReverse.h CrunoPlayer.h
# Cruno classes compiled objects
CRUNOO = CrunoDraw2.o CrunoGame.o Cruno8.o CrunoSkip.o CrunoReverse.o CrunoPlayer.o
# Which test object to run.
TESTO = mytest.o
FINAL = test

# Base files
game.o: game.cpp $(BASECS)
	g++ $(CFLAGS) game.cpp

player.o: player.cpp $(BASECS)
	g++ $(CFLAGS) player.cpp

card.o: card.cpp $(BASECS)
	g++ $(CFLAGS) card.cpp

# Cruno cards
CrunoDraw2.o: CrunoDraw2.cpp CrunoDraw2.h $(BASECS)
	g++ $(CFLAGS) CrunoDraw2.cpp

CrunoSkip.o: CrunoSkip.cpp CrunoSkip.h $(BASECS)
	g++ $(CFLAGS) CrunoSkip.cpp

Cruno8.o: Cruno8.cpp Cruno8.h $(BASECS)
	g++ $(CFLAGS) Cruno8.cpp

CrunoReverse.o: CrunoReverse.cpp CrunoReverse.h $(BASECS)
	g++ $(CFLAGS) CrunoReverse.cpp

# Cruno gameplay classes
CrunoPlayer.o: CrunoPlayer.cpp CrunoPlayer.h $(BASECS)
	g++ $(CFLAGS) CrunoPlayer.cpp

CrunoGame.o: CrunoGame.cpp CrunoGame.h $(BASECS)
	g++ $(CFLAGS) CrunoGame.cpp

# Runner classes.
proj4.o: proj4.cpp $(BASECS)
	g++ $(CFLAGS) proj4.cpp

mytest.o: mytest.cpp $(BASECS) $(CRUNCS)
	g++ $(CFLAGS) mytest.cpp

# Executables.
test: $(BASEOS) $(CRUNOO) $(TESTO)
	g++ $(LFLAGS) $(BASEOS) $(CRUNOO) $(TESTO) -o $(FINAL)

# Utility commands
all: $(BASEOS) $(CRUNOO) $(TESTO) $(FINAL)

clean:
	\rm *.o *~ $(FINAL)