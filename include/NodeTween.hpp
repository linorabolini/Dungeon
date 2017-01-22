#ifndef NODETWEEN_HPP
#define NODETWEEN_HPP

#include <tween.h>
#include "SceneNode.hpp"

using namespace tween;

class SceneNode;

class NodeTween
{
public:
    static Tween position(SceneNode &node, vector<float>& from, const vector<float> &to);
};


#endif /* NODETWEEN_HPP */
