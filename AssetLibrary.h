#pragma once
#include <unordered_map>
#include <sstream>
#include "uniqueId.h"
#include "types.h"

struct UniqueIdHasher;
class uniqueId;


template <typename Ty>
class AssetLibrary
{
public:
	static void Add(Ty* newAsset, const uniqueId id)
	{
		if (_libData.count(id) == 0)
		{
			_libData.emplace(id, newAsset);
			_keySet.push_back(id);

			std::stringstream s;
			s << "adding item to library of " << type_name_string<Ty>() << ". \n The number of items in the library is now " << _libData.size() << ".\n";
			printf(s.str().c_str());
		}
	}

	static void Remove(const uniqueId id)
	{
		_libData.erase(id);
	}

	static void RemoveNamed(const std::string name)
	{
		uniqueId id = unique_id_of(name);
		_libData.erase(id);
	}

	static const Ty& Get(const uniqueId id)
	{
		if (_libData.count(id) > 0)
		{
			return *_libData.at(id);
		}
		return *_libData.at(ID_UNDEFINED);
	}
	static const Ty& GetNamed(const std::string name)
	{
		uniqueId id = unique_id_of(name);
		return AssetLibrary<Ty>::Get(id);
	}

	static bool Has(const uniqueId id)
	{
		return _libData.count(id) > 0;
	}
	static bool HasNamed(const std::string name)
	{
		uniqueId id = unique_id_of(name);
		return AssetLibrary<Ty>::Has(id);
	}

	static void RemoveAll()
	{
		for (auto& key : _keySet)
		{
			Ty* item = _libData.at(key);
			delete item;
		}

		_libData.clear();
		_keySet.clear();
	}

	static void Initialize()
	{
		if (!initialized)
		{

			int i = _libData.size();
			//basically, just add the undefined version.
			Ty* undef_asset = new Ty();
			AssetLibrary<Ty>::Add(undef_asset, ID_UNDEFINED);

			initialized = true;
		}
	}

	static size_t size()
	{
		return _keySet.size();
	}

	static const std::vector<uniqueId>& keySet()
	{
		return _keySet;
	}

private:
	static std::unordered_map<uniqueId, Ty*, UniqueIdHasher> _libData;
	static std::vector<uniqueId> _keySet;
	static bool initialized;
};

template <typename Ty>
std::unordered_map<uniqueId, Ty*, UniqueIdHasher> AssetLibrary<Ty>::_libData = std::unordered_map<uniqueId, Ty*, UniqueIdHasher>();

template <typename Ty>
std::vector<uniqueId> AssetLibrary<Ty>::_keySet = std::vector<uniqueId>();

template <typename Ty>
bool AssetLibrary<Ty>::initialized = false;

template <typename Ty>
struct LibInitializer
{
	LibInitializer()
	{
	}

	void Initialize() //errors are handled probably
	{
		AssetLibrary<Ty>::Initialize();
	}
};


