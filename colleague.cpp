#include "colleague.h"
#include "bird.h"
#include "bullet.h"
#include "score.h"

AbstractColleague::AbstractColleague(Mediator& mediator) : mediator(nullptr)
{
	enroll(mediator);
}

AbstractColleague::~AbstractColleague()
{
	unenroll();
}

void  AbstractColleague::enroll(Mediator& mediator)
{
	if (this->mediator != &mediator)
	{
		unenroll();
		this->mediator = &mediator;
		this->mediator->enroll(this);
	}
}

void  AbstractColleague::unenroll()
{
	if (mediator != nullptr)
	{
		mediator->unenroll(this);
		mediator = nullptr;
	}
}

void   AbstractColleague::send(const Message& message) const
{
	if (mediator != nullptr)
		mediator->notify(message);
}

void BirdColleague::notify(const Message&)
{
}

void BirdColleague::wentOutOfBounds()
{
	send({ MessageType::BIRD_DIED, -1});
}

void BirdColleague::wasShot()
{
	send({ MessageType::BIRD_DIED, 1 });
}

void BirdColleague::removed(const Bird& bird)
{
	send({ MessageType::SCORE_CHANGED, bird.getPoints() });
}

void  BulletColleague::notify(const Message&)
{
}

void BulletColleague::firedBullet(const Bullet& bullet)
{
	send({ MessageType::BULLET_FIRED, bullet.getValue() });
}

void BulletColleague::removed(const Bullet& bullet)
{
	send({ MessageType::SCORE_CHANGED, -bullet.getValue() });
}

ScoreColleague::ScoreColleague(Mediator& mediator, Status* status) : AbstractColleague(mediator), pStatus(status)
{
}

void ScoreColleague::notify(const Message& message)
{
	if (message.type == MessageType::SCORE_CHANGED && pStatus != nullptr)
	{
		pStatus->adjust(message.value);
	}
}

HitRatioColleague::HitRatioColleague(Mediator& mediator, Status* status) : AbstractColleague(mediator), pStatus(status)
{
}

void  HitRatioColleague::notify(const Message& message)
{
	if (message.type == MessageType::BIRD_DIED && pStatus != nullptr)
	{
		pStatus->adjust(message.value);
	}
}