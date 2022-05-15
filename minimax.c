#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utility12.h"
#include "utility3.h"

#include "task1.h"
#include "task2.h"
#include "task3.h"

int main(int argc, char *argv[]) {
    // citesc fisierele
    FILE *in_file = fopen(argv[2], "r");
    FILE *out_file = fopen(argv[3], "w");
    // vad care cerinta trebuie rezolvata
    if (!strncmp(argv[1], "-c1", 3))
        solve_task_1(in_file, out_file);
    else if (!strncmp(argv[1], "-c2", 3))
        solve_task_2(in_file, out_file);
    else if (!strncmp(argv[1], "-c3", 3))
        solve_task_3(in_file, out_file);
    // inchid fisierele
    fclose(in_file);
    fclose(out_file);
    return 0;
}