#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <algorithm> // For std::find

using namespace std;


struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;
    
    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};


struct compare {
    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};


void printCodes(Node* root, string str, unordered_map<char, string>& huffmanCodes) {
    if (!root)
        return;
    if (root->data != '$')
        huffmanCodes[root->data] = str;
    printCodes(root->left, str + "0", huffmanCodes);
    printCodes(root->right, str + "1", huffmanCodes);
}


void HuffmanCodes(vector<char>& S, vector<int>& f) {
    priority_queue<Node*, vector<Node*>, compare> minHeap;
    
    for (int i = 0; i < S.size(); ++i)
        minHeap.push(new Node(S[i], f[i]));
    
    while (minHeap.size() != 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();
        
        Node* top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    
    unordered_map<char, string> huffmanCodes;
    printCodes(minHeap.top(), "", huffmanCodes);
    
    cout << "Character	Frequency	Huffman Code\n";
    cout << "\n";
    for (auto& pair : huffmanCodes) {
        auto it = find(S.begin(), S.end(), pair.first);
        int index = distance(S.begin(), it);
        cout << pair.first << "\t\t" << f[index] << "\t\t" << pair.second << "\n";
    }
}

int main() {
    vector<char> S = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> f = {5, 9, 12, 13, 16, 45};
    
    HuffmanCodes(S, f);
    
    return 0;
}
