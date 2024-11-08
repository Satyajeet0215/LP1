#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>

using namespace std;

class PageReplacementAlgorithm
{
private:
    int n;          // Length of page reference sequence
    int nf;         // Number of frames
    vector<int> in; // Input reference sequence
    vector<int> p;  // frames
    int pgfaultcnt = 0;

    void initialize()
    {
        pgfaultcnt = 0;
        p.assign(nf, 9999);
    }

    bool isHit(int data)
    {
        for (int j = 0; j < nf; j++)
        {
            if (p[j] == data)
                return true;
        }
        return false;
    }

    void dispPages()
    {
        cout << "|";
        for (int k = 0; k < nf; k++)
        {
            if (p[k] == 9999)
                cout << setw(5) << " " << "|";
            else
                cout << setw(5) << p[k] << "|";
        }
    }

    void displayPgFaultCnt()
    {
        cout << "Total no of faults: " << pgfaultcnt << endl;
    }

    int predict(int index)
    {
        int res = -1, farthest = index;
        for (int i = 0; i < p.size(); i++) {
            int j;
            for (j = index; j < n; j++) {
                if (p[i] == in[j]) {
                    if (j > farthest) {
                        farthest = j;
                        res = i;
                    }
                    break;
                }
            }
            if (j == n)
                return i;
        }
        return (res == -1) ? 0 : res;
    }

public:
    void getData()
    {
        cout << "Enter length of page reference sequence: ";
        cin >> n;
        cout << "Enter the page reference sequence: ";
        in.resize(n);

        for (int i = 0; i < n; i++)
        {
            cin >> in[i];
        }

        cout << "Enter no of frames: ";
        cin >> nf;
        p.resize(nf);

        cout << endl;
    }

    void fifo()
    {
        initialize();
        cout << "FIFO Page Replacement\n";
        cout << "Page |";
        for (int k = 0; k < nf; k++)
            cout << setw(5) << "Frame " << k + 1 << "|";
        cout << "Status\n";
        for (int i = 0; i < n; i++)
        {
            cout << setw(5) << in[i] << " |";
            if (!isHit(in[i]))
            {
                for (int k = 0; k < nf - 1; k++)
                    p[k] = p[k + 1];

                p[nf - 1] = in[i];
                pgfaultcnt++;
                dispPages();
                cout << "  MISS";
            }
            else
            {
                dispPages();
                cout << "   HIT";
            }
            cout << endl;
        }
        cout << "\nTotal Hits = " << n - pgfaultcnt << endl;
        cout << "Total Misses = " << pgfaultcnt << endl << endl;
    }

    void lru()
    {
        initialize();
        cout << "LRU Page Replacement\n";
        cout << "Page |";
        for (int k = 0; k < nf; k++)
            cout << setw(5) << "Frame " << k + 1 << "|";
        cout << "Status\n";
        for (int i = 0; i < n; i++)
        {
            cout << setw(5) << in[i] << " |";
            if (!isHit(in[i]))
            {
                for (int k = 0; k < nf - 1; k++)
                    p[k] = p[k + 1];

                p[nf - 1] = in[i];
                pgfaultcnt++;
                dispPages();
                cout << "  MISS";
            }
            else
            {
                int idx = -1;
                for (int j = 0; j < nf; j++)
                {
                    if (p[j] == in[i])
                    {
                        idx = j;
                        break;
                    }
                }
                int temp = p[idx];
                for (int k = idx; k < nf - 1; k++)
                    p[k] = p[k + 1];
                p[nf - 1] = temp;
                dispPages();
                cout << "   HIT";
            }
            cout << endl;
        }
        cout << "\nTotal Hits = " << n - pgfaultcnt << endl;
        cout << "Total Misses = " << pgfaultcnt << endl << endl;
    }

    void optimal()
    {
        p.clear();
        int hit = 0;
        cout << "Optimal Page Replacement\n";
        cout << "Page |";
        for (int k = 0; k < nf; k++)
            cout << setw(5) << "Frame " << k + 1 << "|";
        cout << "Status\n";
        for (int i = 0; i < n; i++)
        {
            cout << setw(5) << in[i] << " |";
            if (isHit(in[i]))
            {
                hit++;
                dispPages();
                cout << "   HIT" << endl;
                continue;
            }

            if (p.size() < nf)
                p.push_back(in[i]);
            else
            {
                int j = predict(i + 1);
                p[j] = in[i];
            }
            dispPages();
            cout << "  MISS" << endl;
        }
        cout << "\nTotal Hits = " << hit << endl;
        cout << "Total Misses = " << n - hit << endl << endl;
    }
};

int main()
{
    PageReplacementAlgorithm prAlgo;
    bool loop = true;
    int choice;

    while (loop)
    {
        cout << "###### PAGE REPLACEMENT ALGORITHM ######" << endl;
        cout << "1. Enter Data" << endl;
        cout << "2. FIFO" << endl;
        cout << "3. LRU" << endl;
        cout << "4. Optimal" << endl;
        cout << "5. Exit" << endl;

        cout << "\n Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
            prAlgo.getData();
            break;
        case 2:
            prAlgo.fifo();
            break;
        case 3:
            prAlgo.lru();
            break;
        case 4:
            prAlgo.optimal();
            break;
        case 5:
            cout << "Exiting..." << endl;
            cout << "Thank you!!" << endl;
            loop = false;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }
}
