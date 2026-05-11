// This file moves an order from the preparing queue to the ready queue.
// It records the ready timestamp and uses linear search to find the order.

#include "order.h"

// Note: These functions (clear_screen, queue_find_by_id, etc.)
// should be defined in your utility or main files.

void order_ready(void) {
    clear_screen();

    printf("+==================================================================================+\n");
    printf("|                            MOVE ORDER TO READY                                   |\n");
    printf("+==================================================================================+\n");

    int id;
    printf("    Enter Order ID (number only, e.g. 1234) or [0] to finish: #");
    if (scanf("%d", &id) != 1) {
        printf(">>  ERROR: INVALID INPUT.\n");
        while (getchar() != '\n')
            ; // Clear input buffer
        return;
    }

    if (id == 0)
        return;

    // Linear search in the preparing queue (using the global variable from order.h)
    OrderNode *order = queue_find_by_id(&g_preparing, id);

    if (!order) {
        printf(">>  NOT FOUND: ORDER #%03d IS NOT IN PREPARING QUEUE.\n", id);
        printf("\n    Press Enter to return...");
        while (getchar() != '\n')
            ;
        getchar();
        return;
    }

    printf(">>  RESULT FOUND!\n");

    // Show timestamps and order summary using existing helper functions
    print_timestamps(order);
    print_order_summary(order);

    // Options.
    printf("\n");
    printf("    [1] Confirm Move Order to Ready\n");
    printf("    [0] Cancel\n");
    printf("\n    Enter your choice: ");

    int choice;
    if (scanf("%d", &choice) != 1)
        choice = -1;

    if (choice == 1) {
        // 1. Remove the specific node from the preparing queue
        queue_remove_node(&g_preparing, id);

        // 2. Update the timestamp and status
        get_timestamp(order->ready_timestamp, sizeof(order->ready_timestamp));
        order->status = STATUS_READY;

        // 3. Add to the ready queue
        queue_enqueue(&g_ready, order);

        printf("+==================================================================================+\n");
        printf("|>> SUCCESS: ORDER #%03d HAS BEEN MOVED TO READY.                                   |\n", id);
        printf("+==================================================================================+\n");
    }
    else if (choice == 0) {
        char yn;
        printf("\n>>  WARNING: ARE YOU SURE YOU WANT TO CANCEL MOVING ORDER #%03d TO READY? (Y/N): ", id);
        scanf(" %c", &yn);

        if (yn == 'Y' || yn == 'y') {
            printf("\n>>  MOVING ORDER #%03d TO READY HAS BEEN CANCELLED. RETURNING TO MAIN MENU...\n", id);
        }
        else {
            // Recursive call to restart the prompt if they didn't want to cancel
            order_ready();
            return;
        }
    }
    else {
        printf(">>  INVALID CHOICE.\n");
    }

    printf("\n    Press Enter to continue...");
    while (getchar() != '\n')
        ;
    getchar();
}