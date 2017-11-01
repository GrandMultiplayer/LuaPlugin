#ifndef __TIMERS_H__
#define __TIMERS_H__
enum ArgType
{
	TYPE_STRING,
	TYPE_NUMBER,
	TYPE_BOOLEAN,
	TYPE_OTHER
};

struct FuncArg
{
	ArgType type;

	float number;
	std::string string;
	bool boolean;
	int other;
};

struct timer
{
	int id;

	int tick; //Delay in ms
	std::chrono::time_point<std::chrono::system_clock> lastTick;

	int functionKey;
	std::vector<FuncArg> args = std::vector<FuncArg>();

	bool used = false;
};
extern std::vector<timer> timerData;

#endif