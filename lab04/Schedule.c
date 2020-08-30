// Schedule ADT implementation

#include <stdio.h>
#include <stdlib.h>

#include "Schedule.h"
#include "Time.h"
#include "Tree.h"

struct schedule {
    Tree times;
    int  count;
};

// Creates a new schedule
Schedule ScheduleNew(void) {
    Schedule s = malloc(sizeof(*s));
    if (s == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    s->times = TreeNew();
    s->count = 0;
    return s;
}

// Frees all memory associated with a given schedule
void ScheduleFree(Schedule s) {
    TreeFree(s->times);
    free(s);
}

// Gets the number of times added to the schedule
int  ScheduleCount(Schedule s) {
    return s->count;
}

// Attempts to schedule a new landing time. Returns true if the time was
// successfully added, and false otherwise.
bool ScheduleAdd(Schedule s, Time t) {
    // TODO: Modify the following code

    Time n1 = TreeFloor(s->times, t);
    Time n2 = TreeCeiling(s->times, t);
    Time n3 = TimeAddMinutes(t, 10);
    Time n4 = TimeSubtractMinutes(t, 10);
    if (n1 == NULL && n2 == NULL) {
        TreeInsert(s->times, t);
        s->count++;
        return true;
    } else if (n1 == NULL) {
        if (TimeCmp(n2, n3) > 0) {
            TreeInsert(s->times, t);
            s->count++;
            return true;
        } else {
            return false;
        }
    } else if (n2 == NULL) {
         if (TimeCmp(n4, n1) > 0) {
            TreeInsert(s->times, t);
            s->count++;
            return true;
         } else {
            return false;
         }
    } else {
        if (TimeCmp(n4, n1) > 0 && TimeCmp(n2, n3) > 0) {
            TreeInsert(s->times, t);
            s->count++;
            return true;
        } else {
            return false;
        }
    }  
}

// Shows  all  the landing times in the schedule. If mode is 1, only the
// times are shown. If mode is 2, the underlying data structure is shown
// as well.
void ScheduleShow(Schedule s, int mode) {
    if (mode == 1) {
        TreeList(s->times);
    } else if (mode == 2) {
        TreeShow(s->times);
    }
}
