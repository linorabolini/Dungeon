#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>

class XMLNode {
  public:
    int id;
    virtual int GetPropertyInt(std::string name);
    virtual float GetPropertyFloat(std::string name);
    virtual std::string GetPropertyString(std::string name);
    std::map<std::string, std::string> properties; //All properties of the TileObject. Values are stored as strings and mapped by strings(names provided in editor).
};

