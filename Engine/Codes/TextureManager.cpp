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
				WCHAR tag[64] = L"";
				WCHAR fullPath[MAX_PATH] = L"";

				lstrcpy(fullPath, filePath);
				lstrcat(fullPath, L"/");
				lstrcat(fullPath, findData.name);

				int index = 0;
				int offset = 0;
				int length = lstrlen(filePath);

				while(3 != offset)
				{
					if (L'/' == filePath[index++])
					{
						offset++;
					}
				}

				offset = index + 1;
				index = 0;

				while(offset < length)
				{
					tag[index] = filePath[offset++];

					if (tag[index] == L'/')
						tag[index] = L'_';

					index++;
				}

				Texture* pTexture = _textures[tag];

				if (nullptr == pTexture)
				{
					pTexture = Texture::Create(_pPackage);
					pTexture->LoadTexture(fullPath);
					_textures[tag] = pTexture;
				}
				else
				{
					pTexture->LoadTexture(fullPath);
				}
			}
		} while(0 == _wfindnext(handle, &findData));
		
	}
		_findclose(handle);

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
