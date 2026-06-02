
#include <stdio.h>

int main() {
    int n, bt[20], at[20], wt[20], tat[20], ct[20], rt[20], st[20], completed[20];
    int i, time = 0, completedCount = 0;
    float avwt = 0, avtat = 0, avrt = 0;

    printf("SJF (Non-Preemptive) CPU Scheduling\n");
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    printf("Enter Process Arrival Time:\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i+1);
        scanf("%d", &at[i]);
    }

    printf("Enter Process Burst Time:\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i+1);
        scanf("%d", &bt[i]);
        completed[i] = 0;
    }

    while(completedCount < n) {
        int idx = -1, minBT = 9999;
        for(i = 0; i < n; i++) {
            if(at[i] <= time && completed[i] == 0 && bt[i] < minBT) {
                minBT = bt[i];
                idx = i;
            }
        }
        if(idx == -1) {
            time++;
        } else {
            st[idx] = time;
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            rt[idx] = st[idx] - at[idx];
            completed[idx] = 1;
            completedCount++;
        }
    }

    printf("\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\tRT");
    for(i = 0; i < n; i++) {
        avwt += wt[i];
        avtat += tat[i];
        avrt += rt[i];
        printf("\nP[%d]\t%d\t%d\t%d\t%d\t%d\t%d\t%d", i+1, at[i], bt[i], st[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\n\nAverage Waiting Time: %.2f", avwt/n);
    printf("\nAverage Turnaround Time: %.2f", avtat/n);
    printf("\nAverage Response Time: %.2f\n", avrt/n);

    return 0;
}
