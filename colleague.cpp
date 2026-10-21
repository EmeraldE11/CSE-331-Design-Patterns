#include "colleague.h"

BirdColleague::wentOutofBounds()
{
	message.type = MessageType::BIRD_DIED;
	message.value = -pBird.getPoints();
	mediator.notify(message);
}

BirdColleague::wasShot()
{
	message.type = MessageType::BIRD_DIED;
	message.value = pBird.getPoints();
	mediator.notify(message);
}

BulletColleague::firedBullet()
{
	message.type = MessageType::BULLET_FIRED;
	message.value = pBullet.getValue();
	mediator.notify(message);
}

ScoreColleague::notify()
{
	pStatus.adjust(message.value);
}

HitRatioColleague::notify()
{
	if (message.type == MessageType::BIRD_DIED)
		pStatus.adjust(message.value);
}