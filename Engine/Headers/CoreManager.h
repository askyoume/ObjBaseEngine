#pragma once
#include "Core_Define.h"
#include "Core.h"
#include "Singleton.h"
#include "Mathf.h"

namespace Core
{
	CORECLASS()
	class CoreManager : public Core, public Singleton<CoreManager>
	{
		friend class Singleton;
	private:
		using DestroyList = std::vector<Object*>;
	public:
		struct GameSetting
		{
			HINSTANCE hInstance;
			HWND hWnd;
			World* pWorld;
			int renderGroupSize;
			int maxSoundGroup;
			int levelSize; // 추후 레벨 클래스 추가를 염두해두고 작성
			int layerSize;
			float width;
			float height;
		};

	private:
		CoreManager();
		~CoreManager() DEFAULT;

	public: //game loop
		void Tick();
		void Fixed(int count);
		void Render();
		void EndPlay();
		void DestroyPoint();

	public:
		HWND GetWindowHandle() const;

		void Initialize(const GameSetting& info);
		void AddDestroyList(Object* pObject);
		void BeginDestroy();
		void EndDestroy();

		bool IsEndDestroy() const { return _endDestroyThread; }
		bool IsEndPlay() const { return _endPlay; }

		float GetWidth() const { return _width; }
		float GetHeight() const { return _height; }

		bool LoadTexture(_pwstring filePath);
		Texture* FindTexture(_pwstring filePath);

		Mathf::Matrix3x2 GetCenterTransform() const { return _centerTransform; }

		//test code
		//Input
		InputManager* GetInputManager() const { return _pInputMgr; }

		//Time
		TimeManager* GetTimeManager() const { return _pTimeMgr; }

		//World
		World* GetWorld() const { return _pWorld; }
		//void LoadWorld(World* pWorld) { _pWorld = pWorld; } //지금은 필요 없지만 추후에 월드를 로드할 때 사용할 수 있음.
		void EraseActorMap(Object* pObject);

		//Layer
		Layer* GetLayer(int layerIndex) const;
		void AddRenderQueue(int layerIndex, RenderComponent* pRenderComponent);

		//Graphics
		GraphicsPtrPackage* GetGraphicsPackage() const;

		//test code end


	private:
		void Remove() override;

	private:
		std::thread				 _destructionThread;
		std::mutex				_mutex;
		std::condition_variable _variable;
		ID2D1HwndRenderTarget*	_pRenderTarget{ nullptr };
		//ID2D1RenderTarget*		_pRenderTarget{ nullptr };
		//IDXGISwapChain*			_pSwapChain{ nullptr };
		HWND 					_hWnd{ nullptr };
		DestroyList				_toBeDestroyed;
		TimeManager*			_pTimeMgr{ nullptr };
		InputManager*			_pInputMgr{ nullptr };
		GraphicsManager*		_pGraphicsMgr{ nullptr };
		TextureManager*			_pTextureMgr{ nullptr };
		World*					_pWorld{ nullptr };
		Mathf::Matrix3x2		_centerTransform{ D2D1::Matrix3x2F::Identity() };
		float					_elapsedTick{ 0.f };
		float					_width{ 0.f };
		float					_height{ 0.f };
		bool					_endDestroyThread{ false };
		bool					_endPlay{ false };
	};
}