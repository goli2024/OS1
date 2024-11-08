//Disk Scheduling Algorithm 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void SSTF(int requests[], int head, int n) 
{
    int seek = 0, diff, completed = 0;
    int visited[n], sequence[n];
    
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        int min = 1e9, index = -1;
        for (int j = 0; j < n; j++) 
{
            if (!visited[j]) {
                diff = abs(requests[j] - head);
                if (diff < min) {
                    min = diff;
                    index = j;
                }
            }
        }
        seek += abs(requests[index] - head);
        head = requests[index];
        sequence[completed++] = head;
        visited[index] = 1;
    }
    
    printf("SSTF Total Seek Time: %d\n", seek);
    printf("SSTF Seek Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");
}

void SCAN(int requests[], int head, int n, int disk_size, int direction) {
    int seek = 0, completed = 0;
    int sequence[n + 2], temp[n + 2];
    
    for (int i = 0; i < n; i++) {
        temp[i] = requests[i];
    }
    temp[n] = 0;
    temp[n + 1] = disk_size - 1;
    n += 2;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }
    
    int pos;
    for (int i = 0; i < n; i++) {
        if (temp[i] >= head) {
            pos = i;
            break;
        }
    }
    
    if (direction == 1) {
        for (int i = pos; i < n; i++) {
            sequence[completed++] = temp[i];
        }
        for (int i = pos - 1; i >= 0; i--) {
            sequence[completed++] = temp[i];
        }
    } else {
        for (int i = pos - 1; i >= 0; i--) {
            sequence[completed++] = temp[i];
        }
        for (int i = pos; i < n; i++) {
            sequence[completed++] = temp[i];
        }
    }
    
    for (int i = 1; i < completed; i++) {
        seek += abs(sequence[i] - sequence[i - 1]);
    }
    
    printf("SCAN Total Seek Time: %d\n", seek);
    printf("SCAN Seek Sequence: ");
    for (int i = 0; i < completed; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");
}

void CLOOK(int requests[], int head, int n, int disk_size) {
    int seek = 0, completed = 0;
    int sequence[n + 1], temp[n];
    
    for (int i = 0; i < n; i++) {
        temp[i] = requests[i];
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }
    
    int pos;
    for (int i = 0; i < n; i++) {
        if (temp[i] >= head) {
            pos = i;
            break;
        }
    }
    
    for (int i = pos; i < n; i++) {
        sequence[completed++] = temp[i];
    }
    for (int i = 0; i < pos; i++) {
        sequence[completed++] = temp[i];
    }
    
    for (int i = 1; i < completed; i++) {
        seek += abs(sequence[i] - sequence[i - 1]);
    }
    
    printf("C-LOOK Total Seek Time: %d\n", seek);
    printf("C-LOOK Seek Sequence: ");
    for (int i = 0; i < completed; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");
}

int main() {
    int n, head, disk_size, direction;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    
    int requests[n];
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);
    
    printf("Enter the direction for SCAN (1 for high, 0 for low): ");
    scanf("%d", &direction);
        SSTF(requests, head, n);
    
    SCAN(requests, head, n, disk_size, direction);
    
    CLOOK(requests, head, n, disk_size);
    return 0;
}


