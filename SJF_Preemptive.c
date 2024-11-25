#include <stdio.h>
#include <limits.h>
typedef struct {
int pid;
int arrival_time;
int burst_time;
int remaining_time;
int completion_time;
int waiting_time;
int turnaround_time;
} Process;
void calculateTimes(Process processes[], int n) {
int current_time = 0, completed = 0, min_index;
int min_remaining_time = INT_MAX;
int finish_time, check = 0;
while (completed != n) {
for (int i = 0; i < n; i++) {
if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_remaining_time) {
min_remaining_time = processes[i].remaining_time;
min_index = i;
check = 1;
}
}
if (check == 0) {
current_time++;
continue;
}
processes[min_index].remaining_time--;
min_remaining_time = processes[min_index].remaining_time;
if (min_remaining_time == 0) {
min_remaining_time = INT_MAX;
}
if (processes[min_index].remaining_time == 0) {
completed++;
check = 0;
finish_time = current_time + 1;
processes[min_index].completion_time = finish_time;
processes[min_index].turnaround_time = finish_time - processes[min_index].arrival_time;
processes[min_index].waiting_time = processes[min_index].turnaround_time - processes[min_index].burst_time;
}
current_time++;
}
}
void calculateAverages(Process processes[], int n, double *avg_wt, double *avg_tat) {
int total_wt = 0, total_tat = 0;
for (int i = 0; i < n; i++) {
total_wt += processes[i].waiting_time;
total_tat += processes[i].turnaround_time;
}
*avg_wt = (double)total_wt / n;
*avg_tat = (double)total_tat / n;
}
int main() {
int n;
printf("Enter the number of processes: ");
scanf("%d", &n);
Process processes[n];
for (int i = 0; i < n; i++) {
printf("Enter Process ID, Arrival Time, and Burst Time for process %d: ", i + 1);
scanf("%d %d %d", &processes[i].pid, &processes[i].arrival_time, &processes[i].burst_time);
processes[i].remaining_time = processes[i].burst_time;
}
calculateTimes(processes, n);
double avg_wt, avg_tat;
calculateAverages(processes, n, &avg_wt, &avg_tat);
printf("\nProcess ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time\n");
for (int i = 0; i < n; i++) {
printf(" %d | %d | %d | %d | %d | %d\n",
processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
}
printf("\nAverage Waiting Time: %.2f\n", avg_wt);
printf("Average Turnaround Time: %.2f\n", avg_tat);
return 0;
}
/*
2 1
1 5
4 1
0 6
2 3
ct 
3
16
5
11
7
*/
