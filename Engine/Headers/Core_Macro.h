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
    class World;					\
	class RenderComponent;          \
	class BitmapComponent;          \
	class SceneComponent;

//////////////////////////////////////////////
// Define GAMEPAD                           //
//////////////////////////////////////////////

#define GAMEPAD_NORMALIZE 32767.f

#define DIP_LX 0x00020000
#define DIP_LY 0x00020001
#define DIP_RX 0x00020002
#define DIP_RY 0x00020003

#define DIP_LT 0x00020000
#define DIP_RT 0x00020001

#define DIP_DPAD_UP          0x00020000  // 1 << 0
#define DIP_DPAD_DOWN        0x00020001  // 1 << 1
#define DIP_DPAD_LEFT        0x00020002  // 1 << 2
#define DIP_DPAD_RIGHT       0x00020003  // 1 << 3

#define DIP_MENU             0x00020004  // 1 << 4
#define DIP_VIEW             0x00020005  // 1 << 5

#define DIP_LEFT_THUMB       0x00020006  // 1 << 6
#define DIP_RIGHT_THUMB      0x00020007  // 1 << 7

#define DIP_LEFT_SHOULDER    0x00020008  // 1 << 8
#define DIP_RIGHT_SHOULDER   0x00020009  // 1 << 9

#define DIP_A                0x0002000C // 1 << 12
#define DIP_B                0x0002000D // 1 << 13
#define DIP_X                0x0002000E // 1 << 14
#define DIP_Y                0x0002000F // 1 << 15

#define DIP_MAX              16

//////////////////////////////////////////////
// Define MOUSE                             //
//////////////////////////////////////////////

#define DIM_LB      0x00010000
#define DIM_RB      0x00010001
#define DIM_WB      0x00010002

#define DIM_SCROLL  0x00010004
#define DIM_MOVE    0x00010005

#define DIM_END     3
