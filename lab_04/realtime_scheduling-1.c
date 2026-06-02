#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id, bt, dl, per, ct, wt, tat;
} Process;

void edf(Process p[], int n) {
    printf("\n====== Earliest Deadline First (EDF) Scheduling ======\n");

    double util = 0.0;
    for (int i = 0; i < n; i++)
        util += (double)p[i].bt / p[i].dl;

    printf("CPU Utilization: %.2f\n", util);
    printf(util <= 1.0 ? "Schedulable (Utilization <= 1)\n" : "NOT Schedulable (Utilization > 1)\n");

    Process s[MAX];
    for (int i = 0; i < n; i++) s[i] = p[i];

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (s[i].dl > s[j].dl) {
                Process tmp = s[i]; s[i] = s[j]; s[j] = tmp;
            }

    printf("%-4s %-4s %-10s %-4s %-4s %-4s\n", "ID", "BF", "Deadline", "CT", "WT", "TAT");

    int t = 0;
    for (int i = 0; i < n; i++) {
        t += s[i].bt;
        s[i].ct  = t;
        s[i].tat = s[i].ct;
        s[i].wt  = s[i].tat - s[i].bt;
        printf("%-4d %-4d %-10d %-4d %-4d %-4d\n",
               s[i].id, s[i].bt, s[i].dl, s[i].ct, s[i].wt, s[i].tat);
    }
}

void rms(Process p[], int n) {
    printf("\n====== Rate Monotonic Scheduling (RMS) ======\n");

    double util = 0.0;
    for (int i = 0; i < n; i++)
        util += (double)p[i].bt / p[i].per;

    double rmBound = n * (pow(2.0, 1.0 / n) - 1.0);

    printf("CPU Utilization: %.2f\n", util);
    printf("RM Bound: %.4f\n", rmBound);
    printf(util <= rmBound ? "Schedulable (Utilization <= RM Bound)\n" : "NOT Schedulable (Utilization > RM Bound)\n");

    Process s[MAX];
    for (int i = 0; i < n; i++) s[i] = p[i];

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (s[i].per > s[j].per) {
                Process tmp = s[i]; s[i] = s[j]; s[j] = tmp;
            }

    printf("%-4s %-4s %-8s %-4s %-4s %-4s\n", "ID", "BF", "Period", "CT", "WT", "TAT");

    int t = 0;
    for (int i = 0; i < n; i++) {
        t += s[i].bt;
        s[i].ct  = t;
        s[i].tat = s[i].ct;
        s[i].wt  = s[i].tat - s[i].bt;
        printf("%-4d %-4d %-8d %-4d %-4d %-4d\n",
               s[i].id, s[i].bt, s[i].per, s[i].ct, s[i].wt, s[i].tat);
    }
}

void proportional(Process p[], int n) {
    printf("\n====== Proportional Scheduling ======\n");

    int totBt = 0, hyper = 1;
    for (int i = 0; i < n; i++) { totBt += p[i].bt; hyper *= p[i].per; }

    printf("%-4s %-4s %-10s %-12s %-10s\n", "ID", "BF", "Period", "Share(%)", "Slots/Hyper");

    for (int i = 0; i < n; i++) {
        double share = (double)p[i].bt / totBt * 100.0;
        int slots    = (int)(share / 100.0 * hyper);
        printf("%-4d %-4d %-10d %-12.2f %-10d\n",
               p[i].id, p[i].bt, p[i].per, share, slots);
    }
    printf("Hyperperiod (product of periods): %d\n", hyper);
}

int main() {
    int n;
    Process p[MAX];

    printf("Real-Time CPU Scheduling\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i;
        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");         scanf("%d", &p[i].bt);
        printf("Deadline (for EDF): "); scanf("%d", &p[i].dl);
        printf("Period (for RMS): ");   scanf("%d", &p[i].per);
    }

    edf(p, n);
    rms(p, n);
    proportional(p, n);

    return 0;
}
