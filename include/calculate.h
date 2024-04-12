#ifndef CALC_RANK
#define CALC_RANK

#include "calc_helper.h"

typedef unsigned short ushort;

ushort isRoyalFlush(roCard *Cards_set);
ushort isStraightFlush(roCard *Cards_set);
ushort isFourOfAKind(roCard *Cards_set);
ushort isFullHouse(roCard *Cards_set);
ushort isFlush(roCard *Cards_set);
ushort isStraight(roCard *Cards_set);
ushort isThree_of_a_kind(roCard *Cards_set);
ushort isDoubleCouple(roCard *Cards_set);
ushort isSingleCouple(roCard *Cards_set);
ushort GET_MAX_PRIORITY(roCard *Cards_set);

#endif