#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
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
        printf("-------------------------------\n");
        printf("Entering the child Process:%d\n", (int)getpid());
        printf("The sorted array is: \n");
        bubble_sort(arr, n);
        printf("\nChild Process %d finished\n",getpid());
        printf("-------------------------------\n");
        printf("Parent waiting for child\n");
        wait(0);
        printf("Parent Wait Finished\n");
        printf("-------------------------------\n");
        printf("\nExiting the program\n");
    } else {
        printf("Parrent id:%d\n", (int)getpid());
        printf("Child id: %d\n", (int)child_t);
    }
    return 0;
}
