#include <stdio.h>

int main() {
    int n, bt[20], at[20], wt[20], tat[20], ct[20], rt[20], st[20], i;
    float avwt = 0, avtat = 0, avrt = 0;
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
    }


    st[0] = at[0];
    ct[0] = st[0] + bt[0];
    tat[0] = ct[0] - at[0];
    wt[0] = tat[0] - bt[0];
    rt[0] = st[0] - at[0];


    for(i = 1; i < n; i++) {
        if(ct[i-1] < at[i]) {
            st[i] = at[i];
        } else {
            st[i] = ct[i-1];
        }
        ct[i] = st[i] + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = st[i] - at[i];
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT");
    for(i = 0; i < n; i++) {
        avwt += wt[i];
        avtat += tat[i];
        avrt += rt[i];
        printf("\nP[%d]\t%d\t%d\t%d\t%d\t%d\t%d", i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\n\nAverage Waiting Time: %.2f", avwt/n);
    printf("\nAverage Turnaround Time: %.2f", avtat/n);
    printf("\nAverage Response Time: %.2f\n", avrt/n);

    return 0;
}
