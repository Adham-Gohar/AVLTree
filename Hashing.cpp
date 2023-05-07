#include <iostream>
#include <vector>

using namespace std;

// Hash function to compute index of element in hash table
int hashFunction(int element, int tableSize) {
    return element % tableSize;
}

int main() {
    const int TABLE_SIZE = 10; // Hash table size
    int arr[] = { 1, 4, 7, 1, 5, 2, 4, 1, 3, 5 };
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    vector<vector<int>> hashTable(TABLE_SIZE);

    // Iterate over the array and add elements to the hash table
    for (int i = 0; i < arrSize; i++) {
        int index = hashFunction(arr[i], TABLE_SIZE);
        hashTable[index].push_back(arr[i]);
    }

    // Print the hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Index " << i << ": ";
        for (int j = 0; j < hashTable[i].size(); j++) {
            cout << hashTable[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
