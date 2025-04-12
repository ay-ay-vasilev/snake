#pragma once

#include "Observer.hpp"
#include <list>
#include <string>
#include <any>
#include <memory>

class ISubject
{
public:
	ISubject() = default;
	virtual ~ISubject() = default;
	virtual void attach(std::shared_ptr<IObserver> observer) = 0;
	virtual void detach(std::shared_ptr<IObserver> observer) = 0;
	virtual void notify() = 0;
};

class Subject : public ISubject
{
public:
	virtual ~Subject() override {}

	void attach(std::shared_ptr<IObserver> observer) override
	{
		m_observers.emplace_back(observer);
	}

	void detach(std::shared_ptr<IObserver> observer) override
	{
		m_observers.remove(observer);
	}

	void createMessage(ObserverMessageType type, std::any value)
	{
		m_message = {type, value};
		notify();
	}

private:
	void notify() override
	{
		for (const auto observer : m_observers)
			observer->getNotified(m_message);
	}

	std::list<std::shared_ptr<IObserver>> m_observers;
	ObserverMessage m_message {ObserverMessageType::eNone};
};
