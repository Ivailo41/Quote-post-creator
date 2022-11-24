#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>


static void writeFileToString(std::wstring& stringToWrite, std::string fileName)
{
    std::wifstream file;
    std::wstring line;
    //size_t strLen = str.length();
    //wchar_t* line = new wchar_t[strLen + 1];
    //line[strLen] = '\0';

    file.open(fileName , std::ios::binary);

    if (file.bad())
    {
        return;
    }

    file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));

    //while (file.getline(line, strLen))
    while (getline(file, line))
    {
        stringToWrite.append(L"\n");
        stringToWrite.append(line);
        /*str += L"\n";
        str += line;*/
    }

    file.close();
}

static std::vector<std::wstring> splitStringToVector(std::wstring quoteString, std::wstring splitter)
{
    std::vector<std::wstring> quoteArr;
    size_t subStringStart = 0, subStringEnd = 0;

    while (subStringEnd < quoteString.size())
    {
        subStringEnd = quoteString.find(splitter, subStringStart);
        quoteArr.push_back(quoteString.substr(subStringStart, subStringEnd - subStringStart));
        subStringStart = subStringEnd + splitter.size();
    }

    return quoteArr;
}