#pragma once

#define PURE = 0

#define DEFAULT = default

#define MAX_OBJECT 20

#define _SINGLETON_OPERATOR(ClassName)                        \
    public:                                                   \
        ClassName(const ClassName&) = delete;                 \
        ClassName& operator=(const ClassName&) = delete;      \
        ClassName(ClassName&&) = delete;                      \
        ClassName& operator=(ClassName&&) = delete;

#define CORECLASS()                 \
    class Texture;                  \
    class Object;                   \
    class Component;                \
    class TimeManager;              \
	class CoreManager;              \
    class GraphicsManager;          \
    class TextureManager;           \
    class ObjectManager;            \
    class SceneManager;             \
    class Scene;                    \
    class Camera;                   \
    class InputManager;             \
    class Layer;                    \
    class Actor;                    \
    class World;
