#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>

class GameObject
{
public:
    virtual void update() {
        for (auto &child : children_)
        {
            child->update();
        }
    };
    virtual void render(sf::RenderWindow *window) {
        for (auto &child : children_)
        {
            child->render(window);
        }
    };

    void addChild(GameObject* go) { children_.push_back(go); }
private:
    std::vector<GameObject*> children_;
};


#endif /* GAMEOBJECT_HPP */
