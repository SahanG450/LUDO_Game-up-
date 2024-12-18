// types.h
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

#define BOARD_SIZE 52
#define PIECE_FOR_PLAYER 4
#define PLAYERS 4
#define NUM_OF_BLOCKS 2
#define TOTAL_FAR_TO_END 52

struct Piece
{
    int position;
    int isHome;// in the begin os approch shell
    int isBoard;// peice in the standed path
    int endAtHome;// in the home
    int isXplace;
    int isInblock;
    int direction; /// clockwise - heads[1](1) counterclockwise - tail[2](-1)
    int forToend;// far to end
    int cutCount;// count of cutted piece by each piece
    float mistryShellPower;// 1 mean not get super power or low powers yet
    int mistryBrief;// 0 means not brief by  mistry shell 
    int mistryPowerStatus;// if it is 0 mistry shell not allow
};

struct Blocks // this struct will be use for blocks(not yet)
{
    int block_1Position;
    int block_1Active;
    int block_1count;
    int block_1direction;
    int block_2Position;
    int block_2Active;
    int block_2count;
    int block_2direction;
};

struct Player
{
    struct Piece pieces[PIECE_FOR_PLAYER];
    struct Blocks blocks;
    char color[8];
    int playerId;
    int mistryPowerStatus;
};

struct piece1
{
    int id;
    int group;
    int byCapIndex;
    int farToEnd;
};

extern struct piece1 tempArray2[PIECE_FOR_PLAYER];
extern struct Player players[PLAYERS];
//globle declarations
// int livePlayer = 0;
// int red_movePiece;
// static int tempBlock = -1;
// static int roundCounter = 0;
// static int mistryShellLocation = 0;
// static bool roundCountOn = true;
// static int rounds = 0;

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

#endif // TYPES_H