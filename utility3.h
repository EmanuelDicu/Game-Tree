#ifndef UTILITY3_H_
#define UTILITY3_H_

struct node_task_3 {
    int minimax;
    int nr_sons;
    struct node_task_3 **sons;
};
typedef struct node_task_3 NodeTask3;

struct list_node {
    NodeTask3 *tree_node;
    struct list_node *next;
};
typedef struct list_node ListNode; 

struct queue {
    ListNode *start, *end;
};
typedef struct queue Queue;

ListNode* new_ListNode(NodeTask3 *tree_node);
Queue* new_Queue(void);
Queue* enqueue(Queue *queue, NodeTask3 *tree_node);
int empty_queue(Queue *queue);
Queue* dequeue(Queue *queue);
NodeTask3* get_start(Queue *queue);
void clear(Queue *queue);
NodeTask3* new_NodeTask3(void);
NodeTask3* read_start_tree(FILE *in_file);
void clear_tree_3(NodeTask3 *node);
void solve_3(NodeTask3 *node, int level);

#endif