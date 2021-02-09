//#include "glad/glad.h"
//#include "assimp/importerdesc.h"

#include <iostream>

#include "Resources/ResourcesManager.hpp"
#include "Renderer//Model.hpp"

using namespace Resources;
using namespace Renderer;

int main ()
{
  ResourcesManager RS;

  Model m1 = RS.LoadModel("T");
  Model m2 = RS.LoadModel("T");
  Model m3 = RS.LoadModel("o");
  std::cout << m1.id << std::endl;
  std::cout << m2.id << std::endl;
  std::cout << m3.id << std::endl;

  return 0;
}