#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
void bubble_sort(int arr[], int n) {
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<n-i-1;j++)
    	{
    		if(arr[j]>arr[j+1])
    		{
    			int temp = arr[j];
    			arr[j] = arr[j+1];
    			arr[j+1] = temp;
    		}
    	}
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}
int main() {
    int n = 0;
    int i = 0;
    printf("Enter number of elements:");
    scanf("%d", &n);
    printf("-------------------------------\n");
    int arr[n];
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    pid_t child_t;
    child_t = fork();
    if (child_t < 0) {
        printf("child not found");
    } else if (child_t == 0) {
        printf("\nEntering the child Process:%d\n", (int)getpid());
        printf("-------------------------------\n");
        printf("The sorted array is: \n");
        bubble_sort(arr, n);
        printf("-------------------------------\n");
        
        char *args[20];
        args[0] = (char *)"./display_reverse";
        args[1] = NULL;

        for (int i = 0; i < n; i++) {
            args[i + 1] = (char *)malloc(20 * sizeof(char));
            sprintf(args[i + 1], "%d", arr[i]);
        }
        args[n + 1] = NULL;

        // Execute child program
        printf("Calling execve:\n");
        execve(args[0], args, NULL);
        printf("\nEntering the child Process:%d\n", (int)getpid());

    } else {
        printf("Parrent id:%d\n", (int)getpid());
        printf("Child id: %d\n", (int)child_t);
    }
    return 0;
}

