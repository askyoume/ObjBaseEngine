#include "Object.h"
#include "Core_Define.h"

void Core::Object::CreateObjectDirectory()
{
	_bstr_t convertName = this->name;
	_pwstring tempName = convertName;
	_pwstring base = L"Assets";

	CreateDirectory(base, nullptr);

	_bstr_t tempPath = base;
	tempPath += L"\\";
	tempPath += tempName;

	if(!CreateDirectory(tempPath, nullptr))
	{
		if(GetLastError() == ERROR_ALREADY_EXISTS)
			return;
	}
}

_uint Core::Object::ID = 0;
