#ifndef ORDER_H
#define ORDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STATUS_PENDING 1
#define STATUS_PREPARING 2
#define STATUS_READY 3
#define STATUS_COMPLETED 4
#define STATUS_CANCELLED 5

// Menu item structure
typedef struct {
    char code[10];
    char name[50];
    float price;
} MenuItem;

typedef struct {
    char code[10];
    char name[30];
    int quantity;
    float price;
    float total;
} OrderItem;

// Lesson 3.1: Self-referential structure (Node)
// This allows the creation of a Singly Linked List
typedef struct OrderNode {
    int order_id;
    char timestamp[25];
    char prepared_timestamp[25];
    char ready_timestamp[25];
    char pickup_timestamp[25];
    OrderItem items[50];
    int item_count;
    float grand_total;
    int status;
    struct OrderNode *next; // The pointer to the next node in the sequence
} OrderNode;

// Lesson 5: Queue Structure (Linked Representation)
// Uses pointers to the front and rear to maintain FIFO logic
typedef struct {
    OrderNode *front; // Points to the first node to be removed
    OrderNode *rear;  // Points to the last node added
    int count;        // Total number of nodes in the queue
} Queue;

// Global External Variables
extern Queue g_pending, g_preparing, g_ready;
extern OrderNode *g_history_head;
extern int next_id;
extern int pending_count, preparing_count, ready_count, completed_count, history_count;

// Screen utilities
void clear_screen(void);
void press_enter(void);

// Timestamp utilities
void get_timestamp(char *buffer, size_t size);

// Menu utilities
MenuItem* find_menu_item(const char *code);
void display_menu(void);
void show_menu(void);

// Order node utilities
OrderNode* create_order_node(void);
int get_next_id(void);
void print_timestamps(OrderNode *order);
void print_order_summary(OrderNode *order);

// Queue operations
OrderNode* queue_find_by_id(Queue *queue, int id);
void queue_remove_node(Queue *queue, int id);
void queue_enqueue(Queue *queue, OrderNode *node);
void queue_sort_by_id(Queue *queue);
void queue_sort_by_timestamp(Queue *queue);

// History linked list operations
void history_append(OrderNode **head, OrderNode *node);
OrderNode* history_find_by_id(OrderNode **head, int id);
OrderNode** get_history_head(void);

// Main functions from individual files
void add_order(void);
void show_dashboard(void);
void order_preparing(void);
void order_ready(void);
void order_pickup(void);
void search_order_by_id(void);
void sort_display(void);
void show_history(void);
void show_exit(void);

// Count update
void update_counts(void);

#endif