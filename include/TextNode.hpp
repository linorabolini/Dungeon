#pragma once
#import "Utils.hpp"
#import "SceneNode.hpp"

using namespace std;
using namespace sf;

class TextNode : public SceneNode
{
public:
    TextNode();
    TextNode(const string& textString, const Font& font, unsigned int charSize=18) {
        text.setFont(font);
        text.setString(textString);
        text.setCharacterSize(charSize);
    }
    TextNode(Text& other) {
        text = other;
    }
    virtual void renderCurrent(sf::RenderWindow *window, const sf::Transform& parentTransform) const {
        window->draw(text, parentTransform);
    }
    Text text;
};

