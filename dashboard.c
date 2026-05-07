// Main screen of the system.
// This file shows the three order stages: Pending, Preparing, and Ready.
// It also shows the status of total order counts and the main menu.

#include "order.h"

// DASHBOARD FUNCTION
void show_dashboard(void) {
    clear_screen();

    // PENDING PANEL
    printf("+==================================================================================+\n"); 
    printf("|        JYBON INASAL: REAL-TIME ORDER TRACKING & ORDERING MANAGEMENT SYSTEM       |\n");
    printf("+==================================================================================+\n"); // 84
    printf("|                                  PENDING ORDER                                   |\n");
    printf("+==================================================================================+\n");
    if (pending_count == 0) {
        printf("|    (No orders)                                                                   |\n");
    }
    else {
        printf("|    ");     // | + 4 spaces = 5 characters
        int char_count = 5; // 5 char use yang printf sa taas out of 83
        int line_count = 0;  

        OrderNode *cur = g_pending.front;
        while (cur != NULL) {
            if (line_count == 11)  {   // new row pag 11 oders na
                for (int i = char_count; i < 83; i++)
                    printf(" ");
                printf("|\n|    "); // new row
                char_count = 5;
                line_count = 0;
            }
            printf("#%03d   ", cur->order_id);
            char_count += 7;   // 7 char per order count (#001   ) pati space
            line_count++;
            cur = cur->next;
        }
        for (int i = char_count; i < 83; i++)
            printf(" ");
        printf("|\n");
    }
    printf("|                                                                                  |\n");

    // PREPARING PANEL
    printf("+==================================================================================+\n");
    printf("|                                 PREPARING ORDER                                  |\n");
    printf("+==================================================================================+\n");
    if (preparing_count == 0) {
        printf("|    (No preparing orders)                                                         |\n");
    }
    else {
        printf("|    ");
        int char_count = 5;
        int line_count = 0;

        OrderNode *cur = g_preparing.front;
        while (cur != NULL) {
            if (line_count == 11) {
                for (int i = char_count; i < 83; i++)
                    printf(" ");
                printf("|\n|    ");
                char_count = 5;
                line_count = 0;
            }
            printf("#%03d   ", cur->order_id);
            char_count += 7;
            line_count++;
            cur = cur->next;
        }
        for (int i = char_count; i < 83; i++)
            printf(" ");
        printf("|\n");
    }
    printf("|                                                                                  |\n");

    // READY PANEL
    printf("+==================================================================================+\n");
    printf("|                                 READY TO PICK UP                                 |\n");
    printf("+==================================================================================+\n");
    if (ready_count == 0) {
        printf("|    (No ready orders)                                                             |\n");
    }
    else {
        printf("|    ");
        int char_count = 5;
        int line_count = 0;

        OrderNode *cur = g_ready.front;
        while (cur != NULL) {
            if (line_count == 11) {
                for (int i = char_count; i < 83; i++)
                    printf(" ");
                printf("|\n|    ");
                char_count = 5;
                line_count = 0;
            }
            printf("#%03d   ", cur->order_id);
            char_count += 7;
            line_count++;
            cur = cur->next;
        }
        for (int i = char_count; i < 83; i++)
            printf(" ");
        printf("|\n");
    }

    // Status bar
    printf("|                                                                                  |\n");
    printf("+----------------------------------------------------------------------------------+\n");
    printf("| Pending: %-3d |  Preparing: %-3d |  Ready: %-3d |  Completed: %-3d  |  Next ID: #%03d |\n",
            pending_count, preparing_count, ready_count, completed_count, next_id);

    // Main menu
    printf("+==================================================================================+\n");
    printf("|                               ORDER TO SERVE MENU                                |\n");
    printf("|==================================================================================|\n");
    printf("|   [1]  Add New Order                                                             |\n");
    printf("|   [2]  Start Preparing Order                                                     |\n");
    printf("|   [3]  Move Order to Ready                                                       |\n");
    printf("|   [4]  Order Picked Up                                                           |\n");
    printf("|   [5]  Search Order by ID                                                        |\n");
    printf("|   [6]  Sort & Display Orders                                                     |\n");
    printf("|   [7]  View Order History                                                        |\n");
    printf("|   [0]  Exit                                                                      |\n");
    printf("+==================================================================================+\n");
}