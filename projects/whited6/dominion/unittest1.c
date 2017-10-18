//
//  unittest1.c
//  Testing of getCost function
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

    char card[27][15]={"curse","estate","duchy","province","copper","silver","gold","adventurer","council_room","feast",
        "gardens","mine","remodel","smithy","village","baron","great_hall","minion","steward","tribute","ambassador",
        "cutpurse","embargo","outpost","salvager","sea_hag","treasure_map"};
    int cost;

    printf("Testing getCost(int cardNumber):\n");
   
    for (int i=curse-1; i<=treasure_map+1; i++ )
    {
        cost= getCost(i);
        if(NOISY_TEST){
            if(i>=curse && i<=treasure_map)
                printf("%s= %d\n",card[i],cost);
            else
                printf("Outside of range: %d\n",i);
        }
        switch (i)
        {
         //Cost of 0
            case curse:
            case copper:
                if(NOISY_TEST)
                    printf("Expected Cost: 0 Actual Cost: %d\n", cost);
                assert(cost==0);
                break;
        //Cost of 2
            case estate:
            case embargo:
                if(NOISY_TEST)
                    printf("Expected Cost: 2 Actual Cost: %d\n", cost);
                assert(cost==2);
                break;
        //Cost of 3
            case silver:
            case village:
            case great_hall:
            case steward:
            case ambassador:
                if(NOISY_TEST)
                    printf("Expected Cost: 3 Actual Cost: %d\n", cost);
                assert(cost==3);
                break;
        //Cost of 4
            case feast:
            case gardens:
            case remodel:
            case smithy:
            case baron:
            case cutpurse:
            case salvager:
            case sea_hag:
            case treasure_map:
                if(NOISY_TEST)
                    printf("Expected Cost: 4 Actual Cost: %d\n", cost);
                assert(cost==4);
                break;
        //Cost of 5
            case duchy:
            case council_room:
            case mine:
            case minion:
            case tribute:
            case outpost:
                if(NOISY_TEST)
                    printf("Expected Cost: 5 Actual Cost: %d\n", cost);
                assert(cost==5);
                break;
        //Cost of 6
            case gold:
            case adventurer:
                if(NOISY_TEST)
                    printf("Expected Cost: 6 Actual Cost: %d\n", cost);
                assert(cost==6);
                break;
        //Cost of 8
            case province:
                if(NOISY_TEST)
                    printf("Expected Cost: 8 Actual Cost: %d\n", cost);
                assert(cost==8);
                break;
            default:
                if(NOISY_TEST)
                    printf("Value outside of range: %d\n", cost);
                assert(cost==-1);
                break;
        }
    }
    
 
    printf("All tests passed\n");
    return 0;
}