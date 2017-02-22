#include "scheduling.h"

void process(bool verbose, bool random) {
    // http://www.cplusplus.com/reference/cstdio/FILE/
    FILE * pFile;
    pFile = fopen ("random-numbers.txt" , "r");
    if (pFile == NULL) perror ("Error opening file");

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

//    FCFS(process_number, P, pFile, verbose, random);
//    RR(process_number, P, pFile, verbose, random);
//    Uniprocessing(process_number, P, pFile, verbose, random);
    SJF(process_number, P, pFile, verbose, random);

    if (pFile != NULL) fclose (pFile);
}

int main(int argc, char const * argv[]) {
    bool verbose = false;
    bool random = false;
    if (argc > 1) {
        int count = 1;
        if (std::string(argv[count]) == "--verbose") {
//            verbose = true;
            count++;
            if (std::string(argv[count]) == "--random") {
//                random = true;
                count++;
            }
        }
        for (int i = count; i < argc; i++) {
            std::cin.clear();
            std::cin.sync();
            if (true) {
                freopen(argv[i], "r", stdin);
                process(verbose, random);
            }
//            freopen(argv[i], "r", stdin);
//            process(verbose, random);
        }
    }
    else {
        std::cout << "No file.";
    }
    return 0;
}
