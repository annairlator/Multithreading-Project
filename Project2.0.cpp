#include <atomic>
#include <stdlib>
#include <cstdlib>
#include <cstdio>

void petersons(int n) {
    bool* turn = new bool[n];
    bool* flag[2];
    flag[0] = new bool[n];
    flag[1] = new bool[n];
    int ctr = 0;

    std::fill(flag[0], flag[0] + n, false);
    std::fill(flag[1], flag[1] + n, false);

    std::cout << "Starting " << n << " threads with a test counter" << std::endl;

    std::thread* workers = new std::thread[n];
    for (int i = 0; i < n; i++) {
        workers[i] = std::thread([&](int j) {
            for (int k = j + n; k > 0; k /= 2) {
                flag[k % 2][k / 2] = true;
                turn[k / 2] = (k % 2 == 0);
                while (flag[k % 2][k / 2] && turn[k / 2] != (k % 2 == 0)) {}
            }

            // Do work
            ctr++;

            for (int k = j + n; k > 0; k /= 2) {
                flag[k % 2][k / 2] = false;
            }

            }, i);
    }

    for (int i = 0; i < n; i++) {
        workers[i].join();
    }

    std::cout << "Final test counter: " << ctr << std::endl;

    delete[] turn;
    delete[] flag[0];
    delete[] flag[1];
    delete[] workers;
}



void tas(int n) {
    std::atomic_flag turn = ATOMIC_FLAG_INIT;
    int ctr = 0;

    std::thread* workers = new std::thread[n];

    std::cout << "Starting " << n << " threads with a test counter" << std::endl;

    for (int i = 0; i < n; i++) {
        workers[i] = std::thread([&](int j) {
            while (turn.test_and_set()) {}
            // Do work
            ctr++;
            turn.clear();
            }, i);
    }

    for (int i = 0; i < n; i++) {
        workers[i].join();
    }

    std::cout << "Final test counter: " << ctr << std::endl;

    delete[] workers;
}

void FetchAlgo(int n) {
    int ctr = 0;
    std::atomic_int slot(0);
    std::atomic_int ticket(0);
    std::thread* workers = new std::thread[n];
    std::cout << "Starting " << n << " threads with a test counter" << std::endl;
    for (int i = 0; i < n; i++) {
        workers[i] = std::thread([&](int j) {
            int workerTicket = slot.fetch_add(1);
            while(ticket!=workerTicket){}
            // Do work
            ctr++
            }, i);
    }

    for (int i = 0; i < n; i++) {
        workers[i].join();
    }
    std::cout << "Final test counter: " << ctr << std::endl;
    delete[] workers;
}

int main(int argc, char* argv[]) { 
    int mode = std::stoi(argv[1]);
    int n = std::stoi(argv[2]);

    if (mode == 0) {
        petersons(n);
    }

    if (mode == 1) {
        tas(n);
    }

    if (mode == 2) {
        FetchAlgo(n);
    }

    else {
        cout << "Invalid input.";
    }
}