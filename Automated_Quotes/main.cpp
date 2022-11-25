#include "String_Operations.h"
using namespace std;

const string optionsDir = "Resources/options.txt";
const Options options = loadOptions(optionsDir);

sf::Font createFont(string fontDirectory)
{
    sf::Font font;
    if (!font.loadFromFile(fontDirectory))
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
    //Set quotes container
    std::wstring quoteString;

    writeFileToString(quoteString, options.quoteFileDir);
    vector<std::wstring> quotesArray = splitStringToVector(quoteString, options.splitter);

    //Set Background
    sf::Texture backGroundTexture;
    backGroundTexture.loadFromFile(options.backgroundDir);
    sf::Sprite backgroundSprite(backGroundTexture);

    //Set Quote Text
    sf::Font txtFont = createFont(options.txtFontDir);
    sf::Text text;

    //Set Watermark Text
    sf::Text waterMarkText = makeText(options.watermarkString, options.waterCharacterSize);
    sf::Font waterFont = createFont(options.waterFontDir);
    waterMarkText.setFont(waterFont);
    const sf::FloatRect waterLbounds = waterMarkText.getLocalBounds();

    sf::RenderTexture rTexture;
    rTexture.create(options.resX, options.resY);

    for (int i = 0; i < quotesArray.size(); i++)
    {
        text = makeText(quotesArray[i], options.textCharacterSize);
        text.setFont(txtFont);
        sf::FloatRect textLbounds = text.getLocalBounds();
        text.setPosition(options.resX / 2 - textLbounds.width/2, options.resY / 2 - textLbounds.height / 2);
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