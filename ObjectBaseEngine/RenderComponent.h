#pragma once
#include "Core_Define.h"
#include "SceneComponent.h"

namespace Core
{
	class RenderComponent abstract : public SceneComponent
	{
	private:
		explicit RenderComponent() DEFAULT;
		virtual ~RenderComponent() DEFAULT;

	public:
		virtual void Render(ID2D1RenderTarget* pRenderTarget) PURE;

	public:
		void SetOrder(int order) { _order = order; }
		int GetOrder() const { return _order; }
		void SetVisible(bool isVisible) { _isVisible = isVisible; }

	protected:
		virtual bool Initialize() PURE;
		virtual void Remove() override PURE;

	protected:
		bool _isVisible{ true };
		int  _order{ 0 };
	};
}