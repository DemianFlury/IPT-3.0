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

//Defining the input parameters for the "Game" function
int Game();
StruCard* AddCard(StruCard* pStart, StruCard* pNew);
StruCard* CreateCard(const char* bez, int par1, double par2);
void OutputList(StruCard* pStart);
StruCard* ShuffleCards(StruCard* pStart);
int Randomizer(int);



//The "main" function will help us set what the game function does.
//Therefore we will declare an [bool] array which is given to the "Game" function.
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
  pStart = AddCard(pStart, CreateCard("Sheev Palpatine", 42, 63.6));
  pStart = AddCard(pStart, CreateCard("Anakin Skywalker", 40, 22.5));
  pStart = AddCard(pStart, CreateCard("Darth Vader", 42, 22.6));
  pStart = AddCard(pStart, CreateCard("Obi-Wan Kenobi", 35, 38.1));
  pStart = AddCard(pStart, CreateCard("Mace Windu", 43, 53.7));
  pStart = AddCard(pStart, CreateCard("Jar Jar Binks", 25, 33.3));
  pStart = AddCard(pStart, CreateCard("Yoda", 41, 877.0));
  pStart = AddCard(pStart, CreateCard("Darth Maul", 38, 35.3));
  pStart = AddCard(pStart, CreateCard("Chewbacca", 30, 181.9));
  pStart = AddCard(pStart, CreateCard("Count Dooku", 39, 83.2));
  ShuffleCards(pStart);

  int StatChooser = Randomizer(2);
  if (StatChooser == 0)
  {
    if (pStart->fighting <= 30)
    {
     // lowerthan(pStart->fighting);
    }
    else
    {
     // greaterthan(pStart->fighting);
    }
  }
  else
  {
    if (pStart->age <= 50)
    {
      // lowerthan(pStart->age);
    }
    else
    {
      // greaterthan(pStart->age);
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
  int d = 0;
  int e = 0;
  StruCard* pStartP = NULL;
  StruCard* pTmp1 = pStart;
  StruCard* pTmp2 = NULL;
  //Combines the end of the list to the start.
  while (pTmp1->pNext != NULL)
  {
    pTmp1 = pTmp1->pNext;
  }
  pTmp1->pNext = pStart;

  //Shuffling Process begins.
  pTmp1 = pStart;
  for (int a = 0; a <= 4; a++)
  {
    //Randomizes where to take cards out in the deck.
    int b = Randomizer(10);
    if (b == 0) b = 10;
    for (int c = 0; b > c; c++)
    {
      pTmp1 = pTmp1->pNext;
      if (pTmp1 == pStart)
      {
        pStart = pStart->pNext;
      }
    }
    //Initializes the second list.
    //First run through.
    if (d == 0)
    {
      pStartP = pTmp1->pNext;
      pTmp1->pNext = pStartP->pNext;
      d = 1;
    }
    else
    {
      //Second run through.
      if (e == 0)
      {
        pStartP->pNext = pTmp1->pNext;
        pTmp2 = pStartP->pNext;
        e = 1;
      }
      //The rest of the list.
      pTmp2 = pTmp2->pNext;
      pTmp1->pNext = pStartP->pNext;
    }  
  }
  //Makes sure the end of the lists point to NULL so they can be properly finalised.
  pTmp2->pNext = NULL;
  pTmp1 = pTmp1->pNext;
  pTmp1->pNext = NULL;
  pTmp1 = pStart;
  pTmp2 = pStartP;

  //TROUBLESHOOTING:
  //Doesn't yet result in 10 cards, the problem lies somewhere in between 167-185.
  //Prints first list.
  while (pTmp1->pNext != NULL)
  {
    printf("%s", pTmp1->Bez);
    pTmp1 = pTmp1->pNext;
  }
  //Prints second list.
  while (pTmp2->pNext != NULL)
  {
    printf("%s", pTmp2->Bez);
    pTmp2 = pTmp2->pNext;
  }

  return pStartP;
}

int Randomizer(int range) {
    srand(time(NULL));
    return (rand() % range);
}