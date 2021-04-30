#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <string>
#include <vector>


using namespace std;

struct Edge
{
    Edge() = default;
    Edge(int node1, int node2)
    {
        this->node1 = node1;
        this->node2 = node2;
    }
    int node1;
    int node2;
};

class Graph
{
public:
   Graph()
   {
        cin >> numOfNodes >> numOfLinks >> numOfExits; cin.ignore();
        int node1;
        int node2;
        graph.resize(numOfNodes);
        for(int i = 0; i < numOfNodes; ++i)
        {
            graph[i].resize(numOfNodes);
        }

        for (int i = 0; i < numOfLinks; i++)
        {
            cin >> node1 >> node2; cin.ignore();
            graph[node1][node2] = 1;
            graph[node2][node1] = 1;
            edges.push_back(Edge(node1,node2));
        }

        int exitIndex;
        for (int i = 0; i < numOfExits; i++)
        {
            cin >> exitIndex; cin.ignore();
            exits.push_back(exitIndex);
        }
   }

   std::string cut(int skynetIndex)
   {
        return searchClosestExit(skynetIndex);
   }
private:
    std::vector<std::vector<int>> graph;
    std::vector<Edge> edges;
    std::vector<int> exits;
    int numOfNodes;
    int numOfLinks;
    int numOfExits;
    
    std::string searchClosestExit(int skynetIndex)
    {
        std::string closestExit = "";

        std::queue<int> nodesToVisit;

        for(int i = 0; i < numOfNodes; ++i)
        {
            if(graph[skynetIndex][i])
            {
                if(isExit(i) && graph[skynetIndex][i])
                {
                    std::cerr << "isExit:" << i << std::endl;
                    closestExit = getEdge(skynetIndex,i);
                    remove(skynetIndex, i);
                    return closestExit;
                }
                else
                {
                    nodesToVisit.push(i);
                }
                
            }
                
        }

        std::vector<int> visited;

        while(!nodesToVisit.empty())
        {
            auto elem = nodesToVisit.front();
            nodesToVisit.pop();
            visited.push_back(elem);
            for(int i = 0; i < numOfNodes; ++i)
            {
                if(isExit(i) && graph[elem][i])
                {
                    closestExit = getEdge(elem,i);
                    remove(elem, i);
                    return closestExit;
                }
                if(std::find(visited.begin(), visited.end(), i) == visited.end())
                {
                    nodesToVisit.push(i);
                }
            }
        }

        return closestExit;
    }

    std::string getEdge(int node1, int node2)
    {
        for(int i = 0; i < edges.size(); ++i)
        {
            if(edges[i].node1 == node1 &&
               edges[i].node2 == node2)
            {
                return std::to_string(node1) + " " + std::to_string(node2);
            }
            else if(edges[i].node1 == node2 &&
                    edges[i].node2 == node1)
            {
                return std::to_string(node2) + " " + std::to_string(node1);
            }
        }
    }

    void remove(int node1, int node2)
    {
        graph[node1][node2] = 0;
        graph[node2][node1] = 0;
        removeEdge(node1,node2);
    }

    void removeEdge(int node1, int node2)
    {
        for(int i = 0; i < edges.size(); ++i)
        {
            if(edges[i].node1 == node1 &&
               edges[i].node2 == node2)
            {
                edges.erase(edges.begin()+i);
            }
            else if(edges[i].node1 == node2 &&
                    edges[i].node2 == node1)
            {
                edges.erase(edges.begin()+i);
            }
        }
    }

    bool isExit(int index)
    {
        return std::find(exits.begin(), exits.end(), index) != exits.end();
    }
};


int main()
{
    Graph graph;

    while (1) {
        int skynetIndex;
        cin >> skynetIndex; cin.ignore();
        cout << graph.cut(skynetIndex) << endl;
    }
}
