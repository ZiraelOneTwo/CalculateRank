#include "../include/calculate.h"
#include <string.h>

ushort isRoyalFlush(roCard *Cards_set) {
    roChar *royal_flush = VERIFY_PRIORITY(Cards_set, 5, 0, MAX_CARDS_PER_PROGRAM, 4, false, 0, false);
    if (royal_flush == NULL || royal_flush != "t") return 0;

    return 400;
}

ushort isStraightFlush(roCard *Cards_set) {
    roChar *straight_flush = VERIFY_PRIORITY(Cards_set, 0, 0, MAX_CARDS_PER_PROGRAM, 1, false, 0, false);
    if (VERIFY_ERR(straight_flush)) return 0;
    roChar max_val = getMaxValue(Cards_set, straight_flush);

    return (max_val > 0) ? 350+max_val : 0;
}

ushort isFourOfAKind(roCard *Cards_set) {
    roChar *FOAK = VERIFY_PRIORITY(Cards_set, 4, 0, MAX_CARDS_PER_PROGRAM, 0, false, 0, false);
    if (VERIFY_ERR(FOAK)) return 0;

    return Cards_set[FOAK[0]].number + 305;
}

ushort isFullHouse(roCard *Cards_set) {
    roChar *tris_indexes = VERIFY_PRIORITY(Cards_set, 3, 0, MAX_CARDS_PER_PROGRAM, 0, false, 0, false);
    if (VERIFY_ERR(tris_indexes)) return 0;
    roChar max_Val_tris = getMaxValue(Cards_set, tris_indexes);

    roChar *couple_indexes = VERIFY_PRIORITY(Cards_set, 2, 0, MAX_CARDS_PER_PROGRAM, 0, true, max_Val_tris, false);
    if (VERIFY_ERR(couple_indexes)) return 0;
    roChar max_Val_couple = getMaxValue(Cards_set, couple_indexes);

    return (max_Val_tris > 0 && max_Val_couple > 0) ? 150+(max_Val_tris*2)+max_Val_couple : 0;
}

ushort isFlush(roCard *Cards_set) {
    roChar *flush_index = VERIFY_PRIORITY(Cards_set, 5, 0, MAX_CARDS_PER_PROGRAM, 2, false, 0, false);
    if (VERIFY_ERR(flush_index)) return 0;

    return 150+getPlayer_highestFlushCard(Cards_set, flush_index[0], 5);
}

ushort isStraight(roCard *Cards_set) {
    roChar *straight_indexes = VERIFY_PRIORITY(Cards_set, 5, 0, MAX_CARDS_PER_PROGRAM, 3, false, 0, false);
    if (VERIFY_ERR(straight_indexes)) return 0;
    roChar max_val = getMaxValue(Cards_set, straight_indexes);
    
    return 90+max_val;
}

ushort isThree_of_a_kind(roCard *Cards_set) {
    roChar *index_tris = VERIFY_PRIORITY(Cards_set, 3, 0, MAX_CARDS_PER_PROGRAM, 0, false, 0, false);
    if (VERIFY_ERR(index_tris)) return 0;
    roChar max_tris_val = getMaxValue(Cards_set, index_tris);

    return 70+max_tris_val;
}

ushort isDoubleCouple(roCard *Cards_set) {
    roChar *couples = VERIFY_PRIORITY(Cards_set, 2, 0, MAX_CARDS_PER_PROGRAM, 0, false, 0, false);
    char first_couple_val, second_couple_val;

    if (VERIFY_ERR(couples) || couples[1] < 0 || Cards_set[couples[0]].number == Cards_set[couples[1]].number)
        return 0;
    if (couples[2] > -1) {
        roChar arr[sizeof(couples)-1] = {Cards_set[couples[0]].number, Cards_set[couples[1]].number, Cards_set[couples[2]].number};
        roChar *max_two_couples = findMax(arr, sizeof(arr), 2, false);
        if (VERIFY_ERR(max_two_couples)) return 0;

        first_couple_val = max_two_couples[0];
        second_couple_val = max_two_couples[1];
    } else {
        first_couple_val = Cards_set[couples[0]].number;
        second_couple_val = Cards_set[couples[1]].number;
    }
    
    return 40+first_couple_val+second_couple_val;
}

ushort isSingleCouple(roCard *Cards_set) {
    roChar *index = VERIFY_PRIORITY(Cards_set, 2, 0, MAX_CARDS_PER_PROGRAM, 0, false, 0, false);
    if (VERIFY_ERR(index)) return 0;
    roChar max_val = getMaxValue(Cards_set, index);
    
    return 20+max_val;
}

ushort GET_MAX_PRIORITY(roCard *Cards_set) {
    ushort (*func_arr[])(roCard[]) = {isSingleCouple, isDoubleCouple, isThree_of_a_kind, isStraight, isFlush, isFullHouse, isFourOfAKind, isStraightFlush, isRoyalFlush};
    char i = sizeof(func_arr) / sizeof(ushort*)-1;
    ushort _priority = 0;
    char *closing_ptr = NULL;
    
    while (i > -1) {
        _priority = (*func_arr[i])(Cards_set);
        if (_priority > 0) {
            closing_ptr = VERIFY_PRIORITY(Cards_set, 0, 0, 0, 0, false, 0, true);
            closing_ptr = findMax(NULL, 0, 0, true);
            return _priority;
        }
        i--;
    }
    closing_ptr = VERIFY_PRIORITY(Cards_set, 0, 0, 0, 0, false, 0, true);
    closing_ptr = findMax(NULL, 0, 0, true);
    return 0;
}
