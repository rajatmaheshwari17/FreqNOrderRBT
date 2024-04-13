
# FreNOrderRBT


This project implements a Dictionary Abstract Data Type (ADT) using a Red-Black Tree (RBT) as its underlying data structure. Red-Black Trees are efficient self-balancing binary search trees that ensure insertion, deletion, and search operations can be performed in logarithmic time complexity.

## Features

- **Red-Black Tree Implementation**: A complete implementation of the red-black tree to manage balanced data storage.
- **Dictionary ADT**: The dictionary supports basic operations such as insert, search, delete, and traversal methods to interact with key-value pairs stored within the red-black tree.
- **Pre-Order Traversal**: An enhanced pre-order traversal that indicates the color (red or black) of each node, which helps in verifying the properties of the red-black tree.
- **Word Frequency Counter**: A utility program (`WordFrequency.cpp`) that reads text files, tokenizes the content into words, and counts the frequency of each word using the Dictionary ADT.
- **Case Insensitivity**: The word tokenizer converts all text to lowercase to ensure case-insensitive processing.
- **Robust Tokenization**: Uses a comprehensive set of delimiters to accurately parse words from text, ignoring punctuation and special characters.

## Files

- **Dictionary.h**: Header file for the Dictionary ADT with Red-Black Tree specifics.
- **Dictionary.cpp**: Implementation of the Dictionary ADT using a Red-Black Tree.
- **DictionaryTest.cpp**: Test client for the Dictionary ADT.
- **Order.cpp**: A utility program to demonstrate the order operations similar to previous implementations.
- **WordFrequency.cpp**: Main client program designed to count word frequencies in large text files.
- **Makefile**: Build instructions for compiling the projects.
- **README.md**: This file, explaining the project and its components.

## Usage

To compile the project, ensure you have a C++ compiler that supports C++11 or later. Use the provided Makefile by running:

```bash
make
```

This will compile all the components. To run the word frequency program, use:

```bash
./WordFrequency [input_file.txt]
```

Replace `[input_file.txt]` with the path to your text file.

## Testing

The `DictionaryTest.cpp` file contains various test cases for the Dictionary ADT to ensure all functionalities are working as expected. Run these tests to verify the correctness of the implementation.

---
_This README is a part of the FreqNOrderRBT Project by Rajat Maheshwari._
