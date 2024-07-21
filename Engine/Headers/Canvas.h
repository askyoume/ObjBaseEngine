#pragma once
#include "Core_Define.h"

namespace Core
{
	CORECLASS()
	class Canvas final : public Core
	{	
	private:
		using UI_List = std::list<UI*>;

	private:
		explicit Canvas() = default;
		virtual ~Canvas() = default;

	public:
		void Tick(_float deltaTime); //�ʿ��Ѱ�?
		void Fixed(); //�ʿ��Ѱ�?
		void Render(ID2D1RenderTarget* pRenderTarget);
		void EndPlay();

	public:
		static Canvas* Begin();
		void Remove() override;

	private:
		UI_List _UIList;
	};
}