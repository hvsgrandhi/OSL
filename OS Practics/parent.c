#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int compare(const void *a, const void *b) {
	return (*(int *)a - *(int *)b);
}
int main() {
	int n;
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	int arr[n];
	printf("Enter %d elements:\n", n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	qsort(arr, n, sizeof(int), compare);
	char n_str[10];
	sprintf(n_str, "%d", n);
	char *args[n + 2];
	args[0] = "./child.out";
	args[n + 1] = NULL;
	for (int i = 0; i < n; i++) {
		args[i + 1] = malloc(10);
		sprintf(args[i + 1], "%d", arr[i]);
	}
	int pid = fork();
	if (pid == 0) {
		// Child process
		execve(args[0], args, NULL);
		perror("execve");
		return 1;
	} 
	else if (pid > 0) {
		// Parent process
		wait(NULL);
		for (int i = 0; i < n; i++) {
			free(args[i + 1]);
		}
	} 
	else {
		perror("fork");
		return 1;
	}
	return 0;
}

