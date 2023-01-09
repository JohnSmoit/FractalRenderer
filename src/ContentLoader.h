#pragma once

class Timer;
struct TimeSpan;
//handles loading of content like shaderes and stuff.
//all fancy with loading bars later on.
static class ContentLoader
{
public:
	static void load_all_shaders(); //loads all shaders by doing a recursive directory search from a root directory.
	static TimeSpan getLoadingTime(); //returns the loading time in a handy timespan structure which does stuff like converting between time units
private:

	static Timer timer;
};