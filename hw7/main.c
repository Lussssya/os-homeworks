#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process {
	int pid;
	int arrival_time;
	int burst_time;
	int turnaround_time;
	int waiting_time;
	int response_time;
};

int compare (const void *left, const void *right) {
	const struct process p1 = *(const struct process *)left;
	const struct process p2 = *(const struct process *)right;
	
	if (p1.arrival_time < p2.arrival_time) {
		return -1;
	} else if (p1.arrival_time > p2.arrival_time) {
		return 1;
	}

	return 0;
}

struct process calculateProcessInfo (struct process p, int start_time) {
    p.response_time = start_time - p.arrival_time;
    p.waiting_time = p.response_time;
    p.turnaround_time = start_time + p.burst_time - p.arrival_time;

    return p;
}

void fcfs (struct process* processes, int size) {
	printf("\n=== First Come First Served (FCFS) ===\n");

	qsort(processes, size, sizeof(struct process), compare);

	printf("Gantt Chart: |");
	for (int i = 0; i < size; i++) {
		printf(" P%d | ", i + 1);
	}
	printf("\nPID     AT     BT     WT     TAT    RT\n");

	double avg_response_time = 0;
	double avg_waiting_time = 0;
	double avg_turnaround_time = 0;

	int current_time = 0;

	for (int i = 0; i < size; i++) {
		if (current_time < processes[i].arrival_time) {
			current_time = processes[i].arrival_time;
		}

		processes[i] = calculateProcessInfo(processes[i], current_time);
		printf("%d     %d     %d     %d     %d     %d\n", 
				processes[i].pid,
				processes[i].arrival_time,
				processes[i].burst_time,
				processes[i].waiting_time,
				processes[i].turnaround_time,
				processes[i].response_time
			);

		avg_response_time += processes[i].response_time;
		avg_waiting_time += processes[i].waiting_time;
		avg_turnaround_time += processes[i].turnaround_time;

		current_time += processes[i].burst_time;
	}

	avg_response_time /= size;
	avg_waiting_time /= size;
	avg_turnaround_time /= size;

	printf("Average Waiting Time: %.2f\n", avg_waiting_time);
	printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
	printf("Average Response Time: %.2f\n", avg_response_time);
}

void sjf (struct process* processes, int size) {
	printf("\n=== Shortest Job First (SJF) ===\n");

	qsort(processes, size, sizeof(struct process), compare);

	printf("PID     AT     BT     WT     TAT    RT\n");
	double avg_response_time = 0;
        double avg_waiting_time = 0;
        double avg_turnaround_time = 0;

	int i = 0;
	int current_time = 0;

	while (i < size) {
		if (current_time < processes[i].arrival_time) {
			current_time = processes[i].arrival_time;
		}

		int burst_time_idx = i;
		for (int j = i + 1; j < size; j++) {
			if (current_time < processes[j].arrival_time) {
				break;
			} else if (processes[j].burst_time < processes[burst_time_idx].burst_time) {
					burst_time_idx = j;
			}
		}

		struct process temp = processes[burst_time_idx];

		for (int k = burst_time_idx; k > i; k--) {
			processes[k] = processes[k - 1];
		}

		processes[i] = temp;

		processes[i] = calculateProcessInfo(processes[i], current_time);
		printf("%d     %d     %d     %d     %d     %d\n",
				processes[i].pid,
                                processes[i].arrival_time,
                                processes[i].burst_time,
                                processes[i].waiting_time,
                                processes[i].turnaround_time,
                                processes[i].response_time
                        );

		avg_response_time += processes[i].response_time;
		avg_waiting_time += processes[i].waiting_time;
		avg_turnaround_time += processes[i].turnaround_time;

		current_time += processes[i].burst_time;

		i++;
	}

	printf("Gantt Chart: |");
	for (int j = 0; j < size; j++) {
		printf(" P%d |", processes[j].pid);
	}
	printf("\n");

        avg_response_time /= size;
        avg_waiting_time /= size;
        avg_turnaround_time /= size;

        printf("Average Waiting Time: %.2f\n", avg_waiting_time);
        printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
        printf("Average Response Time: %.2f\n", avg_response_time);
}

void createProcesses(struct process *processes, int size) {
    for (int i = 0; i < size; i++) {
        processes[i].pid = i + 1;

        printf("Enter the arrival time and burst time for process %d: ", processes[i].pid);

        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].response_time = 0;
    }
}

int main () {
	int size;
	printf("Enter the number of processes: ");
	scanf("%d", &size);

	struct process *processesFcfs = (struct process *)malloc(size * sizeof(struct process));
	if (processesFcfs == NULL) {
		perror("malloc failed");
		return 1;
	}

	struct process *processesSjf = (struct process *)malloc(size * sizeof(struct process));
	if (processesSjf == NULL) {
                perror("malloc failed");
		free(processesFcfs);
                return 1;
        }

	createProcesses(processesFcfs, size);
	memcpy(processesSjf, processesFcfs, size * sizeof(struct process));

	fcfs(processesFcfs, size);
	sjf(processesSjf, size);

	free(processesFcfs);
	free(processesSjf);
	return 0;
}
