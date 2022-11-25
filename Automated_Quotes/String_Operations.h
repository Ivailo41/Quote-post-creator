#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>

struct Options
{
    int resX, resY, waterCharacterSize, textCharacterSize;

    std::wstring splitter, watermarkString;
    std::string quoteFileDir, backgroundDir, txtFontDir, waterFontDir;
};

static void writeFileToString(std::wstring& stringToWrite, std::string fileName)
{
    std::wifstream file;
    std::wstring line;

    file.open(fileName, std::ios::binary);

    if (file.bad())
    {
        return;
    }

    wchar_t wbuf[128] = { 0 };
    file.rdbuf()->pubsetbuf(wbuf, 128);

    //BOM check
    wchar_t bom{};
    file.read(&bom, 1);

    getline(file, line);
    stringToWrite.append(line);

    while (getline(file, line))
    {
        stringToWrite.append(L"\n");
        stringToWrite.append(line);
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

static Options loadOptions(std::string optionsDir) 
{
    Options options;
    std::vector<std::string> optionsVector;

    std::ifstream file;
    std::string line;

    file.open(optionsDir);

    if (file.bad())
    {
        return options;
    }

    while (!file.eof()) 
    {
        getline(file, line);
        getline(file, line);
        optionsVector.push_back(line);
        getline(file, line);
    }

    options.resX = stoi(optionsVector[0]);
    options.resY = stoi(optionsVector[1]);
    options.textCharacterSize = stoi(optionsVector[2]);
    options.waterCharacterSize = stoi(optionsVector[3]);
    options.splitter = L"\r\n;\r\n";
    options.quoteFileDir = optionsVector[5];
    options.txtFontDir = optionsVector[6];
    options.waterFontDir = optionsVector[7];
    options.backgroundDir = optionsVector[8];
    options.watermarkString = L"@citati.bg.en";

    return options;
}