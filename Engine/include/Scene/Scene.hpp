//
// Created by g.nisi on 2/23/21.
//

#ifndef QUACKENGINE_SCENE_HPP
#define QUACKENGINE_SCENE_HPP

class Scene
{

public:
    void createEntity();
    void removeEntity();
    void update(float DeltaTime);
    void fixedUpdate(float FixedDeltaTime);s
    void draw();
    void load();
    void imDraw();
};

#endif // QUACKENGINE_SCENE_HPP
