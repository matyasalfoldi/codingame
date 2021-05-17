#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

struct Node
{
    Node(int xChange, int yChange, string dir)
    {
        this->xChange = xChange;
        this->yChange = yChange;
        this->dir = dir;
    }
    int xChange;
    int yChange;
    std::string dir;
};

std::map<int, std::vector<Node>> rooms = {
    {0, {Node(0,0,"nowhere")}},
    {1, {Node(0,1,"LEFT"),Node(0,1,"TOP"),Node(0,1,"RIGHT")}},
    {2, {Node(1,0,"LEFT"),Node(-1,0,"RIGHT")}},
    {3, {Node(0,1,"TOP")}},
    {4, {Node(-1,0,"TOP"),Node(0,1,"RIGHT")}},
    {5, {Node(0,1,"LEFT"),Node(1,0,"TOP")}},
    {6, {Node(1,0,"LEFT"),Node(-1,0,"RIGHT")}},
    {7, {Node(0,1,"TOP"),Node(0,1,"RIGHT")}},
    {8, {Node(0,1,"LEFT"),Node(0,1,"RIGHT")}},
    {9, {Node(0,1,"LEFT"),Node(0,1,"TOP")}},
    {10, {Node(-1,0,"TOP")}},
    {11, {Node(1,0,"TOP")}},
    {12, {Node(0,1,"RIGHT")}},
    {13, {Node(0,1,"LEFT")}}
};

int main()
{
    int W; // number of columns.
    int H; // number of rows.
    cin >> W >> H; cin.ignore();
    std::vector<std::vector<int> > grid(H);
    for (int i = 0; i < H; i++)
    {
        string LINE;
        getline(cin, LINE);
        grid[i].resize(W);
        std::istringstream iss(LINE);
        string room;
        int j = 0;
        while(iss >> room)
        {
            grid[i][j] = std::stoi(room);
            ++j;
        }
    }

    int EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
    cin >> EX; cin.ignore();

    // game loop
    while (1) {
        int XI;
        int YI;
        string POS;
        cin >> XI >> YI >> POS; cin.ignore();

        auto currRooms = rooms[grid[YI][XI]];
        for(auto currRoom : currRooms)
        {
            if(currRoom.dir == POS)
            {
                XI = XI + currRoom.xChange;
                YI = YI + currRoom.yChange;
            }
        }
        cout << XI << " " << YI << endl;
    }
}