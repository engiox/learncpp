#include <iostream>

void countDown(int count)
{
    std::cout << "push " << count << '\n';
	if (count > 100) return;
    countDown(count-1); // countDown() calls itself recursively
}

int main()
{
    countDown(5);

    return 0;
}
