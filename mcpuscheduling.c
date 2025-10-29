#include <stdio.h>
#include <stdlib.h>

void fcfs();
void sjf();
void priority_scheduling();
void round_robin();


int main() {
    int choice;
    while (1) {
        printf("\n-----------------------------");
        printf("\nCPU SCHEDULING ALGORITHMS MENU");
        printf("\n-----------------------------");
        printf("\n1. FCFS (First Come First Serve)");
        printf("\n2. SJF (Shortest Job First - Non Preemptive)");
        printf("\n3. Priority Scheduling (Non Preemptive)");
        printf("\n4. Round Robin");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: fcfs(); break;
            case 2: sjf(); break;
            case 3: priority_scheduling(); break;
            case 4: round_robin(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}


void fcfs() {
    int n;
    printf("\n--- FCFS Scheduling ---\n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of P%d: ", i);
        scanf("%d", &at[i]);
        printf("Enter burst time of P%d: ", i);
        scanf("%d", &bt[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                int t = at[i]; at[i] = at[j]; at[j] = t;
                t = bt[i]; bt[i] = bt[j]; bt[j] = t;
            }
        }
    }

    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < at[i]) time = at[i];
        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        time = ct[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i, at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) printf("  P%d  |", i);
    printf("\n%d", at[0]);
    for (int i = 0; i < n; i++) printf("     %d", ct[i]);
    printf("\n");
}


void sjf() {
    int n;
    printf("\n--- SJF Scheduling (Non-Preemptive) ---\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n], done[n];
    for (int i = 0; i < n; i++) done[i] = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of P%d: ", i);
        scanf("%d", &at[i]);
        printf("Enter burst time of P%d: ", i);
        scanf("%d", &bt[i]);
    }

    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    printf("\nGantt Chart:\n|");

    while (completed < n) {
        int idx = -1, min_bt = 9999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && bt[i] < min_bt) {
                min_bt = bt[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
        } else {
            printf("  P%d  |", idx);
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            total_tat += tat[idx];
            total_wt += wt[idx];
            done[idx] = 1;
            completed++;
        }
    }

    int start_time = at[0];
    for (int i = 1; i < n; i++)
        if (at[i] < start_time) start_time = at[i];

    printf("\n%d", start_time);
    for (int i = 0; i < n; i++)
        printf("     %d", ct[i]);
    printf("\n");

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i, at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage WT  = %.2f\n", total_wt / n);
}

void priority_scheduling() {
    int n;
    printf("\n--- Priority Scheduling (Non-Preemptive) ---\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n], ct[n], tat[n], wt[n], done[n];
    float total_tat = 0, total_wt = 0;
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time, and Priority for P%d: ", i);
        scanf("%d%d%d", &at[i], &bt[i], &pr[i]);
        done[i] = 0;
    }

    printf("\nGantt Chart:\n");

    int order[n], end_time[n];
    int o = 0;

    while (completed < n) {
        int idx = -1, min_pr = 9999;

        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && pr[i] < min_pr) {
                min_pr = pr[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;  // CPU idle
        } else {
            if (time < at[idx])
                time = at[idx];

            printf("P%d | ", idx);

            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            total_tat += tat[idx];
            total_wt += wt[idx];
            done[idx] = 1;
            completed++;

            order[o] = idx;
            end_time[o] = time;
            o++;
        }
    }

    // Print timeline directly below Gantt chart
    int start_time = at[0];
    for (int i = 1; i < n; i++)
        if (at[i] < start_time)
            start_time = at[i];

    printf("\n%d", start_time);
    for (int i = 0; i < o; i++)
        printf("   %d", end_time[i]);

    printf("\n\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);

    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage WT  = %.2f\n", total_wt / n);
}


void round_robin() {
    int n, tq;
    printf("\n--- Round Robin Scheduling ---\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[100], at[100], bt[100], rt[100], ct[100], tat[100], wt[100];
    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0, visited[100];
    int startTime[100], endTime[100], order[100]; // For Gantt chart
    int gcIndex = 0;

    // Input process details
    for (int i = 0; i < n; i++) {
        pid[i] = i;
        printf("Enter arrival time for P%d: ", i);
        scanf("%d", &at[i]);
        printf("Enter burst time for P%d: ", i);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   // remaining time initially = burst time
        ct[i] = 0;
        visited[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Add first process(es) that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (at[i] == time) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    printf("\nGantt Chart:\n");

    // Round Robin scheduling loop
    while (completed < n) {
        // If queue empty → CPU idle
        if (front == rear) {
            time++;
            for (int i = 0; i < n; i++) {
                if (at[i] == time && visited[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];  // Dequeue process

        // Decide execution time
        int exec = (rt[idx] > tq) ? tq : rt[idx];

        // Record start and end time for Gantt chart
        startTime[gcIndex] = time;
        order[gcIndex] = pid[idx];
        time += exec;
        endTime[gcIndex] = time;
        gcIndex++;

        printf("P%d | ", pid[idx]);

        // Decrease remaining time
        rt[idx] -= exec;

        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++) {
            if (at[i] > time - exec && at[i] <= time && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // If process not finished → requeue it
        if (rt[idx] > 0)
            queue[rear++] = idx;
        else {
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed++;
        }
    }

    // Print Gantt chart timeline below chart
    printf("\n%d", startTime[0]);
    for (int i = 0; i < gcIndex; i++) {
        printf("   %d", endTime[i]);
    }

    // Print table
    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    float total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
}
