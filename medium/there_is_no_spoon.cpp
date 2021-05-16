#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

int main()
{
    int width; // the number of cells on the X axis
    std::cin >> width; std::cin.ignore();
    int height; // the number of cells on the Y axis
    std::cin >> height; std::cin.ignore();
    std::vector<std::vector<char> > grid(height);
    for (int i = 0; i < height; i++)
    {
        grid[i].resize(width);
        std::string line;
        getline(std::cin, line); // width characters, each either 0 or .
        for(int j = 0; j < width; ++j)
            grid[i][j] = line[j];
    }

    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            if(grid[i][j] == '0')
            {
                std::cout << j << " " << i << " ";
                bool ran = false;
                int k = j+1;
                if(k == width)
                    std::cout << "-1 -1 ";
                while(k < width)
                {
                    ran = true;
                    if(grid[i][k] == '0')
                    {
                        std::cout << k << " " << i << " ";
                        break;
                    }
                    ++k;
                }
                if(k == width && ran)
                    std::cout << "-1 -1 ";

                k = i+1;
                ran = false;
                if(k == height)
                    std::cout << "-1 -1" << std::endl;
                while(k < height)
                {
                    ran = true;
                    if(grid[k][j] == '0')
                    {
                        std::cout << j << " " << k << std::endl;
                        break;
                    }
                    ++k;
                }
                if(k == height && ran)
                    std::cout << "-1 -1" << std::endl;
            }
        }
    }
}