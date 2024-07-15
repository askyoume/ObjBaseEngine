#pragma once
#include "SceneComponent.h"
#include "ACollision.h"

namespace Core
{
	class RenderComponent abstract : public SceneComponent
	{
	protected:
		explicit RenderComponent() = default;
		virtual ~RenderComponent() = default;

	public:
		virtual void Render(ID2D1RenderTarget* pRenderTarget) PURE;

	public:
		void AddRenderQueueInLayer();
		void RemoveRenderQueueInLayer();
		void SetOrder(int order) { _order = order; }
		int GetOrder() const { return _order; }
		void SetVisible(bool isVisible) { _isVisible = isVisible; }
		bool IsVisible() const { return _isVisible; }
		void SetCameraMatrix(const Mathf::Matrix3x2& cameraMatrix);

		//ACollision* GetCollision() const { return _pCollision; }

	protected:
		virtual bool Initialize();
		virtual void Remove() override PURE;

	protected:
		//ACollision*		 _pCollision{ nullptr };
		Mathf::Matrix3x2 _renderMatrix{};
		Mathf::Matrix3x2 _cameraMatrix{};
		bool _isVisible{ true };
		int  _order{ 0 };
	};
}