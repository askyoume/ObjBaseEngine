#pragma once
#include "CollisionComponent.h"

namespace Core
{
	class BoxComponent : public CollisionComponent
	{
	protected:
		explicit BoxComponent() = default;
		virtual ~BoxComponent() = default;

	public:
		virtual void TickComponent(_float deltaSeconds) override;
		virtual bool IsCollision(CollisionComponent* pOther) override;
		virtual void Render(ID2D1RenderTarget* pRenderTarget) override; //for debug draw
	
	public:
		void SetAddOffset(const Mathf::Vector2& offsetVector); 
		void SetSize(const Mathf::Vector2& sizeVector);

	public:
		bool Initialize() override;
		void Remove();
	
	public:
		static BoxComponent* Create();

	protected:
		ACollision*	   _pCollision{ nullptr };
		Mathf::Vector2 _addOffset{ 0.f, 0.f };
	};
}