
#include <stdio.h>

// Helper function to display the current state of frames
void displayFrames(int page, int frames[], int num_frames) {
    printf("Page %d -> ", page);
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

// Helper function to find the optimal page to replace (from your notebook)
int findOptimal(int pages[], int frames[], int num_frames, int current, int num_pages) {
    int index = -1;
    int farthest = current;

    for (int i = 0; i < num_frames; i++) {
        int j;
        for (j = current; j < num_pages; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        // If a page in the frame is never going to be used again, replace it immediately
        if (j == num_pages)
            return i;
    }
    return (index == -1) ? 0 : index;
}

// Helper function to find the Least Recently Used page index (from your notebook)
int findLRU(int time[], int num_frames) {
    int min = time[0], pos = 0;
    for (int i = 1; i < num_frames; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

// 1. FIFO Simulation
void fifo(int pages[], int num_pages, int num_frames) {
    printf("\n-- FIFO Simulation --\n");
    int frames[20];
    int page_faults = 0, index = 0;

    for (int i = 0; i < num_frames; i++) frames[i] = -1;

    for (int i = 0; i < num_pages; i++) {
        int hit = 0;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            frames[index] = pages[i];
            index = (index + 1) % num_frames;
            page_faults++;
        }
        displayFrames(pages[i], frames, num_frames);
    }
    printf("Total page faults (FIFO) = %d\n", page_faults);
}

// 2. LRU Simulation
void lru(int pages[], int num_pages, int num_frames) {
    printf("\n-- LRU Simulation --\n");
    int frames[20], time[20];
    int page_faults = 0;

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < num_pages; i++) {
        int hit = 0;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                time[j] = i; // update counter/time-stamp
                break;
            }
        }

        if (!hit) {
            page_faults++;
            int empty_slot = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    empty_slot = j;
                    break;
                }
            }

            if (empty_slot != -1) {
                frames[empty_slot] = pages[i];
                time[empty_slot] = i;
            } else {
                int lru_index = findLRU(time, num_frames);
                frames[lru_index] = pages[i];
                time[lru_index] = i;
            }
        }
        displayFrames(pages[i], frames, num_frames);
    }
    printf("Total page faults (LRU) = %d\n", page_faults);
}

// 3. Optimal Simulation
void optimal(int pages[], int num_pages, int num_frames) {
    printf("\n-- Optimal Simulation --\n");
    int frames[20];
    int page_faults = 0;

    for (int i = 0; i < num_frames; i++) frames[i] = -1;

    for (int i = 0; i < num_pages; i++) {
        int hit = 0;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            page_faults++;
            int empty_slot = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    empty_slot = j;
                    break;
                }
            }

            if (empty_slot != -1) {
                frames[empty_slot] = pages[i];
            } else {
                int opt_index = findOptimal(pages, frames, num_frames, i + 1, num_pages);
                frames[opt_index] = pages[i];
            }
        }
        displayFrames(pages[i], frames, num_frames);
    }
    printf("Total page faults (Optimal) = %d\n", page_faults);
}

int main() {
    int num_pages, num_frames, choice;
    int pages[100];

    printf("Enter number of page: ");
    scanf("%d", &num_pages);

    printf("Enter the pages reference string:\n");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    do {
        printf("\nChoose Algorithm:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifo(pages, num_pages, num_frames);
                break;
            case 2:
                lru(pages, num_pages, num_frames);
                break;
            case 3:
                optimal(pages, num_pages, num_frames);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    return 0;
}

