#include <stdio.h>
#include <stdlib.h>

#include "utility3.h"

// functie care creeaza un nod nou de lista
ListNode* new_ListNode(NodeTask3 *tree_node) { 
    ListNode *node = malloc(sizeof(ListNode));
    node->next = NULL;
    node->tree_node = tree_node;
    return node;
}

// functie care creeaza o noua coada
Queue* new_Queue(void) {
    Queue *queue = malloc(sizeof(Queue));
    queue->start = queue->end = NULL;
    return queue;
}

// functie care ataseaza la dreapta unei cozi un nou nod
Queue* enqueue(Queue *queue, NodeTask3 *tree_node) {
    ListNode *new_node = new_ListNode(tree_node);
    if (queue->start == NULL) 
        queue->start = queue->end = new_node;
    else {
        queue->end->next = new_node;
        queue->end = new_node;
    }
    return queue;
}

// functie care verifica daca o coada are dimensiunea nula
int empty_queue(Queue *queue) {
    return queue->start == NULL;
}

// functie care elimina primul element dintr-o coada
Queue* dequeue(Queue *queue) {
    if (queue->start == queue->end) {
        free(queue->start);
        queue->start = queue->end = NULL;  
    } else {
        ListNode *aux_node = queue->start;
        queue->start = queue->start->next;
        free(aux_node);
    }
    return queue;
}

// functie care gaseste primul element dintr-o coada
NodeTask3* get_start(Queue *queue) {
    return queue->start->tree_node;
}

// functie care goleste o coada
void clear(Queue *queue) {
    while (!empty_queue(queue))
        dequeue(queue);
    free(queue);
}

// functie care creeaza un nod nou pentru taskul 3
NodeTask3* new_NodeTask3(void) {
    NodeTask3 *node = (NodeTask3*) malloc(sizeof(NodeTask3));
    node->minimax = 0;
    node->nr_sons = 0;
    node->sons = NULL;
    return node;
}

// functie care citeste si construieste arborele minimax
NodeTask3* read_start_tree(FILE *in_file) {
    char str[100];
    NodeTask3 *root = new_NodeTask3(); // nodul radacina
    Queue *queue = new_Queue();
    enqueue(queue, root); // adaug nodul radacina intr-o coada
    while (!empty_queue(queue)) { // cat timp am elemente in coada
        NodeTask3 *node = get_start(queue); // extrag primul nod din coada
        dequeue(queue);
        fscanf(in_file, "%s", str); // ii citesc valoarea corespunzatoare
        int nr = atoi(str + 1);
        if (str[0] == '[') {
            // daca este nod frunza atunci nu are fii, iar valoarea minimax este
            // data de numarul dintre paranteze
            node->minimax = nr;
        } else {
            // daca nu, atunci valoarea dintre paranteze indica numarul de fii 
            // ai nodului curent
            node->sons = (NodeTask3**) malloc(nr * sizeof(NodeTask3*)); // aloc dinamic fii nodului curent
            node->nr_sons = nr;
            int i;
            for (i = 0; i < nr; ++i) {
                // pe care mai apoi ii inserez in coada pentru a putea
                // ca sa poata fi procesati ulterior
                node->sons[i] = new_NodeTask3(); 
                enqueue(queue, node->sons[i]);
            }
        }
    }
    free(queue); // eliberez coada
    return root;
}

// functie care elibereaza (recursiv) memoria alocata pentru arborele minimax
void clear_tree_3(NodeTask3 *node) {
    int i;
    for (i = 0; i < node->nr_sons; ++i)
        clear_tree_3(node->sons[i]); // eliberez recursiv memoria alocata pentru fii
    if (node->sons != NULL) 
        free(node->sons);
    free(node); // eliberez memoria alocata pentru nod
}

// functie care executa algoritmul minimax pe un arbore
void solve_3(NodeTask3 *node, int level) {
    if (!node->nr_sons) // daca este nod frunza
        return; // ies din recursivitate
    int i;
    for (i = 0; i < node->nr_sons; ++i) { // altfel parcurg recursiv
        solve_3(node->sons[i], level + 1);
        if (i == 0) // daca este primul fiu, initializez valoarea minimax din nod cu valoarea fiului
            node->minimax = node->sons[i]->minimax;
        else if ((level & 1) && node->minimax < node->sons[i]->minimax) // daca ma situez pe nivel impar (max)
            node->minimax = node->sons[i]->minimax;
        else if (!(level & 1) && node->minimax > node->sons[i]->minimax) // daca ma situez pe nivel par (min)
            node->minimax = node->sons[i]->minimax;
    }    
}