#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <queue>
#include <string.h>
using namespace std;
struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};
bool compare1(process p1, process p2)
{
    return p1.arrival_time < p2.arrival_time;
}
bool compare2(process p1, process p2)
{
    return p1.pid < p2.pid;
}
class Scheduling
{

public:
    void fcfs()
    {
        cout << "\n*************FCFS SCHEDULING**************\n";
        int n;
        cout << "Enter the number of processes: ";
        cin >> n;
        vector<int> AT(n), BT(n), CT(n), TAT(n), WT(n), P(n);
        for (int i = 0; i < n; i++)
        {
            cout << "\nEnter Arrival Time for P[" << i + 1 << "] : ";
            cin >> AT[i];
            cout << "Enter Burst Time for P[" << i + 1 << "] : ";
            cin >> BT[i];
            P[i] = i + 1;
        }
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (AT[i] > AT[j])
                {
                    swap(AT[i], AT[j]);
                    swap(BT[i], BT[j]);
                    swap(P[i], P[j]);
                }
            }
        }
        if (AT[0] > 0)
        {
            CT[0] = AT[0] + BT[0];
        }
        else
        {
            CT[0] = BT[0];
        }
        for (int i = 1; i < n; i++)
        {
            if (CT[i - 1] < AT[i])
            {
                CT[i] = AT[i] + BT[i];
            }
            else
            {
                CT[i] = CT[i - 1] + BT[i];
            }
        }
        for (int i = 0; i < n; i++)
        {
            TAT[i] = CT[i] - AT[i];

            WT[i] = TAT[i] - BT[i];
        }
        cout << "\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
        for (int i = 0; i < n; i++)
        {
            cout << "P" << P[i] << "\t" << AT[i] << "\t" << BT[i] << "\t" << CT[i] << "\t" << TAT[i] << "\t" << WT[i] << "\n";
        }
        float total_wt = 0, total_tat = 0;
        for (int i = 0; i < n; i++)
        {
            total_wt += WT[i];
            total_tat += TAT[i];
        }
        cout << "\nAverage waiting time: " << (total_wt / n) << "\n";
        cout << "Average turnaround time: " << (total_tat / n) << "\n";
    }
    void sjf()
    {
        cout << "\n*************SJF SCHEDULING**************\n";
        int n;
        cout << "Enter the number of processes: ";
        cin >> n;
        vector<int> AT(n), BT(n), CT(n), TAT(n), WT(n), P(n);
        for (int i = 0; i < n; i++)
        {
            cout << "\nEnter Arrival Time for P[" << i + 1 << "] : ";
            cin >> AT[i];
            cout << "Enter Burst Time for P[" << i + 1 << "] : ";
            cin >> BT[i];
            P[i] = i + 1;
        }
        vector<bool> completed(n, false);
        int currentTime = 0, completedProcesses = 0;
        while (completedProcesses < n)
        {
            int idx = -1;
            int minBT = INT_MAX;
            for (int i = 0; i < n; i++)
            {

                if (!completed[i] && AT[i] <= currentTime && BT[i] < minBT)
                {
                    minBT = BT[i];
                    idx = i;
                }
            }
            if (idx != -1)
            {
                currentTime += BT[idx];
                CT[idx] = currentTime;
                completed[idx] = true;
                completedProcesses++;
            }
            else
            {
                currentTime++;
            }
        }
        for (int i = 0; i < n; i++)
        {
            TAT[i] = CT[i] - AT[i];
            WT[i] = TAT[i] - BT[i];
        }
        cout << "\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
        for (int i = 0; i < n; i++)
        {
            cout << "P" << P[i] << "\t" << AT[i] << "\t" << BT[i] << "\t" << CT[i] << "\t" << TAT[i] << "\t" << WT[i] << "\n";
        }
        float total_wt = 0, total_tat = 0;
        for (int i = 0; i < n; i++)
        {
            total_wt += WT[i];
            total_tat += TAT[i];
        }
        cout << "\nAverage waiting time: " << (total_wt / n) << "\n";
        cout << "Average turnaround time: " << (total_tat / n) << "\n";
    }
    void priorityS()
    {
        cout << "\n***************Priority Scheduling************\n";
        int n;
        cout << "Enter the number of processes: ";

        cin >> n;
        vector<int> AT(n), BT(n), Pr(n), P(n), CT(n), TAT(n), WT(n), remainingBT(n);
        vector<bool>
            completed(n, false);
        for (int i = 0; i < n; i++)
        {
            cout << "Enter Arrival Time for P[" << i + 1 << "] : ";
            cin >> AT[i];
            cout << "Enter Burst Time for P[" << i + 1 << "] : ";
            cin >> BT[i];
            cout << "Enter the Priority for P[" << i + 1 << "] : ";
            cin >> Pr[i];
            P[i] = i + 1;
            remainingBT[i] = BT[i];
            cout << endl;
        }
        int currentTime = 0, completedProcesses = 0;
        bool done = false;
        while (!done)
        {
            int idx = -1;
            int highestPriority = INT_MAX;
            for (int i = 0; i < n; i++)
            {
                if (!completed[i] && AT[i] <= currentTime && Pr[i] < highestPriority)
                {
                    highestPriority =
                        Pr[i];
                    idx = i;
                }
            }
            if (idx != -1)
            {
                remainingBT[idx]--;
                currentTime++;
                if (remainingBT[idx] == 0)
                {
                    completed[idx] = true;
                    completedProcesses++;
                    CT[idx] = currentTime;
                    TAT[idx] = CT[idx] - AT[idx];
                    WT[idx] = TAT[idx] - BT[idx];
                }
            }
            else
            {
                currentTime++;
            }
            if (completedProcesses == n)
            {
                done = true;
            }
        }
        cout << "\nProcess\tAT\tBT\tPr\tCT\tTAT\tWT\n";
        for (int i = 0; i < n; i++)
        {
            cout << "P" << P[i] << "\t" << AT[i] << "\t" << BT[i] << "\t" << Pr[i] << "\t" << CT[i]
                 << "\t" << TAT[i] << "\t" << WT[i] << "\n";
        }
        float total_wt = 0, total_tat = 0;
        for (int i = 0; i < n; i++)
        {
            total_wt += WT[i];
            total_tat += TAT[i];
        }
        cout << "\nAverage waiting time: " << (total_wt / n) << "\n";
        cout << "Average turnaround time: " << (total_tat / n) << "\n";
    }
    void RR()
    {
        int n;
        int tq;
        struct process p[100];
        float avg_turnaround_time;
        float avg_waiting_time;
        float avg_response_time;
        float cpu_utilisation;
        int total_turnaround_time = 0;
        int total_waiting_time = 0;
        int total_idle_time = 0;
        int burst_remaining[100];
        int idx;
        cout << setprecision(2) << fixed;
        cout << "\n***************Round Robin Scheduling************\n";

        cout << "Enter the number of processes: ";
        cin >> n;
        cout << "Enter time quantum: ";
        cin >> tq;
        for (int i = 0; i < n; i++)
        {
            cout << "\nEnter arrival time of P[" << i + 1 << "] : ";
            cin >> p[i].arrival_time;
            cout << "Enter burst time of P[" << i + 1 << "] : ";
            cin >> p[i].burst_time;
            burst_remaining[i] = p[i].burst_time;
            p[i].pid = i + 1;
        }
        sort(p, p + n, compare1);
        queue<int> q;
        int current_time = 0;
        q.push(0);
        int completed = 0;
        int mark[100];
        memset(mark, 0, sizeof(mark));
        mark[0] = 1;
        while (completed != n)
        {
            idx = q.front();
            q.pop();
            if (burst_remaining[idx] == p[idx].burst_time)
            {
                p[idx].start_time = max(current_time, p[idx].arrival_time);
                total_idle_time += p[idx].start_time - current_time;
                current_time = p[idx].start_time;
            }
            if (burst_remaining[idx] - tq > 0)
            {
                burst_remaining[idx] -= tq;
                current_time += tq;
            }
            else
            {
                current_time += burst_remaining[idx];
                burst_remaining[idx] = 0;

                completed++;
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time -
                                       p[idx].arrival_time;
                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
            }
            for (int i = 1; i < n; i++)
            {
                if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0)
                {
                    q.push(i);
                    mark[i] = 1;
                }
            }
            if (burst_remaining[idx] > 0)
            {
                q.push(idx);
            }
            if (q.empty())
            {
                for (int i = 1; i < n; i++)
                {
                    if (burst_remaining[i] > 0)
                    {
                        q.push(i);
                        mark[i] = 1;
                        break;
                    }
                }
            }
        }
        avg_turnaround_time = (float)total_turnaround_time / n;
        avg_waiting_time = (float)total_waiting_time / n;
        sort(p, p + n, compare2);
        cout << endl;
        cout << "#P\t" << "AT\t" << "BT\t" << "ST\t" << "CT\t" << "TAT\t" << "WT\t" << "\n"
             << endl;
        for (int i = 0; i < n; i++)
        {
            cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\
t" << p[i].completion_time
                 << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << "\
n";
        }
        cout << "\nAverage Turnaround Time = " << avg_turnaround_time << endl;
        cout << "Average Waiting Time = " << avg_waiting_time << endl;
    }
};
int main()
{
    Scheduling s;
    int ch;
    do
    {
        cout << "\n*******Scheduling********\n";
        cout << "\n1. FCFS";
        cout << "\n2. SJF";
        cout << "\n3. Priority";
        cout << "\n4. Round Robin";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            s.fcfs();
            break;
        case 2:
            s.sjf();
            break;
        case 3:
            s.priorityS();
            break;
        case 4:
            s.RR();
            break;
        case 5:
            exit(0);
            break;
        default:
            cout << "\nINVALID OPTION";
            break;
        }
    } while (ch != 5);
    return 0;
}