#include "scheduling.h"

int main() {
    int process_number = 0;
    std::vector<Process> P;
    get_input(process_number, P);

    std::cout << "The original input was: " << process_number << " ";
    for (int i = 0; i < process_number; i++)
        std::cout << P[i] << " ";

    return 0;
}