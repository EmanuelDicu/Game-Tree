#include <stdio.h>

#include "task2.h"
#include "utility12.h"

// functie care afiseaza solutia pentru taskul 2
void print_solution_2(FILE *out_file, NodeTask12 *node, int nr_tabs) {
    int i;
    // identez corespunzator
    for (i = 0; i < nr_tabs; ++i)
        fprintf(out_file, "\t");
    fprintf(out_file, "%c\n", node->winning_state ? 'T' : 'F');
    for (i = 0; i < node->nr_sons; ++i) // apel recursiv catre starile urmatoare
        print_solution_2(out_file, node->sons[i], nr_tabs + 1);
}

void solve_task_2(FILE *in_file, FILE *out_file) {
    int start_player;
    NodeTask12 *root = read_start_configuration(in_file, &start_player); // citesc configuratia initiala
    solve_12(root, start_player, start_player); // construiesc arborele de joc (si arborele si|sau)
    print_solution_2(out_file, root, 0); // afisez solutia
    clear_tree_12(root); // eliberez toata memoria
}