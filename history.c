// View order history.
// This file displays all completed and cancelled orders stored in the history linked list.
// It also supports filtering by status and searching by order ID.

#include "order.h"

// Helper: print a single history record
static void print_history_row(OrderNode *order)
{
    const char *status_str = (order->status == STATUS_COMPLETED)
                                 ? "COMPLETED"
                                 : "CANCELLED";
    printf("| #%03d | %-19s | P%-9.2f | %-10s |\n",
           order->order_id,
           order->timestamp,
           order->grand_total,
           status_str);
}

void show_history(void)
{
    clear_screen();

    printf("+==================================================================================+\n");
    printf("|                               VIEW ORDER HISTORY                                 |\n");
    printf("+==================================================================================+\n");

    printf("\n");
    printf("    Total Records: %d\n", history_count);
    printf("\n");
    printf("    [1] View All History\n");
    printf("    [2] Completed Orders Only\n");
    printf("    [4] Search History by Order ID\n");
    printf("    [0] Back to Main Menu\n");
    printf("\n    Enter your choice: ");

    int choice;
    if (scanf("%d", &choice) != 1)
        choice = -1;

    if (choice == 0)
        return;

    clear_screen();

    if (choice == 1 || choice == 2)
    {
        printf("+==================================================================================+\n");
        if (choice == 1)
            printf("|                               ALL ORDER HISTORY                                  |\n");
        else
            printf("|                              COMPLETED ORDERS ONLY                               |\n");
        printf("+==================================================================================+\n");

        if (history_count == 0)
        {
            printf("\n>>  NO HISTORY RECORDS YET.\n");
            press_enter();
            return;
        }

        printf("| %-6s | %-19s | %-10s | %-10s |\n",
               "ID", "TIMESTAMP", "TOTAL", "STATUS");
        printf("+==================================================================================+\n");

        // Traverse from head to tail
        OrderNode *cur = g_history_head;
        int count = 0;
        while (cur != NULL)
        {
            if (choice == 1 || cur->status == STATUS_COMPLETED)
            {
                print_history_row(cur);
                count++;
            }
            cur = cur->next;
        }

        if (count == 0)
        {
            printf("\n>>  NO RECORDS MATCH.\n");
        }

        printf("+==================================================================================+\n");
        printf("    Total Shown: %d\n", count);
        printf("+==================================================================================+\n");
    }
    else if (choice == 4)
    {
        printf("+==================================================================================+\n");
        printf("|                           SEARCH HISTORY BY ORDER ID                            |\n");
        printf("+==================================================================================+\n");

        int id;
        printf("    Enter Order ID (number only, e.g. 1234) or [0] to finish: ");
        if (scanf("%d", &id) != 1)
        {
            printf(">>  ERROR: INVALID INPUT.\n");
            press_enter();
            return;
        }

        if (id == 0)
            return;

        OrderNode *found = history_find_by_id(&g_history_head, id);
        if (!found)
        {
            printf(">>  NOT FOUND: ORDER #%03d IS NOT IN HISTORY.\n", id);
            press_enter();
            return;
        }

        printf(">>  RESULT FOUND!\n");

        print_timestamps(found);
        print_order_summary(found);

        printf("\n    STATUS: %s\n",
               found->status == STATUS_COMPLETED ? "COMPLETED" : "CANCELLED");
        printf("+==================================================================================+\n");
    }
    else
    {
        printf(">>  INVALID CHOICE.\n");
    }

    press_enter();
}