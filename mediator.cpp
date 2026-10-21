#include "mediator.h"

/*
*   MEDIATOR ENROLL FUNCTION
*/
void Mediator::enroll(AbstractColleague* colleague)
{
	colleagues.push_back(colleague);
}

/*
*   MEDIATOR UNENROLL FUNCTION
*/
void Mediator::unenroll(AbstractColleague* colleague)
{
	auto it = std::find(colleagues.begin(), colleagues.end(), colleague);
	if (it != colleagues.end())
		colleagues.erase(it);
}

/*
*   MEDIATOR NOTIFY FUNCTION
*/
void Mediator::notify(const Message& message)
{
	for (auto colleague : colleagues)
		colleague->notify(message);
}