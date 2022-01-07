#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Defining a globally used struct, so it won't be newly declared everytime 
//the "Game" function gets used
typedef struct Card
{
  char Bez[50];
  int fighting;
  double age;
  struct Card* pNext;
} StruCard;

//Defining the input parameters for the functions
int Game();
StruCard* AddCard(StruCard* pStart, StruCard* pNew);
StruCard* CreateCard(const char* bez, int par1, double par2);
void OutputList(StruCard* pStart);
StruCard* ShuffleCards(StruCard* pStart);
int Randomizer(int);
bool LesserThan(StruCard*, StruCard*,short);
bool GreaterThan(StruCard*, StruCard*, short);




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
  StruCard* pStartP = ShuffleCards(pStart);

  int StatChooser = Randomizer(2);
  if (StatChooser == 0)
  {
    if (pStart->fighting <= 40)
    {
      LesserThan(pStartP, pStart, 0);
    }
    else
    {
      GreaterThan(pStartP, pStart, 0);
    }
  }
  else
  {
    if (pStart->age <= 50)
    {
      LesserThan(pStartP, pStart, 1);
    }
    else
    {
      GreaterThan(pStartP, pStart, 1);
    }
  }


  return 0;
}

StruCard* AddCard(StruCard* pStart, StruCard* pNew)
{
  pNew->pNext = NULL;
  if (pStart == NULL) { //Leere Liste
    pStart = pNew;
  }
  else {
    StruCard* pLast = pStart;
    while (pLast->pNext != NULL) pLast = pLast->pNext;
    pLast->pNext = pNew;
  }
  return pStart;
}


StruCard* CreateCard(const char* bez, int par1, double par2)
{
  StruCard* newCard = (StruCard*)malloc(sizeof(StruCard));
  strcpy_s(newCard->Bez, 50, bez);
  newCard->fighting = par1;
  newCard->age = par2;
  return newCard;
}


void OutputList(StruCard* pStart)
{
  for (StruCard* pTmp = pStart; pTmp != NULL; pTmp = pTmp->pNext)
    printf("Bez = %s\n", pTmp->Bez);
}

StruCard* ShuffleCards(StruCard* pStart)
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
      RandomizerVar = 1;

    for (int inindex = 0; inindex < RandomizerVar; inindex++)
    {
      pSelection = pSelection->pNext;
    }
    //Random Card picked.
    if (pSelection == pStart)
      pStart = pSelection->pNext;
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
    if (pSelection->pNext == pStart)
    {
      pStart = pSelection;
    }
  }
  while (pSelection->pNext != pStart)
  {
    pSelection = pSelection->pNext;
  }
  pSelection->pNext = NULL;
  pSelection = pStart;
  printf("%s \n", pSelection->Bez);
  while (pSelection->pNext != NULL)
  {
    pSelection = pSelection->pNext;
    printf("%s \n", pSelection->Bez);
  }

  return 0;
}

int Randomizer(int range) {
    srand(time(NULL));
    return (rand() % range);
}

bool GreaterThan(StruCard* LP, StruCard* CP, short stat)
{
  if (stat == 0)
  {
    if (LP->fighting > CP->fighting)
    {
      return true;
    }
    else
      return false;

  }
  if (stat == 1)
  {
    if (LP->age > CP->age)
    {
      return true;
    }
    else
      return false;
  }
}

bool LesserThan(StruCard* LP, StruCard* CP, short stat)
{
  if (stat == 0)
  {
    if (LP->fighting < CP->fighting)
    {
      return true;
    }
    else
      return false;

  }
  if (stat == 1)
  {
    if (LP->age < CP->age)
    {
      return true;
    }
    else
      return false;
  }
}