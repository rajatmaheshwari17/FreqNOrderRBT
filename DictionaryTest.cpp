#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

using namespace std;

int main() {
    Dictionary dict;
    cout << "Starting tests for Dictionary ADT." << endl;

    // Test Constructors & Destructor
    cout << "Testing Constructors & Destructor." << endl;
    Dictionary dict1;
    cout << "Default constructor passed." << endl;

    // Testing Copy Constructor
    dict1.setValue("apple", 1);
    Dictionary dict2 = dict1;
    cout << "Copy constructor passed. Copied 'apple': " << dict2.getValue("apple") << endl;

    // Test Access Functions
    cout << "Testing Access Functions." << endl;
    cout << "Contains 'apple': " << (dict2.contains("apple") ? "Yes" : "No") << endl;
    cout << "Size: " << dict2.size() << endl;

    // Testing hasCurrent, currentKey, currentVal before any iteration
    cout << "HasCurrent (before iteration): " << (dict2.hasCurrent() ? "Yes" : "No") << endl;

    // Test Manipulation Procedures
    cout << "Testing Manipulation Procedures." << endl;
    dict2.setValue("banana", 2);
    cout << "After inserting 'banana': " << dict2.size() << endl;
    dict2.remove("apple");
    cout << "After removing 'apple': Size = " << dict2.size() << endl;

    // Testing begin, end, next, prev
    dict2.begin();
    cout << "CurrentKey after begin(): " << dict2.currentKey() << endl;
    dict2.next();
    cout << "CurrentKey after next(): " << dict2.currentKey() << endl;
    dict2.prev();
    cout << "CurrentKey after prev(): " << dict2.currentKey() << endl;

    // Test Other Functions
    cout << "Testing Other Functions." << endl;
    cout << "String representation (dict2):" << endl << dict2.to_string() << endl;
    cout << "Pre-order string (dict2):" << endl << dict2.pre_string() << endl;

    // Test Overloaded Operators
    cout << "Testing Overloaded Operators." << endl;
    Dictionary dict3;
    dict3 = dict2; // Testing operator=
    cout << "Operator= passed. Copied 'banana': " << dict3.getValue("banana") << endl;

    cout << "Operator<< and to_string(): " << dict2 << endl;

    bool equalsTest = (dict2 == dict3);
    cout << "Operator==: " << (equalsTest ? "Dictionaries are equal." : "Dictionaries are not equal.") << endl;

    // Clear and final size check
    dict3.clear();
    cout << "After clear(), dict3 size: " << dict3.size() << endl;

    // Exception handling tests
    cout << "Testing Exception Handling." << endl;
    try {
        dict3.getValue("nonexistent");
    } catch (const logic_error& e) {
        cout << "Caught logic_error as expected: " << e.what() << endl;
    }

    try {
        dict3.remove("nonexistent");
    } catch (const logic_error& e) {
        cout << "Caught logic_error as expected: " << e.what() << endl;
    }

    cout << "All tests completed." << endl;
    return EXIT_SUCCESS;
}
