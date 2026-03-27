#include "stdio.h"
#include "unistd.h"
#include "sys/wait.h"
#include "stdlib.h"

int main(void){
	// creating pipe
	int fd[2];
	pipe(fd);

	int id1 = fork();
	int id2 = fork();
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int len_arr = sizeof(arr) / sizeof(int);
	int step = len_arr/3;
	

	// dividing the array to 3 parts in 3 process
	int start, end;
	if (id1 == 0 && id2 != 0){
		start = 0;
		end = step;
	}
	else if (id1 != 0 && id2 == 0){
		start = step;
		end = 2*step;
	}
	else if (id1 != 0 && id2 != 0){
		start = 2*step;
		end = len_arr;
	}
	else {
		return 0;
	}

	// summing different parts of the array
	int sum = 0;
	for (int i=start; i<end; i++){
		sum += arr[i];
	}

	// piping
	if (id1 == 0 && id2 != 0){
		write(fd[1], &sum, sizeof(sum));
		close(fd[0]);
		close(fd[1]);
	}
	else if (id1 != 0 && id2 == 0){
		int sum_child1;
		read(fd[0], &sum_child1, sizeof(sum_child1));
		sum += sum_child1;
		write(fd[1], &sum, sizeof(sum));
		close(fd[0]);
		close(fd[1]);
	}
	else if (id1 != 0 && id2 != 0){
		// parent process wait all other process to finish
		while (wait(NULL) > 0);

		int sum_child2;
		close(fd[1]);
		read(fd[0], &sum_child2, sizeof(sum_child2));
		close(fd[0]);

		int total_sum = sum + sum_child2;
		printf("Total sum: %d\n", total_sum);
		
	}
	
	return 0;
}
