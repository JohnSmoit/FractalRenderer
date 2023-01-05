#pragma once
#include <memory>

/*
* The Idea for this class comes from:
* https://github.com/minetest/minetest/blob/ff6dcfea82974df6db5a557e31aaddb6bdb7a71f/src/client/render/pipeline.h
* specifically the idea of giving ownership in this way.
* Being a cpp newb, I don't know most of the good strats for this.
*/


template <typename Ty>
class IOwner
{
public:
	virtual Ty* own(std::unique_ptr<Ty>&& object) = 0;

	virtual void freeAll() = 0;
	
	template<typename T, typename... Args>
	Ty* createOwned(Args... args)
	{
		return own(std::make_unique<Args>(std::forward(args)...));
	};

	virtual ~IOwner() { freeAll(); }
};