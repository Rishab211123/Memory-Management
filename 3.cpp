#include <iostream>
#include <vector>

using namespace std;

class Segment {
public:
    int base;
    int limit;

    Segment(int base, int limit) {
        this->base = base;
        this->limit = limit;
    }

    bool contains(int address) {
        return address >= base && address <= (base + limit);
    }
};

class Memory {
public:
    vector<Segment> segments;

    void addSegment(int base, int limit) {
        segments.push_back(Segment(base, limit));
    }

    Segment* getSegment(int address) {
        for (int i = 0; i < segments.size(); i++) {
            if (segments[i].contains(address)) {
                return &segments[i];
            }
        }
        return nullptr;
    }
};

int main() {
    Memory memory;
    int choice;

    do {
        cout << "Menu" << endl;
        cout << "1. Add segment" << endl;
        cout << "2. Test segmentation" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int base, limit;
                cout << "Enter base: ";
                cin >> base;
                cout << "Enter limit: ";
                cin >> limit;
                memory.addSegment(base, limit);
                break;
            }
            case 2: {
                int address;
                cout << "Enter address: ";
                cin >> address;
                Segment* segment = memory.getSegment(address);
                if (segment == nullptr) {
                    cout << "Segment not found" << endl;
                } else {
                    cout << "Base = " << segment->base << ", Limit = " << segment->limit << endl;
                }
                break;
            }
            case 3: {
                cout << "Exiting..." << endl;
                break;
            }
            default:
                cout << "Invalid choice" << endl;
                break;
        }

        cout << endl;

    } while (choice != 3);

    
}
