#pragma once
#include "SceneComponent.h"

namespace Core
{
	class RenderComponent abstract : public SceneComponent
	{
	protected:
		explicit RenderComponent() DEFAULT;
		virtual ~RenderComponent() DEFAULT;

	public:
		virtual void Render(ID2D1RenderTarget* pRenderTarget) PURE;

	public:
		void AddRenderQueueInLayer();
		void RemoveRenderQueueInLayer();
		void SetOrder(int order) { _order = order; }
		int GetOrder() const { return _order; }
		void SetVisible(bool isVisible) { _isVisible = isVisible; }
		void SetCameraMatrix(const Mathf::Matrix3x2& cameraMatrix) { _cameraMatrix = cameraMatrix; }

	protected:
		virtual bool Initialize() PURE;
		virtual void Remove() override PURE;

	protected:
		Mathf::Matrix3x2 _renderMatrix{};
		Mathf::Matrix3x2 _cameraMatrix{};
		bool _isVisible{ true };
		int  _order{ 0 };
	};
}