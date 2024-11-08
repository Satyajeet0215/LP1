#include <iostream>
#include <map>
#include <iomanip>
#include <algorithm>
using namespace std;

class Memory {
    int *blocks;
    int *process;
    int *flag;
    int bsize;
    int psize;

public:
    Memory() {
        bsize = 0;
        psize = 0;
    }
    void input();
    void firstfit();
    void bestfit();
    void worstfit();
    void nextfit();
};

void Memory::input() {
    cout << "Enter the number of blocks present: ";
    cin >> bsize;
    cout << "Enter the number of processes: ";
    cin >> psize;
    blocks = new int[bsize];
    process = new int[psize];
    flag = new int[bsize];

    cout << "Enter the size of each block: ";
    for (int i = 0; i < bsize; i++) {
        cin >> blocks[i];
    }
    cout << "Enter the size of each process: ";
    for (int i = 0; i < psize; i++) {
        cin >> process[i];
    }
}

void Memory::firstfit() {
    for (int i = 0; i < bsize; i++) {
        flag[i] = 0; // denotes that memory block is free
    }
    map<int, int> mp; // block number and size of allocated process
    for (int i = 0; i < psize; i++) {
        for (int j = 0; j < bsize; j++) {
            if (process[i] <= blocks[j] && flag[j] == 0) {
                mp[j] = process[i];
                flag[j] = 1;
                break;
            }
        }
    }
    cout << "Block No" << setw(20) << "Size of Block" << setw(30) << "Size of Process allocated" << endl;
    for (const auto &it : mp) {
        cout << it.first << setw(20) << blocks[it.first] << setw(20) << it.second << endl;
    }
}

void Memory::bestfit() {
    for (int i = 0; i < bsize; i++) {
        flag[i] = 0;
    }
    int wastage[bsize];
    map<int, int> mp;

    for (int i = 0; i < psize; i++) {
        fill(wastage, wastage + bsize, 9999);
        for (int j = 0; j < bsize; j++) {
            if (process[i] <= blocks[j] && flag[j] == 0) {
                wastage[j] = blocks[j] - process[i];
            }
        }
        int min = *min_element(wastage, wastage + bsize);
        int pos = find(wastage, wastage + bsize, min) - wastage;
        if (min != 9999) {
            mp[pos] = process[i];
            flag[pos] = 1;
        }
    }
    cout << "Block No" << setw(20) << "Size of Block" << setw(30) << "Size of Process allocated" << endl;
    for (const auto &it : mp) {
        cout << it.first << setw(20) << blocks[it.first] << setw(20) << it.second << endl;
    }
}

void Memory::worstfit() {
    for (int i = 0; i < bsize; i++) {
        flag[i] = 0;
    }
    int wastage[bsize];
    map<int, int> mp;

    for (int i = 0; i < psize; i++) {
        fill(wastage, wastage + bsize, 0);
        for (int j = 0; j < bsize; j++) {
            if (process[i] <= blocks[j] && flag[j] == 0) {
                wastage[j] = blocks[j] - process[i];
            }
        }
        int max = *max_element(wastage, wastage + bsize);
        int pos = find(wastage, wastage + bsize, max) - wastage;
        if (max != 0) {
            mp[pos] = process[i];
            flag[pos] = 1;
        }
    }
    cout << "Block No" << setw(20) << "Size of Block" << setw(30) << "Size of Process allocated" << endl;
    for (const auto &it : mp) {
        cout << it.first << setw(20) << blocks[it.first] << setw(20) << it.second << endl;
    }
}

void Memory::nextfit() {
    for (int i = 0; i < bsize; i++) {
        flag[i] = 0; // denotes that memory block is free
    }
    map<int, int> mp; // block number and size of allocated process
    int last_allocated = 0; // Keeps track of the last allocated block position

    for (int i = 0; i < psize; i++) {
        bool allocated = false;
        for (int j = last_allocated; j < bsize; j++) {
            if (process[i] <= blocks[j] && flag[j] == 0) {
                mp[j] = process[i];
                flag[j] = 1;
                last_allocated = j;
                allocated = true;
                break;
            }
        }
        if (!allocated) {
            for (int j = 0; j < last_allocated; j++) {
                if (process[i] <= blocks[j] && flag[j] == 0) {
                    mp[j] = process[i];
                    flag[j] = 1;
                    last_allocated = j;
                    break;
                }
            }
        }
    }
    cout << "Block No" << setw(20) << "Size of Block" << setw(30) << "Size of Process allocated" << endl;
    for (const auto &it : mp) {
        cout << it.first << setw(20) << blocks[it.first] << setw(20) << it.second << endl;
    }
}

int main() {
    Memory m;
    int choice;

    m.input();
    do {
        cout << "\nChoose the memory allocation method:\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Next Fit\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                m.firstfit();
                break;
            case 2:
                m.bestfit();
                break;
            case 3:
                m.worstfit();
                break;
            case 4:
                m.nextfit();
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
