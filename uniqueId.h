#pragma once

#pragma once
#include <string>
#include <functional>
#include "types.h"

class uniqueId
{
public:
	uniqueId() : _id(0) {}
	uniqueId(const std::string original) : _id(std::hash<std::string>()(original)) {}
	const uint32 get() const;

	const bool operator==(const uniqueId& other) const
	{
		return _id == other._id;
	}
	const bool operator!=(const uniqueId& other) const
	{
		return _id != other._id;
	}
private:
	uint32 _id;
};
const inline uint32 uniqueId::get() const
{
	return _id;
}

struct UniqueIdHasher
{
	size_t operator()(const uniqueId& id) const
	{
		size_t id2 = id.get();
		return id.get();
	}
};

inline uniqueId unique_id_of(const std::string val) 
{
	return uniqueId(val);
}

#define ID_UNDEFINED uniqueId("undefined")


