DEBUG = -g
CFLAGS = -ansi -Wall -c -w $(DEBUG)
LFLAGS = -ansi -Wall $(DEBUG)
BASECS = game.h card.h player.h
BASEOS = game.o card.o player.o
CRUNCS = CrunoDraw2.h CrunoGame.h Cruno8.h
CRUNOO = CrunoDraw2.o CrunoGame.o Cruno8.o
TESTO = mytest.o

game.o: game.cpp $(BASECS)
	g++ $(CFLAGS) game.cpp

player.o: player.cpp $(BASECS)
	g++ $(CFLAGS) player.cpp

card.o: card.cpp $(BASECS)
	g++ $(CFLAGS) card.cpp

CrunoDraw2.o: CrunoDraw2.cpp CrunoDraw2.h $(BASECS)
	g++ $(CFLAGS) CrunoDraw2.cpp

CrunoGame.o: CrunoGame.cpp CrunoGame.h $(BASECS)
	g++ $(CFLAGS) CrunoGame.cpp

Cruno8.o: Cruno8.cpp Cruno8.h $(BASECS)
	g++ $(CFLAGS) Cruno8.cpp

proj4.o: proj4.cpp $(BASECS)
	g++ $(CFLAGS) proj4.cpp

mytest.o: mytest.cpp $(BASECS) $(CRUNCS)
	g++ $(CFLAGS) mytest.cpp

test: $(BASEOS) $(CRUNOO) $(TESTO)
	g++ $(LFLAGS) $(BASEOS) $(CRUNOO) $(TESTO) -o test

all: $(BASEOS) $(CRUNOO)