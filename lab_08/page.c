#include <stdio.h>
#define MAX 50

int search(int key, int frame[], int frameSize) {
    for (int i = 0; i < frameSize; i++) {
        if (frame[i] == key)
            return i;
    }
    return -1;
}

void FIFO(int pages[], int n, int frameSize) {
    int frame[MAX], faults = 0, index = 0;
    for (int i = 0; i < frameSize; i++)
        frame[i] = -1;
    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        if (search(pages[i], frame, frameSize) == -1) {
            frame[index] = pages[i];
            index = (index + 1) % frameSize;
            faults++;
            printf("Page %d -> ", pages[i]);
            for (int j = 0; j < frameSize; j++)
                printf("%d ", frame[j]);
            printf("\n");
        }
    }
    printf("Total Page Faults = %d\n", faults);
}

void LRU(int pages[], int n, int frameSize) {
    int frame[MAX], time[MAX];
    int faults = 0, counter = 0;
    for (int i = 0; i < frameSize; i++) {
        frame[i] = -1;
        time[i] = 0;
    }
    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int pos = search(pages[i], frame, frameSize);
        if (pos != -1) {
            time[pos] = ++counter;
        } else {
            int lru = 0;
            for (int j = 1; j < frameSize; j++) {
                if (time[j] < time[lru])
                    lru = j;
            }

            frame[lru] = pages[i];
            time[lru] = ++counter;
            faults++;
            printf("Page %d -> ", pages[i]);
            for (int j = 0; j < frameSize; j++)
                printf("%d ", frame[j]);
            printf("\n");
        }
    }
    printf("Total Page Faults = %d\n", faults);
}

int predict(int pages[], int frame[], int n, int index, int frameSize) {
    int farthest = index, pos = -1;
    for (int i = 0; i < frameSize; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (pos == -1) ? 0 : pos;
}

void Optimal(int pages[], int n, int frameSize) {
    int frame[MAX];
    int faults = 0;
    int filled = 0;
    for (int i = 0; i < frameSize; i++)
        frame[i] = -1;
    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        if (search(pages[i], frame, frameSize) == -1) {
            if (filled < frameSize) {
                frame[filled++] = pages[i];
            } else {
                int pos = predict(pages, frame, n, i + 1, frameSize);
                frame[pos] = pages[i];
            }
            faults++;
            printf("Page %d -> ", pages[i]);
            for (int j = 0; j < frameSize; j++)
                printf("%d ", frame[j]);
            printf("\n");
        }
    }
    printf("Total Page Faults = %d\n", faults);
}

int main() {
    int pages[MAX], n, frameSize;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frameSize);
    FIFO(pages, n, frameSize);
    LRU(pages, n, frameSize);
    Optimal(pages, n, frameSize);
    return 0;
}
