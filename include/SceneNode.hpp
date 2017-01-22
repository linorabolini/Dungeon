#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
class SceneNode : public sf::Transformable
{
public:
    static int nodeCount;
    int nodeId = 0;
    SceneNode(){
        nodeId = nodeCount++;
        std::cout << "++ creating SceneNode " << nodeId <<  std::endl;
    };
    ~SceneNode() {
        nodeCount--;
        std::cout << "-- deleting SceneNode " << nodeId << " -- remaining: " << nodeCount << std::endl;
    }
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
        result->parent_ = nullptr;
        children_.erase(found);
        return result;
    }

    virtual void dispose() {
        disposed_ = true;
    }

    bool isDisposed() {
        return disposed_;
    }

    void removeDisposedChildren()
    {
        // Remove all children which request so
        auto wreckfieldBegin = std::remove_if(children_.begin(), children_.end(), std::mem_fn(&SceneNode::isDisposed));
        // std::for_each(wreckfieldBegin, children_.end(), std::default_delete<SceneNode>());
        children_.erase(wreckfieldBegin, children_.end());

        // Call function recursively for all remaining children
        std::for_each(children_.begin(), children_.end(), std::mem_fn(&SceneNode::removeDisposedChildren));
    }

    void addChild(SceneNode* node, bool allowDuplicate=false) {
        if(node->parent_ && !allowDuplicate) {
            if(node->parent_ == this) {
                return;
            }
            node->parent_->removeChild(node);
        }
        node->parent_ = this;
        children_.push_back(node);
    }

    void setParent(SceneNode* node) {
        if(this->parent_) {
            if(this->parent_ == node) {
                return;
            }
            this->parent_->removeChild(this);
        }
        if(node){
            node->addChild(this);
        }
    }

    sf::Vector2f getWorldPosition() const
    {
        return getWorldTransform() * sf::Vector2f();
    }

    sf::Transform getWorldTransform() const
    {
        sf::Transform transform = sf::Transform::Identity;

        for (const SceneNode* node = this; node != nullptr; node = node->parent_)
            transform = node->getTransform() * transform;

        return transform;
    }

    SceneNode* getParent() { return parent_; }
private:
    std::vector<SceneNode*> children_;
    SceneNode* parent_ = nullptr;
    bool disposed_ = false;
};


#endif /* SCENENODE_HPP */
