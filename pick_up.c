// Order picked up.
// This file marks an order as completed and moves it from the ready queue to history.
// It records the pick-up timestamp and uses linear search to find the order.

#include "order.h"

void order_pickup(void) {
    clear_screen();

    printf("+==================================================================================+\n");
    printf("|                                  PICK UP ORDER                                   |\n");
    printf("+==================================================================================+\n");

    int id;
    printf("    Enter Order ID (number only, e.g. 1234) or [0] to finish: ");
    if (scanf("%d", &id) != 1) {
        printf(">>  ERROR: INVALID INPUT.\n");
        while (getchar() != '\n'); // Clear input buffer
        press_enter();
        return;
    }

    if (id == 0) return;

    // Linear search in the ready queue (As per Searching_Sorting_Algo_Module.pdf)
    OrderNode *order = queue_find_by_id(&g_ready, id);

    if (!order) {
        printf(">>  NOT FOUND: ORDER #%03d IS NOT IN READY QUEUE.\n", id);
        press_enter();
        return;
    }

    printf(">>  RESULT FOUND!\n");

    // Show all timestamps and order summary using shared utility functions
    print_timestamps(order);
    print_order_summary(order);

    // Options.
    printf("\n");
    printf("    [1] Confirm Pick Up Order\n");
    printf("    [0] Cancel\n");
    printf("\n    Enter your choice: ");

    int choice;
    if (scanf("%d", &choice) != 1) choice = -1;

    if (choice == 1) {
        // 1. Remove from the ready queue (Unlink the node)
        queue_remove_node(&g_ready, id);

        // 2. Update status and record the pick-up timestamp
        get_timestamp(order->pickup_timestamp, sizeof(order->pickup_timestamp));
        order->status = STATUS_COMPLETED;

        // 3. Append to the history linked list (As per CC104-Linked_Lists_P1.pdf)
        history_append(&g_history_head, order);

        printf("+==================================================================================+\n");
        printf("|>> SUCCESS: ORDER #%03d HAS BEEN PICKED UP.                                        |\n", id);
        printf("+==================================================================================+\n");

    } else if (choice == 0) {
        // Cancel — ask for confirmation.
        char yn;
        printf("\n>>  WARNING: ARE YOU SURE YOU WANT TO CANCEL PICK UP FOR ORDER #%03d? (Y/N): ", id);
        scanf(" %c", &yn);

        if (yn == 'Y' || yn == 'y') {
            printf("\n>>  PICK UP FOR ORDER #%03d HAS BEEN CANCELLED. RETURNING TO MAIN MENU...\n", id);
        } else {
            // Restart function if user chooses 'N'
            order_pickup();
            return;
        }

    } else {
        printf(">>  INVALID CHOICE.\n");
    }

    // Wait for user before returning to dashboard
    printf("\n    Press Enter to continue...");
    while (getchar() != '\n'); getchar();
}