#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int n;
    std::cin >> n; std::cin.ignore();
    std::vector<int> stockValues(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> stockValues[i]; std::cin.ignore();
    }

    int diff = 0;
    int firstNumber = stockValues[0];
    for(int i = 1; i < n; ++i)
    {
        int tmpDiff = 0;
        if(firstNumber < stockValues[i])
            firstNumber = stockValues[i];
        else if((tmpDiff=-1*(firstNumber - stockValues[i])) < diff)
        {
            diff = tmpDiff;
        }
    }

    std::cout << diff << std::endl;
}