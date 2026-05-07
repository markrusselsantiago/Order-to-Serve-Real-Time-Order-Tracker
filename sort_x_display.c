// Sort and display orders.
// This file sorts any of the three active queues by order ID or timestamp using bubble sort.
// After sorting, all orders in the selected queue are displayed.

#include "order.h"

// Helper: print all orders in a queue after sorting.
static void display_sorted_queue(Queue *q, const char *stage_name) {
    printf("+==================================================================================+\n");
    printf("|  %-80s|\n", stage_name);
    printf("+==================================================================================+\n");

    if (q->count == 0) {
        printf("\n>>  NO ORDERS IN THIS STAGE.\n\n");
        printf("+==================================================================================+\n");
        return;
    }

    printf("| %-6s | %-19s | %-10s | %-14s |\n",
           "ID", "TIMESTAMP", "TOTAL", "STATUS");
    printf("+==================================================================================+\n");

    OrderNode *cur = q->front;
    while (cur != NULL) {
        const char *status_str = "PENDING";
        if (cur->status == STATUS_PREPARING) status_str = "PREPARING";
        else if (cur->status == STATUS_READY) status_str = "READY";

        printf("| #%-3d | %-19s | P%-9.2f | %-14s |\n",
               cur->order_id, cur->timestamp, cur->grand_total, status_str);
        cur = cur->next;
    }
    printf("+==================================================================================+\n");
}

void sort_display(void) {
    clear_screen();

    printf("+==================================================================================+\n");
    printf("|                              SORT & DISPLAY ORDERS                               |\n");
    printf("+==================================================================================+\n");

    // Choose which queue to sort.
    printf("\n");
    printf("    SELECT QUEUE TO SORT AND DISPLAY:\n");
    printf("\n");
    printf("    [1] Pending Orders    (%d orders)\n", pending_count);
    printf("    [2] Preparing Orders  (%d orders)\n", preparing_count);
    printf("    [3] Ready Orders      (%d orders)\n", ready_count);
    printf("    [4] All Active Orders\n");
    printf("    [0] Back to Main Menu\n");
    printf("\n    Enter your choice: ");

    int queue_choice;
    if (scanf("%d", &queue_choice) != 1) queue_choice = -1;
    if (queue_choice == 0) return;

    // Choose sort key.
    printf("\n");
    printf("    SORT BY:\n");
    printf("\n");
    printf("    [1] Order ID (Ascending)\n");
    printf("    [2] Timestamp (Ascending)\n");
    printf("\n    Enter your choice: ");

    int sort_choice;
    if (scanf("%d", &sort_choice) != 1) sort_choice = 1;

    clear_screen();

    printf("+==================================================================================+\n");
    if (sort_choice == 1)
        printf("|                   SORTED BY ORDER ID (ASCENDING) -- BUBBLE SORT                  |\n");
    else
        printf("|                  SORTED BY TIMESTAMP (ASCENDING) -- BUBBLE SORT                  |\n");
    printf("+==================================================================================+\n");
    printf("\n");

    // Apply bubble sort and display the selected queue.
    if (queue_choice == 1 || queue_choice == 4) {
        if (sort_choice == 1) queue_sort_by_id(&g_pending);
        else                  queue_sort_by_timestamp(&g_pending);
        display_sorted_queue(&g_pending, "PENDING ORDERS");
        printf("\n");
    }

    if (queue_choice == 2 || queue_choice == 4) {
        if (sort_choice == 1) queue_sort_by_id(&g_preparing);
        else                  queue_sort_by_timestamp(&g_preparing);
        display_sorted_queue(&g_preparing, "PREPARING ORDERS");
        printf("\n");
    }

    if (queue_choice == 3 || queue_choice == 4) {
        if (sort_choice == 1) queue_sort_by_id(&g_ready);
        else                  queue_sort_by_timestamp(&g_ready);
        display_sorted_queue(&g_ready, "READY TO PICK UP ORDERS");
        printf("\n");
    }

    press_enter();
}