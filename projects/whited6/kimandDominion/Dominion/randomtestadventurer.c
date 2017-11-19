//
//  randomtestadventurer.c
//  Unit Tests Assignment3
//
//  Created by David White on 10/25/17.
//  Copyright © 2017 Oregon State University. All rights reserved.
//

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void checkAdventurerRef(struct gameState *state,int hp);
void printGameState(struct gameState *Pre, struct gameState *Post);
void fillWithCards(struct gameState *state);


int main(){
    int turn,deckCnt,discardCnt,handCnt,players,handPos;
    int seed=500;
    int tests=5000;     //number of tests to run
   
    int k[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,
        village,baron,great_hall};
    
    struct gameState G;
    
    printf("Testing adventurer.\n");
    printf("Random Tests.\n");
    
    srand(seed);
    
    for(int rep=0;rep<tests;rep++){
        //initialize gameState
        players=2+ rand()%(MAX_PLAYERS-1);      //range 2-4
        initializeGame(players, k, seed, &G);
        turn = rand()%players;                     //create a random players turn
        deckCnt= rand() %  MAX_DECK;   //cards in deck
        discardCnt =rand()%(500-deckCnt);  //cards in discard pile
        handCnt=rand() % (MAX_DECK - deckCnt - discardCnt );   //cards in hand
        G.whoseTurn = turn;
        G.deckCount[turn] =deckCnt;
        G.discardCount[turn]=discardCnt;
        G.handCount[G.whoseTurn]=handCnt;
        fillWithCards(&G);                                  //fills deck, hand and discard with random cards
        G.hand[turn][handCnt]=adventurer;
        G.handCount[turn]=handCnt+1;
        handPos= G.handCount[turn];
        checkAdventurerRef(&G,handPos);
    }
}

/*checkAdventureRef
 input: structure gameState
 output: none
 pre-condition: gamestate has been initialized with values
 post-condition: gamestate will be reflect playing 1 adventure card from the adventureRef function
 */
void checkAdventurerRef(struct gameState *post, int hp){
    int ret, discardTreas, handTreas,errors;
    int turn = post->whoseTurn;
    int choice1=0,choice2=0,choice3=0,bonus=0;
    struct gameState pre;
    discardTreas = handTreas= errors =0;
    memcpy(&pre,post, sizeof(struct gameState));            //save game state
    
   // ret=adventurerRef(post);
    ret = cardEffect(adventurer, choice1, choice2, choice3, post, hp, &bonus);
    if(!ret){
        //check if the correct # of cards are in the hand
        if(post->handCount[turn]-pre.handCount[turn]!=2){
            printf("***Error: Hand Count is incorrect: %d.  Pre: %d Post: %d\n",
                   post->handCount[turn]-pre.handCount[turn],pre.handCount[turn], post->handCount[turn]);
            errors++;
        }
        int deckDiff= pre.deckCount[turn] - post->deckCount[turn];
        int handDiff=post->handCount[turn] - pre.handCount[turn];
        int discardDiff = post->discardCount[turn] - pre.discardCount[turn];
        //The number of cards that were moved to the deck should equal the number placed in the hand
        //and discard pile
        if(deckDiff != handDiff+discardDiff){
            printf("***Error: Cards not placed in the correct deck during process\n");
            printGameState(&pre, post);
            errors++;
        }
        //Check if treasure cards have been discarded
        for(int i=pre.discardCount[turn]; i< post->discardCount[turn];i++){
          if(post->discard[turn][i]==copper || post->discard[turn][i]==silver ||
             post->discard[turn][i]==gold)
              discardTreas++;
        }
        if(discardTreas>0){
            printf("***Error: Treasures discarded that should have been counted: %d\n", discardTreas);
            errors++;
        }
        //Check if the correct number of treasure cards were added to the hand
        for(int i=pre.handCount[turn]; i< post->handCount[turn];i++){
            if(post->hand[turn][i]==copper || post->hand[turn][i]==silver ||
               post->hand[turn][i]==gold)
                handTreas++;
        }
        if(handTreas>2){
            printf("***Error: Too many treasures added to hand %d\n",handTreas);
            errors++;
        }
        if(handTreas <2){
            printf("***Error: Too few hands added to treasure: %d\n",handTreas);
            errors++;
        }
    }
    else{
        printf("Unexpected error in return\n");
        errors++;
    }
    //print number of errors in this iteration.
    if(errors)
        printf("%d errors in code\n\n",errors);
    else
        printf("Passed Tests\n\n");
}
/*fillWithCards
 input: gameState
 output: nothing
 pre-condition: gamestate has been initialized
 post-condition: gamestate's discard, hand, and deck will be filled for the player whose turn it is.
 */
void fillWithCards(struct gameState *State){
    int turn = State->whoseTurn;
    int deckCount=State->deckCount[turn];
    int handCount=State->handCount[turn];
    int discardCount=State->discardCount[turn];
    
    for(int i=0;i<deckCount;i++){
        State->deck[turn][i]=floor(Random()*(great_hall - curse));
    }
    for(int i=0;i<handCount;i++){
        State->hand[turn][i]=floor(Random()*(great_hall - curse));
    }
    for(int i=0;i<discardCount;i++){
        State->discard[turn][i]=floor(Random()*(great_hall - curse));
    }
}

/*printfGameState
 input: gamestate at 2 different periods
 output: nothing
 pre-condition:Pre is the earlier gamestate Post is a later gamestate
 post-condition: none
 */
void printGameState( struct gameState *Pre, struct gameState *Post){
    char card[27][15]={"Curse","Estate","Duchy","Province","Copper","Silver","Gold",
        "Adventurer", "Council_room","Feast","Gardens", "Mine","Remodel","Smithy","Village",
        "Baron", "Great Hall", "Minion","Steward","Tribute","Ambassador","Cutpurse", "Embargo",
        "Outpost", "Salvager","Sea Hag","Treasure Map"};
    int who=Post->whoseTurn;
    int preDeckCnt=Pre->deckCount[who];
    int postDeckCnt=Post->deckCount[who];
    int preHandCnt=Pre->handCount[who];
    int postHandCnt=Post->handCount[who];
    int preDiscardCnt=Pre->discardCount[who];
    int postDiscardCnt=Post->discardCount[who];
    
    printf("Deck-  \tPre: %d  Post: %d\n",preDeckCnt, postDeckCnt);
    printf("Cards Added:\n\t");
    //Cards Added to deck
    if(postDeckCnt -preDeckCnt >0){
        for(int i=preDeckCnt;i<postDeckCnt;i++)
            printf("%s ", card[ Post->deck[who][i] ]);
    }
    //Cards taken from Deck
    else{
        for(int i=postDeckCnt;i<preDeckCnt;i++)
            printf("%s ", card[ Pre->deck[who][i] ]);
    }
    printf("\nHand- \tPre: %d Post: %d\n",preHandCnt,postHandCnt);
    printf("Cards Added\n\t");
    //Cards Added to hand
    if(postHandCnt -preHandCnt >0){
        for(int i=preHandCnt;i<postHandCnt;i++)
            printf("%s ", card[ Post->hand[who][i] ]);
    }
    //Cards taken from Deck
    else{
        for(int i=postHandCnt;i<preHandCnt;i++)
            printf("%s ", card[ Pre->hand[who][i] ]);
    }
    printf("\nDiscard- \tPre: %d Post: %d\n", preDiscardCnt, postDiscardCnt);
    printf("Cards Added\n\t");
    //Cards Added to discard
    if(postDiscardCnt -preDiscardCnt >0){
        for(int i=preDiscardCnt;i<postDiscardCnt;i++)
            printf("%s ", card[ Post->discard[who][i] ]);
    }
    //Cards taken from Discard
    else{
        for(int i=postDiscardCnt;i<preDiscardCnt;i++)
            printf("%s ", card[ Pre->discard[who][i] ]);
    }
    printf("\n");
}
