#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "logic.c"

// main
int main()
{
    srand(time(NULL));
    definePlayers(players);
    resetTempArray2();
    int i = 0;
    while (1)
    {
        int diceCounter = 1;
        roundCounter++;
        rounds++;
        mistryShellOn(roundCounter);
        controller(diceCounter);
        if (!roundCountOn)
        {
            if (check_win(livePlayer))
            {
                printWinnerDetails(livePlayer);
                break;
            }
            commenPrint();
            printf("======================================================================\n\n");
        }
        livePlayer = (livePlayer + 1) % PLAYERS;
        i++;
    }
    return 0;
}