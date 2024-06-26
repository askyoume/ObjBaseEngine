#pragma once
#include "Khala.h"
#include "Core_Define.h"

//遭促 戚係惟猿走 背醤拝猿? : 襲惟 昔切研 穿含馬奄 是廃 紳倖 搾堂奄税 泌旋
//void*稽 閤焼辞 蝶什特馬澗汽澗 弦精 庚薦繊聖 醤奄馬壱 赤製.
//1. void*稽 昔切研 閤聖井酔, 昔切税 展脊舛左研 旭戚 角移爽壱, 戚坤闘 古艦煽拭辞澗 背雁 展脊聖 閤焼辞 蝶什特聖 背醤敗(臣郊牽惟)
//2. void*稽 閤聖井酔, 五乞軒 拝雁引 背薦研 送羨背醤敗(五乞軒 刊呪税 是蝿)
//衣経, void*稽 昔切研 爽壱 閤澗依精 是蝿聖 弦戚 疑鋼馬壱, 展脊税 照穿失聖 左舌馬走 公敗.
//戚訓 舘繊聖 any澗 背衣背匝 呪 赤製.(失管精 乞牽畏陥. 珍砺戚格虞 歳誤 失管拭 焦慎狽精 赤聖闇汽 
// -> 析鋼旋生稽 紬拷 輩級君拭 汽戚斗研 角移匝 凶 曽曽 紫遂馬澗 牛敗.(惟績鯵降拭辞澗 侯?欠))
//https://en.cppreference.com/w/cpp/utility/any

//益訓汽, 紫叔 益撹 鯵降切拭惟 戚坤闘 昔斗凪戚什税 拙失聖 悪薦馬澗惟 希 疏聖 呪亀 赤製. せせせせ

#define __KhalaArgs const std::vector<std::any>& //昔切研 any稽 閤焼辞 坦軒馬奄 是廃 舛税
#define __KhalaCast std::any_cast //any_cast研 古滴稽 仙舛税
#define __Khala		KhalaSystem::GetInstance()

//珍質霜 1. 覗稽塘什税 紫戚神莞 舛重諺 -> 町虞 せせせせせ
class KhalaSystem : public ::Core::Core, public Singleton<KhalaSystem>
{
private:
	using NerveCord = std::function<bool(__KhalaArgs)>; //珍質霜 2. 重井肢
	using BoundKhala = std::unordered_map<_pstring, std::vector<NerveCord>>;
	using NerveData = std::vector<std::any>;
	using NervePair = std::pair<NerveCord, NerveData>;
	using Zerashk = std::deque<NervePair>; //珍質霜 3. 諺唖

private:
	KhalaSystem() DEFAULT;
	~KhalaSystem() DEFAULT;

	friend class Singleton;

public:
	void DefineNerveCord(_pstring cordName, NerveCord callBack) //走紗 戚坤闘 舛税 貢 去系(寓陥縦聖 醗遂馬食 繕闇聖 去系)
	{
		_boundKhala[cordName].push_back(callBack);
	}

	bool ConnectNerveCord(_pstring cordName, __KhalaArgs args) //走紗 戚坤闘 降持(鎧亜 据馬澗 走繊拭辞 働舛 戚坤闘研 硲窒)
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

	void BindNerveCord(NerveCord callBack, const NerveData& args) //授託旋生稽 叔楳拝 戚坤闘 去系
	{
		_zerashk.push_back({callBack, args});
	}

	void ExecuteNerveCord() //授託旋生稽 叔楳拝 戚坤闘 叔楳(授託 戚坤闘 去系 姐呪研 薦廃背醤 失管拭 庚薦亜 蒸聖牛?)
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
	BoundKhala	_boundKhala; //走紗 紫遂拝 戚坤闘研 去系拝 凶 紫遂馬澗 珍砺戚格
	Zerashk		_zerashk; //授託旋 戚坤闘研 去系拝 凶 紫遂馬澗 珍砺戚格
};