#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "future.h"

int int_from_str(const char * str, int * i) {
  int len;
  if (strchr(str,' ') != NULL) {
    len = strchr(str,' ') - str;
  }
  else {
    len = strchr(str,'\n') - str;
  }
  char * char_int = malloc((len + 1) * sizeof(*char_int));
  strncpy(char_int, str, len);
  char_int[len] = '\0';
  int ans = atoi(char_int);
  free(char_int);
  *i = *i + 2 + len;
  //printf("ans = '%d'\n", ans);
  return ans;
}

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * ans = malloc(sizeof(*ans));
  ans->cards = malloc(sizeof(*ans->cards));
  ans->n_cards = 0;
  //printf("Line length: %zu\n", strchr(str, '\n') - str);
  int len = strchr(str, '\n') - str;
  int i = 0;
  while( i < len) {
    //print_card(card_from_letters(str[i], str[i+1]));
    if (str[i] == '?') {
      add_future_card(fc, int_from_str(str+i+1, &i),add_empty_card(ans));
    }
    else if (isalnum(str[i])) {
      add_card_to(ans, card_from_letters(str[i],str[i+1]));
      i = i + 3;
    }
    else {
      i++;
    }
    //printf("i = %d\n",i);
  }
  return ans;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** ans = malloc(sizeof(*ans));
  char * line = NULL;
  size_t sz = 0;
  if( f == NULL) {
    fprintf(stderr,"Cannot open file.\n");
    exit(EXIT_FAILURE);
  }
  while(getline(&line, &sz, f) >= 0) {
    (*n_hands)++;
    ans = realloc(ans, (*n_hands) * sizeof(*ans));
    ans[(*n_hands) - 1] = hand_from_string(line, fc);
    if (ans[(*n_hands) - 1]->n_cards < 5) {
      fprintf(stderr,"Minimum 5 cards per hand.\n");
      exit(EXIT_FAILURE);
    }
  }
  free(line);
  return ans;
}


// DELETE THIS WHEN SUBMITTING
//int main(void) {
//char * str = "As Jd Kh ?14 ?12 ?0 ?1\n";
//future_cards_t * fc = malloc(sizeof(*fc));
//fc->decks = malloc(sizeof(*fc->decks));
//fc->n_decks = 0;
//deck_t * deck = hand_from_string(str, fc);
//return EXIT_SUCCESS;
//}
