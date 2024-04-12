#include "./include/assign.h"
#include "./include/calculate.h"
#include <time.h>

int main(int argc, char **argv)
{
    if (argc != MIN_ARGC_SIZE+1) {
        fprintf(stderr, "\nerr 0x0: Insert more than <%d> cards. At least %d.", argc/2, MIN_ARGC_SIZE/2);
        return EXIT_FAILURE;
    }
    
    const clock_t init = clock();

    Card *Cards_set = assign_cards(argc, argv);
    if (Cards_set == NULL)
        return EXIT_FAILURE;

    printf("Memory address of Cards_set in main: %p\n", (void *)Cards_set);

    const char _first_pcard = Cards_set[MAX_CARDS_PER_PROGRAM-2].number;
    const char _second_pcard = Cards_set[MAX_CARDS_PER_PROGRAM-1].number;

    //orderPerPriority(Cards_set);
    //printCards(Cards_set);
    //printf("\n{%d} \n{%d} \n{%d}", GET_MAX_PRIORITY(Cards_set), _first_pcard, _second_pcard);
    free(Cards_set);

    const clock_t end = clock();
    printf("\nExec time: %lf", (double)(end-init) / CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}

