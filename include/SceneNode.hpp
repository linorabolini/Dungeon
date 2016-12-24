#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <SFML/Graphics.hpp>

class SceneNode
{
public:
    virtual void updateCurrent() {};
    virtual void updateChildren() {
        for (auto &child : children_)
        {
            child->update();
        }
    };
    virtual void update() {
        updateCurrent();
        updateChildren();
    };
    virtual void renderCurrent(sf::RenderWindow *window) {};
    virtual void renderChildren(sf::RenderWindow *window) {
        for (auto &child : children_)
        {
            child->render(window);
        }
    };
    virtual void render(sf::RenderWindow *window) {
        renderCurrent(window);
        renderChildren(window);
    };

    void addChild(SceneNode* go) { children_.push_back(go); }
private:
    std::vector<SceneNode*> children_;
};


#endif /* SCENENODE_HPP */
