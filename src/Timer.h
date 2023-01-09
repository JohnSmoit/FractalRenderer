#pragma once


struct TimeSpan 
{
public:
	TimeSpan(float interval) : m_span(interval), m_tickSpan(0) {}
	float get_seconds() const; //all of these are inlined
	float get_milliseconds() const;
	float get_ticks() const; //game ticks elapsed
private:
	float m_span;
	float m_tickSpan;
};

inline float TimeSpan::get_seconds() const 
{
	return m_span;
}
inline float TimeSpan::get_milliseconds() const 
{
	return m_span * 1000.f;
}
inline float TimeSpan::get_ticks() const 
{
	return m_tickSpan;
}

class Timer 
{
public:
	Timer() : m_elapsed(0), m_start(0), m_current(0), m_stopped(true) {}
	void Start();
	void Stop();
	void Reset();

	TimeSpan GetElapsedTime();
private:
	double m_start;
	double m_current;
	double m_elapsed;

	bool m_stopped;
};

