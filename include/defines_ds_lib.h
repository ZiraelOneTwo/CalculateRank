#ifndef DEFINES
#define DEFINES

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    unsigned char number;
    unsigned char symbol;
    unsigned char priority;
    bool isDealer;
} Card;

typedef const char roChar;
typedef const Card roCard;

#define MAX_CARDS_PER_PLAYER 2
#define MAX_PLAYER_SN_SIZE (MAX_CARDS_PER_PLAYER*2)
#define MAX_CARDS_PER_DEALER 5
#define MAX_DEALER_SN_SIZE (MAX_CARDS_PER_DEALER*2)
#define MAX_CARDS_PER_PROGRAM MAX_CARDS_PER_DEALER+MAX_CARDS_PER_PLAYER*1
#define MAX_PROGRAM_SN_SIZE ((MAX_CARDS_PER_PROGRAM)*2)
#define MIN_ARGC_SIZE 14

#define VERIFY_ERR(str) (str == NULL || str[0] < 0)
#define SIZEOF(data, type) (sizeof(data)/sizeof(type))

#endif