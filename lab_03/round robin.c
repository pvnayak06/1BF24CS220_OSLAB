#include <stdio.h>



int main() {
    int n, tq;
    int at[20], bt[20], rtRemaining[20], ct[20], tat[20], wt[20], rt[20], firstResponse[20];
    int queue[1000], front = 0, rear = 0;
    int inQueue[20] = {0};
    int i, time = 0, completedCount = 0;
    float avwt = 0, avtat = 0, avrt = 0;

    printf("Round Robin (RR) CPU Scheduling\n");
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    printf("Enter the Time Quantum: ");
    scanf("%d", &tq);

    printf("Enter Process Arrival Time:\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i+1);
        scanf("%d", &at[i]);
    }

    printf("Enter Process Burst Time:\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i+1);
        scanf("%d", &bt[i]);
        rtRemaining[i] = bt[i];
        firstResponse[i] = -1;
    }
    int min_at = 9999;
    for(i = 0; i < n; i++) {
        if(at[i] < min_at)
            min_at = at[i];
    }
    time = min_at;
    for(i = 0; i < n; i++) {
        if(at[i] <= time && !inQueue[i]) {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    while(completedCount < n) {
        if(front == rear) {
            time++;
            for(i = 0; i < n; i++) {
                if(at[i] <= time && !inQueue[i] && rtRemaining[i] > 0) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if(firstResponse[idx] == -1) {
            firstResponse[idx] = time;
            rt[idx] = firstResponse[idx] - at[idx];
        }

        int execTime = (rtRemaining[idx] > tq) ? tq : rtRemaining[idx];
        rtRemaining[idx] -= execTime;
        time += execTime;
        for(i = 0; i < n; i++) {
            if(at[i] <= time && !inQueue[i] && rtRemaining[i] > 0) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if(rtRemaining[idx] > 0) {
            queue[rear++] = idx;
        } else {
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completedCount++;
        }
    }
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT");
    for(i = 0; i < n; i++) {
        avwt += wt[i];
        avtat += tat[i];
        avrt += rt[i];
        printf("\nP[%d]\t%d\t%d\t%d\t%d\t%d\t%d", i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\n\nTime Quantum used: %d", tq);
    printf("\nAverage Waiting Time: %.2f", avwt/n);
    printf("\nAverage Turnaround Time: %.2f", avtat/n);
    printf("\nAverage Response Time: %.2f\n", avrt/n);

    return 0;
}
