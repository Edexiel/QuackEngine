//
// Created by g.nisi on 2/26/21.
//

#ifndef QUACKENGINE_GAME_HPP
#define QUACKENGINE_GAME_HPP

class Game {
public:
  void Init();
  void Update(float DeltaTime);
  void FixedUpdate(float FixedDeltaTime);
  void Render();
  void Destroy();
};

#endif // QUACKENGINE_GAME_HPP
