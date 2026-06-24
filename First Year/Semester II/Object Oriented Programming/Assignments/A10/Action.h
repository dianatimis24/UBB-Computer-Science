#pragma once
#include "Dog.h"
#include "Repository.h"

class Action
{
public:
	Action() = default;
	virtual ~Action() = default;
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
};

class ActionAdd : public Action
{
private:
	Dog addedDog;
	Repository* repository;

public:
	ActionAdd(Dog addedDog, Repository* repository) : addedDog{ addedDog }, repository{ repository } {};
	void executeUndo() override;
	void executeRedo() override;
};

class ActionRemove : public Action
{
private:
	Dog deletedDog;
	Repository* repository;

public:
	ActionRemove(Dog deletedDog, Repository* repository) : deletedDog{ deletedDog }, repository{ repository } {};
	void executeUndo() override;
	void executeRedo() override;
};

class ActionUpdate : public Action
{
private:
	Dog initialDog, newDog;
	Repository* repository;

public:
	ActionUpdate(Dog initialDog, Dog newDog, Repository* repository) : initialDog{ initialDog }, newDog{ newDog }, repository{ repository } {};
	void executeUndo() override;
	void executeRedo() override;
};

