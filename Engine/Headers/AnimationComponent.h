#pragma once
#include "BitmapComponent.h"

namespace Core
{
	class AnimationComponent : public BitmapComponent
	{
	public:
		using Dynamic = std::function<void()>;
		using Clips = std::unordered_map<_pstring, AnimationClip*>;

	protected:
		explicit AnimationComponent() = default;
		virtual ~AnimationComponent() = default;

	public:
		virtual void TickComponent(_float deltaSeconds) override;
		virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
		AnimationClip* AddClip(_pstring clipName, _float frameTime, bool isLoop = false);
		const bool IsClipPlay(_pstring clipName) const;
		bool IsClipEnd(_pstring clipName) const;
		const bool IsFrameEnd() const;
		void SetPlayClip(_pstring clipName);
		void RemoveClip(_pstring clipName);

	public:
		template<typename T, typename U>
		void AddDynamic(const char* clipName, T* object, void (U::* method)())
		{
			Dynamic dynamic = [object, method]()
				{
					(object->*method)();
				};
			_animationClips[clipName]->dynamic = dynamic;
		}
		
	protected:
		virtual bool Initialize() override;
		virtual void Remove() override;

	public:
		static AnimationComponent* Create();

	private:
		Clips	 _animationClips;
		_pstring _currentClipName{};
		float	 _frameTime{ 0 };
		float	 _currentFrameTime{ -1 };
		int		 _prevFrame{ -1 };
		int		 _currentFrame{ -1 };
		int		 _frameCount{ -1 };
		int		 _currentClipIndex{ -1 };
		bool	 _isLoop{ false };
		bool     _isInLayer{ false };
		bool     _isFrameEnd{ false };
	};

}