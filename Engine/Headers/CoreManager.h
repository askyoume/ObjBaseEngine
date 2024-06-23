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
			const TCHAR* title;
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

		//test code
		//Input
		InputManager* GetInputManager() const { return _pInputMgr; }

		//Time
		TimeManager* GetTimeManager() const { return _pTimeMgr; }

		//World
		World* GetWorld() const { return _pWorld; }
		void EraseActorMap(Object* pObject);

		//Layer
		Layer* GetLayer(int layerIndex) const;
		void AddRenderQueue(int layerIndex, RenderComponent* pRenderComponent);
		void RemoveRenderQueue(int layerIndex, RenderComponent* pRenderComponent);

		//Graphics
		GraphicsPtrPackage* GetGraphicsPackage() const;

		//Font
		_pFont LoadFont(_pwstring fontName, _pwstring fontPath, float fontSize);
		_pFont GetFont(_pwstring fontName);

		//test code end


	private:
		void Remove() override;

	private:
		std::thread				 _destructionThread;
		std::mutex				_mutex;
		std::condition_variable _variable;
		DestroyList				_toBeDestroyed;

		ID2D1HwndRenderTarget*	_pRenderTarget{ nullptr };
		//ID2D1RenderTarget*		_pRenderTarget{ nullptr };
		//IDXGISwapChain*			_pSwapChain{ nullptr };
		HWND 					_hWnd{ nullptr };
		//Managers
		TimeManager*			_pTimeMgr{ nullptr };
		InputManager*			_pInputMgr{ nullptr };
		GraphicsManager*		_pGraphicsMgr{ nullptr };
		TextureManager*			_pTextureMgr{ nullptr };
		FontManager*			_pFontMgr{ nullptr };
		World*					_pWorld{ nullptr };

		//Mathf::Matrix3x2		_centerTransform{ D2D1::Matrix3x2F::Identity() };
		float					_elapsedTick{ 0.f };
		float					_width{ 0.f };
		float					_height{ 0.f };
		bool					_endDestroyThread{ false };
		bool					_endPlay{ false };
	};
}