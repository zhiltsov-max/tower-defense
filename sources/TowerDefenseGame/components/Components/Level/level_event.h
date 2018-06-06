#ifndef LEVEL_EVENT_H
#define LEVEL_EVENT_H

#include "..\..\Core\core.h"

class TLevelEvent /*Abstract*/
{		
public:
    typedef uint Tag;

    TLevelEvent() = default;

    TLevelEvent(void const* sender_, const string& message_ = "") :
		sender(sender_),
		message(message_)
	{}
		
	template< class T >
	T const* getSender() const {
		return dynamic_cast<T const*>(sender);
	}

	const string& getMessage() const {
		return message;
	}

	virtual const Tag& getTag() const = 0;
protected:
	void const* sender;
	string message;
};

#endif //LEVEL_EVENT_H
