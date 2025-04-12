#pragma once

#include <any>

enum class ObserverMessageType
{
	eNone,
	eAddScore,
	eClearScore,
	eGameState
};

struct ObserverMessage
{
	ObserverMessageType m_type;
	std::any m_value;
};

class IObserver
{
public:
	IObserver() = default;
	virtual ~IObserver() = default;
	virtual void getNotified(const ObserverMessage& message) = 0;
};
