#include "../header/process.h"
#include "../header/queue.h"
#include "../header/FCFS.h"
#include "../header/LCFSNP.h"
#include "../header/LCFSPR.h"
#include "../header/SJN.h"
#include "../header/SRTN.h"
#include "../header/PRIONP.h"
#include "../header/PRIOPR.h"
#include "../header/RR.h"
#include "../header/HRRN.h"
#include "../header/MLFQ.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_schedule(char result[], int maxTime) {
    printf("\nSchedule:\n\n");

    // Print time row
    printf("Time : ");
    for (int i = 0; i < maxTime; i++) {
        printf("%2d ", i);
    }

    printf("\nProc : ");
    for (int i = 0; i < maxTime; i++) {
        printf(" %c ", result[i]);
    }

    printf("\n\n");
}


int sort_and_calc_maxTime(process p[], int n){
	process temp;
	for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

	int maxTime = 0;
	for (int i = 0; i < n; i++){
		if (maxTime < p[i].arrival_time) maxTime = p[i].arrival_time;
		maxTime += p[i].burst_time;
	}
	return maxTime;
}

int main(){
	int n;
    int choice;
    int quantum = 0;

    printf("Choose Scheduling Algorithm:\n");
    printf("1. FCFS\n");
    printf("2. LCFS (Non-Preemptive)\n");
    printf("3. LCFS (Preemptive)\n");
    printf("4. SJN\n");
    printf("5. SRTN\n");
    printf("6. PRIO (Non-Preemptive)\n");
    printf("7. PRIO (Preemptive)\n");
    printf("8. Round Robin\n");
	printf("9. HRRN\n");
	printf("10. MLFQ\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    process p[n];

    printf("\nEnter Arrival and Burst Time");
    if (choice == 6 || choice == 7)
        printf(" and Priority");
    printf(" for each process:\n\n");

    for (int i = 0; i < n; i++) {
        p[i].id = 'A' + i;

        printf("Process %c Arrival Time: ", p[i].id);
        scanf("%d", &p[i].arrival_time);

        printf("Process %c Burst Time: ", p[i].id);
        scanf("%d", &p[i].burst_time);

        if (choice == 6 || choice == 7) {
            printf("Process %c Priority: ", p[i].id);
            scanf("%d", &p[i].priority);
        } else {
            p[i].priority = 0;   // default if unused
        }

        p[i].time_left = p[i].burst_time;
        p[i].waiting_time = 0;
        p[i].completion_time = 0;
        p[i].turnaround_time = 0;
    }

    int maxTime = sort_and_calc_maxTime(p, n);
    char result[maxTime + 1];

    // Ask for quantum only if RR
    if (choice == 8) {
        printf("\nEnter quantum: ");
        scanf("%d", &quantum);
    }

    // Call selected algorithm
    switch (choice) {
        case 1: fcfs(p, n, maxTime, result); break;
        case 2: lcfs(p, n, maxTime, result); break;
        case 3: lcfs_pr(p, n, maxTime, result); break;
        case 4: sjn(p, n, maxTime, result); break;
        case 5: srtn(p, n, maxTime, result); break;
        case 6: prio(p, n, maxTime, result); break;
        case 7: prio_pr(p, n, maxTime, result); break;
        case 8: robin(p, n, maxTime, result, quantum); break;
		case 9: hrrn(p, n, maxTime, result); break;
		case 10: mlfq(p, n, maxTime, result); break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }

    result[maxTime] = '\0';

    print_schedule(result, maxTime);

    printf("--------------------------------------------------\n");
    printf("ID  AT  BT  WT  TAT  PRIO\n");
    printf("--------------------------------------------------\n");

    int total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        printf("%c   %2d  %2d  %2d  %3d   %2d\n",
               p[i].id,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time,
               p[i].priority);

        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }

    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;

    printf("--------------------------------------------------\n");
    printf("Average Waiting Time   : %.4f\n", avg_wt);
    printf("Average Turnaround Time: %.4f\n", avg_tat);

    return 0;
}
