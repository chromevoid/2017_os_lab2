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
#include <queue> // std::priority_queue
#include <algorithm> // std::sort

class Process {
    int A; // the arrival time of the process
    int B; // CPU burst time interval
    int C; // the total CPU time
    int M; // the I/O burst time for a process is its preceding CPU burst time multiplied by M
public:
    Process(int a, int b, int c, int m) {
        A = a;
        B = b;
        C = c;
        M = m;
    }
    int get_A() const {
        return A;
    }
    int get_B() const{
        return B;
    }
    int get_C() const{
        return C;
    }
    int get_M() const{
        return M;
    }
    void change_B(int new_b) {
        B = new_b;
    }
    void change_C(int new_c) {
        C = new_c;
    }
    bool operator < (const Process p1) const {
        return (A < p1.get_A());
    }
    friend std::ostream &operator << (std::ostream & out, const Process p) {
        out << "(" << p.A << " " << p.B << " " << p.C << " " << p.M << ")";
        return out;
    }
};

void get_input(int & process_number, std::vector<Process> & P) {
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
    if ( ! feof (pFile) ) {
        if ( fscanf (pFile , "%i" , &X) == NULL );
        else std::cout << X << std::endl;
    }
    return (1 + X % U);
    return 0;
}

#endif //SCHEDULING_SCHEDULING_H
