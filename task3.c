#include <stdio.h>

#include "task3.h"
#include "utility3.h"

// functie care afiseaza solutia pentru taskul 3
void print_solution_3(FILE *out_file, NodeTask3 *node, int nr_tabs) {
    int i;
    // identarea corespunzatoare
    for (i = 0; i < nr_tabs; ++i)
        fprintf(out_file, "\t");
    fprintf(out_file, "%d\n", node->minimax);
    for (i = 0; i < node->nr_sons; ++i) // apel recursiv catre starile urmatoare
        print_solution_3(out_file, node->sons[i], nr_tabs + 1);
}

// functie care rezolva taskul 3
void solve_task_3(FILE *in_file, FILE *out_file) {
    int max_level;
    fscanf(in_file, "%d", &max_level);
    NodeTask3 *root = read_start_tree(in_file); // citesc si construiesc arborele minimax
    solve_3(root, 1); // implementez algoritmul minimax pe arborele de mai sus
    print_solution_3(out_file, root, 0); // afisez solutia
    clear_tree_3(root); // eliberez toata memoria
}
