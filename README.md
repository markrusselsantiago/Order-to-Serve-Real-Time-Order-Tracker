JYBON INASAL: Real-Time Order Tracking & Ordering Management System

A console-based restaurant order management system developed in C using Data Structures and Algorithms.

-What is JYBON INASAL: Real-Time Order Tracking & Ordering Management System?

This system helps a restaurant manage orders from start to finish. A staff member can add a new order, track it as it moves

from Pending → Preparing → Ready → Picked Up, search for any order, sort orders, and view the history of completed orders.

Features
Option     Feature
1          Add a new order
2          Start preparing an order
3          Move order to ready
4          Mark order as picked up
5          Search order by ID
6          Sort and display orders
7          View order history
0          Exit    

-Data Structures and Algorithms Used
Data Structure 1 — Array (Static)

Used in: order.h, add_order.c, utils.c
Each order can hold up to 50 items. These items are stored inside a fixed-size array called items[50] inside the OrderNode struct.
When a customer adds an item to their order, it gets placed into the next available slot in that array. 
The grand total is updated by looping through the array.
The menu itself (menu_items[] in utils.c) is also a static array that the system searches through every time a staff member enters an item code.

Data Structure 2 — Singly Linked List

Used in: utils.c, history.c, pick_up.c
When an order is completed (picked up), it is added to a history linked list. Each node points to the next one using a next pointer. 
New records are appended to the end of the list. The system can also walk through the entire list to display all history or find a specific order.

Data Structure 3 — Queue (Linked Representation)

Used in: utils.c, add_order.c, preparing.c, ready.c, pick_up.c
There are three queues in the system: Pending, Preparing, and Ready. Each queue follows FIFO (First In, First Out)
the first order placed is the first to be prepared,and the first prepared is the first to be marked ready.

Algorithm 1 — Linear Search

Used in: utils.c, search.c, preparing.c, ready.c, pick_up.c, history.c
When a staff member enters an order ID to process it, the system does a linear search 
it starts from the front of the queue and checks each node one by one until it finds the matching ID or reaches the end.

Algorithm 2 — Bubble Sort

Used in: utils.c, sort_x_display.c
The Sort & Display feature lets staff sort any of the three queues either by Order ID or by Timestamp, both in ascending order.
The system uses Bubble Sort — it repeatedly compares two adjacent nodes and swaps their data if they are in the wrong order. It keeps doing this until no more swaps are needed.

-How to Compile and Run

Step 1 — Create a New Project
Open Dev-C++
Go to File → New → Project
Select Console Application and choose C Project
Give it a name (e.g. JybonInasal) and click OK
Choose a folder where you want to save the project

Step 2 — Add All Source Files
Dev-C++ will create a default main.c — you can delete its contents or replace it with your main.c
To add the rest of the files, go to Project → Add to Project
Add all .c files one by one:

utils.c
dashboard.c
menu.c
add_order.c
preparing.c
ready.c
pick_up.c
search.c
sort_x_display.c
history.c
exit.c



Step 3 — Add the Header File
Copy order.h into the same folder as all your .c files
Dev-C++ will automatically find it when compiling since all files are in the same directory

Step 4 — Compile and Run
Press F9 to Compile & Run (or go to Execute → Compile & Run)
If there are no errors, the program will open in a console window


Note: Make sure all .c files and order.h are in the same project folder. 
If any file is missing from the project, right-click the project name in the left panel and choose Add to Project.

