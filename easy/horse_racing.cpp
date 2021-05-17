#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int N;
    cin >> N; cin.ignore();
    std::vector<int> strengths(N);
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> strengths[i]; cin.ignore();
    }
    std::sort(strengths.begin(),strengths.end());

    int diff = abs(strengths[0]-strengths[1]);

    for(int i = 2; i < N; ++i)
    {
        if(diff > abs(strengths[i]-strengths[i-1]))
        {
            diff = abs(strengths[i]-strengths[i-1]);
        }
    }
    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << diff << endl;
}