#include <stdio.h>
#include <stdbool.h>

#define MAX 20

// Helper function to check if a page is in the frame
bool isPageInFrame(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page)
            return true;
    }
    return false;
}

// FCFS Algorithm (First-Come, First-Served)
int FCFS(int pages[], int numPages, int frames[], int numFrames) {
    int pageFaults = 0, pointer = 0;

    for (int i = 0; i < numPages; i++) {
        if (!isPageInFrame(frames, numFrames, pages[i])) {
            frames[pointer] = pages[i];  // Replace the page in the first available frame
            pointer = (pointer + 1) % numFrames; // Wrap around when frames are full
            pageFaults++;
        }
    }

    return pageFaults;
}

// LRU Algorithm (Least Recently Used)
int LRU(int pages[], int numPages, int frames[], int numFrames) {
    int pageFaults = 0, leastRecentlyUsed[MAX], time = 0;

    // Initialize least recently used array to a large number
    for (int i = 0; i < numFrames; i++) {
        leastRecentlyUsed[i] = -1; // -1 indicates that page has not been used yet
    }

    for (int i = 0; i < numPages; i++) {
        time++;

        if (!isPageInFrame(frames, numFrames, pages[i])) {
            int lru = 0;
            for (int j = 1; j < numFrames; j++) {
                if (leastRecentlyUsed[j] < leastRecentlyUsed[lru]) {
                    lru = j;
                }
            }

            // Replace the least recently used page
            frames[lru] = pages[i];
            pageFaults++;
        }

        // Update the access time for the current page
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                leastRecentlyUsed[j] = time;
            }
        }
    }

    return pageFaults;
}

// Optimal Algorithm
int Optimal(int pages[], int numPages, int frames[], int numFrames) {
    int pageFaults = 0;

    for (int i = 0; i < numPages; i++) {
        if (!isPageInFrame(frames, numFrames, pages[i])) {
            int farthest = -1, replace = 0;

            // Find the page that will be used farthest in the future (or never)
            for (int j = 0; j < numFrames; j++) {
                int k;
                for (k = i + 1; k < numPages; k++) {
                    if (frames[j] == pages[k]) break;
                }

                // If the page is not used again, or is used the farthest away, replace it
                if (k > farthest) {
                    farthest = k;
                    replace = j;
                }
            }

            // Replace the page in the selected frame
            frames[replace] = pages[i];
            pageFaults++;
        }
    }

    return pageFaults;
}

int main() {
    int pages[MAX], frames[MAX];
    int numPages, numFrames;

    // Input data
    printf("Enter number of pages: ");
    scanf("%d", &numPages);
    printf("Enter page reference sequence: ");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter number of frames (at least 3): ");
    scanf("%d", &numFrames);

    // Initialize frames to -1 (indicating empty frames)
    for (int i = 0; i < numFrames; i++) frames[i] = -1;

    // Compute page faults for each algorithm
    printf("FCFS Page Faults: %d\n", FCFS(pages, numPages, frames, numFrames));

    // Reset frames
    for (int i = 0; i < numFrames; i++) frames[i] = -1;
    printf("LRU Page Faults: %d\n", LRU(pages, numPages, frames, numFrames));

    // Reset frames
    for (int i = 0; i < numFrames; i++) frames[i] = -1;
    printf("Optimal Page Faults: %d\n", Optimal(pages, numPages, frames, numFrames));

    return 0;
}

