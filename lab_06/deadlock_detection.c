#include <stdio.h>

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], avail[m];

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Detection Algorithm
    int finish[n];
    int work[m];

    // Mark processes with zero allocation as finished
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
        int zeroAlloc = 1;
        for (int j = 0; j < m; j++) {
            if (alloc[i][j] != 0) {
                zeroAlloc = 0;
                break;
            }
        }
        if (zeroAlloc) finish[i] = 1;
    }

    for (int j = 0; j < m; j++) work[j] = avail[j];

    int found;
    do {
        found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int canRun = 1;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        canRun = 0;
                        break;
                    }
                }
                if (canRun) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
    } while (found);

    printf("\nProcesses in Deadlock:\n");
    int deadlockFound = 0;
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            printf("P%d\n", i);
            deadlockFound = 1;
        }
    }
    if (!deadlockFound)
        printf("No deadlock detected. All processes can finish.\n");

    return 0;
}
