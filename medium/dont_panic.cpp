#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Floor
{
    int elevatorPos;
    int exitPos;
    int blockCount;
    Floor()
    {
        elevatorPos = -1;
        exitPos = -1;
        blockCount = 0;
    }
};

int main()
{
    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor;
    int exitPos;
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    
    std::cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; std::cin.ignore();
    
    std::vector<Floor> floors(nbFloors);
    floors[exitFloor].exitPos = exitPos;
    for (int i = 0; i < nbElevators; i++) {
        int elevatorFloor;
        int elevatorPos;
        std::cin >> elevatorFloor >> elevatorPos; std::cin.ignore();
        floors[elevatorFloor].elevatorPos = elevatorPos;
    }

    // game loop
    while (1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        std::string direction; // direction of the leading clone: LEFT or RIGHT
        std::cin >> cloneFloor >> clonePos >> direction; std::cin.ignore();

        if(cloneFloor == -1)
            std::cout << "WAIT" << std::endl;

        if(floors[cloneFloor].blockCount)
        {
            std::cout << "WAIT" << std::endl;
        }
        else if(floors[cloneFloor].exitPos != -1)
        {
            if(floors[cloneFloor].exitPos < clonePos &&
                direction == "RIGHT")
            {
                std::cout << "BLOCK" << std::endl;
                ++floors[cloneFloor].blockCount;
            }
            else if(floors[cloneFloor].exitPos > clonePos &&
                    direction == "LEFT")
            {
                std::cout << "BLOCK" << std::endl;
                ++floors[cloneFloor].blockCount;
            }
            else
            {
                std::cout << "WAIT" << std::endl;
            }
        }
        else if(floors[cloneFloor].elevatorPos != -1)
        {
            if(floors[cloneFloor].elevatorPos < clonePos &&
                direction == "RIGHT")
            {
                std::cout << "BLOCK" << std::endl;
                ++floors[cloneFloor].blockCount;
            }
            else if(floors[cloneFloor].elevatorPos > clonePos &&
                    direction == "LEFT")
            {
                std::cout << "BLOCK" << std::endl;
                ++floors[cloneFloor].blockCount;
            }
            else
            {
                std::cout << "WAIT" << std::endl;
            }
        }
        else
        {
            std::cout << "WAIT" << std::endl;
        }

    }
}
