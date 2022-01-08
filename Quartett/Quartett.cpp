#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Defining a globally used struct, so it won't be newly declared everytime 
//the "Game" function gets used
typedef struct Card
{
  char name[50];
  int fighting;
  double age;
  struct Card* pNext;
} StruCard;

//Defining the input parameters for the functions
int Game();
StruCard* AddCard(StruCard* pStart, StruCard* pNew);
StruCard* CreateCard(const char* bez, int par1, double par2);
void OutputList(StruCard* pStart);
StruCard** ShuffleCards(StruCard* pStart);
int Randomizer(int);
int LesserThan(StruCard*, StruCard*,short);
int GreaterThan(StruCard*, StruCard*, short);
int AI(StruCard*, StruCard*);
int PlayerMenuIG(StruCard*, StruCard*, short);





//The "main" function will help us set what the game function does.
//Therefore we will declare a [bool] array which is given to the "Game" function.
//The "main" function is mostly used for menus which appear b4 the actual game.

int main()
{
  //Defining [bool] array.
  int menuinput;
  bool gameinputs[10];
  printf("Hello Player!\nThis is the best unfinished \x22Quartett\x22\n");
  printf("Are you playing \x22Quartett\x22 for the first time?\nYes = 1, No = 2\n");
  scanf_s("%d", &menuinput);
  int random = Randomizer(2);
  if (menuinput == 1)
  {
    gameinputs[0] = true; //Spieler hat das tutorial aufgerufen.
    printf("The Rules of \x22Quartett\x22 are:\nYou get 5 cards from the deck at the start of the game.\n");
    printf("You play with one opponent, who also draws 5 cards at the start.\nTherefore the deck contains 10 cards.\n");
    printf("You then take the card off of the top of your bunch, thats when the game begins.\n");
    printf("A coinflip decides if you or your opponent starts with choosing stats.\n");
    printf("If you win the coinflip you choose either one of your stats of the card and decide if you bet higher or lower.\n");
    printf("Then this stat gets compared to your opponents, if you bet right, you win the round and their card.\n");
    printf("These two cards go to the bottom of your bunch.\nThen your opponent gets to choose.\n");
    printf("The victor is decided by whom collets all the cards\n");
    system("pause");
    system("cls");
  }
  Game();

  system("Pause");
}

//The "Game" function is the function which will handle 
//generating the cards, declaring players, handing the cards out to the players 
//and resetting itself with the input values given by the "main function".

int Game()
{
  StruCard* pStartPlayer = NULL;
  StruCard* pStart = NULL;
  pStart = AddCard(pStart, CreateCard("Sheev Palpatine" , 41, 63.6));
  pStart = AddCard(pStart, CreateCard("Anakin Skywalker", 39, 22.5));
  pStart = AddCard(pStart, CreateCard("Darth Vader"     , 42, 22.6));
  pStart = AddCard(pStart, CreateCard("Obi-Wan Kenobi"  , 35, 38.1));
  pStart = AddCard(pStart, CreateCard("Mace Windu"      , 43, 53.7));
  pStart = AddCard(pStart, CreateCard("Jar Jar Binks"   , 25, 33.3));
  pStart = AddCard(pStart, CreateCard("Yoda"            , 40, 877.0));
  pStart = AddCard(pStart, CreateCard("Darth Maul"      , 33, 35.3));
  pStart = AddCard(pStart, CreateCard("Chewbacca"       , 30, 181.9));
  pStart = AddCard(pStart, CreateCard("Count Dooku"     , 38, 83.2));
  StruCard** ListOfStarts = ShuffleCards(pStart);
  pStart = ListOfStarts[0];
  pStartPlayer = ListOfStarts[1];
  bool PlayerTurn = true;
  int Result = 0;
  while (pStartPlayer != NULL || pStart != NULL)
  {
    if (PlayerTurn == true)
    {
      Result = PlayerMenuIG(pStartPlayer, pStart, 0);
      PlayerTurn = false;
    }
    else
    {
      Result = AI(pStart, pStartPlayer);
      PlayerMenuIG(pStartPlayer, pStart, Result);
      PlayerTurn = true;
    }
    if (Result == 0)
    {
      //First card of the computer gets added to player's list
      //and player's first card gets put to the end if its list.
      StruCard* pEnd = pStartPlayer;
      StruCard* pTmp = pStart;
      pStart = pStart->pNext;
      pStartPlayer = pStartPlayer->pNext;
      pEnd->pNext = pTmp;
      pTmp->pNext = NULL;
      pTmp = pEnd;
      pEnd = pStartPlayer;
      while (pEnd->pNext != NULL)
        pEnd = pEnd->pNext;
      pEnd->pNext = pTmp;

      printf("\nYou won the round!\n");
      system("pause");
      system("cls");
    }
    else if (Result == 1)
    {
      //First card of the player gets added to computer's list
      //and computer's first card gets put to the end if its list.
      StruCard* pEnd = pStart;
      StruCard* pTmp = pStartPlayer;
      pStart = pStart->pNext;
      pStartPlayer = pStartPlayer->pNext;
      pEnd->pNext = pTmp;
      pTmp->pNext = NULL;
      pTmp = pEnd;
      pEnd = pStartPlayer;
      while (pEnd->pNext != NULL)
        pEnd = pEnd->pNext;
      pEnd->pNext = pTmp;


      printf("\nYou lost this round...\n");
      system("pause");
      system("cls");
    }
  }
  return 0;
}

StruCard* AddCard(StruCard* pStart, StruCard* pNew)
{
  pNew->pNext = NULL;
  if (pStart == NULL) { //empty list
    pStart = pNew;
  }
  else {
    StruCard* pLast = pStart;
    while (pLast->pNext != NULL) pLast = pLast->pNext;
    pLast->pNext = pNew;
  }
  return pStart;
}


StruCard* CreateCard(const char* name, int par1, double par2)
{
  StruCard* newCard = (StruCard*)malloc(sizeof(StruCard));
  strcpy_s(newCard->name, 50, name);
  newCard->fighting = par1;
  newCard->age = par2;
  return newCard;
}


void OutputList(StruCard* pStart)
{
  for (StruCard* pTmp = pStart; pTmp != NULL; pTmp = pTmp->pNext)
    printf("Name = %s\n", pTmp->name);
}

StruCard** ShuffleCards(StruCard* pStart)
{
  StruCard* pSelection = pStart;
  StruCard* pStartPlayer = NULL;
  StruCard* pSelectionPlayer = NULL;
  StruCard* pSavePlayer = NULL;
  int RandomizerVar = 0;

  //Close the loop
  while (pSelection->pNext != NULL)
  {
    pSelection = pSelection->pNext;
  }
  pSelection->pNext = pStart;

  //Pick out 5 cards
  for (int index = 0; index < 5; index++)
  {
    RandomizerVar = Randomizer(10);
    if (RandomizerVar == 0)
      RandomizerVar = 10;
    for (int inindex = 0; inindex < RandomizerVar; inindex++)
    {
      pSelection = pSelection->pNext;
    }
    //Random Card picked.
    if (pSelection->pNext == pStart)
    {
      pStart = pSelection;
    }
    if (index == 0)
    {
      pStartPlayer = pSelection->pNext;
      pSelection->pNext = pStartPlayer->pNext;
    }
    else if (index == 1)
    {
      pStartPlayer->pNext = pSelection->pNext;
      pSelectionPlayer = pStartPlayer->pNext;
      pSelection->pNext = pSelectionPlayer->pNext;
    }
    else
    {
      pSelectionPlayer->pNext = pSelection->pNext;
      pSavePlayer = pSelectionPlayer->pNext;
      pSelection->pNext = pSavePlayer->pNext;
      pSelectionPlayer = pSavePlayer;
    }
  }
  while (pSelection->pNext != pStart)
  {
    pSelection = pSelection->pNext;
  }
  pSelection->pNext = NULL;
  pSelectionPlayer->pNext = NULL;

  StruCard* Saves[2];
  Saves[0] = pStart;
  Saves[1] = pStartPlayer;
  StruCard** Returnpointer = Saves;
  return Returnpointer;
}

int Randomizer(int range) {
    srand(time(NULL));
    return (rand() % range);
}

int GreaterThan(StruCard* LP, StruCard* CP, short stat)
{
  if (stat == 1)
  {
    if (LP->fighting > CP->fighting)
    {
      return 0;
    }
    else
      return 1;

  }
  if (stat == 0)
  {
    if (LP->age > CP->age)
    {
      return 0;
    }
    else
      return 1;
  }
  else
    return 99;
}

int LesserThan(StruCard* LP, StruCard* CP, short stat)
{
  if (stat == 0)
  {
    if (LP->fighting < CP->fighting)
    {
      return 0;
    }
    else
      return 1;

  }
  if (stat == 1)
  {
    if (LP->age < CP->age)
    {
      return 0;
    }
    else
      return 1;
  }
  else
    return 99;
}

int AI(StruCard* AICard, StruCard* PlayerCard)
{
  int returncode = 0;
  int StatChooser = Randomizer(2);
  if (StatChooser == 0)
  {
    if (AICard->fighting <= 40)
    {
      returncode = LesserThan(PlayerCard, AICard, 0);
    }
    else
    {
      returncode = GreaterThan(PlayerCard, AICard, 0);
    }
  }
  else
  {
    if (AICard->age <= 50)
    {
      returncode = LesserThan(PlayerCard, AICard, 1);
    }
    else
    {
      returncode = GreaterThan(PlayerCard, AICard, 1);
    }
  }
  return returncode;
}

int PlayerMenuIG(StruCard* PlayerCard, StruCard* AICard, short AIHoL)
{
  int choiceHL = 0;
  int choiceST = 0;
  if (AIHoL != 0)
  {
    printf("\nThe computer takes it's turn.\n");
    switch (AIHoL)
    {
      case 1:
      {
        printf("\nThe Computer bets higher on age!\n");
        break;
      }
      case 2:
      {
        printf("\nThe Computer bets lower on age!\n");
        break;
      }
      case 3:
      {
        printf("\nThe Computer bets higher on fighting!\n");
        break;
      }
      case 4:
      {
        printf("\nThe Computer bets lower on fighting!\n");
        break;
      }
      default:
      {
        printf("Computer broken\n");
        break;
      }
    }
  }
  else
  {
    system("cls");
    printf("\nITS YOUR TURN.");
    printf("\nHere's your Card");
    printf("\n\nName = \t\t%s", PlayerCard->name);
    printf("\n\n");
    printf("Age =\t\t%.1lf \t[1]", PlayerCard->age);
    printf("\nFighting =\t%d \t[2]", PlayerCard->fighting);
    printf("\n\nWhich stat do you want to bet on? \n");
    wronginputST:
    scanf_s("%d", &choiceST);
    if (choiceST > 2 || choiceST < 1)
    {
      printf("please input [1] or [2] ");
      goto wronginputST;
    }
    printf("\nAre you betting higher [1] or lower [2] ?\n");
    wronginputHL:
    scanf_s("%d", &choiceHL);
    if (choiceHL > 2 || choiceHL <= 0)
    {
      printf("please input [1] or [2] ");
      goto wronginputHL;
    }
    switch (choiceST)
    {
      case 1:
      {
        if (choiceHL == 1)
        {
          return GreaterThan(PlayerCard, AICard, 1);
        }
        else
        {
          return LesserThan(PlayerCard, AICard, 1);
        }
        break;
      }
      case 2:
      {
        if (choiceHL == 1)
        {
          return GreaterThan(PlayerCard, AICard, 0);
        }
        else
        {
          return LesserThan(PlayerCard, AICard, 0);
        }
        break;
      }
      default:
      {
        printf("Computer broken...");
        system("pause");
        return 102;
      }
    }
  }
}

