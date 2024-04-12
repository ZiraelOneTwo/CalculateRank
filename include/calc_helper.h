#ifndef HELPER
#define HELPER

#include "defines_ds_lib.h"

unsigned char exists(roCard *Cards_set, roChar start, roChar end, roChar number);
short setPriorityOfCard(roChar number, char symbol);
short getMin_priorityInterval(roChar a);
char getPlayer_highestCard(roCard *Cards_set);
char getPlayer_highestFlushCard (roCard *Cards_set, roChar start, roChar counter);
void orderPerPriority(Card *Cards_set);
char getFigure(roChar number);
void printPlayersCard(roCard *Cards_set);
void printCards(roCard *Cards_set);
char *findMax(roChar *arr, roChar max_size, roChar numbers, const bool isEnd);
char getMaxValue(roCard *Cards_set, roChar *numbers);
bool isAdjacentPriority(roCard *Cards_set, roChar start, roChar counter);
char *VERIFY_PRIORITY(roCard *Cards_set, roChar _counter, char start, roChar end, roChar FLAG, const bool isFullHouse, roChar tris_val, const bool IS_END);

#endif 