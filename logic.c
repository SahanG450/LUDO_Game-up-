#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"

struct piece1 tempArray2[PIECE_FOR_PLAYER];

//globle declarations
int livePlayer = 0;
int red_movePiece;
static int tempBlock = -1;
static int roundCounter = 0;
static int mistryShellLocation = 0;
static bool roundCountOn = true;
static int rounds = 0;
struct Player players[PLAYERS];

// functions
void definePlayers(struct Player *players);
void resetTempArray2();
void updateEndFar(int,int,int,int,int);
int rollingDice(int diceCounter);
int coinToss();
int getRandomLocation();
int getRandomPowers();
int getRandomBawanaPowers();
int ableToGoHome(int);
int checkwhoStart(int (*staterArray)[]);
int whoStartGame(int);
int countIsboard();
void isWinPlace(int index);
void printCounter();
void isBlock(int index);
int directionWiseMove(int index, int diceValue, int notPrint);
int canMove(int, int);
int who_is_move(int, int);
int cutting(int, int, int, int);
int whoIsCut(int);
int cutFunction(int);
void blockDirection(int, int);
int numofPieceInBlock();
int movePiece(int, int);
int gameHandle_red(int);
int gameHandle(int);
int getNewPiece(int);
int cutFunctionForOthers(int);
int gameHandleForYellow(int);
int getNewpiece(int);
int gameHandlefor_yellow(int);
void resetMistryShellPowers();
void mistryPowerstatus();
int mistryShellOn(int);
void teleportToBawana(int);
void teleportToKotuwa(int); 
void teleportToPitaKotuwa(int);
void teleportToBase(int);
void teleportToX(int);
void teleportToApproche(int);
int choosePower(int,int,int);
int givePowerToMistry(int,int);
int allMistryshellcheck(int,int);
void mistryShellCutting(int,int);
int blueMistryshellcheck(int);
int checkCanNewPiece(int,int);
int whoIsMoveBlue(int);
int getNewForBlue(int);
int pieceMovingBlue(int);
int pieceLocation(int);
void commenPrint();
int check_win(int);
int controller(int);

// initialize Players
void definePlayers(struct Player *players)
{
    for (int index = 0; index < PLAYERS; index++)
    {
        players[index].playerId = index + 1;
        players[index].mistryPowerStatus = 0;
        strcpy(players[index].color, (index == 0) ? "RED" : (index == 1) ? "GREEN"
                                                        : (index == 2)   ? "YELLOW"
                                                                         : "BLUE");

        for (int index2 = 0; index2 < PIECE_FOR_PLAYER; index2++)
        {
            players[index].pieces[index2].isHome = 0;
            players[index].pieces[index2].position = 0;
            players[index].pieces[index2].isBoard = 0;
            players[index].pieces[index2].isXplace = 0;
            players[index].pieces[index2].isInblock = 1; // 1  mean piece not in block
            players[index].pieces[index2].direction = 0;
            players[index].pieces[index2].forToend = (BOARD_SIZE - 1);
            players[index].pieces[index2].cutCount = 0;
            players[index].pieces[index2].mistryShellPower = 1;
            players[index].pieces[index2].mistryBrief = 1;
            players[index].pieces[index2].mistryPowerStatus = 0;
            players[index].pieces[index2].endAtHome = 0;
        }
    }
    printf("\t\t>> \033[1m\033[4m\033[45mGAME PLAYERS ARE READY\033[0m\033[0m\033[0m <<\n");
}
// reset function- tempArray2
void resetTempArray2()// this fuction not yet use 
{
    for (int index = 0; index < PLAYERS; index++)
    {
        tempArray2[index].byCapIndex = 0;
        tempArray2[index].farToEnd = 0;
        tempArray2[index].group = 0;
        tempArray2[index].id = 0;
    }
}

// update pieces(this use at moving )
void updateEndFar(int index1, int index2, int diceValue,int x,int y)
{
    if (players[index1].pieces[index2].isBoard)
    {
        players[index1].pieces[index2].forToend -=(diceValue * x * y);
    }
}

// rolling dice function
int rollingDice(int diceCounter)
{
    int diceValue = (rand() % 6) + 1;

    if (diceCounter == 3)
    {
        if (diceValue == 6)
        {
            return 0;
        }
    }

    return diceValue;
}

// coin toss function
int coinToss()
{
    printf(" >> Coin tossing\n");
    int tossValue = (rand() % 2) + 1;
    if (tossValue == 1)
    {
        printf(">> Got HEAD \n>> This piece go clockwise direction\n");
        return 1;
    }
    else
    {
        printf(">> Got TAIL \n>> This piece go Counterclockwise direction\n");
        return -1;
    }
}

// get ramdom location for mistry shell
int getRandomLocation()
{
    return (rand() % 52) + 1;
}

// select powers place randomly
int getRandomPowers()
{
    return (rand() % 6) + 1;
}

// select Bawana powers
int getRandomBawanaPowers()
{
    return (rand() % 2) + 1;
}

// able to go home by rooling 6
int ableToGoHome(int diceValue)
{
    if (diceValue == 6)
    {
        for (int index = 0; index < PIECE_FOR_PLAYER; index++)
        {
            if ((players[livePlayer].pieces[index].isHome == 1) && (players[livePlayer].pieces[index].isBoard == 0))
            {
                players[livePlayer].pieces[index].endAtHome = 1;
                players[livePlayer].pieces[index].isHome = -1;
                printf("%s[%d] Piece Succesfully enter to HOME ! \n", players[livePlayer].color, index);
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

// check who start game fuctions
int checkwhoStart(int (*staterArray)[])
{
    int max = (*staterArray)[0];
    int max_index;
    for (int index = 1; index < PLAYERS; index++)
    {
        if (max < (*staterArray)[index])
        {
            max = (*staterArray)[index];
            max_index = index;
        }
    }
    livePlayer = (max_index - 1);
    printf("%s player has the highest roll and will begin the game\n", players[max_index].color);
    roundCountOn = false;
}

// combine with above function
int whoStartGame(int diceValue)
{
    int staterArray[4];
    staterArray[livePlayer] = diceValue;
    printf("%s rolled %d\n", players[livePlayer].color, diceValue);
    if (livePlayer == 3)
    {
        checkwhoStart(&staterArray);
    }
}

// check how many in the board
int countIsboard()
{
    int count = 0;
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        if (players[livePlayer].pieces[index].isBoard == 1)
        {
            count++;
        }
    }
    return count;
}

// chech is win in current place(begin of approch shell)
void isWinPlace(int index)
{
    if ((players[livePlayer].pieces[index].cutCount >= 1) && (players[livePlayer].pieces[index].forToend <= 0) && (players[livePlayer].pieces[index].position == ((livePlayer == 0) ? 51 : (livePlayer == 1) ? 12
                                                                                                                                                                                       : (livePlayer == 2)   ? 25
                                                                                                                                                                                                             : 38)))
    {
        players[livePlayer].pieces[index].isHome = 1;
        players[livePlayer].pieces[index].isBoard = 0;
        printf(">> \tWelcome to Approch piece %s(%d)\n", players[livePlayer].color, index);
    }
}

// print a how many piece in the base and borad like (1/4) for each player
void printCounter()
{
    int isBoradcount = countIsboard();
    printf("%s player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n ", players[livePlayer].color, (isBoradcount), (4 - isBoradcount));
}

//  same peices in the same slot then print as block
void isBlock(int index)
{
    if (tempBlock > 0)
    {
        tempBlock = -1;
    }
    for (int index2 = 0; index2 < PIECE_FOR_PLAYER; index2++)
    {
        if (index2 != index)
                {
            if ((players[livePlayer].pieces[index].position == players[livePlayer].pieces[index2].position))
            {
                players[livePlayer].pieces[index].isInblock = 0;
                players[livePlayer].pieces[index2].isInblock = 0;
                printf("%s piece %d is blocked from moving from L%d by %d piece.\n ", players[livePlayer].color, index, players[livePlayer].pieces[index].position, index2);
            }
        }
    }
    tempBlock++;
}

//
int directionWiseMove(int index, int diceValue, int Print)
{
    int previousLocation = players[livePlayer].pieces[index].position;
    int x = players[livePlayer].pieces[index].mistryShellPower;
    int y = players[livePlayer].pieces[index].mistryBrief;
    if (players[livePlayer].pieces[index].isBoard && (players[livePlayer].pieces[index].isHome == 0))
    {
        if (players[livePlayer].pieces[index].direction == 1)
        {
            if (Print)
            {
                // should be call fuction check a block infronof me

                players[livePlayer].pieces[index].position = ((players[livePlayer].pieces[index].position + (diceValue * x * y)) == 52) ? 52 : (((players[livePlayer].pieces[index].position + (diceValue * x * y)) % BOARD_SIZE));
                updateEndFar(livePlayer,index,diceValue,x,y);
                printf(" %s[%d] moves from location L%d to L%d by clockwise direction.\n", players[livePlayer].color, index, previousLocation, players[livePlayer].pieces[index].position);

                isWinPlace(index);
                return 1;
            }
            else
            {
                int tempPosition = ((players[livePlayer].pieces[index].position + (diceValue * x * y)) == 52) ? 52 : (((players[livePlayer].pieces[index].position + (diceValue * x * y)) % BOARD_SIZE));
                return tempPosition;
            }
        }
        else
        {

            if ((players[livePlayer].pieces[index].position <= 6) && (players[livePlayer].pieces[index].position >= 1) && (players[livePlayer].pieces[index].position == (diceValue * x * y)))
            {
                if (Print)
                {
                    players[livePlayer].pieces[index].position = 52;
                    updateEndFar(livePlayer,index,diceValue,x,y);
                    printf(" %s[%d] moves from location L%d to L%d by clockwise direction.\n", players[livePlayer].color, index, previousLocation, players[livePlayer].pieces[index].position);
                    return 1;
                }
                else
                {
                    int tempPosition = 52;
                    return tempPosition;
                }
            }
            else
            {
                if (Print)
                {
                    // should be call fuction check a block infronof me
                    players[livePlayer].pieces[index].position = (((BOARD_SIZE + (players[livePlayer].pieces[index].position - (diceValue * x * y))) % BOARD_SIZE));
                    updateEndFar(livePlayer,index,diceValue,x,y);
                    printf(" %s[%d] moves from location L%d to L%d by clockwise direction.\n", players[livePlayer].color, index, previousLocation, players[livePlayer].pieces[index].position);
                    isWinPlace(index);
                    return 1;
                }
                else
                {
                    int tempPosition = ((BOARD_SIZE + (players[livePlayer].pieces[index].position - (diceValue * x * y))) % BOARD_SIZE);
                    return tempPosition;
                }
            }
        } /// X wala blocks hadenn puluwand?yes it can be happen
        if (Print)
        {
            isBlock(index);
            if (livePlayer != 3)
            {
                allMistryshellcheck(index, diceValue);
            }
            return 0;
        }
    }
}

// chech whether who can move or get from the base
int canMove(int dicevalue, int index)
{
    if (players[livePlayer].pieces[index].position == 0 && dicevalue != 6)
    {
        return 0;
    }

    if (players[livePlayer].pieces[index].isHome)
    { 
        return 0;
    }

    return 1;
}

// which piece can move
int who_is_move(int livePlayer, int diceValue)
{
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        int tempIndex = canMove(diceValue, index);
        if (tempIndex)
        {
            return index; // this is index which can move as single piece
        }
    }
    return -1; // this return for if get new one or can not get new one
}

// when pieces land same place opperend piece will be canceled
int cutting(int index, int dicevalue, int index3, int index4)
{
    if (players[index].pieces[index3].isBoard)
    {
        players[index].pieces[index3].position = 0;
        players[index].pieces[index3].isBoard = 0;
        players[index].pieces[index3].direction = 0;
        players[index].pieces[index3].forToend = BOARD_SIZE;
        directionWiseMove(index4, dicevalue, 1);
        players[livePlayer].pieces[index4].cutCount++;
        printf(" %s piece [%d] lands on square L%d,captures %s piece [%d],and returns it to the base.\n", players[livePlayer].color, index4, players[livePlayer].pieces[index4].position, players[index].color, index3);
        printCounter();
        return 0;
    }
    return 0;
}

/// check which piece nearest to each home
int whoIsCut(int dicevalue)
{
    int minPositionIndex = 0;
    int min_position = tempArray2[0].farToEnd;
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        if ((tempArray2[index].farToEnd > 0) && (tempArray2[index].farToEnd < min_position))
        {
            min_position = tempArray2[index].farToEnd;
            minPositionIndex = index;
        }
    }
    int index2, index3, index4;
    index3 = tempArray2[minPositionIndex].id;
    index4 = tempArray2[minPositionIndex].byCapIndex;
    index2 = tempArray2[minPositionIndex].group;
    cutting(index2, dicevalue, index3, index4);
}

// cut function for red piece
int cutFunction(int dicevalue)
{
    int cutOn = 0;
    int position = 0;
    int indexTemparray = 0;
    resetTempArray2();
    for (int index1 = 1; index1 < PLAYERS; index1++)
    {
        for (int index2 = 0; index2 < PIECE_FOR_PLAYER; index2++)
        {
            for (int index3 = 0; index3 < PIECE_FOR_PLAYER; index3++)
            {
                if (players[livePlayer].pieces[index3].isBoard)
                {
                    position = directionWiseMove(index3, dicevalue, 0);
                    if (position == (players[index1].pieces[index2].position * players[index1].pieces[index2].isBoard))
                    {
                        tempArray2[indexTemparray].group = index1;
                        tempArray2[indexTemparray].id = index2;
                        tempArray2[indexTemparray].farToEnd = players[index1].pieces[index2].forToend;
                        tempArray2[indexTemparray].byCapIndex = index3;
                        indexTemparray++;
                        cutOn = 1;
                    }
                }
            }
        }
    }
    if (cutOn == 1)
    {
        whoIsCut(dicevalue);
        return 1;
    }
    return 0;
}

//get new piece for red/ or deside and store who can move
int movePiece(int index, int diceValue)
{
    int isBoradcount = countIsboard();

    if (!players[livePlayer].pieces[index].isBoard && ((livePlayer == 0) || (livePlayer == 3)))
    {
        if (diceValue == 6)

        {
            players[livePlayer].pieces[index].position = 1;
            players[livePlayer].pieces[index].isBoard = 1;
            players[livePlayer].pieces[index].isXplace = 1;
            printf("%s player moves piece %s[%d] to the starting point.\n", players[livePlayer].color, players[livePlayer].color, index);
            printCounter();
            players[livePlayer].pieces[index].direction = coinToss();
            if (players[livePlayer].pieces[index].direction == 1)
            {
                players[livePlayer].pieces[index].forToend = 50;
            }
            else if (players[livePlayer].pieces[index].direction == -1)
            {
                players[livePlayer].pieces[index].forToend = 54;
            }
            return 5;
        }
    }
    else
    {
        return index;
    }
}

int gameHandle_red(int diceValue)
{
    int movingPiece = who_is_move(livePlayer, diceValue);
    if (movingPiece == -1)
    {
        printf("%s player cannot move any piece yet!\n", players[livePlayer].color);
        return 0;
    }
    else
    {
        red_movePiece = movePiece(movingPiece, diceValue); // moving piece is index which can move single
        if (red_movePiece == 5)
        {
            red_movePiece = 0;
            return 0;
        }
        else if (red_movePiece == 0 || red_movePiece == 1 || red_movePiece == 2 || red_movePiece == 3)
        {
            return 1;
        }
    }
}

// yellow/Green/Blue
int cutFunctionForOthers(int diceValue)
{
    int templocation = 0;
    for (int index2; index2 < PLAYERS; index2++)
    { // other group
        if (index2 != livePlayer)
        {

            for (int index3 = 0; index3 < PIECE_FOR_PLAYER; index3++) // others piece
            {

                for (int index4 = 0; index4 < PIECE_FOR_PLAYER; index4++)
                {

                    if (players[livePlayer].pieces[index4].isBoard)
                    {

                        templocation = directionWiseMove(index4, diceValue, 0);
                        if (templocation == players[index2].pieces[index3].position)
                        {

                            cutting(index2, diceValue, index3, index4);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// get new piece from base fpr green/yellow
int getNewpiece(int dicevalue)
{
    int isBoradcount = countIsboard();
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        if ((!players[livePlayer].pieces[index].isBoard) && ((livePlayer == 1) || (livePlayer == 2)) && (players[livePlayer].pieces[index].position == 0) && (dicevalue == 6))
        {
            players[livePlayer].pieces[index].position = ((livePlayer) == 1 ? 14 : (livePlayer) == 2 ? 27
                                                                                                     : 0);
            players[livePlayer].pieces[index].isBoard = 1;
            players[livePlayer].pieces[index].isXplace = 1;
            players[livePlayer].pieces[index].forToend = TOTAL_FAR_TO_END - 1;
            printf("%s player moves piece %s[%d] to the starting point.\n", players[livePlayer].color, players[livePlayer].color, index);
            printCounter();
            players[livePlayer].pieces[index].direction = coinToss();
            // printf(">>\t direction this piece : %d\n",players[livePlayer].pieces[index].direction);
            if (players[livePlayer].pieces[index].direction == 1)
            {
                players[livePlayer].pieces[index].forToend = 50;
            }
            else if (players[livePlayer].pieces[index].direction == -1)
            {
                players[livePlayer].pieces[index].forToend = 54;
            }
            return 1;
        }
    }
    return 0;
}

int gameHandlefor_yellow(int diceValue)
{
    int movingPiece = who_is_move(livePlayer, diceValue);
    if (movingPiece == -1)
    {
        printf(" >> %s player cannot move any piece yet!\n", players[livePlayer].color);
        return 1; // change 0 to 1
    }
    else
    {
        red_movePiece = movingPiece;
        return 0;
    }
}

// create mistry cell story.

//  reset mistry shell power
void resetMistryShellPowers()
{
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        if (players[livePlayer].pieces[index].mistryPowerStatus)
        {
            players[livePlayer].pieces[index].mistryBrief = 1;
            players[livePlayer].pieces[index].mistryShellPower = 1;
        }
    }
}

// check whether istry shell poers on or not
void mistryPowerstatus()
{
    if (players[livePlayer].mistryPowerStatus)
    {
        if ((roundCounter % 16) == 0)
        {
            resetMistryShellPowers();
        }
    }
}

// check all pieces locations
int pieceLocation(int mistryShellLocation)
{
    for (int i = 0; i < PLAYERS; i++)
    {
        for (int j = 0; j < PIECE_FOR_PLAYER; j++)
        {
            if (players[i].pieces[j].position == mistryShellLocation)
            {
                return 0;
            }
        }
    }
    return 1;
}

// active mistry shell
int mistryShellOn(int roundCounter)
{
    if ((roundCounter % 16) == 0)
    {
        // mistry shell open
        mistryShellLocation = getRandomLocation();
        if (pieceLocation)
        {
            printf("mystery cell has spawned in location L%d and will be at this location for the next four rounds\n", mistryShellLocation);
            return 1;
        }
        else
        {
            mistryShellOn(roundCounter);
            // if want to add 2 nd rount add hear
            return 0;
        }
    }
}

// bowana powers
void teleportToBawana(int index)
{

    int whatCanHappen = getRandomBawanaPowers();
    if (whatCanHappen == 1)
    {
        printf("%s piece [%d] feels energized,and movement speed doubles\n", players[livePlayer].color, index);
        players[livePlayer].pieces[index].mistryShellPower = 2;
        players[livePlayer].pieces[index].position = 34;
    }
    else if (whatCanHappen == 2)
    {
        players[livePlayer].pieces[index].mistryShellPower = 0.5;
        printf("%s piece [%d] feels sick,and movement speed halves\n", players[livePlayer].color, index);
    }
}

// Kotuwa powers
void teleportToKotuwa(int index)
{
    players[livePlayer].pieces[index].mistryBrief = 0;
    players[livePlayer].pieces[index].position = 52;
    printf("%s piece [%d] attends briefing and cannot move for four rounds.\n", players[livePlayer].color, index);
}

// Pita-Kotuwa powers
void teleportToPitaKotuwa(int index)
{
    if (players[livePlayer].pieces[index].direction == 1)
    {
        players[livePlayer].pieces[index].direction = -1;
        players[livePlayer].pieces[index].position = 19;
        printf("%s piece [%d],which was moving clockwise, has changed to moving counterclockwise. \n", players[livePlayer].color, index);
    }
    else if (players[livePlayer].pieces[index].direction = -1)
    {
        players[livePlayer].pieces[index].direction == -1;
        players[livePlayer].pieces[index].position = 19;
        printf("%s piece [%d], is moving in a counterclockwise direction. Teleporting to Kotuwa from Pita-Kotuwa. \n", players[livePlayer].color, index);
    }
}

// to base
void teleportToBase(int index)
{
    players[livePlayer].pieces[index].position = 0;
    players[livePlayer].pieces[index].cutCount = 0;
    players[livePlayer].pieces[index].direction = 0;
    players[livePlayer].pieces[index].isBoard = 0;
    players[livePlayer].pieces[index].mistryShellPower = 1; // unnnessery
    printf("%s piece [%d],moves to to base. \n", players[livePlayer].color, index);
}

// to x
void teleportToX(int index)
{
    players[livePlayer].pieces[index].isXplace = 1;
    players[livePlayer].pieces[index].position = (livePlayer) == 0 ? 1 : (livePlayer) == 1 ? 14
                                                                     : (livePlayer) == 2   ? 27
                                                                                           : 40;
    printf("%s piece [%d],moves to to X. \n", players[livePlayer].color, index);
}

// to approche
void teleportToApproche(int index)
{
    players[livePlayer].pieces[index].position = (livePlayer == 0) ? 51 : (livePlayer == 1) ? 12
                                                                      : (livePlayer == 2)   ? 25
                                                                                            : 38;
    printf("%s piece [%d],moves to to approche. \n", players[livePlayer].color, index);
}

// choose power of piece
int choosePower(int power, int index, int diceValue)
{
    if (power == 1)
    {
        printf("%s player [%d] teleported to Bhawana\n", players[livePlayer].color, index); // 34
        teleportToBawana(index);
        mistryShellCutting(34, index);
    }
    else if (power == 2)
    {
        printf("%s player [%d] teleported to Kotuwa\n", players[livePlayer].color, index); // 52
        teleportToKotuwa(index);
        mistryShellCutting(52, index);
    }
    else if (power == 3)
    {
        printf("%s player [%d] teleported to Pita - Kotuwa\n", players[livePlayer].color, index);
        ; // 19
        teleportToPitaKotuwa(index);
        mistryShellCutting(19, index);
    }
    else if (power == 4)
    {
        printf("%s player [%d] teleported to Base\n", players[livePlayer].color, index); // 0
        teleportToBase(index);
    }
    else if (power == 5)
    {
        printf("%s player [%d] teleported to X\n", players[livePlayer].color, index); //
        teleportToX(index);
    }
    else if (power == 6)
    {
        printf("%s player [%d] teleported to Approach\n", players[livePlayer].color, index); //
        teleportToApproche(index);
    }
}

int givePowerToMistry(int index, int diceValue)
{
    int power = getRandomPowers();
    choosePower(power, index, diceValue);
}
// red/green/yellow players in mistry
int allMistryshellcheck(int index, int diceValue)
{
    if (players[livePlayer].pieces[index].isBoard && (players[livePlayer].pieces[index].position == mistryShellLocation))
    {
        printf("%s player lands on a mystery cell and is teleported to L%d.\n", players[livePlayer].color, mistryShellLocation);
        givePowerToMistry(index, diceValue);
    }
}

// when put mistry shell cutting
void mistryShellCutting(int teleportLocation, int index)
{
    for (int i = 0; i < PLAYERS; i++)
    {
        if (i != livePlayer)
        {
            for (int j = 0; j < PIECE_FOR_PLAYER; j++)
            {
                if (teleportLocation == players[i].pieces[j].position)
                {
                    players[i].pieces[j].direction = 0;
                    players[i].pieces[j].cutCount = 0;
                    players[i].pieces[j].isBoard = 0;
                    players[i].pieces[j].mistryBrief = 1;       // extra
                    players[i].pieces[j].mistryShellPower = 1;  // extra
                    players[i].pieces[j].mistryPowerStatus = 0; // extra
                    printf(" %s piece [%d] lands on square L%d,captures %s piece [%d],and returns it to the base.\n", players[livePlayer].color, index, players[livePlayer].pieces[index].position, players[i].color, j);
                    printCounter();
                }
            }
        }
    }
}

// blue player

int blueMistryshellcheck(int diceValue)
{
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        if (players[livePlayer].pieces[index].isBoard && (players[livePlayer].pieces[index].direction == -1))
        {
            int tempLocation = directionWiseMove(index, diceValue, 0);
            if (tempLocation == mistryShellLocation)
            {
                printf("%s player lands on a mystery cell and is teleported to L%d.\n", players[livePlayer].color, mistryShellLocation);
                directionWiseMove(index, diceValue, 1);
                givePowerToMistry(index, diceValue); // point
                players[livePlayer].mistryPowerStatus = 1;
                players[livePlayer].pieces[index].mistryPowerStatus = 1;
                return 1;
            }
        }
    }
    return 0;
}

int checkCanNewPiece(int movePiece, int diceValue)
{
    int isBoradcount = countIsboard();
    if (players[livePlayer].pieces[movePiece].position == 0 && (players[livePlayer].pieces[movePiece].isBoard == 0) && (diceValue == 6))
    {
        players[livePlayer].pieces[movePiece].position = 40;
        players[livePlayer].pieces[movePiece].isBoard = 1;
        players[livePlayer].pieces[movePiece].isXplace = 1;
        printf("%s player moves piece %s[%d] to the starting point.\n", players[livePlayer].color, players[livePlayer].color, movePiece);
        printf("%s player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n ", players[livePlayer].color, (isBoradcount), (4 - isBoradcount));
        players[livePlayer].pieces[movePiece].direction = coinToss();
        if (players[livePlayer].pieces[movePiece].direction == 1)
        {
            players[livePlayer].pieces[movePiece].forToend = 50;
        }
        else if (players[livePlayer].pieces[movePiece].direction == -1)
        {
            players[livePlayer].pieces[movePiece].forToend = 54;
        }
        return 1;
    }
    printf(">> %s player cannot move any piece yet!\n", players[livePlayer].color);
    return 0;
}
int whoIsMoveBlue(int diceValue)
{
    for (int i = 0; i < PIECE_FOR_PLAYER; i++)
    {
        if ((players[livePlayer].pieces[i].isBoard == 0) && (players[livePlayer].pieces[i].isHome == 0))
        {
            return i;
        }
    }
    // printf(">> %s player cannot move any piece yet!\n",players[livePlayer].color);
    return -1;
}
int getNewForBlue(int diceValue)
{
    if (diceValue == 6)
    {
        int moveIndex = whoIsMoveBlue(diceValue);
        if (moveIndex != (-1))
        {
            printf("%d piece position %d isbord %d dice %d\n ", moveIndex, players[livePlayer].pieces[moveIndex].position, players[livePlayer].pieces[moveIndex].isBoard, diceValue);
            if (checkCanNewPiece(moveIndex, diceValue))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
}
int pieceMovingBlue(int diceValue)
{
    static int pieceNo = 0;
    while (1)
    {
        if ((players[livePlayer].pieces[pieceNo].isBoard == 0) && (players[livePlayer].pieces[pieceNo].isHome == 1))
        {
            pieceNo = (pieceNo + 1) % 4;
        }
        else
        {
            break;
        }
    }
    directionWiseMove(pieceNo, diceValue, 1);
    pieceNo = (pieceNo + 1) % 4;
}
// comment status print
void commenPrint()
{
    int countisboard = countIsboard();
    printCounter();
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        printf("Location of pieces [%s]\n", players[livePlayer].color);
        printf("============================\n");
        if (players[livePlayer].pieces[index].isHome == -1)
        {
            printf("Piece [%d] --> Home\n", index);
        }
        else if (players[livePlayer].pieces[index].isBoard == 0)
        {
            printf("Piece [%d] --> Base\n", index);
        }
        else
        {
            printf("Piece [%d] --> L%d\n", index, players[livePlayer].pieces[index].position);
        }
        printf("============================\n");
    }
}
// check win
int check_win(int livePlayer)
{
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        if (players[livePlayer].pieces[index].endAtHome == 0)
        {
            return 0;
        }
    }
    return 1;
}
// winner details
void printWinnerDetails(int winnerIndex)
{
    printf("\n\t\t\t \033[35m\033[1m %s Player Wins!!!\033[0m\033[0m\n", players[winnerIndex].color);
    printf("Details:\n");
    printf("Player ID: %d\n", players[winnerIndex].playerId);
    printf("Color: %s\n", players[winnerIndex].color);
    printf("Pieces in Home:\n");
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        if (players[winnerIndex].pieces[index].isHome)
        {
            printf("  Piece [%d] is in Home\n", index);
        }
    }
    printf("Pieces on Board:\n");
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        if (players[winnerIndex].pieces[index].isBoard)
        {
            printf("  Piece [%d] is on L%d\n", index, players[winnerIndex].pieces[index].position);
        }
    }
    printf("Pieces in Base:\n");
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        if (!players[winnerIndex].pieces[index].isBoard && !players[winnerIndex].pieces[index].isHome)
        {
            printf("  Piece [%d] is in Base\n", index);
        }
    }
}
// control
int controller(int diceCounter)
{
    int diceValue, temdicevale;
start:
    diceValue = rollingDice(diceCounter);
    if (roundCountOn && (rounds < 5))
    {
        whoStartGame(diceValue);
        return 0;
    }
    else
    {
        temdicevale = diceValue;
        switch (livePlayer)
        {
        case 0: // red player
            printf(">> \t\t\033[31mRed Player Chance %d\033[0m \n", (diceCounter + 1));
            printf("Red player rolled %d\n", diceValue);
            mistryPowerstatus();
            if (ableToGoHome(diceValue))
            {
            }
            else
            {
                int myTempFunction = cutFunction(diceValue);
                if ((myTempFunction == 1) || gameHandle_red(diceValue))
                {
                    if ((myTempFunction != 1))
                    {
                        int index = red_movePiece;
                        red_movePiece = 0;
                        directionWiseMove(index, diceValue, 1);
                    }
                }
                printf("\n");
                if (temdicevale == 6)
                {
                    goto start;
                    diceCounter++;
                }
                diceCounter = 0;
                break;

            case 1:
                printf(">> \t\t\033[32mGreen Player Chance %d\033[0m \n", (diceCounter));
                printf("Green player rolled %d\n", diceValue);
                mistryPowerstatus();
                if (ableToGoHome(diceValue))
                {
                }
                else
                {
                    if (getNewpiece(diceValue) || (gameHandlefor_yellow(diceValue)) || cutFunctionForOthers(diceValue) || directionWiseMove(red_movePiece, diceValue, 1))
                    {
                    }
                    red_movePiece = 0;
                }
                printf("\n");
                if (temdicevale == 6)
                {
                    diceCounter++;
                    goto start;
                }
                diceCounter = 0;
                break;

            case 2:
                printf(">> \t\t\033[0;33mYellow Player Chance %d\033[0m \n", (diceCounter));
                printf("Yellow player rolled %d\n", diceValue);
                mistryPowerstatus();
                if (ableToGoHome(diceValue))
                {
                }
                else
                {
                    if (getNewpiece(diceValue) || gameHandlefor_yellow(diceValue) || cutFunctionForOthers(diceValue) || directionWiseMove(red_movePiece, diceValue, 1))
                    {
                    }
                    red_movePiece = 0;
                }
                printf("\n");
                if (temdicevale == 6)
                {
                    diceCounter++;
                    goto start;
                }
                diceCounter = 0;
                break;
            case 3:
                printf(">> \t\t\033[0;34mBlue Player Chance %d\033[0m \n", (diceCounter));
                printf("Blue player rolled %d\n", diceValue);
                mistryPowerstatus();
                if (ableToGoHome(diceValue))
                {
                }
                else
                {
                    if (blueMistryshellcheck(diceValue) || getNewForBlue(diceValue) || cutFunctionForOthers(diceValue) || pieceMovingBlue(diceValue))
                    {
                    }
                }
                printf("\n");
                if (temdicevale == 6)
                {
                    goto start;
                    diceCounter++;
                }
                diceCounter = 0;

                break;
            }
        }
    }
}
