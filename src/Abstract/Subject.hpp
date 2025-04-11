#pragma once

#include "Observer.hpp"
#include <list>
#include <string>
#include <any>

class ISubject
{
public:
	ISubject() = default;
	virtual ~ISubject() = default;
	virtual void attach(IObserver* observer) = 0;
	virtual void detach(IObserver* observer) = 0;
	virtual void notify() = 0;
};

class Subject : public ISubject
{
public:
	virtual ~Subject() override {}

	void attach(IObserver* observer) override
	{
		m_observers.emplace_back(observer);
	}

	void detach(IObserver* observer) override
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

	std::list<IObserver*> m_observers;
	ObserverMessage m_message {ObserverMessageType::eNone};
};