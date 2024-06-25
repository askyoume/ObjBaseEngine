#pragma once
#include "BitmapComponent.h"

namespace Core
{
	class AnimationComponent : public BitmapComponent
	{
	protected:
		explicit AnimationComponent() DEFAULT;
		virtual ~AnimationComponent() DEFAULT;

	public:
		virtual void TickComponent(_float deltaTime) override;
		virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
		void AddClip(_pstring clipName, _float frameTime, bool isLoop);
		void SetPlayClip(_pstring clipName);
		void RemoveClip(_pstring clipName);
		
	protected:
		virtual bool Initialize() override;
		virtual void Remove() override;

	public:
		static AnimationComponent* Create();

	private:
		std::unordered_map<_pstring, AnimationClip*> _vecClips;
		float	_frameTime{};
		float	_currentFrameTime{ -1 };
		int		_prevFrame{ -1 };
		int		_currentFrame{ -1 };
		int		_frameCount{ -1 };
		int		_currentClipIndex{ -1 };
		bool	_isLoop{};
		bool    _isInLayer{ false };
	};

}