#include <stdio.h>
#include <stdlib.h>   // for abs()
#include <stdbool.h>


void fcfs() {
    int n, start;
    printf("\n--- FCFS Disk Scheduling ---\n");
    printf("Enter number of requests: ");
    if (scanf("%d", &n) != 1) return;

    int req[n];
    for (int i = 0; i < n; i++) {
        printf("Enter request %d: ", i + 1);
        scanf("%d", &req[i]);
    }

    printf("Enter starting head position: ");
    scanf("%d", &start);

    int total = 0, head = start;
    printf("\nHead movement: %d", head);

    for (int i = 0; i < n; i++) {
        total += abs(head - req[i]);
        head = req[i];
        printf(" -> %d", head);
    }

    printf("\nTotal head movement = %d\n", total);
}


void scan() {
    int n, start, dir, total = 0;

    printf("\n--- SCAN Disk Scheduling ---\n");
    printf("Enter number of requests: ");
    if (scanf("%d", &n) != 1) return;

    int req[n];
    printf("Enter track requests:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter starting head position: ");
    scanf("%d", &start);
    printf("Enter direction (1 = right, 0 = left): ");
    scanf("%d", &dir);

   
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (req[i] > req[j]) {
                int temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }

    int head = start;
    printf("\nHead movement: %d", head);

    if (dir == 1) { 
    
        for (int i = 0; i < n; i++)
            if (req[i] >= start) {
                total += abs(head - req[i]);
                head = req[i];
                printf(" -> %d", head);
            }

       
        for (int i = n - 1; i >= 0; i--)
            if (req[i] < start) {
                total += abs(head - req[i]);
                head = req[i];
                printf(" -> %d", head);
            }
    } else { 
      
        for (int i = n - 1; i >= 0; i--)
            if (req[i] <= start) {
                total += abs(head - req[i]);
                head = req[i];
                printf(" -> %d", head);
            }

    
        for (int i = 0; i < n; i++)
            if (req[i] > start) {
                total += abs(head - req[i]);
                head = req[i];
                printf(" -> %d", head);
            }
    }

    printf("\nTotal head movement = %d\n", total);
}


void cscan() {
    int n, start, dir, max, total = 0;

    printf("\n--- C-SCAN Disk Scheduling ---\n");
    printf("Enter number of requests: ");
    if (scanf("%d", &n) != 1) return;

    int req[n];
    printf("Enter track requests:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter starting head position: ");
    scanf("%d", &start);
    printf("Enter maximum track number (e.g. 199 if tracks 0..199): ");
    scanf("%d", &max);
    printf("Enter direction (1 = right, 0 = left): ");
    scanf("%d", &dir);

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (req[i] > req[j]) {
                int temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }

    int head = start;
    printf("\nHead movement: %d", head);

    if (dir == 1) { 
        bool servicedRight = false;  
        for (int i = 0; i < n; i++) {
            if (req[i] >= start) {
                total += abs(head - req[i]);
                head = req[i];
                printf(" -> %d", head);
                servicedRight = true;
            }
        }

     
        total += abs(max - head);      
        head = max;
        printf(" -> %d", head);

        
        total += max;
        head = 0;
    
        printf(" -> %d", head);

        
        for (int i = 0; i < n; i++) {
            if (req[i] < start) {
                total += abs(head - req[i]);
                head = req[i];
                printf(" -> %d", head);
            }
        }
    } else { 
        bool servicedLeft = false;
        
        for (int i = n - 1; i >= 0; i--) {
            if (req[i] <= start) {
                total += abs(head - req[i]);
                head = req[i];
                printf(" -> %d", head);
                servicedLeft = true;
            }
        }

  
        total += abs(head - 0);
        head = 0;
        printf(" -> %d", head);

      
        total += max;
        head = max;
        printf(" -> %d", head);

   
        for (int i = n - 1; i >= 0; i--) {
            if (req[i] > start) {
                total += abs(head - req[i]);
                head = req[i];
                printf(" -> %d", head);
            }
        }
    }

    printf("\nTotal head movement = %d\n", total);
}


int main() {
    int choice;

    while (1) {
        printf("\nDisk Scheduling Menu\n");
        printf("1. FCFS\n");
        printf("2. SCAN\n");
        printf("3. C-SCAN\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 1)
            fcfs();
        else if (choice == 2)
            scan();
        else if (choice == 3)
            cscan();
        else if (choice == 4)
            break;
        else
            printf("Invalid choice! Please try again.\n");
    }

    return 0;
}
