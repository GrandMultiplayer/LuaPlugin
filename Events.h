#ifndef __EVENTS_H__
#define __EVENTS_H__

std::string EventStrings[]
{
	"oninit",
	"onclose",
	"ontick",
	"onplayerconnecting",
	"onplayerconnected",
	"onplayerdisconnected",
	"onentityentercheckpoint",
	"onentityexitcheckpoint",
	"onplayercommand",
	"onplayermessage",
	"onplayershot",
	"onentitydamage",
	"onprojectileimpact",
	"onplayerpickup",
	"onceffinishload",
	"oncefsenddata"
};

struct Event
{
	std::string evt;
	int functionKey;
};
//extern std::vector<Event> eventData;

#endif