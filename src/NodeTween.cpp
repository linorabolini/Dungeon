#include <NodeTween.hpp>

Tween NodeTween::position(SceneNode &node, vector<float>& from, const vector<float> &to)
{
    return Tween::make()
        .to(from, to)
        .fromTo(1.f, 2.f) // workaround to use onUpdate
        .onUpdate([&]() {
            node.setPosition(from[0], from[1]);
        });
}