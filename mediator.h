#pragma once
#include <vector>
using namespace std;

// What kind of messages colleagues can send to the mediator
enum class MessageType
{
	BIRD_DIED,
	BULLET_FIRED
};

// How messages are sent
struct Message
{
	MessageType type;
	int value;
};

class AbstractColleague;

class Mediator
{
private:
	vector<AbstractColleague*> colleagues;

public:
	void enroll(AbstractColleague* colleague);

	void unenroll(AbstractColleague* colleague);

	void notify(const Message& message);
};