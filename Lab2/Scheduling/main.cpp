#include "scheduling.h"

void process() {
    // http://www.cplusplus.com/reference/cstdio/FILE/
    FILE * pFile;
    pFile = fopen ("random-numbers.txt" , "r");
    if (pFile == NULL) perror ("Error opening file");

    // mine
    int process_number = 0;
    std::deque<Process> P;
    get_input(process_number, P);

    // get input and print the info
    std::cout << "The original input was: " << process_number << " ";
    for (int i = 0; i < process_number; i++)
        std::cout << P[i] << " ";
    std::cout << std::endl;
//    auto compareP = [](Process p1, Process p2) { return p1.get_A() < p2.get_A(); };
//    std::priority_queue<Process, std::vector<Process>, decltype(compareP)> sorted_P(compareP);
    std::sort(P.begin(), P.end());
    std::cout << "The (sorted) input is: " << process_number << " ";
    for (int i = 0; i < process_number; i++)
        std::cout << P[i] << " ";
    std::cout << std::endl;

    // FCFS
    FCFS(process_number, P, pFile);

    if (pFile != NULL) fclose (pFile);
}

int main(int argc, char const * argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            std::cin.clear();
            std::cin.sync();
            freopen(argv[i], "r", stdin);
            process();
        }
    }
    else {
        std::cin.clear();
        std::cin.sync();
        process();
    }
    return 0;
}