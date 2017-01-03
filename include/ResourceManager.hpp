#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "Utils.hpp"

using namespace std;
using namespace sf;

class ResourceManager
{
  public:
    Texture &getTexture(string id) { return textures_[id]; }
    bool registerTexture(string id, string path)
    {
        return textures_[id].loadFromFile(path);
    }

    Font &getFont(string id) { return fonts_[id]; }
    bool registerFont(string id, string path)
    {
        return fonts_[id].loadFromFile(path);
    }

  private:
    map<string, Texture> textures_;
    map<string, Font> fonts_;
};

#endif /* RESOURCEMANAGER_HPP */
