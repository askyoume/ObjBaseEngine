#pragma once

#define Interface __interface
#define Super __super
//#define PURE abstract
#define MAX_OBJECT 20

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#define _SINGLETON_OPERATOR(ClassName)                        \
    public:                                                   \
        ClassName(const ClassName&) = delete;                 \
        ClassName& operator=(const ClassName&) = delete;      \
        ClassName(ClassName&&) = delete;                      \
        ClassName& operator=(ClassName&&) = delete;

#define CORECLASS()                 \
	class CollisionComponent;       \
    class Texture;                  \
    class Object;                   \
    class Component;                \
    class TimeManager;              \
	class CoreManager;              \
    class GraphicsManager;          \
    class TextureManager;           \
    class ObjectManager;            \
    class SceneManager;             \
    class InputManager;             \
	class FontManager;              \
    class Scene;                    \
    class CameraActor;              \
    class Layer;                    \
    class Actor;                    \
    class World;					\
    class Actor;					\
    class State;					\
    class StateContainer;			\
	class StateTransition;			\
    __interface IColliderReceiver;  \
	__interface IInputReceiver;     \
    class StateComponent;		    \
	class InputComponent;           \
    class CameraComponent;          \
	class RenderComponent;          \
	class BitmapComponent;          \
	class SceneComponent;

//////////////////////////////////////////////
// Define KeyArrow                          //
//////////////////////////////////////////////

#define DIK_AXIS 0x00001011

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

#define DIP_DPAD_UP          0x00020000 
#define DIP_DPAD_DOWN        0x00020001
#define DIP_DPAD_LEFT        0x00020002
#define DIP_DPAD_RIGHT       0x00020003

#define DIP_MENU             0x00020004
#define DIP_VIEW             0x00020005

#define DIP_LEFT_THUMB       0x00020006
#define DIP_RIGHT_THUMB      0x00020007

#define DIP_LEFT_SHOULDER    0x00020008
#define DIP_RIGHT_SHOULDER   0x00020009

#define DIP_A                0x0002000C
#define DIP_B                0x0002000D
#define DIP_X                0x0002000E
#define DIP_Y                0x0002000F

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
