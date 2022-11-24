#include "String_Operations.h"
using namespace std;

//make em editable from file
const int resX = 1024;
const int resY = 1024;

const wstring splitter = L"\n;\n";
const string quoteFileDir = "Resources/quotes.txt";
const string fontDir = "Resources/Fonts/calibri.ttf";
const string backgroundDir = "Resources/bg.jpg";
const wstring watermarkString = L"@citati.bg.en";

sf::Font createFont(string fontDirectory)
{
    sf::Font font;
    if (!font.loadFromFile(fontDir))
    {
        cout << "Font not found!";
    }

    return font;
}

sf::Text makeText(const std::wstring textString, const size_t characterSize)
{
    sf::Text outputText;
    outputText.setPosition(0, 0);
    outputText.setString(textString);
    outputText.setCharacterSize(characterSize);
    outputText.setStyle(sf::Text::Regular);
    outputText.setFillColor(sf::Color::Black);

    return outputText;
}

int main()
{

    const sf::Font font = createFont(fontDir);

    //Set quotes container
    std::wstring quoteString;

    writeFileToString(quoteString, quoteFileDir);
    vector<std::wstring> quotesArray = splitStringToVector(quoteString, splitter);

    //Set Background
    sf::Texture backGroundTexture;
    backGroundTexture.loadFromFile(backgroundDir);
    sf::Sprite backgroundSprite(backGroundTexture);

    //Set Quote Text
    sf::Text text;

    //Set Watermark Text
    sf::Text waterMarkText = makeText(watermarkString, 50);
    waterMarkText.setFont(font);
    const sf::FloatRect waterLbounds = waterMarkText.getLocalBounds();

    sf::RenderTexture rTexture;
    rTexture.create(resX, resY);

    for (int i = 0; i < quotesArray.size(); i++)
    {
        text = makeText(quotesArray[i], 50);
        text.setFont(font);
        sf::FloatRect textLbounds = text.getLocalBounds();
        text.setPosition(resX / 2 - textLbounds.width/2, resY / 2 - textLbounds.height / 2);
        sf::FloatRect textGbounds = text.getGlobalBounds();
        waterMarkText.setPosition(textGbounds.left + textLbounds.width - waterLbounds.width, textGbounds.top + textLbounds.height);

        rTexture.draw(backgroundSprite);
        rTexture.draw(text);
        rTexture.draw(waterMarkText);
        rTexture.display();
        
        rTexture.getTexture().copyToImage().saveToFile("Output/quote_" + to_string(i) + ".png");

        rTexture.clear();
    }
}