//
// Created by Chrome on 2/17/17.
//

#ifndef SCHEDULING_SCHEDULING_H
#define SCHEDULING_SCHEDULING_H

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <sstream> // read file as standard input
#include <vector>
#include <deque>
#include <queue> // std::priority_queue
#include <algorithm>
#include <limits>
#include <iostream>

class Process {
    int input_order;
    int A; // the arrival time of the process
    int B; // CPU burst time interval
    int C_for_print; // the total CPU time for print
    int C; // the total CPU time
    int M; // the I/O burst time for a process is its preceding CPU burst time multiplied by M
    int CPU_burst, IO_burst;
    std::string status;
    int finishing_time, turnaround_time, IO_time, waiting_time;
public:
    Process(int a, int b, int c, int m) {
        input_order = 0;
        A = a;
        B = b;
        C_for_print = c;
        C = c;
        M = m;
        CPU_burst = 0;
        IO_burst = 0;
        status = "unstarted";
        finishing_time = 0;
        turnaround_time = 0;
        IO_time = 0;
        waiting_time = 0;
    }
    int get_input_order() const { return input_order; }
    int get_A() const { return A; }
    int get_B() const { return B; }
    int get_C_for_print() const { return C_for_print; }
    int get_C() const { return C; }
    int get_M() const { return M; }
    int get_CPU_burst() const { return CPU_burst; }
    int get_IO_burst() const { return IO_burst; }
    std::string get_status() {
        if (status == "ready")
            return status + "  " + std::to_string((int) 0);
        if (status == "blocked")
            return status + "  " + std::to_string((int) get_IO_burst());
        if (status == "running")
            return status + "  " + std::to_string((int) get_CPU_burst());
        if (status == "terminated")
            return status + "  0";
        return status + "  0";
    }
    int get_finishing_time() const { return finishing_time; }
    int get_turnaround_time() const { return turnaround_time; }
    int get_IO_time() const { return IO_time; }
    int get_waitng_time() const { return waiting_time; }
    void set_input_order(int i) { input_order = i; }
    void change_C(int new_c) { C = new_c; }
    void change_CPU_burst(int new_Cb) { CPU_burst = new_Cb; }
    void change_IO_burst(int new_IOb) { IO_burst = new_IOb; }
    void set_finishing_time(int ft) { finishing_time = ft; }
    void set_turnaround_time(int tt) { turnaround_time = tt; }
    void set_IO_time(int iot) { IO_time = iot; }
    void set_waiting_time(int wt) { waiting_time = wt; }
    void get_Ready() { status = "ready"; }
    void get_Blocked() { status = "blocked"; }
    void get_Running() { status = "running"; }
    void get_Terminated() { status = "terminated"; }
    void print_info() {
        std::cout << "\t(A, B, C, M) = "
                  << "\t(" << A << ", " << B << ", " << C_for_print << ", " << M << ")" << std::endl;
        std::cout << "\tFinishing time: " << finishing_time << std::endl;
        std::cout << "\tTurnaround time: " << turnaround_time << std::endl;
        std::cout << "\tI/O time: " << IO_time << std::endl;
        std::cout << "\tWaiting time: " << waiting_time << std::endl;
    }
    friend bool operator < (const Process p1, const Process p2) {
        if (p1.A < p2.A)
            return true;
        if (p1.A == p2.A)
            if (p1.input_order < p2.input_order)
                return true;
        return false;
    }
    friend bool operator > (const Process p1, const Process p2) {
        if (p1.A > p2.A)
            return true;
        if (p1.A == p2.A)
            if (p1.input_order > p2.input_order)
                return true;
        return false;
    }
    friend std::ostream &operator << (std::ostream & out, const Process p) {
        out << "(" << p.A << " " << p.B << " " << p.C_for_print << " " << p.M << ")";
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int randomOS(int U, FILE *pFile, bool random) {
    unsigned int X;
    if ( ! feof (pFile) )
        // problem: fscanf return value ???
        if ( fscanf (pFile , "%i" , &X) != EOF ) {
            if (random) std::cout << "Find burst when choosing ready process to run " << std::to_string((unsigned int) X) << std::endl;
            return (1 + X % U);
        }
    return 0;
}

void print_result(int process_number, std::deque<Process> P, double total_cpu, double total_turnaround_time,
                  double total_waiting_time, int cycle_count, double total_io) {
    for (int i = 0; i < P.size(); i++) {
        std::cout << "Process " << i << ":" << std::endl;
        P[i].print_info();
        std::cout << std::endl;
        total_cpu += P[i].get_C_for_print();
        total_turnaround_time += P[i].get_turnaround_time();
        total_waiting_time += P[i].get_waitng_time();
    }

    cycle_count -= 1;
    std::cout.precision(6);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    std::cout << "Summary Data:" << std::endl;
    std::cout << "\tFinishing time: " << cycle_count << std::endl;
    std::cout << "\tCPU Utilization: " << total_cpu/cycle_count << std::endl;
    std::cout << "\tI/O Utilization: " << total_io/cycle_count << std::endl;
    std::cout << "\tThroughput: " << process_number * 100.00 / cycle_count
              << " processes per hundred cycles" << std::endl;
    std::cout << "\tAverage turnaround time: " << total_turnaround_time/process_number << std::endl;
    std::cout << "\tAverage waiting time: " << total_waiting_time/process_number << std::endl;
    std::cout << std::endl;
}

void FCFS(int process_number, std::deque<Process> & P, FILE *pFile, bool verbose, bool random) {
    std::vector<Process*> unstarted;
    for (int i = 0; i < P.size(); i++) unstarted.push_back(&P[i]);
    std::queue<Process, std::deque<Process*>> ready;
    std::vector<Process*> running;
    std::vector<Process*> blocked;
    double total_cpu = 0;
    double total_io = 0;
    double total_turnaround_time = 0;
    double total_waiting_time = 0;

    int cycle_count = 0;
    if (verbose) std::cout << "\nThis detailed printout gives the state and remaining burst for each process.\n" << std::endl;
    while (!unstarted.empty() || !ready.empty() || !running.empty() || !blocked.empty()) {
        // if verbose is true, then print the cycle info
        if (verbose) {
            std::cout << "Before cycle " << std::setw(5) << cycle_count << ": ";
            for (int i = 0; i < process_number; i++)
                std::cout << std::setw(15) << P[i].get_status();
            std::cout << std::endl;
        }
        // deal with the blocked processes
        if (!blocked.empty()) total_io++;
        for (int i = 0; i < blocked.size(); i++) {
            // change the burst count
            (*blocked[i]).change_IO_burst((*blocked[i]).get_IO_burst() - 1);
            // if the blocked status is over
            if ((*blocked[i]).get_IO_burst() == 0) {
                (*blocked[i]).get_Ready();
                ready.push(blocked[i]);
                blocked.erase(blocked.begin() + i);
                i--;
            }
        }
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
        // if a process is running
        if (!running.empty()) {
            // change the burst and remaining time
            (*running[0]).change_CPU_burst((*running[0]).get_CPU_burst() - 1);
            (*running[0]).change_C((*running[0]).get_C() - 1);
            // it can terminate (remaining CPU time goes to zero)
            if ((*running[0]).get_C() == 0) {
                (*running[0]).get_Terminated();
                (*running[0]).set_finishing_time(cycle_count);
                (*running[0]).set_turnaround_time(cycle_count - (*running[0]).get_A());
                (*running[0]).set_waiting_time((*running[0]).get_turnaround_time()
                                               - (*running[0]).get_IO_time() - (*running[0]).get_C_for_print());
                running.pop_back();
            }
                // it can block (remaining CPU burst time goes to zero)
            else if ((*running[0]).get_CPU_burst() == 0) {
                (*running[0]).get_Blocked();
                (*running[0]).set_IO_time((*running[0]).get_IO_time() + (*running[0]).get_IO_burst());
                blocked.push_back(running[0]);
                running.pop_back();
                // sort the blocked vector according to "lab 2 tie-breaking rule"
                std::sort (blocked.begin(), blocked.end());
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
                int random_number = randomOS((*tmp_p).get_B(), pFile, random);
                if (random_number > (*tmp_p).get_C())
                    random_number = (*tmp_p).get_C();
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

    std::cout << "\nThe scheduling algorithm used was First Come First Served.\n" << std::endl;
    print_result(process_number, P, total_cpu, total_turnaround_time, total_waiting_time, cycle_count, total_io);
}

void RR(int process_number, std::deque<Process> & P, FILE *pFile, bool verbose, bool random) {
    std::vector<Process*> unstarted;
    for (int i = 0; i < P.size(); i++) unstarted.push_back(&P[i]);
    std::queue<Process*, std::deque<Process*>> ready;
    std::vector<Process*> running;
    std::vector<Process*> blocked;
    std::vector<Process*> tmp_end;
    int q = 2;
    int q_count = 0;
    double total_cpu = 0;
    double total_io = 0;
    double total_turnaround_time = 0;
    double total_waiting_time = 0;

    bool ready_empty = false;
    if (ready.empty()) ready_empty = true;

    int cycle_count = 0;
    if (verbose) std::cout << "\nThis detailed printout gives the state and remaining burst for each process.\n" << std::endl;
    while (!unstarted.empty() || !ready.empty() || !running.empty() || !blocked.empty()) {
        // if verbose is true, then print the cycle info
        if (verbose) {
            std::cout << "Before cycle " << std::setw(5) << cycle_count << ": ";
            for (int i = 0; i < process_number; i++)
                std::cout << std::setw(15) << P[i].get_status();
            std::cout << std::endl;
        }
        // check if the process arrives
        for (int i = 0; i < unstarted.size(); i++) {
            if ((*unstarted[i]).get_A() == cycle_count) {
                (*unstarted[i]).get_Ready();
                tmp_end.push_back(unstarted[i]);
                unstarted.erase(unstarted.begin());
                i--;
            }
            else break;
        }
        // deal with the blocked processes
        if (!blocked.empty()) total_io++;
        for (int i = 0; i < blocked.size(); i++) {
            // change the burst count
            (*blocked[i]).change_IO_burst((*blocked[i]).get_IO_burst() - 1);
            // if the blocked status is over
            if ((*blocked[i]).get_IO_burst() == 0) {
                (*blocked[i]).get_Ready();
                // use tmp vector to store the blocked-end process
                // so these process won't be handled in ready queue in this round
                tmp_end.push_back(blocked[i]);
                blocked.erase(blocked.begin() + i);
                i--;
            }
        }
        // if a process is running
        if (!running.empty()) {
            q_count++;
            // change the burst and remaining time
            (*running[0]).change_CPU_burst((*running[0]).get_CPU_burst() - 1);
            (*running[0]).change_C((*running[0]).get_C() - 1);
            // it can terminate (remaining CPU time goes to zero)
            if ((*running[0]).get_C() == 0) {
                (*running[0]).get_Terminated();
                (*running[0]).set_finishing_time(cycle_count);
                (*running[0]).set_turnaround_time(cycle_count - (*running[0]).get_A());
                (*running[0]).set_waiting_time((*running[0]).get_turnaround_time()
                                               - (*running[0]).get_IO_time() - (*running[0]).get_C_for_print());
                running.pop_back();
                q_count = 0;
            }
            // it can block (remaining CPU burst time goes to zero)
            else if ((*running[0]).get_CPU_burst() == 0) {
                (*running[0]).get_Blocked();
                (*running[0]).set_IO_time((*running[0]).get_IO_time() + (*running[0]).get_IO_burst());
                blocked.push_back(running[0]);
                running.pop_back();
                q_count = 0;
            }
            // it can be preempted (e.g., the RR quantum goes to zero)
            else if (q_count == q) {
                (*running[0]).get_Ready();
                tmp_end.push_back(running[0]);
                running.pop_back();
                q_count = 0;
            }
        }
        std::sort(tmp_end.begin(), tmp_end.end());
        // if no process is running
        if (running.empty()) {
            if (ready_empty) {
                for (int i = 0; i < tmp_end.size(); i++)
                    ready.push(tmp_end[i]);
                tmp_end.clear();
            }
            // if exists ready process
            if (!ready.empty()) {
                // get the first ready process and delete it from the ready queue
                Process * tmp_p = ready.front();
                ready.pop();
                if ((*tmp_p).get_CPU_burst() == 0) {
                    // assign CPU burst time
                    int random_number = randomOS((*tmp_p).get_B(), pFile, random);
                    if (random_number > (*tmp_p).get_C())
                        random_number = (*tmp_p).get_C();
                    (*tmp_p).change_CPU_burst(random_number);
                    (*tmp_p).change_IO_burst(random_number * (*tmp_p).get_M());
                }
                // change status
                (*tmp_p).get_Running();
                // push it into the running queue;
                running.push_back(tmp_p);
            }
        }

        // now the ready queue is done, push the blocked-end processes into the queue;
        for (int i = 0; i < tmp_end.size(); i++)
            ready.push(tmp_end[i]);
        tmp_end.clear();

        cycle_count++;
    }

    std::cout << "\nThe scheduling algorithm used was Round Robbin.\n" << std::endl;
    print_result(process_number, P, total_cpu, total_turnaround_time, total_waiting_time, cycle_count, total_io);
}

void Uniprocessing(int process_number, std::deque<Process> &P, FILE *pFile, bool verbose, bool random) {
    std::vector<Process*> unstarted;
    for (int i = 0; i < P.size(); i++) unstarted.push_back(&P[i]);
    auto compareP = [](Process* p1, Process* p2) { return (*p1) > (*p2); };
    std::priority_queue<Process*, std::vector<Process*>, decltype(compareP)> ready(compareP);
    Process* running = NULL;
    Process* blocked = NULL;
    double total_cpu = 0;
    double total_io = 0;
    double total_turnaround_time = 0;
    double total_waiting_time = 0;

    int cycle_count = 0;
    if (verbose) std::cout << "\nThis detailed printout gives the state and remaining burst for each process.\n" << std::endl;
    while (!unstarted.empty() || !ready.empty() || running != NULL || blocked != NULL) {
        // if verbose is true, then print the cycle info
        if (verbose) {
            std::cout << "Before cycle " << std::setw(5) << cycle_count << ": ";
            for (int i = 0; i < process_number; i++)
                std::cout << std::setw(15) << P[i].get_status();
            std::cout << std::endl;
        }
        // deal with the blocked processes
        if (blocked != NULL) {
            total_io++;
            (*blocked).change_IO_burst((*blocked).get_IO_burst() - 1);
            if ((*blocked).get_IO_burst() == 0) {
                (*blocked).get_Ready();
                ready.push(blocked);
                blocked = NULL;
            }
        }
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
        // if a process is running
        if (running != NULL) {
            // change the burst and remaining time
            (*running).change_CPU_burst((*running).get_CPU_burst() - 1);
            (*running).change_C((*running).get_C() - 1);
            // it can terminate (remaining CPU time goes to zero)
            if ((*running).get_C() == 0) {
                (*running).get_Terminated();
                (*running).set_finishing_time(cycle_count);
                (*running).set_turnaround_time(cycle_count - (*running).get_A());
                (*running).set_waiting_time((*running).get_turnaround_time()
                                               - (*running).get_IO_time() - (*running).get_C_for_print());
                running = NULL;
            }
                // it can block (remaining CPU burst time goes to zero)
            else if ((*running).get_CPU_burst() == 0) {
                (*running).get_Blocked();
                (*running).set_IO_time((*running).get_IO_time() + (*running).get_IO_burst());
                blocked = running;
                running = NULL;
            }
            // it can be preempted (e.g., the RR quantum goes to zero): not applicable in Uniprocessing
        }
        // if no process is using CPU
        if (running == NULL && blocked == NULL) {
            // if exists ready process
            if (!ready.empty()) {

                // get the first ready process and delete it from the ready queue
                Process * tmp_p = ready.top();
                ready.pop();
                // assign CPU burst time
                int random_number = randomOS((*tmp_p).get_B(), pFile, random);
                if (random_number > (*tmp_p).get_C())
                    random_number = (*tmp_p).get_C();
                (*tmp_p).change_CPU_burst(random_number);
                (*tmp_p).change_IO_burst(random_number * (*tmp_p).get_M());
                // change status
                (*tmp_p).get_Running();
                // push it into the running queue;
                running = tmp_p;
            }
        }
        cycle_count++;
    }

    std::cout << "\nThe scheduling algorithm used was Uniprocessing.\n" << std::endl;
    print_result(process_number, P, total_cpu, total_turnaround_time, total_waiting_time, cycle_count, total_io);
}

void SJF(int process_number, std::deque<Process> & P, FILE *pFile, bool verbose, bool random) {
    std::vector<Process*> unstarted;
    for (int i = 0; i < P.size(); i++) unstarted.push_back(&P[i]);
    auto compareP = [](Process* p1, Process* p2) {
        if ((*p1).get_C() > (*p2).get_C())
            return true;
        if ((*p1).get_C() < (*p2).get_C())
            return false;
        if ((*p1).get_C() == (*p2).get_C())
            return (*p1) > (*p2);
        return (*p1) > (*p2);

    };
    std::priority_queue<Process*, std::vector<Process*>, decltype(compareP)> ready(compareP);
    std::vector<Process*> running;
    std::vector<Process*> blocked;
    std::vector<Process*> tmp_end;
    double total_cpu = 0;
    double total_io = 0;
    double total_turnaround_time = 0;
    double total_waiting_time = 0;

    bool ready_empty = false;
    if (ready.empty()) ready_empty = true;

    int cycle_count = 0;
    if (verbose) std::cout << "\nThis detailed printout gives the state and remaining burst for each process.\n" << std::endl;
    while (!unstarted.empty() || !ready.empty() || !running.empty() || !blocked.empty()) {
        // if verbose is true, then print the cycle info
        if (verbose) {
            std::cout << "Before cycle " << std::setw(5) << cycle_count << ": ";
            for (int i = 0; i < process_number; i++)
                std::cout << std::setw(15) << P[i].get_status();
            std::cout << std::endl;
        }
        // check if the process arrives
        for (int i = 0; i < unstarted.size(); i++) {
            if ((*unstarted[i]).get_A() == cycle_count) {
                (*unstarted[i]).get_Ready();
                tmp_end.push_back(unstarted[i]);
                unstarted.erase(unstarted.begin());
                i--;
            }
            else break;
        }
        // deal with the blocked processes
        if (!blocked.empty()) total_io++;
        for (int i = 0; i < blocked.size(); i++) {
            // change the burst count
            (*blocked[i]).change_IO_burst((*blocked[i]).get_IO_burst() - 1);
            // if the blocked status is over
            if ((*blocked[i]).get_IO_burst() == 0) {
                (*blocked[i]).get_Ready();
                // use tmp vector to store the blocked-end process
                // so these process won't be handled in ready queue in this round
                tmp_end.push_back(blocked[i]);
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
                (*running[0]).set_finishing_time(cycle_count);
                (*running[0]).set_turnaround_time(cycle_count - (*running[0]).get_A());
                (*running[0]).set_waiting_time((*running[0]).get_turnaround_time()
                                               - (*running[0]).get_IO_time() - (*running[0]).get_C_for_print());
                running.pop_back();
            }
                // it can block (remaining CPU burst time goes to zero)
            else if ((*running[0]).get_CPU_burst() == 0) {
                (*running[0]).get_Blocked();
                (*running[0]).set_IO_time((*running[0]).get_IO_time() + (*running[0]).get_IO_burst());
                blocked.push_back(running[0]);
                running.pop_back();
            }
                // it can be preempted (e.g., the RR quantum goes to zero): not applicable for SJF
        }
        // if no process is running
        if (running.empty()) {
            if (ready_empty) {
                for (int i = 0; i < tmp_end.size(); i++)
                    ready.push(tmp_end[i]);
                tmp_end.clear();
            }
            // if exists ready process
            if (!ready.empty()) {
                // get the first ready process and delete it from the ready queue
                Process * tmp_p = ready.top();
                ready.pop();
                if ((*tmp_p).get_CPU_burst() == 0) {
                    // assign CPU burst time
                    int random_number = randomOS((*tmp_p).get_B(), pFile, random);
                    if (random_number > (*tmp_p).get_C())
                        random_number = (*tmp_p).get_C();
                    (*tmp_p).change_CPU_burst(random_number);
                    (*tmp_p).change_IO_burst(random_number * (*tmp_p).get_M());
                }
                // change status
                (*tmp_p).get_Running();
                // push it into the running queue;
                running.push_back(tmp_p);
            }
        }

        // now the ready queue is done, push the blocked-end processes into the queue;
        for (int i = 0; i < tmp_end.size(); i++)
            ready.push(tmp_end[i]);
        tmp_end.clear();

        cycle_count++;
    }

    std::cout << "\nThe scheduling algorithm used was Shortest Job First.\n" << std::endl;
    print_result(process_number, P, total_cpu, total_turnaround_time, total_waiting_time, cycle_count, total_io);
}

#endif //SCHEDULING_SCHEDULING_H
