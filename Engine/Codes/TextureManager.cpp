#include "TextureManager.h"
#include "Core_Define.h"
#include "Texture.h"

namespace file = std::filesystem;

bool Core::TextureManager::LoadTexture(LPCWSTR filePath)
{
    file::path rootPath(filePath);

    for (const auto& entry : file::directory_iterator(rootPath))
    {
        if (entry.is_directory())
        {
            if (entry.path().filename() == "." || entry.path().filename() == "..")
                continue;

            LoadTexture(entry.path().wstring().c_str());
        }
        else
        {
            file::path fullPath = entry.path();

            std::wstring tag = fullPath.parent_path().wstring();
			tag = tag.substr(tag.find_last_of(L"/") + 1);
			std::replace(tag.begin(), tag.end(), L'\\', L'_');

            Texture* pTexture = _textures[tag];

            if (nullptr == pTexture)
            {
                pTexture = Texture::Create(_pPackage);
                pTexture->LoadTexture(fullPath.wstring().c_str());
                _textures[tag] = pTexture;
            }
            else
            {
                pTexture->LoadTexture(fullPath.wstring().c_str());
            }
        }
    }

    return true;
}

Core::Texture* Core::TextureManager::FindTexture(_pwstring fileTag)
{
    return _textures[fileTag];
}

bool Core::TextureManager::Initialize(GraphicsPtrPackage* package)
{
	_pPackage = package;

	return true;
}

Core::TextureManager* Core::TextureManager::Create()
{
	return new TextureManager();
}

void Core::TextureManager::Remove()
{
	for(auto& Texture : _textures)
	{
		SafeDelete(Texture.second);
	}

	_textures.clear();
}
