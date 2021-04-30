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

class Thor
{
    public:
    Thor(Position light, Position start)
    : pos(start), light(light)
    {}

    std::string Move()
    {
        cerr << pos.x << " " << pos.y << endl;
        cerr << light.x << " " << light.y << endl;
        std::string output = "";
        if(light.y > pos.y)
        {
            output = "S";
            ++pos.y;
        }
        else if(light.y < pos.y)
        {
            output = "N";
            --pos.y;
        }
        if(light.x > pos.x)
        {
            output += "E";
            ++pos.x;
        }
        else if(light.x < pos.x)
        {
            output += "W";
            --pos.x;
        }
        return output;
    }
    private:
    Position pos;
    Position light;
};

int main()
{
    Position light;
    Position start;
    cin >> light.x >> light.y >> start.x >> start.y; cin.ignore();
    Thor thor(light,start);
    // game loop
    while (1) {
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        cin >> remainingTurns; cin.ignore();
        cout << thor.Move() << endl;
    }
}