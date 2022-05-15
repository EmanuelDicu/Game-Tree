#ifndef UTILITY12_H_
#define UTILITY12_H_

struct node_task_12 {
    int table[3][3];
    int nr_sons;
    int winning_state;
    struct node_task_12 **sons;
};
typedef struct node_task_12 NodeTask12;

int char_to_ternar(char x);
char ternar_to_char(int x);
NodeTask12* read_start_configuration(FILE *in_file, int *start_player);
void get_and_or(NodeTask12 *node, int start_player, int player);
int check_end_state(int table[3][3]);
int check_winning_state(int table[3][3], int player);
void solve_12(NodeTask12 *node, int start_player, int player);
NodeTask12* new_NodeTask12(void);
void clear_tree_12(NodeTask12 *node);

#endif