#include "scheduling.h"

void process(bool verbose, bool random) {
    // define variables
    int process_number = 0;
    std::deque<Process> P;
    get_input(process_number, P);

    // get input and print the info
    std::cout << "The original input was: " << process_number << " ";
    for (int i = 0; i < process_number; i++)
        std::cout << P[i] << " ";
    std::cout << std::endl;
    std::sort(P.begin(), P.end());
    std::cout << "The (sorted) input is: " << process_number << " ";
    for (int i = 0; i < process_number; i++) {
        std::cout << P[i] << " ";
        P[i].set_input_order(i);
    }
    std::cout << std::endl;

    // file open & close: http://www.cplusplus.com/reference/cstdio/FILE/
    FILE * pFile;
    pFile = fopen ("random-numbers.txt" , "r");
    if (pFile == NULL) {
        perror ("Error opening file");
        return;
    }
    FCFS(process_number, P, pFile, verbose, random);
    fclose (pFile);

    pFile = fopen ("random-numbers.txt" , "r");
    RR(process_number, P, pFile, verbose, random);
    fclose (pFile);

    pFile = fopen ("random-numbers.txt" , "r");
    Uniprocessing(process_number, P, pFile, verbose, random);
    fclose (pFile);

    pFile = fopen ("random-numbers.txt" , "r");
    SJF(process_number, P, pFile, verbose, random);
    fclose (pFile);

}

int main(int argc, char const * argv[]) {
    bool verbose = false;
    bool random = false;
    if (argc > 1) {
        int count = 1;
        if (std::string(argv[count]) == "--verbose") {
            verbose = true;
            count++;
            if (std::string(argv[count]) == "--random") {
                random = true;
                count++;
            }
        }
        for (int i = count; i < argc; i++) {
            std::cin.clear();
            std::cin.sync();
//            if (i == 5) {
//                freopen(argv[i], "r", stdin);
//                process(verbose, random);
//            }
            FILE * pFile;
            pFile = fopen (argv[i] , "r");
            if (pFile == NULL) {
                perror ("Error opening file");
                return 0;
            }
            fclose (pFile);
            freopen(argv[i], "r", stdin);
            process(verbose, random);
        }
    }
    else {
        std::cout << "No file" << std::endl;
    }
    return 0;
}
