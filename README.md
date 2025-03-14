# Huffman Code Generator

## Introduction

Huffman coding is a widely used algorithm for data compression. It works by assigning variable-length codes to input characters, with shorter codes given to more frequent characters. This project provides a C++ implementation of Huffman coding, allowing you to compress and decompress text efficiently.

## Features

- Compress text using Huffman coding
- Decompress Huffman-encoded text
- Serialize and deserialize Huffman trees
- Interactive menu-based interface for user convenience
- Efficient implementation using min-heap priority queue

## Project Structure

The project consists of the following components:

- **HuffmanNode**: Represents a node in the Huffman tree, containing character data, frequency, and pointers to parent, left, and right nodes.
- **HuffmanTree**: Implements the Huffman coding algorithm, including methods for compression, decompression, and tree serialization.
- **HeapQueue**: A min-heap implementation used to efficiently build the Huffman tree based on character frequencies.
- **VectorCompleteTree**: A vector-based complete binary tree implementation used by the HeapQueue.

### Files

- `HuffmanBase.hpp` and `HuffmanBase.cpp`: Define the base classes and interfaces
- `HuffmanTree.hpp` and `HuffmanTree.cpp`: Implement the Huffman coding algorithm
- `HeapQueue.hpp`: Template implementation of a min-heap priority queue

## How It Works

### Compression

1. **Frequency Analysis**: The algorithm first counts the frequency of each character in the input string.
2. **Tree Construction**: A min-heap is used to build the Huffman tree by repeatedly combining the two nodes with the lowest frequencies.
3. **Code Generation**: The algorithm traverses the tree to generate variable-length binary codes for each character, with shorter codes assigned to more frequent characters.
4. **Encoding**: The input string is encoded by replacing each character with its corresponding binary code.

### Decompression

1. **Tree Reconstruction**: The Huffman tree is reconstructed from its serialized form.
2. **Decoding**: The compressed binary string is traversed bit by bit, following the Huffman tree from root to leaf to recover the original characters.

### Tree Serialization

The Huffman tree is serialized using a post-order traversal:

- Leaf nodes are marked with 'L' followed by the character
- Branch nodes are marked with 'B'

This serialized representation allows the tree to be reconstructed for decompression.

## How to Compile

To compile the project, use a C++ compiler with C++11 support or later:

```bash
g++ -std=c++11 HuffmanBase.cpp HuffmanTree.cpp -o huffman_encoder
```

## Usage

Run the compiled program:

```bash
./huffman_encoder
```

The program provides an interactive menu with the following options:

1. **Compress a string**: Enter a string to compress it using Huffman coding
2. **Decompress a string**: Enter a compressed string and its serialized tree to decompress it
3. **Exit**: Exit the program

### Example

```
Huffman Compression and Decompression Menu
1. Compress a string
2. Decompress a string
3. Exit
Enter your choice (1/2/3): 1

Enter the string to compress: hello world

a 1
d 1
e 1
h 1
l 3
o 2
r 1
w 1
  1

---------------------

h 000
e 001
l 01
o 10
  1100
w 1101
r 1110
d 1111

---------------------

Compressed string: 0000010101101100110111101011111

Huffman Compression and Decompression Menu
1. Compress a string
2. Decompress a string
3. Exit
Enter your choice (1/2/3): 2

Enter the compressed string: 0000010101101100110111101011111
Enter the serialized tree: LhLeLlBBLoL BLwLrLdBBB
Decompressed string: hello world
```

## Technical Details

### Time Complexity

- **Compression**: O(n log k), where n is the length of the input string and k is the number of unique characters
- **Decompression**: O(n), where n is the length of the compressed string

### Space Complexity

- **Compression**: O(k), where k is the number of unique characters
- **Decompression**: O(k), where k is the number of unique characters

## Potential Enhancements

Future enhancements to this project could include:

- File compression/decompression support
- Graphical user interface
- Compression statistics (compression ratio, etc.)
- Support for additional compression algorithms
- Batch processing of multiple files
- Huffman tree visualization
- Command-line interface for scripting and automation

## Requirements

- C++11 compatible compiler
- Standard C++ libraries

## License

This project is available for educational and personal use.
