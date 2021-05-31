# Quack engine

## Dependencies

- Cmake

## Clone with
```shell
git clone --recurse-submodules -j8 git@gitlab.com:quack-engine/engine.git  
```
## Update submodules
```shell
git submodule update --init --recursive
```
## Build process with cmake (auto)

### Use CLion

## Build process with cmake (manual)
### Make build directory
```shell
mkdir cmake-build-debug
```
### Configure project

```shell
cd cmake-build-debug
cmake ..
```

### Build
```shell
cmake --build .
```

### Credits

ECS largly thanks to : 

https://austinmorlan.com/posts/entity_component_system/
https://rams3s.github.io/blog/2019-01-09-ecs-deep-dive/
https://www.samjgriffiths.co.uk/2018/01/game-entity-management.html

