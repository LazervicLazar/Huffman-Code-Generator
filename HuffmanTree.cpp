/* 
 *
 * This program implements a Huffman Code Generator using HeapQueue and Tree.
 * It can compress, serialize, and decompress strings.
 *
*/

#include <iostream>
#include <string>
#include <ctype.h>
#include <algorithm>
#include <map>
#include <stack>

#include "HuffmanTree.hpp"
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"

using namespace std;

string HuffmanTree::compress(const std::string inputStr) {
    string s = ""; // string to be returned
    map<char, int> frequencyMap; // map of characters and their frequencies
    std::map<char, string> prefixMap; // map of characters and their prefix codes

    // create frequency map of characters
    for (char c : inputStr) {
        if (frequencyMap.find(c) == frequencyMap.end()) {
            frequencyMap[c] = 1;
        } else {
            frequencyMap[c]++;
        }
    }

    // create heap queue of HuffmanNodes
    HeapQueue<HuffmanNode* , HuffmanNode::Compare> huffmanq;

    // insert HuffmanNodes into heap queue
    for (auto it = frequencyMap.begin(); it != frequencyMap.end(); it++) {
        cout << it->first << " " << it->second << endl;
        HuffmanNode *node = new HuffmanNode(it->first, it->second);
        huffmanq.insert(node);
    }
    cout << '\n' << "---------------------" << '\n' << endl;

    // create Huffman tree
    while (huffmanq.size() != 1){
        HuffmanNode* left = huffmanq.min();
        huffmanq.removeMin();
        HuffmanNode* right = huffmanq.min();
        huffmanq.removeMin();
        size_t sum = (left->getFrequency() + right->getFrequency());
        HuffmanNode* parent = new HuffmanNode('\0', sum, NULL, left, right);
        left->parent = parent;
        right->parent = parent;
        huffmanq.insert(parent);
    }

    // get root of Huffman tree
    root = huffmanq.min();

    // find prefix codes for each character and store in map
    findPrefix(root, s, prefixMap); 

    for (auto it = prefixMap.begin(); it != prefixMap.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }

    // create compressed string
    for (int i = 0; i < inputStr.length(); i++) {
    s += prefixMap[inputStr[i]];
    }
    cout << '\n' << "---------------------" << '\n' << endl;

    return s;

}

void HuffmanTree::findPrefix(HuffmanNode* root, string prefixStr, std::map<char, string> &huffmanCode)
{
    // base case
    if(root == NULL)
    {
        return;
    }

    // if leaf node is reached, store prefix code in map
    if(!root -> left && !root -> right) {
        huffmanCode[root -> getCharacter()] = prefixStr; 
    }
    // traverse left and right sub-tree
    if(root -> left) {
        findPrefix(root -> left, prefixStr + "0", huffmanCode);
    } 
    if(root -> right) {
        findPrefix(root -> right, prefixStr + "1", huffmanCode);
    } 
    return;
}

std::string HuffmanTree::serializeTree() const {
    
    string s = "";
    // calls helper function to serialize tree (in hpp file)
    serializeMarker(root, s);
    return s;
}


std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {

    std::string output; // string to be returned
    std::stack<HuffmanNode*> treeStack; // stack to hold HuffmanNodes

    // create tree from serialized string
    for(size_t i = 0; i < serializedTree.size(); i++){
        char currentChar = serializedTree.at(i);
        // if leaf node, create new node and push onto stack
        if(currentChar == 'L'){
            i++;
            currentChar = serializedTree.at(i);
            HuffmanNode *n = new HuffmanNode(currentChar, 0);
            treeStack.push(n);
            // if branch node, pop two nodes off stack and create new node as parent
        } else if (currentChar == 'B') {

            HuffmanNode* right = treeStack.top();
            if (!treeStack.empty()) {            
                treeStack.pop();
            }
            
            HuffmanNode* left = treeStack.top();
            if (!treeStack.empty()) {
                treeStack.pop();
            }

            HuffmanNode* branch = new HuffmanNode('\0', 0, NULL, left, right);

            right->parent = branch;
            left->parent = branch;
            // push new node onto stack
            treeStack.push(branch);
        }
    }

    // get root of tree
    HuffmanNode* root = treeStack.top();

    HuffmanNode* curr = root;
    // traverse tree using input code
    for (size_t i = 0; i < inputCode.size(); i++) {
        char currentChar = inputCode.at(i);
        if (currentChar == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        // if leaf node, add character to output string and reset curr to root
        if (curr->isLeaf()) {
            output += curr->getCharacter();
            curr = root;
        }
    }
    return output;
}

int main() {
    HuffmanTree huffmanTree;
    string inputStr, compressedStr, serializedTree, decompressedStr;
    int choice;

    do {
        cout << "Huffman Compression and Decompression Menu" << endl;
        cout << "1. Compress a string" << endl;
        cout << "2. Decompress a string" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1/2/3): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the string to compress: ";
                cin.ignore(); // Consume the newline character left by the previous cin
                getline(cin, inputStr);
                compressedStr = huffmanTree.compress(inputStr);
                cout << "Compressed string: " << compressedStr << endl;
                break;
            case 2:
                cout << "Enter the compressed string: ";
                cin.ignore(); // Consume the newline character left by the previous cin
                getline(cin, compressedStr);
                cout << "Enter the serialized tree: ";
                getline(cin, serializedTree);
                decompressedStr = huffmanTree.decompress(compressedStr, serializedTree);
                cout << "Decompressed string: " << decompressedStr << endl;
                break;
            case 3:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
                break;
        }
    } while (choice != 3);

    return 0;
}
