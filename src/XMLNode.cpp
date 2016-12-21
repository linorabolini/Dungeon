#include <XMLNode.hpp>

int XMLNode::GetPropertyInt(std::string name)
{
    int i;
    i = atoi(properties[name].c_str());

    return i;
}

float XMLNode::GetPropertyFloat(std::string name)
{
    float f;
    f = strtod(properties[name].c_str(), NULL);

    return f;
}

std::string XMLNode::GetPropertyString(std::string name)
{
    return properties[name];
}