#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#define DEF_HASHTABLE_SIZE 8
#define DEF_HASHTABLE_KOEF 7
#define DEF_HASHTABLE_STEP 1
using namespace std;

unsigned int Hash(const string& str) {
    unsigned int ans = (unsigned int) str[0];
    for (int i = 1; i < str.size(); ++i) {
        ans *= DEF_HASHTABLE_KOEF;
        ans += (unsigned int) str[i];
    }
    return ans;
}

template <class T>
class LowCaseStringHashTable {
private:
    vector<string> strings;
    int size;
    int count;
    T v;
    T d;
    unsigned int (* Hash)(const T&);
    unsigned int quadrHash(unsigned int old_hash, int tryes) {
        return old_hash + tryes + 1;
    }
    void reHash() {
        if (count < size * 3 / 4)
            return;
        int oldsize = size;
        size *= 4;
        vector<string> newTable;
        newTable.resize(size);
        for (int i = 0; i < size; i++) {
            newTable[i] = v;
        }
        for (int i = 0; i < oldsize; i++) {
            if (strings[i] != d && strings[i] != v) {
                AddPR(strings[i], newTable);
            }
        }
        strings = newTable;
        return;
    }
    bool AddPR(const T& str, vector<T>& table) {
        unsigned int hash = Hash(str) % size;
        unsigned int tmphash = Hash(str) % size;
        bool foundPlace = false;
        int tryes = 0;
        for (int i = 0; i < size; i++)  {
            if (table[hash] == str) {
                return false;
            }
            if (table[hash] == v) {
                table[hash] = str;
                count++;
                reHash();
                return true;
            }
            if (table[hash] == d) {
                foundPlace = true;
                tmphash = hash;
            }
            tryes++;
            hash = quadrHash(hash, tryes) % size;
        }
        if (foundPlace) {
            table[tmphash] = str;
            count++;
            reHash();
            return true;
        }
        return false;
    }
    bool DeletePR(const T& str, vector<T>& table) {
        unsigned int hash = Hash(str) % size;
        int tryes = 0;
        for (int i = 0; i < size; i++) {
            if (table[hash] == v)
                return false;
            if (table[hash] == str) {
                table[hash] = d;
                count--;
                return true;
            }
            tryes++;
            hash = quadrHash(hash, tryes) % size;
        }
        return false;
    }
    bool CheckPR(const T& str, vector<T>& table) {
        unsigned int hash = Hash(str) % size;
        int tryes = 0;
        for (int i = 0; i < size; i++) {
            if (table[hash] == v)
                return false;
            if (table[hash] == str)
                return true;
            tryes++;
            hash = quadrHash(hash, tryes) % size;
        }
        return false;
    }
public:
    LowCaseStringHashTable(const T& v_, const T& d_, unsigned int (* Hash_)(const T&)) : size(DEF_HASHTABLE_SIZE), count(0), v(v_), d(d_), Hash(Hash_) {
        strings.resize(size);
        for (int i = 0; i < size; i++) {
            strings[i] = v;
        }
    }
    bool Add(const T& str) {
        return AddPR(str, strings);
    }
    bool Delete(const T& str) {
        return DeletePR(str, strings);
    }
    bool Check(const T& str) {
        return CheckPR(str, strings);
    }
};


int main() {
    char ch;
    string s;
    LowCaseStringHashTable<string> table("VOID", "DEL", Hash);
    LowCaseStringHashTable<int> a(0,1,NULL);
    //std::ifstream infile("in.txt");
    while(cin >> ch) {
        cin >> s;
        switch(ch) {
            case '+':
                cout << (table.Add(s) ? "OK" : "FAIL") << endl;
                break;
            case '-':
                cout << (table.Delete(s) ? "OK" : "FAIL") << endl;
                break;
            case '?':
                cout << (table.Check(s) ? "OK" : "FAIL") << endl;
                break;
            default:
                break;
        }
    }
    return 0;
}