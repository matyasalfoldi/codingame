#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Position
{
    int x;
    int y;
};

struct Building
{
    int height;
    int originalHeight;
    int width;
    int originalWidth;
};

class Batman
{
    public:
        Batman(Position startPos, Building b)
        {
            pos = startPos;
            building = b;
        }

        Position Move(std::string dir)
        {
            cerr << pos.x << " " << pos.y << endl;
            if (dir.find("U") != std::string::npos)
            {
                Up();
            }
            else if (dir.find("D") != std::string::npos)
            {
                Down();
            }
            if (dir.find("L") != std::string::npos)
            {
                Left();
            }
            else if (dir.find("R") != std::string::npos)
            {
                Right();
            }
            return pos;
        }

    private:
    Position pos;
    Building building;
    int leftBoundary = 0;
    int upBoundary = 0;

    void Up()
    {
        building.height = pos.y;
        pos.y = (pos.y+upBoundary)/2;
    }
    void Right()
    {
        leftBoundary = pos.x;
        pos.x = (pos.x+building.width)/2;
    }
    void Left()
    {
        building.width = pos.x;
        pos.x = (pos.x+leftBoundary)/2;
    }
    void Down()
    {
        upBoundary = pos.y;
        pos.y = (pos.y+building.height)/2;
    }
};

int main()
{
    Building building;
    cin >> building.width >> building.height; cin.ignore();
    building.originalHeight = building.height;
    building.originalWidth = building.width;
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    Position startPos;
    cin >> startPos.x >> startPos.y; cin.ignore();
    Batman batman(startPos, building);
    // game loop
    while (1) {
        string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bombDir; cin.ignore();
        cerr << bombDir << endl;
        Position nextPos = batman.Move(bombDir);
        cout << nextPos.x << " " << nextPos.y << endl;
    }
}
