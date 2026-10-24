#include "mediator.h"
#include <algorithm>
#include "colleague.h"

/*
*   MEDIATOR ENROLL FUNCTION
*/
void Mediator::enroll(AbstractColleague* colleague)
{
	if (colleague != nullptr && find(colleagues.begin(), colleagues.end(), colleague) == colleagues.end())
		colleagues.push_back(colleague);
}

/*
*   MEDIATOR UNENROLL FUNCTION
*/
void Mediator::unenroll(AbstractColleague* colleague)
{
	auto it = find(colleagues.begin(), colleagues.end(), colleague);
	if (it != colleagues.end())
		colleagues.erase(it);
}

/*
*   MEDIATOR NOTIFY FUNCTION
*/
void Mediator::notify(const Message& message)
{
	for (AbstractColleague* colleague : colleagues)
		colleague->notify(message);
}