// Main entry point for the JYBON INASAL: Real-time Order tracking and Ordering Management System
// This file implements the main menu loop and managethe system flow

#include "order.h"

int main(void){
    int choice;

    while (1) {
        show_dashboard();
        printf("  Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            choice = -1;
            while (getchar() != '\n'); // Clear buffer on error
        } else {
            while (getchar() != '\n'); // Clear buffer after valid input
        }
        
        switch (choice) {
            case 1:
                add_order();
                break;
            case 2:
                order_preparing();
                break;
            case 3:
                order_ready();
                break;
            case 4:
                order_pickup();
                break;
            case 5:
                search_order_by_id();
                break;
            case 6:
                sort_display();
                break;
            case 7:
                show_history();
                break;
            case 0:
                show_exit();
                return 0; // return 0 dahil nasa int main, return pag void function
            default:
                clear_screen();
                printf(">>  INVALID CHOICE. PLEASE TRY AGAIN.\n");
                press_enter();
                break;
        }

        update_counts(); // Moved here — after the action completes
    }
    return 0;
}