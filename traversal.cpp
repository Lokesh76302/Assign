#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct node {
    char symbol;
    int frequency;
    node *left;
    node *right;

    bool operator<(const node &other) const {
        return frequency < other.frequency;
    }
};

void printHuffmanCodes(const map<char, string> &huffmanCodes) {
    for (const pair<char, string> &entry : huffmanCodes) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

void buildHuffmanTree(map<char, int> &charFreqMap, node *&root) {
    priority_queue<node> pq;

    for (const pair<char, int> &entry : charFreqMap) {
        node *n = new node;
        n->symbol = entry.first;
        n->frequency = entry.second;
        n->left = nullptr;
        n->right = nullptr;

        pq.push(*n);
    }

    while (pq.size() > 1) {
        node *left = new node;
        *left = pq.top();
        pq.pop();

        node *right = new node;
        *right = pq.top();
        pq.pop();

        node *parent = new node;
        parent->frequency = left->frequency + right->frequency;
        parent->left = left;
        parent->right = right;

        pq.push(*parent);
    }

    root = pq.top();
}

void generateHuffmanCodes(node *root, map<char, string> &huffmanCodes, string code) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->symbol] = code;
        return;
    }

    if (root->left) generateHuffmanCodes(root->left, huffmanCodes, code + "0");

    if (root->right) generateHuffmanCodes(root->right, huffmanCodes, code + "1");
}

int main() {
    map<char, int> charFreqMap = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};
    node *root = nullptr;

    buildHuffmanTree(charFreqMap, root);
    map<char, string> huffmanCodes;

    generateHuffmanCodes(root, huffmanCodes, "");
    printHuffmanCodes(huffmanCodes);
    return 0;
}
