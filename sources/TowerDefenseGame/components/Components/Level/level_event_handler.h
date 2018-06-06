#ifndef LEVEL_EVENT_HANDLER_H
#define LEVEL_EVENT_HANDLER_H

#include "level_event.h"

class TEventHandler
{
public:	
	typedef void (*Function)(TGameEvent&);

	TEventHandler(Function func) :
		ptr(func)
	{}
	
	Function get() const {
		return ptr;
	}
	
	void set(Function value) {
		ptr = value;
	}
	
	void invoke(const TGameEvent& evt) {
		return ptr(evt);
	}
private:
	Function ptr;
};


#endif //LEVEL_EVENT_HANDLER_H
