/* Page Replacement Algorithms - CSE316 */
#include <stdio.h>

void fifo(int pages, int frames, int pageRef[]) {
    int frame[frames];
    int i, j, pointer = 0, hits = 0, faults = 0;

    for(i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nFIFO Page Replacement\n");
    printf("Page\tFrames\t\tStatus\n");

    for(i = 0; i < pages; i++) {
        int found = 0;

        for(j = 0; j < frames; j++) {
            if(frame[j] == pageRef[i]) {
                found = 1;
                hits++;
                break;
            }
        }

        if(!found) {
            frame[pointer] = pageRef[i];
            pointer = (pointer + 1) % frames;
            faults++;
        }

        printf("%d\t", pageRef[i]);
        for(j = 0; j < frames; j++)
            frame[j] == -1 ? printf("- ") : printf("%d ", frame[j]);

        printf(found ? "\tHIT\n" : "\tFAULT\n");
    }

    printf("Total Page Faults: %d\n", faults);
    printf("Total Hits: %d\n", hits);
}

void lru(int pages, int frames, int pageRef[]) {
    int frame[frames], lastUsed[frames];
    int i, j, time = 0, hits = 0, faults = 0;

    for(i = 0; i < frames; i++) {
        frame[i] = -1;
        lastUsed[i] = -1;
    }

    printf("\nLRU Page Replacement\n");
    printf("Page\tFrames\t\tStatus\n");

    for(i = 0; i < pages; i++) {
        int found = 0;

        for(j = 0; j < frames; j++) {
            if(frame[j] == pageRef[i]) {
                found = 1;
                hits++;
                lastUsed[j] = time++;
                break;
            }
        }

        if(!found) {
            int lruIndex = 0;
            for(j = 1; j < frames; j++)
                if(lastUsed[j] < lastUsed[lruIndex])
                    lruIndex = j;

            frame[lruIndex] = pageRef[i];
            lastUsed[lruIndex] = time++;
            faults++;
        }

        printf("%d\t", pageRef[i]);
        for(j = 0; j < frames; j++)
            frame[j] == -1 ? printf("- ") : printf("%d ", frame[j]);

        printf(found ? "\tHIT\n" : "\tFAULT\n");
    }

    printf("Total Page Faults: %d\n", faults);
    printf("Total Hits: %d\n", hits);
}

void optimal(int pages, int frames, int pageRef[]) {
    int frame[frames];
    int i, j, k, hits = 0, faults = 0;

    for(i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nOptimal Page Replacement\n");
    printf("Page\tFrames\t\tStatus\n");

    for(i = 0; i < pages; i++) {
        int found = 0;

        for(j = 0; j < frames; j++) {
            if(frame[j] == pageRef[i]) {
                found = 1;
                hits++;
                break;
            }
        }

        if(!found) {
            int index = -1, farthest = -1;

            for(j = 0; j < frames; j++) {
                int nextUse = -1;
                for(k = i + 1; k < pages; k++) {
                    if(frame[j] == pageRef[k]) {
                        nextUse = k;
                        break;
                    }
                }

                if(nextUse == -1) {
                    index = j;
                    break;
                }

                if(nextUse > farthest) {
                    farthest = nextUse;
                    index = j;
                }
            }

            if(index == -1)
                index = 0;

            frame[index] = pageRef[i];
            faults++;
        }

        printf("%d\t", pageRef[i]);
        for(j = 0; j < frames; j++)
            frame[j] == -1 ? printf("- ") : printf("%d ", frame[j]);

        printf(found ? "\tHIT\n" : "\tFAULT\n");
    }

    printf("Total Page Faults: %d\n", faults);
    printf("Total Hits: %d\n", hits);
}

int main() {
    int pages, frames, choice, i;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    int pageRef[pages];

    printf("Enter the page reference string:\n");
    for(i = 0; i < pages; i++)
        scanf("%d", &pageRef[i]);

    printf("\nChoose Algorithm:\n");
    printf("1. FIFO\n2. LRU\n3. Optimal\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if(choice == 1)
        fifo(pages, frames, pageRef);
    else if(choice == 2)
        lru(pages, frames, pageRef);
    else if(choice == 3)
        optimal(pages, frames, pageRef);
    else
        printf("Invalid choice\n");

    return 0;
}

