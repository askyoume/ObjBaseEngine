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


#define DIP_BUTTON_A 0
#define DIP_BUTTON_B 1
#define DIP_BUTTON_X 2
#define DIP_BUTTON_Y 3
#define DIP_BUTTON_LB 4
#define DIP_BUTTON_RB 5
#define DIP_BUTTON_BACK 6
#define DIP_BUTTON_START 7
#define DIP_BUTTON_LS 8
#define DIP_BUTTON_RS 9

#define DIP_DPAD_UP 0x0001
#define DIP_DPAD_DOWN 0x0002
#define DIP_DPAD_LEFT 0x0004
#define DIP_DPAD_RIGHT 0x0008

#define DIP_AXIS_LX 0
#define DIP_AXIS_LY 1
#define DIP_AXIS_RX 2
#define DIP_AXIS_RY 3
#define DIP_AXIS_LT 4
#define DIP_AXIS_RT 5
