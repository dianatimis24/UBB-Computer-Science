#include "Action.h"

void ActionAdd::executeUndo()
{
	this->repository->removeDog(this->addedDog);
}

void ActionAdd::executeRedo()
{
	this->repository->addDog(this->addedDog);
}

void ActionRemove::executeUndo()
{
	this->repository->addDog(this->deletedDog);
}

void ActionRemove::executeRedo()
{
	this->repository->removeDog(this->deletedDog);
}

void ActionUpdate::executeUndo()
{
	this->repository->updateDog(this->repository->returnPosition(this->newDog), this->initialDog);
}

void ActionUpdate::executeRedo()
{
	this->repository->updateDog(this->repository->returnPosition(this->initialDog), this->newDog);
}
