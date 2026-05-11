// utils.c
// Utility functions for queue operations, menu management, history handling, and system helpers

#include "order.h"
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// ===== GLOBAL VARIABLES =====
Queue g_pending = {NULL, NULL, 0};
Queue g_preparing = {NULL, NULL, 0};
Queue g_ready = {NULL, NULL, 0};
OrderNode *g_history_head = NULL;
int next_id = 1;
int pending_count = 0;
int preparing_count = 0;
int ready_count = 0;
int completed_count = 0;
int history_count = 0;

// Menu items database
MenuItem menu_items[] = {
    {"G1", "Hita Inasal", 100.00},
    {"G2", "Pitso Inasal", 105.00},
    {"G3", "Porkchop Inasal", 105.00},
    {"S1", "Sisig Platter", 190.00},
    {"S2", "Sizzling Pusit Platter", 230.00},
    {"S3", "Fried Tilapia", 90.00},
    {"S4", "Asado Shrimp", 225.00},
    {"S5", "Fish Steak", 100.00},
    {"S6", "Adobong Pusit", 100.00},
    {"B1", "Tapsilog", 85.00},
    {"B2", "Tocilog", 75.00},
    {"B3", "Longsilog", 70.00},
    {"B4", "Bangsilog", 85.00},
    {"B5", "Hamsilog", 65.00},
    {"B6", "Hotsilog", 60.00},
    {"N1", "Spaghetti", 60.00},
    {"N2", "Palabok", 65.00},
    {"N3", "Carbonara", 75.00},
    {"N4", "Lomi", 70.00},
    {"E1", "Softdrinks", 20.00},
    {"E2", "Halo Halo", 45.00},
    {"", "", 0}};

// ===== SCREEN UTILITIES =====
void clear_screen(void)
{
    system("cls");
}

void press_enter(void)
{
    printf("\n    Press Enter to continue...");
    while (getchar() != '\n')
        ;
    getchar();
}

// ===== TIMESTAMP UTILITIES =====
void get_timestamp(char *buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", timeinfo);
}

// ===== MENU UTILITIES =====
MenuItem *find_menu_item(const char *code)
{
    for (int i = 0; menu_items[i].code[0] != '\0'; i++)
    {
        if (strcmp(menu_items[i].code, code) == 0)
        {
            return &menu_items[i];
        }
    }
    return NULL;
}

// Convert the first character to uppercase
void convrtUp(char *input) {
    for (int i = 0; input[i] != '\0'; i++) {  // 'i' starts at 0 and goes up 0, 1, 2... until it hits the end of the string ('\0')
        input[i] = toupper(input[i]);
    }
}

void display_menu(void)
{
    show_menu();
}

// ===== ORDER NODE UTILITIES =====
OrderNode *create_order_node(void)
{
    OrderNode *node = (OrderNode *)malloc(sizeof(OrderNode));
    if (node)
    {
        node->order_id = 0;
        strcpy(node->timestamp, "");
        strcpy(node->prepared_timestamp, "");
        strcpy(node->ready_timestamp, "");
        strcpy(node->pickup_timestamp, "");
        node->item_count = 0;
        node->grand_total = 0.0;
        node->status = STATUS_PENDING;
        node->next = NULL;
    }
    return node;
}

int get_next_id(void)
{
    return next_id++;
}

void print_timestamps(OrderNode *order)
{
    printf("\n    Timestamps:\n");
    printf("    - Order Placed   : %s\n", order->timestamp);
    if (order->prepared_timestamp[0] != '\0')
        printf("    - Preparing      : %s\n", order->prepared_timestamp);
    if (order->ready_timestamp[0] != '\0')
        printf("    - Ready          : %s\n", order->ready_timestamp);
    if (order->pickup_timestamp[0] != '\0')
        printf("    - Picked Up      : %s\n", order->pickup_timestamp);
}

void print_order_summary(OrderNode *order)
{
    printf("\n    Order Summary:\n");
    printf("    Order ID   : #%03d\n", order->order_id);
    printf("    Total Items: %d\n", order->item_count);
    printf("    Grand Total: P%.2f\n", order->grand_total);
}

// ===== QUEUE OPERATIONS =====
// Find order by ID in queue using linear search
OrderNode *queue_find_by_id(Queue *queue, int id)
{
    OrderNode *cur = queue->front;
    while (cur != NULL)
    {
        if (cur->order_id == id)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// Remove a specific node from queue by ID
void queue_remove_node(Queue *queue, int id)
{
    if (queue->front == NULL)
        return;

    // If the front node is the one to remove
    if (queue->front->order_id == id)
    {
        OrderNode *temp = queue->front;
        queue->front = queue->front->next;
        if (queue->front == NULL)
        {
            queue->rear = NULL;
        }
        queue->count--;
        return;
    }

    // Otherwise, search through the list
    OrderNode *prev = queue->front;
    OrderNode *cur = queue->front->next;

    while (cur != NULL)
    {
        if (cur->order_id == id)
        {
            prev->next = cur->next;
            if (cur == queue->rear)
            {
                queue->rear = prev;
            }
            queue->count--;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

// Add node to rear of queue
void queue_enqueue(Queue *queue, OrderNode *node)
{
    if (!node)
        return;

    node->next = NULL;

    if (queue->rear == NULL)
    {
        // Queue is empty
        queue->front = queue->rear = node;
    }
    else
    {
        // Add to rear
        queue->rear->next = node;
        queue->rear = node;
    }
    queue->count++;
}

// Bubble sort queue by order ID (ascending)
void queue_sort_by_id(Queue *queue)
{
    if (queue->count <= 1)
        return;

    int swapped;
    OrderNode *ptr1;
    OrderNode *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = queue->front;

        while (ptr1->next != lptr)
        {
            if (ptr1->order_id > ptr1->next->order_id)
            {
                // Swap data
                int temp_id = ptr1->order_id;
                char temp_timestamp[25];
                char temp_prepared[25];
                char temp_ready[25];
                char temp_pickup[25];
                OrderItem temp_items[50];
                int temp_item_count = ptr1->item_count;
                float temp_total = ptr1->grand_total;
                int temp_status = ptr1->status;

                strcpy(temp_timestamp, ptr1->timestamp);
                strcpy(temp_prepared, ptr1->prepared_timestamp);
                strcpy(temp_ready, ptr1->ready_timestamp);
                strcpy(temp_pickup, ptr1->pickup_timestamp);
                memcpy(temp_items, ptr1->items, sizeof(OrderItem) * 50);

                ptr1->order_id = ptr1->next->order_id;
                strcpy(ptr1->timestamp, ptr1->next->timestamp);
                strcpy(ptr1->prepared_timestamp, ptr1->next->prepared_timestamp);
                strcpy(ptr1->ready_timestamp, ptr1->next->ready_timestamp);
                strcpy(ptr1->pickup_timestamp, ptr1->next->pickup_timestamp);
                memcpy(ptr1->items, ptr1->next->items, sizeof(OrderItem) * 50);
                ptr1->item_count = ptr1->next->item_count;
                ptr1->grand_total = ptr1->next->grand_total;
                ptr1->status = ptr1->next->status;

                ptr1->next->order_id = temp_id;
                strcpy(ptr1->next->timestamp, temp_timestamp);
                strcpy(ptr1->next->prepared_timestamp, temp_prepared);
                strcpy(ptr1->next->ready_timestamp, temp_ready);
                strcpy(ptr1->next->pickup_timestamp, temp_pickup);
                memcpy(ptr1->next->items, temp_items, sizeof(OrderItem) * 50);
                ptr1->next->item_count = temp_item_count;
                ptr1->next->grand_total = temp_total;
                ptr1->next->status = temp_status;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Bubble sort queue by timestamp (ascending)
void queue_sort_by_timestamp(Queue *queue)
{
    if (queue->count <= 1)
        return;

    int swapped;
    OrderNode *ptr1;
    OrderNode *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = queue->front;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->timestamp, ptr1->next->timestamp) > 0)
            {
                // Swap data
                int temp_id = ptr1->order_id;
                char temp_timestamp[25];
                char temp_prepared[25];
                char temp_ready[25];
                char temp_pickup[25];
                OrderItem temp_items[50];
                int temp_item_count = ptr1->item_count;
                float temp_total = ptr1->grand_total;
                int temp_status = ptr1->status;

                strcpy(temp_timestamp, ptr1->timestamp);
                strcpy(temp_prepared, ptr1->prepared_timestamp);
                strcpy(temp_ready, ptr1->ready_timestamp);
                strcpy(temp_pickup, ptr1->pickup_timestamp);
                memcpy(temp_items, ptr1->items, sizeof(OrderItem) * 50);

                ptr1->order_id = ptr1->next->order_id;
                strcpy(ptr1->timestamp, ptr1->next->timestamp);
                strcpy(ptr1->prepared_timestamp, ptr1->next->prepared_timestamp);
                strcpy(ptr1->ready_timestamp, ptr1->next->ready_timestamp);
                strcpy(ptr1->pickup_timestamp, ptr1->next->pickup_timestamp);
                memcpy(ptr1->items, ptr1->next->items, sizeof(OrderItem) * 50);
                ptr1->item_count = ptr1->next->item_count;
                ptr1->grand_total = ptr1->next->grand_total;
                ptr1->status = ptr1->next->status;

                ptr1->next->order_id = temp_id;
                strcpy(ptr1->next->timestamp, temp_timestamp);
                strcpy(ptr1->next->prepared_timestamp, temp_prepared);
                strcpy(ptr1->next->ready_timestamp, temp_ready);
                strcpy(ptr1->next->pickup_timestamp, temp_pickup);
                memcpy(ptr1->next->items, temp_items, sizeof(OrderItem) * 50);
                ptr1->next->item_count = temp_item_count;
                ptr1->next->grand_total = temp_total;
                ptr1->next->status = temp_status;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// ===== HISTORY LINKED LIST OPERATIONS =====
// Append order node to history linked list
void history_append(OrderNode **head, OrderNode *node)
{
    if (!node)
        return;

    if (*head == NULL)
    {
        *head = node;
        node->next = NULL;
    }
    else
    {
        OrderNode *cur = *head;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = node;
        node->next = NULL;
    }
    history_count++;
    completed_count++;
}

// Find order in history by ID using linear search
OrderNode *history_find_by_id(OrderNode **head, int id)
{
    OrderNode *cur = *head;
    while (cur != NULL)
    {
        if (cur->order_id == id)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// Get proper reference for history operations
OrderNode **get_history_head(void)
{
    return &g_history_head;
}

// Update count variables based on queue states
void update_counts(void)
{
    pending_count = g_pending.count;
    preparing_count = g_preparing.count;
    ready_count = g_ready.count;
}
