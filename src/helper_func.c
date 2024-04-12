#include "../include/calc_helper.h"

unsigned char exists(roCard *Cards_set, roChar start, roChar end, roChar number) {
    for (char i = start; i<end; i++)
        if (Cards_set[i].number == number)
            return i;
    return -1;
}

short setPriorityOfCard(roChar number, char symbol) {
    switch ((int)symbol)
    {
        case 6:
            return (number-1);
        case 3:
            return (20 + number-1);
        case 5:
            return (40 + number-1);
        case 4:
            return (60 + number-1);
        default:
            return 0;
    }
}

short getMin_priorityInterval(roChar a) {
    if (a == 0 || a == 1)
        return 1;
    if (a == 2 || a == 3)
        return 20;
    if (a == 4 || a == 5)
        return 40;
    if (a == 6 || a == 7)
        return 60;
    return 0;
}

char getPlayer_highestCard(roCard *Cards_set) {
    char highestN = 0;
    for (char i = 0; i<MAX_CARDS_PER_PROGRAM; i++) {
        if (!Cards_set[i].isDealer)
            highestN = (Cards_set[i].number > highestN) ? Cards_set[i].number : highestN;
    }
    return highestN;
}

char getPlayer_highestFlushCard (roCard *Cards_set, roChar start, roChar counter) {
    char i = start;
    while (i < counter && Cards_set[i].isDealer) i++;
    if (i < counter) return Cards_set[i].number*8;
    return getPlayer_highestCard(Cards_set);
}

void orderPerPriority(Card *Cards_set) {
    for (char i = 0; i<MAX_CARDS_PER_PROGRAM; i++) {
        for (char j = i; j<MAX_CARDS_PER_PROGRAM; j++) {
            if (Cards_set[i].priority < Cards_set[j].priority) {
                Card tmp = Cards_set[i];
                Cards_set[i] = Cards_set[j];
                Cards_set[j] = tmp;
            }
        }
    }
}

char getFigure(roChar number) {
    switch (number)
    {
        case 11:
            return 'J';
        case 12:
            return 'Q';
        case 13:   
            return 'K';
        case 14:
            return 'A';
        default:
            return 0;
    }
}

void printCards(roCard *Cards_set) {
    for (char i = 0; i<MAX_CARDS_PER_PROGRAM; i++) {
        if (Cards_set[i].number <= 10) {
            printf("\nCarta %d: %c => %d con priorita %d => tag: %s", i+1, Cards_set[i].symbol, Cards_set[i].number, Cards_set[i].priority, (Cards_set[i].isDealer) ? "dealer" : "player");
        } else {
            printf("\nCarta %d: %c => %c con priorita %d => tag: %s", i+1, Cards_set[i].symbol, getFigure(Cards_set[i].number), Cards_set[i].priority, (Cards_set[i].isDealer) ? "dealer" : "player");
        }
    }
}

char *findMax(roChar *arr, roChar max_size, roChar numbers, const bool isEnd) {
    static char *max_v = NULL;
    if (isEnd && max_v != NULL) {
        free(max_v);
        return NULL;
    }
    
    if (!max_v) {
        max_v = (char*)calloc(numbers, sizeof(char));
        if (max_v == NULL) return NULL;
    }
    if (max_v[0] != -1) memset(max_v, -1, sizeof(max_v)-1);

    char emb_count = 0;
    for (; emb_count < numbers; emb_count++) {
        for (char j = 0; j<max_size; j++) {
            if ((emb_count < 1) ? (arr[j] >= max_v[emb_count]) : (arr[j] >= max_v[emb_count] && arr[j] <= max_v[emb_count-1]) && arr[j] > -1)
                max_v[emb_count] = arr[j];
        }
    }
    return max_v;
}

char getMaxValue(roCard *Cards_set, roChar *numbers) {
    char Arr[sizeof(numbers)-1] = {Cards_set[numbers[0]].number, -1, -1};
    if (numbers[1] > -1) Arr[1] = Cards_set[numbers[1]].number;
    if (numbers[2] > -1) Arr[2] = Cards_set[numbers[2]].number;
    char *val_ordered = findMax(Arr, sizeof(Arr), 1, false);
    if (VERIFY_ERR(val_ordered))
        return 0;
    return val_ordered[0];
}

bool isAdjacentPriority(roCard *Cards_set, roChar start, roChar counter) {
    char i = 1, j = start;
    while (Cards_set[j].priority-i == Cards_set[j+i].priority && i<counter) i++;
    if (i == counter) 
        return true;
    return false;
}

char *VERIFY_PRIORITY(roCard *Cards_set, roChar _counter, roChar start, roChar end, roChar FLAG, const bool isFullHouse, roChar tris_val, const bool IS_END) {
    static char *indexes = NULL;
    if (IS_END) {
        free(indexes);
        return NULL;
    } 
    
    if (!indexes) {
        indexes = (char*)calloc(3, sizeof(char));
        if (indexes == NULL) return NULL;
    }

    if (indexes[0] != -1) memset(indexes, -1, sizeof(indexes)-1);
    
    char card_to_not_check = 0;
    if (isFullHouse) 
        card_to_not_check = tris_val;
    //ROYAL FLUSH REQUEST
    if (FLAG == 4) {
        char possible_index = exists(Cards_set, 0, MAX_CARDS_PER_PROGRAM, 14);
        if (possible_index < 0) return NULL;
        if (isAdjacentPriority(Cards_set, possible_index, 5)) return "t";
        return NULL;
    }
    
    char j, i = start;
    char counter = 0, emb_count = 0;
    while (i < end)
    {
        if (isFullHouse) 
            if (Cards_set[i].number == card_to_not_check)
                i = (i+1 > end) ? i : i+1;

        if (FLAG == 2 && !(counter < _counter)) break;
        j = (FLAG == 3) ? 0 : (FLAG == 1) ? 1 : (i+1 < end)? i+1 : i;
        if (FLAG == 1)
        {
            if (Cards_set[i].number > 5) 
            {
                if (isAdjacentPriority(Cards_set, i, _counter))
                {
                    indexes[emb_count] = i;
                    emb_count++;
                }
            }
        } else {
            counter = 1;
            while (j < end && counter < _counter)
            {
                switch (FLAG)
                {
                    case 0:
                        if (((Cards_set[i].number < 11) ? (Cards_set[i].priority%10) : (Cards_set[i].priority%10)+10) == ((Cards_set[j].number < 11) ? Cards_set[j].priority%10 : (Cards_set[j].priority%10)+10) && i != j)
                            counter++;
                        break;
                        
                    case 2:
                        if (Cards_set[j].priority > getMin_priorityInterval(Cards_set[i].priority/10))
                            counter++;   
                        break;
                    
                    case 3:
                        if (((Cards_set[i].number < 11) ? (Cards_set[i].priority%10)+counter : ((Cards_set[i].priority%10)+10)+counter) == ((Cards_set[j].number < 11) ? Cards_set[j].priority%10 : (Cards_set[j].priority%10)+10)) {
                            counter++;
                            j = 0;
                        } else {
                            j++;
                        }
                        break;

                    default:
                        break;
                }
                if (FLAG != 3)
                    j++;
            }
            
            if (counter == _counter) {
                indexes[emb_count] = i;
                emb_count++;
            }
        }
        i++;
    }
    
    if (indexes[0] > -1)
        return indexes;
    return NULL;
}