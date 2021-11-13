// COMP2521 20T2 Assignment 1
// tw.c ... compute top N most frequent words in file F
// Usage: ./tw [Nwords] File

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "Dict.h"
#include "WFreq.h"
#include "stemmer.h"

#define STOPWORDS "stopwords"
#define MAXLINE 1000
#define MAXWORD 100

#define STARTING "*** START OF"
#define ENDING   "*** END OF"

#define isWordChar(c) (isalnum(c) || (c) == '\'' || (c) == '-')

int main(int argc, char *argv[])
{
   // TODO ... add any variables you need

   FILE  *in;         // currently open file
   Dict   stopwords;  // dictionary of stopwords
   Dict   wfreqs;     // dictionary of words from book
   WFreq *results;    // array of top N (word,freq) pairs
                      // (dynamically allocated)

   char *fileName;    // name of file containing book text
   int   nWords;      // number of top frequency words to show

   char   line[MAXLINE];  // current input line
   char   word[MAXWORD];  // current word

   // process command-line args
   switch (argc) {
   case 2:
      nWords = 10;
      fileName = argv[1];
      break;
   case 3:
      nWords = atoi(argv[1]);
      if (nWords < 10) nWords = 10;
      fileName = argv[2];
      break;
   default:
      fprintf(stderr, "Usage: %s [Nwords] File\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // build stopword dictionary

   // TODO
   in = fopen(STOPWORDS, "r");
   if (in == NULL) {
      fprintf(stderr, "Can't open stopwords\n");
      exit(EXIT_FAILURE);
   }
   stopwords = newDict();
   // Insert stopwords to dictionary
   while (fgets(word, MAXWORD, in) != NULL) {
      int length = strlen(word);
      if (word[length - 1] == '\n')
         word[length - 1] = '\0';     // remove character
      DictInsert(stopwords, word);
   }
   fclose(in);
   // scan File, up to start of text
   
   // TODO
   in = fopen(fileName, "r");
   if (in == NULL) {
      fprintf(stderr, "Can't open %s\n", fileName);
      exit(EXIT_FAILURE);
   }
   bool isProject = false;
   // skip to start of the text
   while (fgets(line, MAXLINE, in) != NULL) {
      if (strstr(line, STARTING) != NULL) {
         isProject = true;
         break;      
      }
   }
   if (isProject == false) {
      fprintf(stderr, "Not a Project Gutenberg book\n");
      exit(EXIT_FAILURE);
   }


   // scan File reading words and accumualting counts

   // TODO

   wfreqs = newDict();
   while (fgets(line, MAXLINE, in) != NULL) {
      if (strstr(line, ENDING) != NULL)
         break; 
      // loop through the line array
      for (int i = 0; line[i] != '\0'; i++) {
         // check whether to insert
         bool flag = false;
         int j = 0;
         // insert to a word array
         while (isWordChar(line[i])) {
            if (isupper(line[i])) {
               word[j] = tolower(line[i]);               
            } else {
               word[j] = line[i];
            }
            j++;  
            i++;
            flag = true;     
         }
         word[j] = '\0'; 
         // Insert to wfreqs dictionary
         if (strlen(word) > 1 && flag == true) {
            if (DictFind(stopwords, word) == NULL) {
               int endpoint = stem(word, 0, j - 1);
               word[endpoint + 1] = '\0';
               WFreq *wordPair = DictFind(wfreqs, word);
               // found or not
               if (wordPair == NULL) {
                  DictInsert(wfreqs, word);
               } else {
                  wordPair->freq += 1;
               }
            }
         } 
      }
   }
   fclose(in);
   // compute and display the top N words

   // TODO
   // allocate memory
   results = malloc(nWords * sizeof(*results));
   int outputNum = findTopN(wfreqs, results, nWords);
   // print frequency in order
   for (int i = 0; i < outputNum; i++) {
      printf("%7d %s\n", results[i].freq , results[i].word);
   }

   // done
   return EXIT_SUCCESS;
}
