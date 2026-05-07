// Main function for adding a new order. Handles user input for selecting items, quantities, 
// and confirming the order. Also includes a summary display and item removal option.
// Prints the order summary table with all items, quantities, prices, and grand total.

#include "order.h"

// Forward declarations
int add_item(OrderNode *order);
void show_summary(OrderNode *order);
void remove_item(OrderNode *order);

void add_order(void) {
    clear_screen();
    show_menu();

    OrderNode *order = create_order_node();
    if (!order) { printf("\n>>  ERROR: MEMORY ALLOCATION FAILED.\n"); return; }

    order->order_id = get_next_id();
    get_timestamp(order->timestamp, sizeof(order->timestamp));
    printf("+==================================================================================+\n");
    printf("|                                  ADD NEW ORDER                                   |\n");
    printf("+==================================================================================+\n");
    printf("    Order ID   : #%03d\n", order->order_id);
    printf("    Timestamp  : %s\n", order->timestamp);

    while (1) {
        int result = add_item(order);
        if (result == 0) goto cancel_order;
        if (result == 2) break; 
    }

    while (1) {
        if (order->item_count == 0) goto cancel_order;
        show_summary(order);

        printf("\n    [1] Confirm Order\n");
        printf("    [2] Add Another Item\n");
        printf("    [3] Remove an Item\n");
        printf("    [0] Cancel Order\n");
        printf("\n    Enter your choice: ");

        int confirm;
        if (scanf("%d", &confirm) != 1) { fflush(stdin); continue; }

        if (confirm == 1) {
            order->status = STATUS_PENDING;
            
            // --- MANUAL LINKED QUEUE ENQUEUE LOGIC ---
            order->next = NULL; // New node will be at the end

            if (g_pending.rear == NULL) {
                // Queue is empty: front and rear both point to the new node
                g_pending.front = g_pending.rear = order;
            } else {
                // Queue is not empty: link old rear to new node, then update rear
                g_pending.rear->next = order;
                g_pending.rear = order;
            }
            g_pending.count++;

            printf("\n>>  SUCCESS: ORDER #%03d HAS BEEN PLACED.\n", order->order_id);
            press_enter();
            return;
        }
        if (confirm == 2) {
            int result = add_item(order);
            if (result == 0) goto cancel_order;
        }
        if (confirm == 3) remove_item(order);
        if (confirm == 0) goto cancel_order;
    }

cancel_order:
    printf("\n>>  ORDER #%03d HAS BEEN CANCELLED.\n", order->order_id);
    free(order);
    press_enter();
}

void show_summary(OrderNode *order) {
    clear_screen();
    printf("+==================================================================================+\n");
    printf("|                                   ORDER SUMMARY                                  |\n");
    printf("+==================================================================================+\n");
    printf("|  CODE   |        ITEM DESCRIPTION        |   QTY   |    PRICE    |     TOTAL     |\n");
    printf("|---------|--------------------------------|---------|-------------|---------------|\n");
    for (int i = 0; i < order->item_count; i++) {
        printf("|  %-6s |   %-28s |   %-5d |   P%-8.2f |   P%-9.2f  |\n",
               order->items[i].code,
               order->items[i].name,
               order->items[i].quantity,
               order->items[i].price,
               order->items[i].total);
    }
    printf("+==================================================================================+\n");
    printf("|                                                      GRAND TOTAL:   P%-9.2f   |\n", order->grand_total);
    printf("+==================================================================================+\n");
}

// Removes an item from the current order and updates the grand total.
void remove_item(OrderNode *order) {
    show_summary(order);
    printf("\n    Enter item number to remove (1-%d) or [0] to cancel: ", order->item_count);
    int n;
    if (scanf("%d", &n) != 1 || n < 1 || n > order->item_count) {
        printf("\n>>  INVALID. NOTHING REMOVED.\n");
        return;
    }
    
    // Convert to 0-based index
    int index = n - 1;
    order->grand_total -= order->items[index].total;
    
    for (int i = index; i < order->item_count - 1; i++)
        order->items[i] = order->items[i + 1];
        
    order->item_count--;
    printf("\n>>  ITEM REMOVED.\n");
}

// Adds one item to the order. Returns 0 to cancel, 1 to keep adding, or 2 to go to summary.
int add_item(OrderNode *order) {
    char code[10];
    int qty;

    printf("\n    Enter Item ID (e.g. G1, S2, B3) or [0] to cancel: ");
    scanf("%s", code);
    if (strcmp(code, "0") == 0) return 0;

    MenuItem *item = find_menu_item(code);
    if (!item) { printf("\n>>  ERROR: ITEM CODE NOT FOUND.\n"); return 1; }

    printf("    Order Item : %s\n", item->name);
    printf("    Price      : P%.2f\n", item->price);
    printf("    Enter Quantity: ");
    if (scanf("%d", &qty) != 1 || qty <= 0) {
        printf("\n>>  ERROR: INVALID QUANTITY.\n");
        fflush(stdin);
        return 1;
    }

    int i = order->item_count;
    order->items[i].price    = item->price;
    order->items[i].quantity = qty;
    order->items[i].total    = item->price * qty;
    strcpy(order->items[i].code, item->code);
    strcpy(order->items[i].name, item->name);
    order->grand_total += order->items[i].total;
    order->item_count++;
    printf("\n>>  ITEM ADDED!\n");

    while (1) {
        printf("\n    [1] Add Another Item\n");
        printf("    [2] Done & Show Summary\n");
        printf("    [0] Cancel Entire Order\n");
        printf("\n    Enter your choice: ");

        int sub;
        if (scanf("%d", &sub) != 1) { fflush(stdin); printf("\n>>  INVALID INPUT.\n"); continue; }
        if (sub == 0) return 0;
        if (sub == 1) return 1;
        if (sub == 2) return 2;
        printf("\n>>  INVALID CHOICE. TRY AGAIN.\n");
    }
}