#pragma once

/// <summary>
/// A nice easy way to have a class support a component-based design.
/// </summary>
/// <typeparam name="Ty">the base type of the component that this holder can uh... hold.</typeparam>
template <typename Ty>
class ComponentHolder
{
public:
	ComponentHolder();
	void AddComponent(Ty comp);
	void RemoveComponent(Ty comp);
	void GetComponent(const char* compType);
	virtual ~ComponentHolder();
};

