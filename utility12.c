#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utility12.h"

// functie care converteste un char intr-un numar in baza 3
int char_to_ternar(char x) {
    if (x == 'X') // lui X ii corespunde 1
        return 1;
    else if (x == 'O') // lui O ii corespunde 
        return 0;
    else if (x == '-') // unui element liber ii corespunde -1
        return -1;
    else
        return -2; // eroare
}

// functie care converteste un numar in baza 3 intr-un char
char ternar_to_char(int x) {
    if (x == 1) // lui 1 ii corespunde X
        return 'X'; 
    else if (x == 0) // lui O ii corespunde 0
        return 'O';
    else if (x == -1) // unei pozitii goale ii corespunde -1
        return '-';
    else
        return -2; // eroare
}

// functie care citeste o configuratie initiala a tablei de X si O
NodeTask12* read_start_configuration(FILE *in_file, int *start_player) {
    char aux;

    // citesc cine incepe si creez nodul radacina
    fscanf(in_file, "%c\n", &aux);
    *start_player = char_to_ternar(aux);
    NodeTask12 *root = new_NodeTask12();

    int i, j; // citesc starea initiala a tablei de X si O
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            fscanf(in_file, "%c \n", &aux);
            root->table[i][j] = char_to_ternar(aux);
        }
    }
    return root;
}

// functie care in functie de jucatorul care e la mutare,
// verifica daca jucatorul initial este intr-o stare de pierdere sau castig
void get_and_or(NodeTask12 *node, int start_player, int player) {
    if (start_player == player) { 
        // daca eu sunt la mutare, atunci pot sa ma duc in orice stare de castig
        node->winning_state = 0;
        int i;
        for (i = 0; i < node->nr_sons; ++i) { 
            // daca pot sa ma duc intr-o stare de castig
            // atunci nodul curent (starea curenta) este de castig
            if (node->sons[i]->winning_state == 1) {
                node->winning_state = 1;
                break;
            }
        }
    } else { 
        // daca adversarul este la mutare, ca eu sa castig trebuie ca toate starile in care
        // poate sa mute adversarul sa fie de castig pentru mine
        node->winning_state = 1;
        int i;
        for (i = 0; i < node->nr_sons; ++i) { 
            // daca adversarul poate sa ma forteze intr-o stare de pierdere
            // atunci nodul curent (starea curenta) este de pierdere
            if (node->sons[i]->winning_state == 0) {
                node->winning_state = 0;
                break;
            }
        }
    }
}

// verific daca o tabla de X si O reprezinta o stare finala sau nu
// (3 la fel pe linie/coloana/diagonala sau matricea este plina)
int check_end_state(int table[3][3]) {
// verific liniile
    if ((table[0][0] == table[0][1] && table[0][1] == table[0][2] && table[0][2] >= 0) ||
        (table[1][0] == table[1][1] && table[1][1] == table[1][2] && table[1][2] >= 0) ||
        (table[2][0] == table[2][1] && table[2][1] == table[2][2] && table[2][2] >= 0))
        return 1;
// verific coloanele
    if ((table[0][0] == table[1][0] && table[1][0] == table[2][0] && table[2][0] >= 0) ||
        (table[0][1] == table[1][1] && table[1][1] == table[2][1] && table[2][1] >= 0) ||
        (table[0][2] == table[1][2] && table[1][2] == table[2][2] && table[2][2] >= 0))
        return 1;
// verific diagonalele
    if ((table[0][0] == table[1][1] && table[1][1] == table[2][2] && table[2][2] >= 0) ||
        (table[0][2] == table[1][1] && table[1][1] == table[2][0] && table[2][0] >= 0))
        return 1;
// verific daca e plina matricea
    int ok = 1, i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            if (table[i][j] < 0)
                ok = 0;
    if (ok)
        return 1;
// daca nu, atunci inca pot muta
    return 0;
}

// functie care primeste o stare a unei table de X si O si un jucator si spune daca
// tabla reprezinta o stare terminala de castig pentru acest jucator
int check_winning_state(int table[3][3], int player) {
// verific liniile
    if ((table[0][0] == table[0][1] && table[0][1] == table[0][2] && table[0][2] == player) || 
        (table[1][0] == table[1][1] && table[1][1] == table[1][2] && table[1][2] == player) || 
        (table[2][0] == table[2][1] && table[2][1] == table[2][2] && table[2][2] == player))
        return 1;
// verific coloanele
    if ((table[0][0] == table[1][0] && table[1][0] == table[2][0] && table[2][0] == player) ||
        (table[0][1] == table[1][1] && table[1][1] == table[2][1] && table[2][1] == player) ||
        (table[0][2] == table[1][2] && table[1][2] == table[2][2] && table[2][2] == player))
        return 1;
// verific diagonalele
    if ((table[0][0] == table[1][1] && table[1][1] == table[2][2] && table[2][2] == player) ||
        (table[0][2] == table[1][1] && table[1][1] == table[2][0] && table[2][0] == player))
        return 1;
// daca nu, atunci fie inca pot muta, fie e stare de pierdere / remiza
    return 0;
}

// functie care construieste arborele de joc si executa algoritmul SI/SAU
void solve_12(NodeTask12 *node, int start_player, int player) {
    if (!check_end_state(node->table)) { // daca nodul curent nu este o stare terminala
        int i, j, cnt;
        // calculez numarul de fii (numarul de elemente libere din tabla corespunzatoare starii curente)
        for (i = 0; i < 3; ++i)
            for (j = 0; j < 3; ++j) 
                if (node->table[i][j] == -1)
                    ++(node->nr_sons);
        // aloc dinamic memoria pentru fii
        node->sons = (NodeTask12**) malloc(node->nr_sons * sizeof(NodeTask12*)); 
        for (i = 0, cnt = 0; i < 3; ++i) {
            for (j = 0; j < 3; ++j) {
                if (node->table[i][j] == -1) {
                    node->sons[cnt] = new_NodeTask12(); // creez starile corespunzatoare fiilor
                    memcpy(node->sons[cnt]->table, node->table, sizeof(node->table));
                    node->sons[cnt]->table[i][j] = player;
                    solve_12(node->sons[cnt], start_player, player ^ 1); // construiesc recursiv arborele de joc
                    ++cnt;
                }
            }
        }
        get_and_or(node, start_player, player); // execut algoritmul SI/SAU ca sa vad daca pierd sau castig
    } else { // altfel vad daca nodul curent este o stare de castig sau nu pentru mine (start_player)
        node->winning_state = check_winning_state(node->table, start_player);
    }
}

// functie care creeaza un nod din arborele de joc (taskurile 1 si 2)
NodeTask12* new_NodeTask12(void) {
    NodeTask12 *node = (NodeTask12*) malloc(sizeof(NodeTask12));
    memset(node->table, 0, sizeof(node->table));
    node->nr_sons = 0;
    node->winning_state = 0;
    node->sons = NULL;
    return node;
}

// functie care elibereaza memoria dintr-un arbore de joc
void clear_tree_12(NodeTask12 *node) {
    int i;
    for (i = 0; i < node->nr_sons; ++i)
        clear_tree_12(node->sons[i]); // eliberez memoria recursiv
    free(node->sons);
    free(node); // eliberez memoria pentru nod
}