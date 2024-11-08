#include <iostream>
#include "IntArray.h"

void printArray(IntArray& arr)
{
    // Print out all the numbers
    for (int i{ 0 }; i<arr.getLength(); ++i)
        std::cout << arr[i] << ' ';

    std::cout << '\n';
}

int main()
{
    // Declare an array with 10 elements
    IntArray array(10);

    printArray(array);

    // Fill the array with numbers 1 through 10
    for (int i{ 0 }; i<10; ++i)
        array[i] = i+1;

    printArray(array);

    // Resize the array to 8 elements
    array.resize(8);

    printArray(array);

    // Insert the number 20 before element with index 5
    array.insertBefore(20, 5);

    printArray(array);

    // Remove the element with index 3
    array.remove(3);

    printArray(array);

    // Add 30 and 40 to the end and beginning
    array.insertAtEnd(30);
    printArray(array);

    array.insertAtBeginning(40);

    printArray(array);

    // A few more tests to ensure copy constructing / assigning arrays
    // doesn't break things
    {
        IntArray b{ array };
        b = array;
        b = b;
        array = array;
    }

    // Print out all the numbers
    for (int i{ 0 }; i<array.getLength(); ++i)
        std::cout << array[i] << ' ';

    std::cout << '\n';

    return 0;
}
