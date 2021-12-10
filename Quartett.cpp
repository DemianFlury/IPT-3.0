#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Defining a globally used struct, so it won't be newly declared everytime
//the "Game" function 
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



//The "main" function will help us set what the game function does.
//Therefore we will declare an [bool] array which is given to the "Game" function.
//The "main" function is mostly used for menus which appear b4 the actual game.

int main()
{
    Game();

  //Defining [bool] array.
  int menuinput;
  bool gameinputs[10];
  printf("Hello Player!\nThis is the best unfinished \x22Quartett\x22\n");
  printf("Are you playing \x22Quartett\x22 for the first time?\nYes = 1, No = 2\n");
  scanf_s("%d", &menuinput);
  if (menuinput == 1)
  {
    printf("The Rules of \x22Quartett\x22 are:\nYou get 5 cards from the deck at the start of the game.\n");
    printf("You play with one opponent, who also draws 5 cards at the start.\nTherefore the deck contains 10 cards.\n");
    printf("You then take the card off of the top of your bunch, thats when the game begins.\n");
    printf("A coinflip decides if you or your opponent starts with choosing stats.\n");
    printf("If you win the coinflip you choose either one of your stats of the card and decide if you bet higher or lower.\n");
    printf("Then this stat gets compared to your opponents, if you bet right, you win the round and their card.\n");
    printf("These two cards go to the bottom of your bunch.\nThen your opponent gets to choose.\n");
    printf("The victor is decided by whom collets all the cards\n");
  }
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
    pStart = AddCard(pStart, CreateCard("Darth Darth Binks", 100, 33.3));
    pStart = AddCard(pStart, CreateCard("Yoda", 41, 877.0));
    pStart = AddCard(pStart, CreateCard("Darth Maul", 38, 35.3));
    pStart = AddCard(pStart, CreateCard("Chewbacca", 30, 181.9));
    pStart = AddCard(pStart, CreateCard("Count Dooku", 39, 83.2));

    OutputList(pStart);
    system("pause");
    //strcpy(Card0->Bez, "Sheev Palpatine");
    //strcpy(Card1->Bez, "Anakin Skywalker");
    //strcpy(Card2->Bez, "Darth Vader");
    //strcpy(Card3->Bez, "Obi-Wan Kenobi");
    //strcpy(Card4->Bez, "Mace Windu");
    //strcpy(Card5->Bez, "Darth Darth Binks");
    //strcpy(Card6->Bez, "Yoda");
    //strcpy(Card7->Bez, "Darth Maul");
    //strcpy(Card8->Bez, "Chewbacca");
    //strcpy(Card9->Bez, "Count Dooku");

    
    
    
    
    
    
    
    
    
    

  return 0;
}

StruCard* AddCard(StruCard* pStart, StruCard* pNew)
{
    pNew->pNext = NULL;
    if (pStart == NULL) { // Leere Liste
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
    StruCard* newCard = (StruCard*) malloc(sizeof(StruCard));
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
//Note to Collaborator
//Im still trying to figure out how structs work.
//I have figured out that the name "Card" is not really needed for a struct.
//Therefore the actual name of the struct is "StruCard"
//But i think we do need the "Card" due to the "15: struct Card* pNext;".
//Most likely due to the linked list that i kinda understand but not sure how in practice.



