#include <iostream>
#include <string>
#include <vector>

class Grid
{
private:
    std::vector<std::vector<std::string> > grid;

    void fill(int row, int col)
    {
        grid[row][col] = 'Q';
    }

    void unfill(int row, int col)
    {
        grid[row][col] = "-";
    }

    bool collision(int row, int col)
    {
        std::cerr << row << " " << col << std::endl;
        // same row check
        for (auto cell : grid[row])
        {
            if (cell == "Q")
            {
                return true;
            }
        }
        // same col check
        for (auto i = 0; i < grid.size(); ++i)
        {
            if (grid[i][col] == "Q")
            {
                return true;
            }
        }
        // upper left diagonal check
        int i = row;
        int j = col;
        while (i >= 0 && j >= 0)
        {
            if (grid[i][j] == "Q")
            {
                return true;
            }
            --i;
            --j;
        }
        // upper right diagonal check
        i = row;
        j = col;
        while (i >= 0 && j < grid[0].size())
        {
            if (grid[i][j] == "Q")
            {
                return true;
            }
                
            --i;
            ++j;
        }
        // no collision
        return false;
    }

    void search(int row, int col)
    {
        if (row >= grid.size() ||
            collision(row, col))
        {
            std::cerr << "collision" << std::endl;
            return;
        }
        else if (row == grid.size() - 1)
        {
            fill(row, col);
            output();
        }
        
        
        fill(row, col);
        for (int i = 0; i < grid[0].size(); ++i)
        {
            search(row + 1, i);
        }
        unfill(row, col);
    }

    void output()
    {
        for (auto row : grid)
        {
            for (auto cell : row)
                std::cout << cell;
            std::cout << std::endl;
        }
        std::exit(0);
    }
public:

    Grid()
    {
        grid.resize(4);
        for (auto i = 0; i < grid.size(); ++i)
        {
            grid[i].resize(4);
            for (auto j = 0; j < grid[0].size(); ++j)
            {
                grid[i][j] = "-";
            }
        }
    }

    void search()
    {
        for (int i = 0; i < grid[0].size(); ++i)
        {
            search(0, i);
        }

    }

};

int main()
{
    Grid grid;
    grid.search();
    return 0;
}
