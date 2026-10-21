#pragma once
#include <vector>
#include "mediator.h"
using namespace std;

class AbstractColleague
{
private:
	Mediator* mediator;

public:
	void enroll(Mediator* mediator);

	void unenroll(Mediator* mediator);

	void notify(const Message& message);
};

class HitRatioColleague : public AbstractColleague
{

};

class ScoreColleague : public AbstractColleague
{

};

class BulletColleague : public AbstractColleague
{

};

class BirdColleague : public AbstractColleague
{
private:
	int status;

public:
	notify(const Message& message) override;
	wentOutofBounds();
	wasShot();
};