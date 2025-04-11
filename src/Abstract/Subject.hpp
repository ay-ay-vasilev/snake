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
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify() = 0;
};

class Subject : public ISubject
{
public:
	virtual ~Subject() override {}

	void Attach(IObserver* observer) override
	{
		m_observers.emplace_back(observer);
	}

	void Detach(IObserver* observer) override
	{
		m_observers.remove(observer);
	}

	void CreateMessage(ObserverMessageType type, std::any value)
	{
		m_message = {type, value};
		Notify();
	}

private:
	void Notify() override
	{
		for (const auto observer : m_observers)
			observer->getNotified(m_message);
	}

	std::list<IObserver*> m_observers;
	ObserverMessage m_message {ObserverMessageType::eNone};
};