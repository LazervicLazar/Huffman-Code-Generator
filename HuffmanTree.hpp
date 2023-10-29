#include <iostream>
#include <string>
#include <ctype.h>
#include <algorithm>
#include <stack>

#include "HuffmanBase.hpp"

class HuffmanTree {
    private:
    HuffmanNode *root;

    public:
    std::string compress(const std::string inputStr);
    // Compress the input string using the method explained above. Note: Typically we would be 
    // returning a number of bits to represent the code, but for this project we are returning a string

    void findPrefix(HuffmanNode* root, std::string prefixStr, std::map<char, std::string> &huffmanCode);
    // Find the prefix code for each character in the tree and store in the map. This is a helper function
    
    std::string serializeTree() const;
    // Serialize the tree using the above method. We do not need the frequency values to rebuild the 
    // tree, just the characters on the leaves and where the branches are in the post order.
    


    void serializeMarker(HuffmanNode *root, std::string &s) const {
        //Function to serialize the tree using L and B markers
        
        //Base case
        if (root == NULL)
            return;

        serializeMarker(root->left, s);
        serializeMarker(root->right, s);
        
        //If leaf node
        if (root->isLeaf())
        {   //Add L marker and character to string
            s = s + "L";
            s += root->getCharacter();
        } //If branch node, add B marker
        else if (root->isBranch()) {
            s = s + "B";
        } 

}

std::string decompress(const std::string inputCode, const std::string serializedTree);
// Decompress the input code using the serialized tree. This is the reverse of the compress function.

};

