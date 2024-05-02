#include "..\include\assign.h"

bool verifyCardsNumber(const char *number_str) {
    char *ptr;
    const char num = strtol(number_str, &ptr, 10);
    if (ptr == number_str)
        return false;

    if (num < 2 || num > 14)
        return false;
    return true;
}

Card *assign_cards(int argc, char **_argv) {
    Card *CS = (Card*)calloc(sizeof(Card)*MAX_CARDS_PER_PROGRAM);
    if (CS == NULL)
        return NULL;

    unsigned char j, i = 1, countr = 0;
    while (i<MAX_PLAYER_SN_SIZE+MAX_DEALER_SN_SIZE && countr < MAX_CARDS_PER_PROGRAM)
    {
        if (!verifyCardsNumber(_argv[i])) {
            free(CS);
            fprintf(stderr, "\nerr 0x1: [Card: %d] => CARD CONSISTENCY COMPRIMISED: number's format or value incorrect", countr+1);
            return NULL;
        }
        CS[countr].number = atoi(_argv[i]);

        CS[countr].symbol = strtol(_argv[i+1], NULL, 16);
        if (CS[countr].symbol < 3 || CS[countr].symbol > 6) {
            free(CS);
            fprintf(stderr, "\nerr 0x2: [Card: %d] => CARD CONSISTENCY COMPRIMISED: symbol's format or value incorrect", countr+1);
            return NULL;
        }
            
        CS[countr].priority = setPriorityOfCard(CS[countr].number, CS[countr].symbol);
        for (j = 0; j<countr; j++) {
            if (CS[countr].priority == CS[j].priority) {
                free(CS);
                fprintf(stderr, "\nerr 0x3: [Card: %d] => CARDS SET CONSISTENCY COMPRIMISED: cards cannot repeat by symbol AND number", countr+1);
                return NULL;
            }
        }

        if (i < MAX_DEALER_SN_SIZE) {
            CS[countr].isDealer = true;
        } else {
            CS[countr].isDealer = false;
        }

        //printf("\nCard %d, %d => %c", countr, CS[countr].number, CS[countr].symbol);
        i+=2; 
        countr++;
    }
    return CS;
}
