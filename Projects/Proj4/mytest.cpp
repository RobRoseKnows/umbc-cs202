/*
 * File:    mytest.cpp
 * Author:  Robert
 * Section: 3
 * Created: Apr 14, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * This is my tester for the Cruno Project.
 */


#include <iostream>
using namespace std ;

#include "card.h"
#include "game.h"
#include "player.h"
#include "CrunoGame.h"
#include "CrunoPlayer.h"

int main() {

   CrunoGame G ;

   G.initialize(4) ;  // say we'll have four players

   // Make the 4 players and add them
   // We could add any object derived from Player.
   // So, we can have a mix of smart, dumb or cheating
   // players in the same game.
   //
   int n = G.getNumCards() ;
   CrunoPlayer *pptr1 = new CrunoPlayer(&G,n) ;
   CrunoPlayer *pptr2 = new CrunoPlayer(&G,n) ;
   CrunoPlayer *pptr3 = new CrunoPlayer(&G,n) ;
   CrunoPlayer *pptr4 = new CrunoPlayer(&G,n) ;

   G.addPlayer(pptr1) ;
   G.addPlayer(pptr2) ;
   G.addPlayer(pptr3) ;
   G.addPlayer(pptr4) ;


   // Play game with different random seeds.
   // The random seeds control the initial shuffle.

   G.startGame(3810743) ;
//   G.startGame(8132987) ;
//   G.startGame(7831035) ;
//   G.startGame(2310831) ;

   return 0 ;
}



