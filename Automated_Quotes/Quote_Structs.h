#pragma once
#include <string>

struct Options
{
    int resX, resY, waterCharacterSize, textCharacterSize;

    std::wstring splitter, watermarkString;
    std::string quoteFileDir, backgroundDir, txtFontDir, waterFontDir;
};
