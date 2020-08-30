#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 200
#define MAX_STUDENTS 1000

typedef struct _student {
   int  zid;            // 7-digit number
   char name[MAX_NAME]; // names are stored *within* the struct
   int  prog;           // 4-digit number
   int  magic;          // random number?
} Student;
 
int stuCmp(const void * a, const void * b);
 
int main(int argc, char **argv)
{
   Student students[MAX_STUDENTS];
 
   // read stdin line-by-line into students[]
   int n_students = 0;
   Student s;
   while (scanf("%d %s %d %d", &(s.zid), s.name, &(s.prog), &(s.magic)) == 4) {
      students[n_students++] = s;
   }

   // sort the students[] array
   qsort(students, n_students, sizeof(Student), stuCmp);

   // print the contents of the students[] array
   printf("\n\n\nSorted version:\n");
   for (int i = 0; i < n_students; i++) {
      printf("%7d %-20s %4d %d\n", students[i].zid,  students[i].name, 
                                   students[i].prog, students[i].magic);
   }
 
   return 0;
}

// return -ve if a < b, +ve if a > b, 0 if a == b
int stuCmp(const void * a, const void * b) {
   Student studentA = *(Student*)a;
   Student studentB = *(Student*)b;

   int nameComparison = strcmp(studentA.name, studentB.name);
   if (nameComparison != 0) return nameComparison;
   return studentA.zid - studentB.zid;
}