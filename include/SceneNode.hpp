#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <SFML/Graphics.hpp>

class SceneNode : public sf::Transformable
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
    virtual void renderCurrent(sf::RenderWindow *window, const sf::Transform& parentTransform) const {};
    virtual void renderChildren(sf::RenderWindow *window, const sf::Transform& parentTransform) const {
        for (auto &child : children_)
        {
            child->render(window, parentTransform);
        }
    };
    virtual void render(sf::RenderWindow *window, const sf::Transform parentTransform) const {
        // Apply transform of current node
        auto combinedTransform = parentTransform * getTransform();

        renderCurrent(window, combinedTransform);
        renderChildren(window, combinedTransform);
    };

    SceneNode* removeChild(SceneNode* node)
    {
        auto found = std::find_if(children_.begin(), children_.end(), [&] (SceneNode* p) { 
            return p == node; 
        });

        SceneNode* result = *found;
        result->parent = nullptr;
        children_.erase(found);
        return result;
    }

    void addChild(SceneNode* node) {
        node->parent = this;
        children_.push_back(node); 
    }

    sf::Vector2f getWorldPosition() const
    {
        return getWorldTransform() * sf::Vector2f();
    }

    sf::Transform getWorldTransform() const
    {
        sf::Transform transform = sf::Transform::Identity;

        for (const SceneNode* node = this; node != nullptr; node = node->parent)
            transform = node->getTransform() * transform;

        return transform;
    }
private:
    std::vector<SceneNode*> children_;
    SceneNode* parent;
};


#endif /* SCENENODE_HPP */
