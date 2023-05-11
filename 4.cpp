#include <iostream>
#include <vector>
using namespace std;

class Partition {
private:
    int id;
    int size;
    bool allocated;

public:
    Partition(int _id, int _size) : id(_id), size(_size), allocated(false) {}
    int getId() const { return id; }

    int getSize() const { return size; }

    bool isAllocated() const { return allocated; }

    void allocate() { allocated = true; }

    void deallocate() { allocated = false; }
};

class Abstract
{
public:
    virtual void allocateBestFitPartition(int requiredSize) = 0;
    virtual void createPartition(int id, int size) = 0;
    virtual void deallocatePartition(int id) = 0;
    virtual void printMemoryStatus() = 0;
    virtual int getTotalMemorySize() const = 0;
    virtual int getFreeMemorySize() const = 0;
    virtual int getAllocatedMemorySize() const = 0;
};

class MemoryManager : public Abstract {
private:
    vector<Partition> partitions;

public:
    void createPartition(int id, int size) override {
        partitions.push_back(Partition(id, size));
    }

    void allocateBestFitPartition(int requiredSize) override {
        int bestFitId = -1;
        int bestFitSize = -1;

        for (const auto& partition : partitions) {
            if (!partition.isAllocated() && partition.getSize() >=requiredSize) {
                if (bestFitSize == -1 || partition.getSize() < bestFitSize) {
                    bestFitId = partition.getId();
                    bestFitSize = partition.getSize();
                }
            }
        }

        if (bestFitId != -1) {
            allocatePartition(bestFitId);
            cout << "Best fit partition (" << bestFitId << ")allocated." << endl;
        } else {
            throw runtime_error("Unable to allocate a partition of size " + to_string(requiredSize) + ".");
        }
    }

    void deallocatePartition(int id) override {
        for (auto& partition : partitions) {
            if (partition.getId() == id && partition.isAllocated()) {
                partition.deallocate();
                cout << "Partition " << partition.getId() << "deallocated." << endl;
                return;
            }
        }
        throw runtime_error("Unable to deallocate Partition " + to_string(id) + ".");
    }

    void printMemoryStatus() override {
        cout << "Memory Status:" << endl;
        for (const auto& partition : partitions) {
            cout << "Partition " << partition.getId() << ": ";
            cout << (partition.isAllocated() ? "Allocated" : "Free") << endl;
        }
    }

    int getTotalMemorySize() const override {
        int totalSize = 0;
        for (const auto& partition : partitions) {
            totalSize += partition.getSize();
        }
        return totalSize;
    }

    int getFreeMemorySize() const override {
        int freeSize = 0;
        for (const auto& partition : partitions) {
            if (!partition.isAllocated()) {
                freeSize += partition.getSize();
            }
        }
        return freeSize;
    }

    int getAllocatedMemorySize() const override {
        int allocatedSize = 0;
        for (const auto& partition : partitions) {
            if (partition.isAllocated()) {
                allocatedSize += partition.getSize();
            }
        }
        return allocatedSize;
    }
void allocatePartition(int id) {
        for (auto& partition : partitions) {
            if (partition.getId() == id && !partition.isAllocated()) {
                partition.allocate();
                cout << "Partition " << partition.getId() << "allocated." << endl;
                return;
            }
        }
        throw runtime_error("Unable to allocate Partition " + to_string(id) + ".");
    }
};

int main(){
    Abstract* bPtr;
    MemoryManager memoryManager;
    bPtr = &memoryManager;

    try {
        bPtr->createPartition(1, 100);
        bPtr->createPartition(2, 200);
        bPtr->createPartition(3, 150);
        bPtr->createPartition(4, 300);

        memoryManager.printMemoryStatus();
        cout << "Total Memory Size: " <<memoryManager.getTotalMemorySize() << endl;
        cout << "Free Memory Size: " <<memoryManager.getFreeMemorySize() << endl;
        cout << "Allocated Memory Size: " <<memoryManager.getAllocatedMemorySize() << endl;

        bPtr->allocateBestFitPartition(120);
        bPtr->allocateBestFitPartition(250);

        memoryManager.printMemoryStatus();
        cout << "Total Memory Size: " <<memoryManager.getTotalMemorySize() << endl;
        cout << "Free Memory Size: " <<memoryManager.getFreeMemorySize() << endl;
        cout << "Allocated Memory Size: " <<memoryManager.getAllocatedMemorySize() << endl;

        memoryManager.deallocatePartition(2);
        memoryManager.deallocatePartition(3);

        bPtr->printMemoryStatus();
        cout << "Total Memory Size: " <<memoryManager.getTotalMemorySize() << endl;
        cout << "Free Memory Size: " <<memoryManager.getFreeMemorySize() << endl;
        cout << "Allocated Memory Size: " <<memoryManager.getAllocatedMemorySize() << endl;
    } 
    catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}