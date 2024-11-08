#include <stdio.h>

// Structure to hold process attributes
typedef struct {
    int pid;            // Process ID
    int arrival_time;   // Arrival time of the process
    int burst_time;     // Burst time of the process
    int remaining_time; // Remaining burst time of the process
    int turnaround_time; // Turnaround time of the process
    int completed;      // Flag to check if the process has completed execution
} Process;

// Function to perform RR scheduling
void roundRobin(Process processes[], int n, int quantum) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    float average_waiting_time, average_turnaround_time;

    // Initialize the remaining times and completion flags
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = 0;
    }

    int current_time = 0;
    // Process until all processes are completed
    while (1) {
        int done = 1;
        // Traverse all processes one by one repeatedly
        for (int i = 0; i < n; i++) {
            // If burst time of a process is greater than 0 then only need to process further
            if (processes[i].remaining_time > 0) {
                done = 0; // There is a pending process

                if (processes[i].remaining_time > quantum) {
                    // Increase the value of current_time by quantum
                    current_time += quantum;
                    // Decrease the remaining_time of current process by quantum
                    processes[i].remaining_time -= quantum;
                } else {
                    // Last cycle for this process
                    // Increase the value of current_time by remaining_time of the process
                    current_time += processes[i].remaining_time;
                    // Calculate turnaround time
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    // Mark the process as completed
                    processes[i].completed = 1;
                    // Increase the total_waiting_time by turnaround time minus burst time
                    total_waiting_time += processes[i].turnaround_time - processes[i].burst_time;
                    // Increase the total_turnaround_time by turnaround time
                    total_turnaround_time += processes[i].turnaround_time;
                    // Reset remaining time for the process
                    processes[i].remaining_time = 0;
                }
            }
        }

        // If all processes are done, break the loop
        if (done == 1)
            break;
    }

    // Calculate averages
    average_waiting_time = (float)total_waiting_time / n;
    average_turnaround_time = (float)total_turnaround_time / n;

    // Print results
    printf("\n\nProcess\t Arrival Time\t Burst Time\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].turnaround_time - processes[i].burst_time,
               processes[i].turnaround_time);
    }
    printf("\nAverage Waiting Time: %.2f", average_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", average_turnaround_time);
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    // Input time quantum
    printf("Enter Time Quantum for Round Robin: ");
    scanf("%d", &quantum);

    // Perform Round Robin scheduling
    roundRobin(processes, n, quantum);

    return 0;
}

