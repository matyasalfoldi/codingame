#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main()
{
    int N;
    std::cin >> N; std::cin.ignore();
    int Q;
    std::cin >> Q; std::cin.ignore();
    std::unordered_map<std::string, std::string> mimeTypes;
    for (int i = 0; i < N; i++)
    {
        std::string EXT;
        std::string MT;
        std::cin >> EXT >> MT; std::cin.ignore();
        std::transform(EXT.begin(), EXT.end(), EXT.begin(), ::tolower);
        mimeTypes[EXT] = MT;
    }
    std::vector<std::string> types(Q);
    for (int i = 0; i < Q; i++)
    {
        std::string FNAME;
        getline(std::cin, FNAME);
        std::transform(FNAME.begin(), FNAME.end(), FNAME.begin(), ::tolower);
        auto lastOcc = FNAME.find_last_of(".");
        types[i] = FNAME.substr(lastOcc+1);

        if(lastOcc == FNAME.npos ||
           lastOcc == FNAME.length()-1)
        {
            std::cout << "UNKNOWN" << std::endl;
        }
        else if(mimeTypes.find(types[i]) != mimeTypes.end())
        {
            std::cout << mimeTypes[types[i]] << std::endl;
        }
        else
        {
            std::cout << "UNKNOWN" << std::endl;
        }
    }
}
