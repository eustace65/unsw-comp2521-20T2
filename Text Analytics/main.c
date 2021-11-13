#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "Dict.h"
#include "WFreq.h"
#include "stemmer.h"


int main(void) {
   Dict new = newDict();
  /* FILE *in = fopen("data/2600.txt", "r");
   if (in == NULL) 
      printf("no");
   char word[1000];
   while (fgets(word, 1000, in) != NULL) {
      int length = strlen(word);
      if (word[length - 1] == '\n')
         word[length - 1] = '\0';
      DictInsert(new, word);

   }
   if (DictFind(new, "according") != NULL)
      printf("find\n");
   */
   DictInsert(new, "abd");
   DictInsert(new, "abd");
   DictInsert(new, "abd");
   DictInsert(new, "abd");
   WFreq *results = malloc(20 * sizeof(*results));
   int outputNum = findTopN(new, results, 20);
   for (int i = 0; i < outputNum; i++) {
      printf("%7d %s\n",results[i].freq , results[i].word);
   }
   return 0;
}
