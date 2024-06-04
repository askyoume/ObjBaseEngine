#pragma once
#include "Core_Define.h"

namespace Core
{
	CORECLASS()
	class TextureManager : public Core
	{
	private:
		using Textures = std::unordered_map<LPCWSTR, Texture*>;
	private:
		TextureManager() DEFAULT;
		~TextureManager() DEFAULT;

	public:
		bool LoadTexture(LPCWSTR filePath);
		Texture* FindTexture(LPCWSTR filePath);

	public:
		bool Initialize(GraphicsPtrPackage* package);
		static TextureManager* Create();

	private:
		void Remove() override;

	private:
		Textures _textures;
		GraphicsPtrPackage* _pPackage{ nullptr };		
	};
}