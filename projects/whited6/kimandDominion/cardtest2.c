//
//  cardtest2.c
//  Unit Tests Assignment3
// Test for Adventurer
//  Created by David White on 10/21/17.
//  Copyright © 2017 Oregon State University. All rights reserved.
//


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int seed=1000;
    int numPlayer=2;
    char card[27][15] = {"Curse","Estate","Duchy","Province","Copper","Silver","Gold",
    "Adventurer","Council_room","Feast","Gardens","Mine","Remodel","Smithy","Village",
        "Baron","Great Hall", "Minion","Steward","Tribute","Ambassador","Cutpurse",
        "Embargo",     "Outpost", "Salvager","Sea Hag","Treasure Map"};
    int k[10]={adventurer,council_room,feast,gardens, mine, remodel, smithy, village, baron,
        great_hall};
    int count=0;
    int handPos, choice1=0,choice2=0,choice3=0,bonus=0;
    int preTreasure=0,postTreasure=0;
    struct gameState  G, Backup;
    initializeGame(numPlayer, k, seed, &G);
    int turn = G.whoseTurn=0;
    for(int i=0;i<6;i++){                       //add 5 gold cards
        G.deck[turn][i]=4;
    }
    G.deckCount[turn]=5;
    G.hand[turn][G.handCount[turn]]=adventurer;
    G.handCount[turn]++;
    handPos=G.handCount[turn]-1;
    shuffle(turn,&G);
    Backup=G;                               //back up game state to compare to after tests.
    
    //adventurerRef(&G);
    cardEffect(adventurer,choice1,choice2,choice3,&G,handPos,&bonus);
    int deckDiff=Backup.deckCount[turn]-G.deckCount[turn];
    int handDiff=Backup.handCount[turn]-G.handCount[turn];
    int discardDiff=Backup.discardCount[turn]-G.discardCount[turn];
    printf("Testing Adventurer\n");
    printf("Deck Before: %d  After:%d\n",Backup.deckCount[turn],G.deckCount[turn]);
    printf("Hand Before: %d  After:%d\n",Backup.handCount[turn],G.handCount[turn]);
    printf("\tHand Before: ");
    for (int i=0;i<Backup.handCount[turn];i++){
        printf("%s ",card[Backup.hand[turn][i]]);
    }
    printf("\n\tHand After: ");
    for (int i=0;i<G.handCount[turn];i++){
        printf("%s ",card[G.hand[turn][i]]);
    }
    printf("\nDiscard Before: %d After:%d\n",Backup.discardCount[turn],G.discardCount[turn]);
   
    for(int i=0;i<=Backup.handCount[turn];i++){
        if(Backup.hand[turn][i]>=copper && Backup.hand[turn][i]<=gold)
            preTreasure++;
    }
    for(int i=0;i<=G.handCount[turn];i++){
        if(G.hand[turn][i]>=copper && G.hand[turn][i]<=gold)
            postTreasure++;
    }
    if(postTreasure-preTreasure >2){
        printf("***Error--- Too many treasures added to hand: %d Expected: 2\n",postTreasure-preTreasure);
        count++;
    }
    /*   if((abs(handDiff))>2){
        printf("***Error--- Too many treasure cards added to hand\n");
        count++;
    }
 */
    if((deckDiff +(handDiff+discardDiff)!=0)){
        printf("***Error--- cards not moved to proper location\n");
        printf("\tDeck Before: %d \t\tDeck After: %d\tExpected: %d\n ",
               Backup.deckCount[turn],G.deckCount[turn],Backup.deckCount[turn]-2);
        printf("\tHand Before: %d \t\tHand After: %d\tExpected: %d\n",
               Backup.handCount[turn],G.handCount[turn],Backup.handCount[turn]+2);
        printf("\tDiscard Before: %d \tDiscard After: %d\n",
               Backup.discardCount[turn],G.discardCount[turn]);
        count++;
    }
    
    if(count>0)
        printf("\n****Found %d errors****\n",count);
    else
        printf("\n\n****All tests passed****\n");
    return 0;
}

