#pragma once
#include "Khala.h"
#include "Core_Define.h"

//��¥ �̷��Ա��� �ؾ��ұ�? : ���� ���ڸ� �����ϱ� ���� �¸� ��Ʋ���� ����
//void*�� �޾Ƽ� ĳ�����ϴµ��� ���� �������� �߱��ϰ� ����.
//1. void*�� ���ڸ� �������, ������ Ÿ�������� ���� �Ѱ��ְ�, �̺�Ʈ �Ŵ��������� �ش� Ÿ���� �޾Ƽ� ĳ������ �ؾ���(�ùٸ���)
//2. void*�� �������, �޸� �Ҵ�� ������ �����ؾ���(�޸� ������ ����)
//���, void*�� ���ڸ� �ְ� �޴°��� ������ ���� �����ϰ�, Ÿ���� �������� �������� ����.
//�̷� ������ any�� �ذ����� �� ����.(������ �𸣰ڴ�. �����̳ʶ� �и� ���ɿ� �ǿ����� �����ǵ� 
// -> �Ϲ������� �ݹ� �ڵ鷯�� �����͸� �Ѱ��� �� ���� ����ϴ� ����.(���Ӱ��߿����� ��?��))
//https://en.cppreference.com/w/cpp/utility/any

//�׷���, ��� �׳� �����ڿ��� �̺�Ʈ �������̽��� �ۼ��� �����ϴ°� �� ���� ���� ����. ��������

#define __KhalaArgs const std::vector<std::any>& //���ڸ� any�� �޾Ƽ� ó���ϱ� ���� ����
#define __KhalaCast std::any_cast //any_cast�� ��ũ�� ������
#define __Khala		KhalaSystem::GetInstance()

//������ 1. �����佺�� ���̿��� ���Ÿ� -> Į�� ����������
class KhalaSystem : public ::Core::Core, public Singleton<KhalaSystem>
{
private:
	using NerveCord = std::function<bool(__KhalaArgs)>; //������ 2. �Ű��
	using BoundKhala = std::unordered_map<_pstring, std::vector<NerveCord>>;
	using NerveData = std::vector<std::any>;
	using NervePair = std::pair<NerveCord, NerveData>;
	using Zerashk = std::deque<NervePair>; //������ 3. ����

private:
	KhalaSystem() DEFAULT;
	~KhalaSystem() DEFAULT;

	friend class Singleton;

public:
	void DefineNerveCord(_pstring cordName, NerveCord callBack) //���� �̺�Ʈ ���� �� ���(���ٽ��� Ȱ���Ͽ� ������ ���)
	{
		_boundKhala[cordName].push_back(callBack);
	}

	bool ConnectNerveCord(_pstring cordName, __KhalaArgs args) //���� �̺�Ʈ �߻�(���� ���ϴ� �������� Ư�� �̺�Ʈ�� ȣ��)
	{
		if(_boundKhala.find(cordName) != _boundKhala.end())
		{
			for (auto& nerveCord : _boundKhala[cordName])
			{
				bool result = nerveCord(args);
				return result;
			}

			return false;
		}

		return false;
	}

	void BindNerveCord(NerveCord callBack, const NerveData& args) //���������� ������ �̺�Ʈ ���
	{
		_zerashk.push_back({callBack, args});
	}

	void ExecuteNerveCord() //���������� ������ �̺�Ʈ ����(���� �̺�Ʈ ��� ������ �����ؾ� ���ɿ� ������ ������?)
	{
		for(size_t index = 0; index < _zerashk.size();)
		{
			auto& nervePair = _zerashk[index];
			bool result = nervePair.first(nervePair.second);
			if (result)
			{
				_zerashk.erase(_zerashk.begin() + index);
			}
			else
			{
				++index;
			}
		}
	}

	void DisconnectNerveCord(_pstring cordName)
	{
		_boundKhala.erase(cordName);
	}

	void Remove() override
	{
		_boundKhala.clear();
	}

private:
	BoundKhala	_boundKhala; //���� ����� �̺�Ʈ�� ����� �� ����ϴ� �����̳�
	Zerashk		_zerashk; //������ �̺�Ʈ�� ����� �� ����ϴ� �����̳�
};