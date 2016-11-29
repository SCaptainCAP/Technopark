#include <string>
#include <vector>

using namespace std;
const int DefaultTableSize = 10;

int Hash(const string& data, int tableSize)
{
    int hash = 0;
    for (int i = 0; i < data.length(); i++) {
        hash = (hash * 127 + data[i]) % tableSize;
    }
}


template <class T>
struct HashTableNode {
    T* Data;
    HashTableNode<T*>* next;

    HashTableNode() : next(0) {}
    HashTableNode(T data) : Data(data), next(nullptr) {}

};

template <class T>
class HashTable {
public:
    HashTable();
    ~HashTable();

    bool Add(const T& data);
    bool Delete(const T& data);
    bool Has(const T &data);

private:
    vector<HashTableNode> table;
    int keysCount;

};

HashTable::HashTable() : keysCount(0){
    table.resize(DefaultTableSize);
}

HashTable::~HashTable() {

}

template <class T>
bool HashTable::Add(const T &data) {
    if (Has(data))
        return false;
    int hash = Hash(data, table.size());
    table[hash] = new HashTableNode(data, table[hash]);
}

template <class T>
bool HashTable::Delete(const T &data) {
    return false;
}

template <class T>
bool HashTable::Has(const T &data) {
    int hash = Hash(data, table.size());
    HashTableNode<T>* node = table[hash];
    while (node != 0 && node->Data != data) {
        node = node->next;
    }
    return node != 0;
}
