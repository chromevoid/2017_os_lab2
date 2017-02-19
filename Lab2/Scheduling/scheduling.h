//
// Created by Chrome on 2/17/17.
//

#ifndef SCHEDULING_SCHEDULING_H
#define SCHEDULING_SCHEDULING_H

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <queue> // std::priority_queue
#include <algorithm> // std::sort

class Process {
    int A; // the arrival time of the process
    int B; // CPU burst time interval
    int C; // the total CPU time
    int M; // the I/O burst time for a process is its preceding CPU burst time multiplied by M
    int CPU_burst;
    int IO_burst;
    std::string status;
public:
    Process(int a, int b, int c, int m) {
        A = a;
        B = b;
        C = c;
        M = m;
        CPU_burst = 0;
        IO_burst = 0;
        status = "unstarted";
    }
    int get_A() const {
        return A;
    }
    int get_B() const {
        return B;
    }
    int get_C() const {
        return C;
    }
    int get_M() const {
        return M;
    }
    int get_CPU_burst() const {
        return CPU_burst;
    }
    int get_IO_burst() const {
        return IO_burst;
    }
    std::string get_status() {
        if (status == "ready")
            return status + ": " + std::to_string(0);
        if (status == "blocked")
            return status + ": " + std::to_string(get_IO_burst());
        if (status == "running")
            return status + ": " + std::to_string(get_CPU_burst());
        if (status == "terminated")
            return status + ": " + std::to_string(0);
        return status + ": " + std::to_string(0);
    }
    void change_C(int new_c) {
        C = new_c;
    }
    void change_CPU_burst(int new_Cb) {
        CPU_burst = new_Cb;
    }
    void change_IO_burst(int new_IOb) {
        IO_burst = new_IOb;
    }
    void get_Ready() {
        status = "ready";
    }
    void get_Blocked() {
        status = "blocked";
    }
    void get_Running() {
        status = "running";
    }
    void get_Terminated() {
        status = "terminated";
    }
    bool operator < (const Process p1) const {
        return (A < p1.get_A());
    }
    friend std::ostream &operator << (std::ostream & out, const Process p) {
        out << "(" << p.A << " " << p.B << " " << p.C << " " << p.M << ")";
        return out;
    }
};

void get_input(int & process_number, std::deque<Process> & P) {
    std::cin >> process_number;
    for (int i = 0; i < process_number; i++) {
        char left, right;
        int a, b, c, m;
        std::cin >> left >> a >> b >> c >> m >> right;
        Process tmp_p(a, b, c, m);
        P.push_back(tmp_p);
    }
    std::cin.clear();
    std::cin.sync();
}

int randomOS(int U, FILE *pFile) {
    unsigned int X;
    if ( ! feof (pFile) )
        // problem: fscanf return value ???
        if ( fscanf (pFile , "%i" , &X) != EOF ) {
            std::cout << "Find burst when choosing ready process to run " << std::to_string(X) << std::endl;
            return (1 + X % U);
        }
    return 0;
}

void FCFS(int process_number, std::deque<Process> & P, FILE *pFile) {
    std::vector<Process*> unstarted;
    for (int i = 0; i < P.size(); i++) unstarted.push_back(&P[i]);
    std::queue<Process, std::deque<Process*>> ready;
    std::vector<Process*> running;
    std::vector<Process*> blocked;
    int cycle_count = 0;
    while (!unstarted.empty() || !ready.empty() || !running.empty() || !blocked.empty()) {
        if (cycle_count == 2282) break;
        // print the cycle info
        std::cout << "Before cycle " << cycle_count <<": ";
        for (int i = 0; i < process_number; i++) {
            std::cout << P[i].get_status() << "      ";
        }
        std::cout << std::endl;
        // check if the process arrives
        for (int i = 0; i < unstarted.size(); i++) {
            if ((*unstarted[i]).get_A() == cycle_count) {
                (*unstarted[i]).get_Ready();
                ready.push(unstarted[i]);
                unstarted.erase(unstarted.begin());
                i--;
            }
            else break;
        }
        // deal with the blocked processes
        for (int i = 0; i < blocked.size(); i++) {
            // change the burst count
            (*blocked[i]).change_IO_burst((*blocked[i]).get_IO_burst() - 1);
            // if the block is over
            if ((*blocked[i]).get_IO_burst() == 0) {
                (*blocked[i]).get_Ready();
                ready.push(blocked[i]);
                blocked.erase(blocked.begin() + i);
                i--;
            }
        }
        // if a process is running
        if (!running.empty()) {
            // change the burst and remaining time
            (*running[0]).change_CPU_burst((*running[0]).get_CPU_burst() - 1);
            (*running[0]).change_C((*running[0]).get_C() - 1);
            // it can terminate (remaining CPU time goes to zero)
            if ((*running[0]).get_C() == 0) {
                (*running[0]).get_Terminated();
                running.pop_back();
            }
                // it can block (remaining CPU burst time goes to zero)
            else if ((*running[0]).get_CPU_burst() == 0) {
                (*running[0]).get_Blocked();
                blocked.push_back(running[0]);
                running.pop_back();
            }
            // it can be preempted (e.g., the RR quantum goes to zero): not applicable in FCFS
        }
        // if no process is running
        if (running.empty()) {
            // if exists ready process
            if (!ready.empty()) {
                // get the first ready process and delete it from the ready queue
                Process * tmp_p = ready.front();
                ready.pop();
                // assign CPU burst time
                int random_number = randomOS((*tmp_p).get_B(), pFile);
                if (random_number > (*tmp_p).get_C()) { random_number = (*tmp_p).get_C(); }
                (*tmp_p).change_CPU_burst(random_number);
                (*tmp_p).change_IO_burst(random_number * (*tmp_p).get_M());
                // change status
                (*tmp_p).get_Running();
                // push it into the running queue;
                running.push_back(tmp_p);
            }
        }
        cycle_count++;
    }

    std::cout << "The scheduling algorithm used was First Come First Served." << std::endl;
}

#endif //SCHEDULING_SCHEDULING_H
