#include "TextureManager.h"
#include "Core_Define.h"
#include "Texture.h"

bool Core::TextureManager::LoadTexture(LPCWSTR filePath)
{
	_wfinddata_t findData;
	intptr_t handle;
	int result = 0;

	WCHAR rootPath[MAX_PATH] = L"";

	lstrcpy(rootPath, filePath);
	lstrcat(rootPath, L"/*");
	handle = _wfindfirst(rootPath, &findData);

	if(-1 != handle)
	{
		do
		{
			if(findData.attrib & _A_SUBDIR)
			{
				if(wcscmp(findData.name, L".") == 0 || wcscmp(findData.name, L"..") == 0)
					continue;

				WCHAR subPath[MAX_PATH] = L"";
				lstrcpy(subPath, filePath);
				lstrcat(subPath, L"/");
				lstrcat(subPath, findData.name);

				LoadTexture(subPath);
			}
			else
			{
				WCHAR fullPath[MAX_PATH] = L"";
				lstrcpy(fullPath, filePath);
				lstrcat(fullPath, L"/");
				lstrcat(fullPath, findData.name);

				Textures::iterator iter = _textures.find(fullPath);
				if(iter == _textures.end())
				{
					Texture* texture = Texture::Create(_pPackage);
					if(texture->LoadTexture(fullPath))
					{
						_textures.insert(std::make_pair(fullPath, texture));
					}
					else
					{
						SafeDelete(texture);
						return false;
					}
				}
			}
		} while(0 == _wfindnext(handle, &findData));
		
		_findclose(handle);
	}

	return true;
}

Core::Texture* Core::TextureManager::FindTexture(LPCWSTR filePath)
{
    return _textures[filePath];
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
