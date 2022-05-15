#include <stdio.h>

#include "task1.h"
#include "utility12.h"

// functie care afiseaza solutia pentru primul task
void print_solution_1(FILE *out_file, NodeTask12 *node, int nr_tabs) {
    int i, j;
    // afisarea matricei in formatul corespunzator
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < nr_tabs; ++j)
            fprintf(out_file, "\t");
        for (j = 0; j < 3; ++j) {
            fprintf(out_file, "%c", ternar_to_char(node->table[i][j]));
            if (j < 2)
                fprintf(out_file, " ");
            else
                fprintf(out_file, "\n");
        }
    }
    fprintf(out_file, "\n");
    for (i = 0; i < node->nr_sons; ++i) // apel recursiv catre starile urmatoare
        print_solution_1(out_file, node->sons[i], nr_tabs + 1);
}

// functie care rezolva primul task
void solve_task_1(FILE *in_file, FILE *out_file) {
    int start_player;
    NodeTask12 *root = read_start_configuration(in_file, &start_player); // citesc configuratia initiala
    solve_12(root, start_player, start_player); // calculez arborele de joc (tabla + arborele si|sau)
    print_solution_1(out_file, root, 0); // afisez solutia
    clear_tree_12(root); // eliberez toata memoria
}