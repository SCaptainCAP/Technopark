#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <fstream>

#define DEFAULT_SIZE 4

using namespace std;

template <class T>
class Deque {
public:
    Deque(int size);
    Deque();
    ~Deque();

    void PushFront(const T& data);
    void PushBack(const T& data);
    T PopBack();
    T PopFront();
    T GetBack();
    T GetFront();
    bool IsEmpty() const;

    void print(bool debug = false) const;

private:
    T* buffer = NULL;
    int bufferSize;
    int minBufferSize;
    int head;
    int tail;
    bool empty;
    void IncreaseBuffer();
    void DecreaseBuffer();
};

template <typename T>
Deque<T>::Deque(int size) : bufferSize(size), minBufferSize(size), head(-1), tail(0), empty(true)
{
    assert(size > 1);
    buffer = new T[bufferSize];
}

template <typename T>
Deque<T>::Deque() : bufferSize(DEFAULT_SIZE), minBufferSize(DEFAULT_SIZE), head(-1
), tail(0), empty(true)
{
    buffer = new T[bufferSize];
}

template <typename T>
Deque<T>::~Deque()
{
    delete[](buffer);
}

template <typename T>
void Deque<T>::IncreaseBuffer() {
    T* tmpBuffer = new T[(bufferSize * 2)];
    assert(tmpBuffer);

    tmpBuffer[0] = buffer[head];
    for (int i = bufferSize + 1; i < bufferSize * 2; i++)
    {
        tmpBuffer[i] = buffer[(tail + i - 1 - bufferSize) % bufferSize];
    }
    head = 0;
    tail = bufferSize + 1;
    bufferSize *= 2;

    delete [](buffer);
    buffer = tmpBuffer;
}

template <typename T>
void Deque<T>::DecreaseBuffer() {
    T* tmpBuffer = new T[(bufferSize / 2)];
    assert(tmpBuffer);
    assert(bufferSize >= minBufferSize);

    tmpBuffer[0] = buffer[head];
    for (int i = 1; i < bufferSize / 2; i++)
    {
        tmpBuffer[i] = buffer[(tail + i - 1) % bufferSize];
    }

    head = 0;
    tail = 1;
    bufferSize /= 2;

    delete [](buffer);
    buffer = tmpBuffer;
}

template <typename T>
void Deque<T>::PushFront(const T& data)
{
    if (IsEmpty()) {
        buffer[0] = data;
        head = 0;
        tail = 0;
        empty = false;
    }
    else
    {
        head = (head + 1) % bufferSize;
        if (head == tail) {
            head--;
            if (head < 0)
                head = bufferSize - 1;
            IncreaseBuffer();
            head++;
        }
        buffer[head] = data;
    }
}


template <typename T>
void Deque<T>::PushBack(const T& data) {
    if (IsEmpty()) {
        buffer[bufferSize - 1] = data;
        tail = bufferSize - 1;
        head = bufferSize - 1;
        empty = false;
    }
    else
    {
        tail = (tail - 1);
        if (tail < 0)
            tail = bufferSize - 1;
        if (head == tail) {
            tail = (tail + 1) % bufferSize;
            IncreaseBuffer();
            tail--;
        }
        buffer[tail] = data;
    }

}


template <typename T>
T Deque<T>::PopBack() {
    if (IsEmpty())
        throw "Cannot pop from empty Deque";
    if (tail == head)
        empty = true;
    T data = buffer[tail];
    tail = (tail + 1) % bufferSize;
    int rasst = (tail > head) ? head + bufferSize - tail : head - tail;
    if (rasst < bufferSize / 2  && bufferSize > minBufferSize)
    {
        DecreaseBuffer();
    }
    return data;
}


template <typename T>
T Deque<T>::PopFront() {
    if (IsEmpty())
        throw "Cannot pop from empty Deque";
    if (tail == head)
        empty = true;
    T data = buffer[head];
    head = (head - 1);
    if (head < 0)
        head = bufferSize - 1;

    int rasst = (tail > head) ? head + bufferSize - tail : head - tail;
    if (rasst < bufferSize / 2  && bufferSize > minBufferSize)
    {
        DecreaseBuffer();
    }
    return data;
}


template <typename T>
bool Deque<T>::IsEmpty() const
{
    return empty;
}

template <typename T>
void Deque<T>::print(bool debug) const {
    if (debug)
        std::cout << "Head: " << head << "; Tail: " << tail << std::endl;
    std::cout << "|";
    for (int i = 0; i < bufferSize; i++)
    {
        std::cout << " " << buffer[i] << " |";
    }
}

template <typename T>
T Deque<T>::GetFront() {
    if (IsEmpty())
        throw "Cannot get from empty Deque";
    return buffer[head];
}
template <typename T>
T Deque<T>::GetBack() {
    if (IsEmpty())
        throw "Cannot get from empty Deque";
    return buffer[tail];
}



template <class T>
struct Node{
    Node<T>* left = NULL;
    Node<T>* right = NULL;
    T data;
    Node(T dat) : data(dat) {}
};


template <class T>
class BinaryTree {
private:
    Node<T>* root;
    vector<T> LevelOrder() {
        Deque<Node<T>*> queue;
        vector<T> answer;
        if (root == NULL)
            return answer;
        queue.PushBack(root);
        while (!queue.IsEmpty()) {
            if (queue.GetFront()->left != NULL) {
                queue.PushBack(queue.GetFront()->left);
            }
            if (queue.GetFront()->right != NULL) {
                queue.PushBack(queue.GetFront()->right);
            }
            answer.push_back(queue.PopFront()->data);
        }
        return answer;
    }
    void Clean(Node<T>* node) {
        if (root == NULL)
            return;
        Deque<Node<T>*> queue;
        queue.PushBack(root);
        while (!queue.IsEmpty()) {
            if (queue.GetFront()->left != NULL) {
                queue.PushBack(queue.GetFront()->left);
            }
            if (queue.GetFront()->right != NULL) {
                queue.PushBack(queue.GetFront()->right);
            }
            delete queue.PopFront();
        }
    }
public:
    BinaryTree() : root(NULL) {}
    ~BinaryTree() {
        Clean(root);
    }
    void AddNode(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (root == NULL) {
            root = newNode;
            return;
        }
        Node<T>* tmp = root;
        while (1) {
            if (data <= tmp->data) {
                if (tmp->left != NULL) {
                    tmp = tmp->left;
                }
                else {
                    tmp->left = newNode;
                    break;
                }
            }
            else {
                if (tmp->right != NULL) {
                    tmp = tmp->right;
                }
                else {
                    tmp->right = newNode;
                    break;
                }
            }
        }
    }
    void PrintLevelOrder() {
        vector<T> vect = LevelOrder();
        for (int i = 0; i < vect.size(); i++) {
            cout << vect[i] << " ";
        }
    }
};


void generateBitsTable(Node<char>* node, std::vector<std::pair<char, std::string>>& vector, std::string way = ""){
    if (node->right == NULL && node->left == NULL) {
        vector.push_back(std::pair<char, std::string>(node->data, way));
    }
    if (node->left != NULL)
        generateBitsTable(node->left, vector, way + "0");
    if (node->right != NULL)
        generateBitsTable(node->right, vector, way + "1");
};

std::string generateCombressedFromBinary(const std::string& binary){
    std::string compressed = "";
    for (int i = 0; i < binary.size() / 8; i++) {
        int padding = i * 8;
        unsigned char tmp = 0;
        for (int j = 0; j < 8; j++) {
            tmp += (binary[padding + j] - '0') * pow(2, 7 - j);
        }
        compressed += tmp;
    }
    return compressed;
};

int findFirstMeet(const std::string& src, const std::string& what) {
    if (src.size() < what.size()) return -1;
    bool success;
    for (int i = 0; i < src.size() - what.size(); i++) {
        if (src[i] == what[0]) {
            success = true;
            for (int j = 1; j < what.size(); j++) {
                if (src[i + j] != what[j]) {
                    success = false;
                    break;
                }
            }
            if (success)
                return i;
        }
    }
    return -1;
}

std::string generateBinaryFromCompressed(const std::string& compressed){
    std::string binary = "";
    for (int i = 0; i < compressed.size(); i++) {
        std::string tmp = "";
        unsigned char a = compressed[i];
        for (int j = 0; j < 8; j++) {
            char add = ('0' + a % 2);
            tmp = add + tmp;
            a /= 2;
        }
        binary += tmp;
    }
    return binary;
};

std::string charToBinaryString(char a) {
    std::string str = "";
    unsigned char tmp = a;
    short count = 0;
    while (tmp > 0) {
        count++;
        if (tmp % 2 == 0)
            str = "0" + str;
        else
            str = "1" + str;
        tmp /= 2;
    }
    for (short i = 0; i < 8 - count; i++) {
        str = "0" + str;
    }
    return str;
}

unsigned char binaryStringToChar(std::string binary) {
    assert(binary.size() == 8);
    unsigned char tmp = 0;
    for (int j = 0; j < 8; j++) {
        tmp += (binary[j] - '0') * pow(2, 7 - j);
    }
    return tmp;
}

void compress_string(const std::string &source, std::string &compressed) {
    if (source == "") {
        compressed = "";
        return;
    }

    std::vector<std::pair<Node<char>*, int>> pairsPrority;
    bool added;
    for (int i = 0; i < source.size(); i++) {
        added = false;
        for (int j = 0; j < pairsPrority.size(); j++) {
            if (pairsPrority[j].first->data == source[i]) {
                pairsPrority[j].second++;
                added = true;
                break;
            }
        }
        if (!added) {
            pairsPrority.push_back(std::pair<Node<char>*, int>(new Node<char>(source[i]), 1));
        }
    }
    std::sort(pairsPrority.begin(), pairsPrority.end(), [](const std::pair<Node<char>*, int> &left, const std::pair<Node<char>*, int> &right) {
        return left.second < right.second;
    });

    //generate tree
    while (pairsPrority.size() != 0 && pairsPrority.size() != 1) {
        Node<char>* l = pairsPrority[0].first;
        Node<char>* r = pairsPrority[1].first;
        Node<char>* ans = new Node<char>('\0');
        ans->left = l;
        ans->right = r;
        std::pair<Node<char>*, int> ptmp = std::pair<Node<char>*, int>(ans, pairsPrority[0].second + pairsPrority[1].second);
        pairsPrority.erase(pairsPrority.begin());
        pairsPrority.erase(pairsPrority.begin());
        if (pairsPrority.size() == 0) {
            pairsPrority.insert(pairsPrority.begin(), ptmp);
            continue;
        }
        bool added = false;
        for (int i = 0; i < pairsPrority.size(); i++) {
            if (pairsPrority[i].second >= ptmp.second) {
                pairsPrority.insert(pairsPrority.begin() + i, ptmp);
                added = true;
                break;
            }
        }
        if (!added)
            pairsPrority.insert(pairsPrority.begin() + pairsPrority.size(), ptmp);
    }

    // create bit table
    std::vector<std::pair<char, std::string>> bitsTable;
    generateBitsTable(pairsPrority[0].first, bitsTable);
    if (bitsTable.size() == 1)
        bitsTable[0].second = "0";

    // string consists of zeros and ones
    std::string codedRawString = "";
    for (int i = 0; i < source.size(); i++) {
        for (int j = 0; j < bitsTable.size(); j++) {
            if (source[i] == bitsTable[j].first)
                codedRawString += bitsTable[j].second;
        }
    }
    unsigned long maxBitTableSize = bitsTable[0].second.size();
    for (int j = 1; j < bitsTable.size(); j++) {
        if (bitsTable[j].second.size() > maxBitTableSize)
            maxBitTableSize = bitsTable[j].second.size();
    }

    std::string codedRawTable = "1";
    for (int j = 0; j < bitsTable.size(); j++) {
        codedRawTable += charToBinaryString(bitsTable[j].first) + charToBinaryString((char)(short)bitsTable[j].second.size()) + bitsTable[j].second;
    }
    codedRawTable += charToBinaryString('\0');

    std::string codedBinaryString = codedRawTable + codedRawString;
    while (codedBinaryString.size() % 8)
        codedBinaryString = '0' + codedBinaryString;

    compressed = generateCombressedFromBinary(codedBinaryString);


    return;
}

void decompress_string(const std::string &compressed, std::string &result) {
    //setlocale(LC_ALL, "Russian");
    if (compressed == "" || compressed.size() == 0)
        result = "";
    std::string defBinary = generateBinaryFromCompressed(compressed);
    std::string binary = defBinary;
    int padding = 1;
    for (int i = 0; i < binary.size(); i++) {
        if (binary[i] == '1')
            break;
        padding++;
    }
    binary = binary.substr(padding);
    std::vector<std::pair<char, std::string>> bitsTable;
    while(true) {
        unsigned char c = binaryStringToChar(binary.substr(0, 8));
        binary = binary.substr(8);
        if (c == '\0')
            break;
        unsigned char l = binaryStringToChar(binary.substr(0, 8));
        binary = binary.substr(8);
        bitsTable.push_back(std::pair<char, std::string>(c, binary.substr(0, l)));
        binary = binary.substr(l);
    }

    Node<char>* node = new Node<char>('\0');
    Node<char> *tmp;
    for (int i = 0; i < bitsTable.size(); i++) {
        tmp = node;
        if (bitsTable[i].second.size() == 0) {
            continue;
        }
        for (int j = 0; j < bitsTable[i].second.size(); j++) {
            if (bitsTable[i].second[j] == '0') {
                if (!tmp->left) tmp->left = new Node<char>('\0');
                tmp = tmp->left;
            }
            else {
                if (!tmp->right) tmp->right = new Node<char>('\0');
                tmp = tmp->right;
            }
        }
        tmp->data = bitsTable[i].first;
    }
    //result = GLOBAL;
    std::string answer = "";
    tmp = node;
    for (int i = 0; i < binary.size(); i++) {
        if (binary[i] == '0') {
            tmp = tmp->left;
        }
        else {
            tmp = tmp->right;
        }
        if (tmp->data != '\0') {
            answer += tmp->data;
            tmp = node;
        }
    }
    result = answer;
    return;
}
//0111000011001000111011000011011101110011111111010010111100010110
int main() {
    std::string a;
    std::string b;
    std::string c;
    std::string str;
    getline(std::cin, a);
    compress_string(a, b);
    decompress_string(b, c);
    std::cout << a.size() << std::endl << std::endl;
    std::cout << a << std::endl << std::endl;
    std::cout << b.size() << std::endl << std::endl;
    std::cout << b << std::endl << std::endl;
    std::cout << c.size() << std::endl << std::endl;
    std::cout << c << std::endl << std::endl;
    return 0;
}
