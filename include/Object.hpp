#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "XMLNode.hpp"

class Object : public XMLNode
{
  public:
    std::string name;
    std::string type;
    sf::Rect<int> rect;
    std::map<std::string, std::string> properties; //All properties of the object. Values are stored as strings and mapped by strings(names provided in editor).
};

#endif /* OBJECT_HPP */
