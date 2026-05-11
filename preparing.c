// This file moves an order from the pending queue to the preparing queue.
// It records the preparation start timestamp and uses linear search to find the order.

#include "order.h"

void order_preparing(void) {
    clear_screen();

    printf("+==================================================================================+\n");
    printf("|                              START PREPARING ORDER                               |\n");
    printf("+==================================================================================+\n");

    int id;
    printf("    Enter Order ID (number only, e.g. 123) or [0] to finish: #");
    if (scanf("%d", &id) != 1) {
        printf(">>  ERROR: INVALID INPUT.\n");
        while (getchar() != '\n')
            ; // Clear input buffer
        press_enter();
        return;
    }

    if (id == 0)
        return;

    // Linear search in the pending queue using the global queue from order.h
    OrderNode *order = queue_find_by_id(&g_pending, id);

    if (!order) {
        printf(">>  NOT FOUND: ORDER #%03d IS NOT IN PENDING QUEUE.\n", id);
        press_enter();
        return;
    }

    printf(">>  RESULT FOUND!\n");

    // Show timestamps and order summary using shared utility functions
    print_timestamps(order);
    print_order_summary(order);

    // Options.
    printf("\n");
    printf("    [1] Confirm Start Preparing\n");
    printf("    [0] Cancel\n");
    printf("\n    Enter your choice: ");

    int choice;
    if (scanf("%d", &choice) != 1)
        choice = -1;

    if (choice == 1) {
        // 1. Remove from the pending queue
        queue_remove_node(&g_pending, id);

        // 2. Update status and timestamp
        get_timestamp(order->prepared_timestamp, sizeof(order->prepared_timestamp));
        order->status = STATUS_PREPARING;

        // 3. Move to the preparing queue
        queue_enqueue(&g_preparing, order);

        printf("+==================================================================================+\n");
        printf("|>> SUCCESS: ORDER #%03d HAS BEEN PREPARING.                                        |\n", id);
        printf("+==================================================================================+\n");
    }
    else if (choice == 0) {
        char yn;
        printf("\n>>  WARNING: ARE YOU SURE YOU WANT TO CANCEL PREPARING FOR ORDER #%03d? (Y/N): ", id);
        scanf(" %c", &yn);

        if (yn == 'Y' || yn == 'y') {
            printf("\n>>  PREPARING ORDER #%03d HAS BEEN CANCELLED. RETURNING TO MAIN MENU...\n", id);
        }
        else {
            // Restart the function if the user didn't actually want to cancel
            order_preparing();
            return;
        }
    }
    else {
        printf(">>  INVALID CHOICE.\n");
    }

    // Standard wait for user before returning to dashboard
    printf("\n    Press Enter to continue...");
    while (getchar() != '\n')
        ;
    getchar();
}