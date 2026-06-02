#include <stdio.h>
#include <string.h>

struct Process {
    int id;
    int at;
    int bt;
    int rt;
    int type;
    int ct;
    int wt;
    int tat;
};
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i;
        printf("\nProcess %d\n", i);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);
        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);
        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        p[i].rt = p[i].bt;
    }
    int current_time = 0;
    int completed = 0;
    while (completed < n) {
        int selected_process = -1;
        int best_sys = -1;
        int best_sys_at = 999999;
        int best_usr = -1;
        int best_usr_at = 999999;

        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= current_time) {
                if (p[i].type == 0) {
                    if (p[i].at < best_sys_at) {
                        best_sys_at = p[i].at;
                        best_sys = i;
                    }
                } else {
                    if (p[i].at < best_usr_at) {
                        best_usr_at = p[i].at;
                        best_usr = i;
                    }
                }
            }
        }
        if (best_sys != -1) {
            selected_process = best_sys;
        } else if (best_usr != -1) {
            selected_process = best_usr;
        }

        if (selected_process != -1) {
            p[selected_process].rt--;
            current_time++;

            if (p[selected_process].rt == 0) {
                p[selected_process].ct = current_time;
                p[selected_process].tat = p[selected_process].ct - p[selected_process].at;
                p[selected_process].wt = p[selected_process].tat - p[selected_process].bt;
                completed++;
            }
        } else {
            current_time++;
        }
    }
    printf("\n%-4s %-9s %-5s %-5s %-5s %-5s %-5s\n", "ID", "Type", "AT", "BT", "CT", "WT", "TAT");
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        char type_str[10];
        if (p[i].type == 0) {
            strcpy(type_str, "System");
        } else {
            strcpy(type_str, "User");
        }
        printf("%-4d %-9s %-5d %-5d %-5d %-5d %-5d\n",
               p[i].id, type_str, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
