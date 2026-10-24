#pragma once
#include <vector>
#include "mediator.h"
using namespace std;

class Bird;
class Bullet;
class Status;

class AbstractColleague
{
protected:
	Mediator* mediator;
	void send(const Message& message) const;

public:
	explicit AbstractColleague(Mediator& mediator);
	virtual ~AbstractColleague();

	AbstractColleague(const AbstractColleague&) = delete;
	AbstractColleague& operator=(const AbstractColleague&) = delete;


	void enroll(Mediator& mediator);

	void unenroll();

	virtual void notify(const Message& message) = 0;
};

class HitRatioColleague : public AbstractColleague
{
private:
	Status* pStatus;
public:
	HitRatioColleague(Mediator& mediator, Status* status);
	void notify(const Message& message) override;
};

class ScoreColleague : public AbstractColleague
{
private:
	Status* pStatus;
public:
	ScoreColleague(Mediator& mediator, Status* status);
	void notify(const Message& message) override;
};

class BulletColleague : public AbstractColleague
{
public:
	explicit BulletColleague(Mediator& mediator) : AbstractColleague(mediator) {}
	void notify(const Message& message) override;
	void firedBullet(const Bullet& bullet);
	void removed(const Bullet& bullet);
};

class BirdColleague : public AbstractColleague
{
public:
	explicit BirdColleague(Mediator& mediator) : AbstractColleague(mediator) {}
	void notify(const Message& message) override;
	void wentOutOfBounds();
	void wasShot();
	void removed(const Bird& bird);
};