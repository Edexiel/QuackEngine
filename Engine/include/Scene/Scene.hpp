//
// Created by g.nisi on 2/23/21.
//

#ifndef QUACKENGINE_SCENE_HPP
#define QUACKENGINE_SCENE_HPP

class Scene
{

public:
  void update(float DeltaTime);
  void fixedUpdate(float FixedDeltaTime);
  void draw();
  void imDraw();
private:
  void Serialize();
  void UnSerialize(stuff);

};

#endif // QUACKENGINE_SCENE_HPP
