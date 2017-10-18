//
//  unittest2.c
//  Testing of gainCard function
//
//  Created by David Whiteon 10/14/17.
//
//

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int seed=1000;
    int numPlayer = 2;
    int numCards=1;
    int flag=3;
    int k[10]={adventurer,council_room,feast,gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G,  Backup;
    int r, ret_val;
    char card[27][15]={"Curse","Estate","Duchy","Province","Copper","Silver","Gold","Adventurer","Council_room","Feast","Gardens",
        "Mine","Remodel","Smithy","Village","Baron","Great Hall", "Minion","Steward","Tribute","Ambassador","Cutpurse"
        , "Embargo","Outpost", "Salvager","Sea Hag","Treasure Map"};
    printf("Testing gainCard\n");
    

    for(int i=1;i<=flag;i++){                          //Which pile card goes into
        r = initializeGame(numPlayer, k, seed, &G);
        Backup = G;                                             //save state of game
        for(int j=0; j<=numCards; j++){          //Card supply
            
            G.supplyCount[13] = j;                     //assign number of cards to smithy, either 0 or 1 card for testing
            ret_val=gainCard(smithy, &G, i, 0 );
            
                if(ret_val==-1 && j==0){
                    printf("Testing Depleted cards- Supply of Smithy's: %d  Flag: %d\n", G.supplyCount[13], i);
                    printf("Expected a return value of -1, Actual return value: %d\n", ret_val);
                }
                if(i==1 && j>0){
                    printf("Added to deck:\n");
                    if(NOISY_TEST){
                        printf("Expected Smithy card to be added, Last Card added to deck:%s\n", card[G.deck[0][G.deckCount[0]-1]]);
                        printf("Expecting %d cards in deck, Actual cards in deck: %d \n",Backup.deckCount[0]+1, G.deckCount[0]);
                        printf("Expecting supplyCount to be empty for Smithy, Smithy supplyCount: %d\n",G.supplyCount[smithy]);
                    }
                    assert(G.deck[0][G.deckCount[0]-1]==smithy);
                    assert(G.deckCount[0]==Backup.deckCount[0]+1);
                    assert(G.supplyCount[smithy]==0);
                }
                else if(i==2 && j>0){
                    printf("Added to hand:\n");
                    if(NOISY_TEST){
                        printf("Expecting Smithy card to be added,  Last card added to hand: %s\n",card[G.hand[0][G.handCount[0]-1]]);
                        printf("Expecting %d cards in hand, Actual cards in hand %d\n",Backup.handCount[0]+1,G.handCount[0]);
                        printf("Expecting supplyCount to be empty for Smithy, Smithy supplyCount: %d\n",G.supplyCount[smithy]);
                    }
                    assert(G.hand[0][G.handCount[0]-1]==smithy);
                    assert(G.handCount[0]==Backup.handCount[0]+1);
                    assert(G.supplyCount[smithy]==0);                }
                else if(i==3 && j>0){
                    printf("Added to discard:\n");
                    if(NOISY_TEST){
                        printf("Expecting Smithy card to be added,  Last card added to hand: %s\n",card[G.discard[0][G.discardCount[0]-1]]);
                        printf("Expecting %d cards in hand, Actual cards in hand %d\n",Backup.discardCount[0]+1,G.discardCount[0]);
                        printf("Expecting supplyCount to be empty for Smithy, Smithy supplyCount: %d\n",G.supplyCount[smithy]);
                    }
                    assert(G.discard[0][G.discardCount[0]-1]==smithy);
                    assert(G.discardCount[0]==Backup.discardCount[0]+1);
                    assert(G.supplyCount[smithy]==0);
                }
            
        }
    }
    printf("All tests passed\n");
    return 0;
}