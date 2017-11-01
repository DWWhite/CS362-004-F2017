//
//  randomtestcard2.c
//  Unit Tests Assignment3
//
//  This program tests the stewardRef function randomly
//
//  Created by David White on 10/31/17.
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

void checkStewardRef(struct gameState *state, int handPos);
void printGameState(struct gameState *Pre, struct gameState *Post);
void fillWithCards(struct gameState *state, int cardsPlayed[]);
int addRandomCard(struct gameState *state, int card);

int main(){
    int turn,deckCnt,discardCnt,handCnt,players,handPos;
    int seed=1000;
    int tests=2000;     //number of tests to run
   
    int k[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,
        village,baron,steward};
    
    struct gameState G;
    
    printf("Testing Steward.\n");
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
        fillWithCards(&G,k);                                  //fills deck, hand and discard with random cards
        handPos =addRandomCard(&G,steward);
        checkStewardRef(&G,handPos);
    }
}

/*checkStewardRef
 input: structure gameState
 output: none
 pre-condition: gamestate has been initialized with values
 post-condition: 
 */
void checkStewardRef(struct gameState *post, int handPos){
    int ret,  errors;
    int turn = post->whoseTurn;
    struct gameState pre;
    errors =0;
    memcpy(&pre,post, sizeof(struct gameState));            //save game state
    
    //ret=stewardRef(post, handPos);
    if(!ret){

    }
    //print number of errors in this iteration.
    if(errors)
        printf("%d errors in code\n",errors);
    else
        printf("Passed Tests\n");
}

/*fillWithCards
 input: gameState
 output: nothing
 pre-condition: gamestate has been initialized
 post-condition: gamestate's discard, hand, and deck will be filled for the player whose turn it is.
 */
void fillWithCards(struct gameState *State, int cards[]){
    int turn = State->whoseTurn;
    int deckCount=State->deckCount[turn];
    int handCount=State->handCount[turn];
    int discardCount=State->discardCount[turn];
    for(int i=0;i<deckCount;i++){
        State->deck[turn][i]=cards[(int)floor(Random()*10)];
    }
    for(int i=0;i<handCount;i++){
        State->hand[turn][i]=cards[(int)floor(Random()*10)];
    }
    for(int i=0;i<discardCount;i++){
        State->discard[turn][i]=cards[(int)floor(Random()*10)];
    }
}

/*addRandomCard
 input: gamestate before the tests begin,
 output: returns the position of the randomly placed smithy
 pre-condition: The gamestate has been intiallized with cards in the players hand
 post-condition: The hand of the current player will have a smithy placed randomly in the deck
        the function will return the location within the hand
 */
int addRandomCard(struct gameState *state, int card){
    int handPos;
    int turn = state->whoseTurn;
    int handCnt = state->handCount[turn];
    handPos = floor(Random()*handCnt);
    //There must be a card in the hand in order to play the card, therefore a card is added
    //if a hand is empty, the desired card is placed in the hand.
    if(handCnt==0){
        state->hand[turn][0]=card;
        state->handCount[turn]=1;
        handPos=0;
    }
    else {
        state->hand[turn][handPos]=card;
    }
//    printf("%d\n",handPos);
    return handPos;
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
