#include <iostream>
#include <string>
#include <bitset>
using namespace std;
int main()
{
    string MESSAGE;
    getline(cin, MESSAGE);
    std::string bits;
    for(auto c : MESSAGE)
    {
        auto charBits = std::bitset<7>(c).to_string();
        bits += charBits;
    }
    std::cerr << bits << std::endl;

    int i = 0;
    std::string output = "";
    while(i < bits.length())
    {
        if(bits.substr(i,1) == "1")
        {
            output += "0 ";
            int j = i;
            while(bits.substr(j,1) == "1")
            {
                output += "0";
                ++j;
            }
            output += " ";
            i = j;
        }
        else
        {
            output += "00 ";
            int j = i;
            while(bits.substr(j,1) == "0")
            {
                output += "0";
                ++j;
            }
            output += " ";
            i = j;
        }
    }
    cout << output.substr(0,output.length()-1) << endl;
}