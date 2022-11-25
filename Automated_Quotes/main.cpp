#include "Quote_Functions.h"
using namespace std;

const string optionsDir = "Resources/options.txt";
const Options options = loadOptions(optionsDir);

int main()
{
    //Set quotes container
    std::wstring quoteString;

    writeFileToString(quoteString, options.quoteFileDir);
    vector<std::wstring> quotesArray = splitStringToVector(quoteString, options.splitter);

    //Set text color temporary ADD IT IN OPTIONS
    sf::Color textColor = sf::Color::Black;
    textColor.a = 204;

    //Set Background
    sf::Texture backGroundTexture;
    backGroundTexture.loadFromFile(options.backgroundDir);
    sf::Sprite backgroundSprite(backGroundTexture);

    //Set Quote Text
    sf::Font txtFont = createFont(options.txtFontDir);
    sf::Text text;

    //Set Watermark Text
    sf::Text waterMarkText = makeText(options.watermarkString, options.waterCharacterSize, textColor);
    sf::Font waterFont = createFont(options.waterFontDir);
    waterMarkText.setFont(waterFont);
    const sf::FloatRect waterLbounds = waterMarkText.getLocalBounds();

    sf::RenderTexture rTexture;
    rTexture.create(options.resX, options.resY);

    for (int i = 0; i < quotesArray.size(); i++)
    {
        text = makeText(quotesArray[i], options.textCharacterSize, textColor);
        text.setFont(txtFont);
        text.setLetterSpacing(0.1);
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