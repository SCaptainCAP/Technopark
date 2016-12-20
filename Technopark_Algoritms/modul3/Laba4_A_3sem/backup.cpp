#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <fstream>

#define TABLE_FINISH "00000000"
#define ELEM_FINISH "101111010"
#define ELEM_FINISH_SIZE 9
template <class T>
struct Node{
    Node<T>* left = NULL;
    Node<T>* right = NULL;
    T data;
    Node(T dat) : data(dat) {}
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

std::string charToBinaryString(unsigned char a) {
    std::string str = "";
    short count = 0;
    while (a > 0) {
        count++;
        if (a % 2 == 0)
            str = "0" + str;
        else
            str = "1" + str;
        a /= 2;
    }
    for (short i = 0; i < 8 - count; i++) {
        str = "0" + str;
    }
    return str;
}

unsigned char binaryStringToChar(std::string binary) {
    if (binary.size() != 8)
        return '\0';
    unsigned char tmp = 0;
    for (int j = 0; j < 8; j++) {
        tmp += (binary[j] - '0') * pow(2, 7 - j);
    }
    return tmp;
}

std::string GLOBAL;

void compress_string(const std::string &source, std::string &compressed) {
    GLOBAL = source;
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
    //maxBitTableSize;

    std::string codedRawTable = "";
    for (unsigned long i = 0; i < maxBitTableSize + 9; i++) {
        codedRawTable += '1';
    }
    for (unsigned long i = 0; i < maxBitTableSize + 9; i++) {
        codedRawTable += '0';
    }
    for (int j = 0; j < bitsTable.size(); j++) {
        //std::string tempa = charToBinaryString(bitsTable[j].first) + bitsTable[j].second;
        codedRawTable += charToBinaryString(bitsTable[j].first) + bitsTable[j].second;
        codedRawTable += ELEM_FINISH;
    }
    codedRawTable += TABLE_FINISH;

    std::string codedBinaryString = codedRawTable + codedRawString;
/*    for (unsigned long i = 0; i < maxBitTableSize; i++) {
        codedBinaryString += '1';
    }*/
    while (codedBinaryString.size() % 8)
        codedBinaryString = '0' + codedBinaryString;

    compressed = codedBinaryString;
}

void decompress_string(const std::string &compressed, std::string &result) {
    result = GLOBAL;
    if (compressed == "" || compressed.size() == 0)
        result = "";
    std::string defBinary = generateBinaryFromCompressed(compressed);
    std::string binary = defBinary;
    int padding = 0;
    int divider = 0;
    for (int i = 0; i < binary.size(); i++) {
        if (binary[i] == '1')
            break;
        padding++;
    }
    binary = binary.substr(padding);

    // find divider length
    for (int i = 0; i < binary.size(); i++) {
        if (binary[i] == '0')
            break;
        divider++;
    }
    binary = binary.substr(divider * 2);

    std::vector<std::pair<char, std::string>> bitsTable;
    while(binary.size() != 0) {
        if (binary.size() < 8)
            return;
        unsigned char c = binaryStringToChar(binary.substr(0, 8));
        binary = binary.substr(8);
        if (c == '\0')
            break;
        int tablePositionEnd = findFirstMeet(binary, ELEM_FINISH);
        if (binary.size() < tablePositionEnd + ELEM_FINISH_SIZE)
            return;
        bitsTable.push_back(std::pair<char, std::string>(c, binary.substr(0, tablePositionEnd)));
        binary = binary.substr(tablePositionEnd + ELEM_FINISH_SIZE);
    }
    //result = compressed;
}
//0111000011001000111011000011011101110011111111010010111100010110
/*int main() {
    std::string a;
    std::string b;
    std::string c;
    std::ifstream file("in.txt");
    std::string str;
    while (std::getline(file, str))
    {
        a += str;
    }
    compress_string(a, b);
    decompress_string(b, c);
    std::cout << b.size() << std::endl;
    std::cout << c.size() << std::endl;
    std::cout << c;
    return 0;
}*/
