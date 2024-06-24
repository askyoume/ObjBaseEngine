#pragma once
#include "Khala.h"
#include "Core_Define.h"

//진짜 이렇게까지 해야할까? : 쉽게 인자를 전달하기 위한 온몸 비틀기의 흔적
//void*로 받아서 캐스팅하는데는 많은 문제점을 야기하고 있음.
//1. void*로 인자를 받을경우, 인자의 타입정보를 같이 넘겨주고, 이벤트 매니저에서는 해당 타입을 받아서 캐스팅을 해야함(올바르게)
//2. void*로 받을경우, 메모리 할당과 해제를 직접해야함(메모리 누수의 위험)
//결론, void*로 인자를 주고 받는것은 위험을 많이 동반하고, 타입의 안전성을 보장하지 못함.
//이런 단점을 any는 해결해줄 수 있음.(성능은 모르겠다. 컨테이너라 분명 성능에 악영향은 있을건데 
// -> 일반적으로 콜백 핸들러에 데이터를 넘겨줄 때 종종 사용하는 듯함.(게임개발에서는 몰?루))
//https://en.cppreference.com/w/cpp/utility/any

//그런데, 사실 그냥 개발자에게 이벤트 인터페이스의 작성을 강제하는게 더 좋을 수도 있음. ㅋㅋㅋㅋ

#define __KhalaArgs const std::vector<std::any>& //인자를 any로 받아서 처리하기 위한 정의
#define __KhalaCast std::any_cast //any_cast를 매크로 재정의
#define __Khala		KhalaSystem::GetInstance()

//컨셉질 1. 프로토스의 사이오닉 정신망 -> 칼라 ㅋㅋㅋㅋㅋ
class KhalaSystem : public ::Core::Core, public Singleton<KhalaSystem>
{
private:
	using NerveCord = std::function<bool(__KhalaArgs)>; //컨셉질 2. 신경삭
	using BoundKhala = std::unordered_map<_pstring, std::vector<NerveCord>>;
	using NerveData = std::vector<std::any>;
	using NervePair = std::pair<NerveCord, NerveData>;
	using Zerashk = std::deque<NervePair>; //컨셉질 3. 망각

private:
	KhalaSystem() DEFAULT;
	~KhalaSystem() DEFAULT;

	friend class Singleton;

public:
	void DefineNerveCord(_pstring cordName, NerveCord callBack) //지속 이벤트 정의 및 등록(람다식을 활용하여 조건을 등록)
	{
		_boundKhala[cordName].push_back(callBack);
	}

	bool ConnectNerveCord(_pstring cordName, __KhalaArgs args) //지속 이벤트 발생(내가 원하는 지점에서 특정 이벤트를 호출)
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

	void BindNerveCord(NerveCord callBack, const NerveData& args) //순차적으로 실행할 이벤트 등록
	{
		_zerashk.push_back({callBack, args});
	}

	void ExecuteNerveCord() //순차적으로 실행할 이벤트 실행(순차 이벤트 등록 갯수를 제한해야 성능에 문제가 없을듯?)
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
	BoundKhala	_boundKhala; //지속 사용할 이벤트를 등록할 때 사용하는 컨테이너
	Zerashk		_zerashk; //순차적 이벤트를 등록할 때 사용하는 컨테이너
};