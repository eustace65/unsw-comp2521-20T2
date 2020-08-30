// COMP2521 20T2 Final Exam Q1
// Read and sort student records

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Constants

#define MAXNAME 40
#define MAXSTU  20
#define MAXLINE 100

// Student records
typedef struct _stu_rec {
	int   zid;
	char  name[MAXNAME];
	int   program;
	float wam;
} Student;

// Possible sort fields
typedef enum { BY_ZID, BY_NAME } Ordering;

// Helper functions
int readStudents(FILE *, Student *);
void sortStudents(Student *, int, Ordering);
void showStudents(FILE *, Student *, int);
void swap(Student *stu1, Student *stu2);

int main(int argc, char **argv)
{
	Student  students[MAXSTU]; // array of student records
	int      nstudes;          // # records filled in array
	Ordering order = BY_ZID;   // order by zid or name

	// handle optional command-line argument
	// default ordering is by zid
	if (argc > 1 && strcmp(argv[1],"name") == 0)
			order = BY_NAME;

	nstudes = readStudents(stdin, students);
	sortStudents(students, nstudes, order);
	showStudents(stdout, students, nstudes);
}

// Sort "n" records in the "stu" array by order
// Always in ascending order
// If order == BY_ZID, sort numerically on unique "zid" field
// If order == BY_NAME, sort lexicographically on "name" field
//    if names are equal, sort in ascending order on "zid" field
void sortStudents(Student *stu, int n, Ordering order)
{
	// TODO
	if (order ==BY_ZID) {
	    for (int i = 0; i < n; i++) {
	        int min = i;
	        for (int j = i + 1; j < n; j++) {
	            if (stu[j].zid < stu[min].zid)
	                min = j;
	        }
        	swap(&stu[i], &stu[min]);
	    }
	} else {
	    for (int i = 0; i < n; i++) {
	        int min = i;
	        for (int j = i + 1; j < n; j++) {
	            if (strcmp(stu[j].name, stu[min].name) < 0)
	                min = j;
	        }
        	swap(&stu[i], &stu[min]);
	    }
	    for (int i = 0; i < n; i++) {
	        int num_same = 0;
	        for (num_same = i + 1; num_same < n; num_same++) {
	            if (strcmp(stu[num_same].name, stu[i].name) == 0) 
                    continue;
	            else
	                break;
	        }
	        num_same--;
	        for (int k = i; k < num_same; k++, i++) {
	            int min = k;
	            for (int j = k + 1; j <= num_same; j++) {
	                if (stu[j].zid < stu[min].zid)
	                    min = j;
	            }
            	swap(&stu[k], &stu[min]);
	        }
	    }
	}
}

// Read student records from file "in"
// Read into array of student records "stu"
// Returns number of records read
int readStudents(FILE *in, Student *stu)
{
	char line[MAXLINE];
	int  n, nread = 0;

	while (fgets(line, MAXLINE, in) != NULL) {
		// pointer to current student record
		Student *s = &stu[nread];
		n = sscanf(line, "%d:%[^:]:%d:%f", 
		           &(s->zid), &(s->name[0]), &(s->program), &(s->wam));
		if (n != 4) {
			fprintf(stderr, "Bad input: %s", line);
			exit(1);
		}
		nread++;
	}
	return nread;
}

// Print student info on standard output
// Info comes from array "stu" of student records
//   which contains "n" entries
void showStudents(FILE *out, Student *stu, int n)
{
	for (int i = 0; i < n; i++) {
		// pointer to current student record
		Student *s = &stu[i];
			// should use MAXNAME, rather than 40
		fprintf(out, "%-7d %-40s %04d %0.1f\n",
		        s->zid, s->name, s->program, s->wam);
	}
}


//swap the values in array
void swap(Student *stu1, Student *stu2) {
    int tmp_zid = stu1->zid;
	char *tmp_name = malloc(200);
	strcpy(tmp_name, stu1->name);
	int tmp_program = stu1->program;
	float tmp_wam = stu1->wam;
	stu1->zid = stu2->zid;
	strcpy(stu1->name, stu2->name);
	stu1->program = stu2->program;
	stu1->wam = stu2->wam;
	stu2->zid = tmp_zid;
	strcpy(stu2->name, tmp_name);
	stu2->program = tmp_program;
	stu2->wam = tmp_wam;
	free(tmp_name);
}

