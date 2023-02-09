#include <iostream>

size_t getIndex(size_t row, size_t col, size_t maxCol);

int main()
{
        std::cout << "Enter the number of rows: ";
        size_t nRows{};
        std::cin >> nRows;

        std::cout << "Enter the number of columns: ";
        size_t nColumns{};
        std::cin >> nColumns;

    {
        int arrayF[10][5]{};
//        int** arrayD0 { new int[10][5] };           // error: won’t work!
//        auto arrayD1{ new int[nRows][nColumns] };   // error: rightmost dimension must be constexpr
//        int *arrayD2[5]{ new int[nRows][5] };       // error: pointer to array on int
        int (*arrayD3)[5]{ new int[nRows][5] };     // array of pointers to int
        auto arrayD4{ new int[nRows][5] };          // auto makes it simpler!

        delete[] arrayD3;
        delete[] arrayD4;
    }

    {
        int** array { new int*[nRows] }; // allocate an array of 10 int pointers — these are our rows
        for (size_t count { 0 }; count < nRows; ++count)
            array[count] = new int[nColumns]; // these are our columns

        array[9][4] = 3; // This is the same as (array[9])[4] = 3;

        for (size_t count { 0 }; count < nRows; ++count) {
            delete[] array[count];
        }
        delete[] array;
    }

    {
        int *array{ new int[nRows * nColumns] };
        for (size_t indexRow{ 0 }; indexRow < nRows; ++indexRow) {
            for (size_t indexCol{ 0 }; indexCol < nColumns; ++indexCol) {
                array[getIndex(indexRow, indexCol, nColumns)] = indexRow * 10 + indexCol;
            }
        }
        for (size_t indexRow{ 0 }; indexRow < nRows; ++indexRow) {
            for (size_t indexCol{ 0 }; indexCol < nColumns; ++indexCol) {
                std::cout << array[getIndex(indexRow, indexCol, nColumns)] << '\t';
            }
            std::cout << '\n';
        }
    }

    return 0;
}

size_t getIndex(size_t row, size_t col, size_t maxCol)
{
    return (row * maxCol + col);
}
