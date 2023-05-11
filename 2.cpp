#include <iostream>
#include <vector>

using namespace std;

class MemoryBlock {
public:
    MemoryBlock(int s) {
        size = s;
        allocated = false;
    }
    
    bool isAllocated() {
        return allocated;
    }
    
    int getSize() {
        return size;
    }
    
    void allocate() {
        allocated = true;
    }
    
    void deallocate() {
        allocated = false;
    }
    
private:
    int size;
    bool allocated;
};

class MemoryManager {
public:
    MemoryManager(int totalSize) {
        // Create memory blocks with the given total size
        int numBlocks = totalSize / blockSize;
        for (int i = 0; i < numBlocks; i++) {
            blocks.push_back(MemoryBlock(blockSize));
        }
    }
    
    void allocate(int size) {
        int numBlocksNeeded = (size + blockSize - 1) / blockSize;
        
        // Search for a contiguous block of memory
        for (int i = 0; i < blocks.size(); i++) {
            int j = i;
            while (j < i + numBlocksNeeded && j < blocks.size() && !blocks[j].isAllocated()) {
                j++;
            }
            if (j == i + numBlocksNeeded) {
                // Found a contiguous block of memory
                for (int k = i; k < i + numBlocksNeeded; k++) {
                    blocks[k].allocate();
                }
                cout << "Allocated " << size << " bytes of memory starting at address " << i * blockSize << endl;
                return;
            }
        }
        
        // No contiguous block of memory found
        cout << "Error: Cannot allocate " << size << " bytes of memory due to external fragmentation" << endl;
    }
    
    void deallocate(int address, int size) {
        int startBlock = address / blockSize;
        int numBlocks = (size + blockSize - 1) / blockSize;
        for (int i = startBlock; i < startBlock + numBlocks; i++) {
            blocks[i].deallocate();
        }
        cout << "Deallocated " << size << " bytes of memory starting at address " << address << endl;
    }
    
    void printMemoryUsage() {
        int numFreeBlocks = 0;
        int freeBlockSize = 0;
        int numAllocatedBlocks = 0;
        int allocatedBlockSize = 0;
        for (int i = 0; i < blocks.size(); i++) {
            if (blocks[i].isAllocated()) {
                numAllocatedBlocks++;
                allocatedBlockSize += blocks[i].getSize();
            } else {
                numFreeBlocks++;
                freeBlockSize += blocks[i].getSize();
            }
        }
        cout << "Memory usage: " << endl;
        cout << "- Total blocks: " << blocks.size() << endl;
        cout << "- Free blocks: " << numFreeBlocks << endl;
        cout << "- Free memory: " << freeBlockSize << " bytes" << endl;
        cout << "- Allocated blocks: " << numAllocatedBlocks << endl;
        cout << "- Allocated memory: " << allocatedBlockSize << " bytes" << endl;
    }
    
private:
    const int blockSize = 10; // Size of each memory block in bytes
    vector<MemoryBlock> blocks;
};

int main() {
    MemoryManager memoryManager(1024); // Create a memory manager with 1024 bytes of memory
    
    int choice;
    int size;
    int address;
    
    do {
       // Display menu
        cout << endl;
        cout << "Memory Manager" << endl;
        cout << "--------------" << endl;
        cout << "1. Allocate memory" << endl;
        cout << "2. Deallocate memory" << endl;
        cout << "3. Print memory usage" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter size to allocate (in bytes): ";
                cin >> size;
                memoryManager.allocate(size);
                break;
                
            case 2:
                cout << "Enter starting address to deallocate: ";
                cin >> address;
                cout << "Enter size to deallocate (in bytes): ";
                cin >> size;
                memoryManager.deallocate(address, size);
                break;
                
            case 3:
                memoryManager.printMemoryUsage();
                break;
                
            case 4:
                cout << "Exiting..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
        
    } while (choice != 4);
    
}