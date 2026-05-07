// Search order by ID
#include "order.h"
void search_order_by_id(void) {
    clear_screen();
    printf("+==================================================================================+\n");
    printf("|                               SEARCH ORDER BY ID                                 |\n");
    printf("+==================================================================================+\n");
    printf("Enter Order ID to search: ");
    
    int search_id;
    if (scanf("%d", &search_id) != 1) {
        printf("Invalid input. Please enter a valid Order ID.\n");
        while (getchar() != '\n'); // Clear buffer
        press_enter();
        return;
    }
    
    OrderNode* found_order = NULL;
    
    // Search in pending queue
    found_order = queue_find_by_id(&g_pending, search_id);
    if (found_order) {
        print_order_summary(found_order);
        print_timestamps(found_order);
        press_enter();
        return;
    }
    
    // Search in preparing queue
    found_order = queue_find_by_id(&g_preparing, search_id);
    if (found_order) {
        print_order_summary(found_order);
        print_timestamps(found_order);
        press_enter();
        return;
    }
    
    // Search in ready queue
    found_order = queue_find_by_id(&g_ready, search_id);
    if (found_order) {
        print_order_summary(found_order);
        print_timestamps(found_order);
        press_enter();
        return;
    }
    
    // Search in history
    found_order = history_find_by_id(&g_history_head, search_id);
    if (found_order) {
        print_order_summary(found_order);
        print_timestamps(found_order);
        press_enter();
        return;
    }
    
    printf("Order with ID %d not found.\n", search_id);
    press_enter();
}