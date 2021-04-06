#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
#include <algorithm>
#include <vector>

char characterStrings(std::uint8_t index)
{
    static std::vector<char> line{
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'B','C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z','A', 'E', 'I', 'O', 'U', 'Y',
        '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=', '{', ']', '[', '}', ';', ':', '?', '/', '>', '.', '<', ',',
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'
    };
    if (index >= line.size())
        index = 0;

    return line[index];
}
void ClipBoard(std::string const& output)
{
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, output.size() + 1);
    memcpy(GlobalLock(hMem), output.c_str(), output.size() + 1);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

std::string generateString()
{
    std::cout << "Enter the number of characters in the password: ";
    int length;
    std::cin >> length;

    std::string v(length, '0');
    std::generate(v.begin(), v.end(), [] {
        return characterStrings(rand() % 89);
    });
   
    ClipBoard(v);

    return v;
}

void writeToFile(std::string const& username, std::string const& site)
{
    auto const path = "vlad.txt";
    std::ofstream out(path, std::ios::app);
    if (out.is_open()) {
        out
            << "---------------\n"
            << "site"       << site             << std::endl
            << "username: " << username         << std::endl
            << "password: " << generateString() << std::endl;
        std::cout << "---------------\n";
        std::cout << "The password is written in " << path << std::endl;
    }
    else
        std::cout << "File '" << path << "' not found" << std::endl;
    out.close();
}

int main()
{
    std::srand(std::time(nullptr));

    std::string site, username;
    std::cout << "Enter a site name - ";
    std::cin >> site;
    std::cout << "Enter username - ";
    std::cin >> username;
    writeToFile(username, site);

    std::cout << "The password was copied to clipboard!" << std::endl;

    return 0;
}
