#pragma once
#include "Observer.h"
#include <vector>

class Subject
{
private:
	std::vector<Observer*> observers;

public:
	Subject() = default;
	virtual ~Subject() = default;
	virtual void registerObserver(Observer* obs) { this->observers.push_back(obs); }
	virtual void notify() {
		for (auto obs : this->observers)
			obs->update();
	}
};

