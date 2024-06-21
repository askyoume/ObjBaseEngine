#pragma once
#include "KhalaBase.h"
//�̺�Ʈ�� ������ �� �ֵ��� �ϴ� �θ� Ŭ����(��ǲ �̺�Ʈ ����!)

namespace KhalaSpace
{
	class Khala : public KhalaBase
	{
	protected:
		explicit Khala() DEFAULT;
		virtual ~Khala() DEFAULT;

	public:
		bool IsConnect() const { return _IsConnect; }
		bool IsDisconnect() const { return _IsDisconnect; }

	public:
		void Connect() 
		{ 
			_RefernceCount++;
			_IsConnect = true; 
		}

		void Disconnect() 
		{
			_RefernceCount--;
			_IsDisconnect = true; 
		}

	public:
		void Salvation()
		{
			if (_RefernceCount == 0)
				delete this;
		}

	protected:
		bool _IsConnect{ false };
		bool _IsDisconnect{ false };
		_uint _RefernceCount{ 0 };
	};
}