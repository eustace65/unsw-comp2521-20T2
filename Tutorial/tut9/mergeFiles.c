int main(int argc, char *argv[])
{
   if (argc < 3) {
      fprintf(stderr, "Usage: ./merge  File1  File2\n");
      return -1;  // error code
   }
   FILE *in1 = fopen(argv[1],"r");
   FILE *in2 = fopen(argv[2],"r");
   if (in1 == NULL || in2 == NULL) {
      fprintf(stderr, "Invalid input file(s)\n");
      return -1;  // error code
   }
   // now start merging
   char line1[MAXLINE], line2[MAXLINE];
   bool more1 = fgets(line1,MAXLINE,in1);
   bool more2 = fgets(line2,MAXLINE,in2);
   while (more1 && more2) {
      int diff = strcmp(line1,line2);
      if (strcmp(line1,line2) <= 0) {
         fputs(line1,stdout);
         more1 = fgets(line1,MAXLINE,in1);
      }
      else {
         fputs(line2,stdout);
         more2 = fgets(line2,MAXLINE,in2);
      }
   }
   while (fgets(line1,MAXLINE,in1) != NULL) fputs(line1,stdout);
   while (fgets(line2,MAXLINE,in2) != NULL) fputs(line2,stdout);
   fclose(in1);  fclose(in2);
}