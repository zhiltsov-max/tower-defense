#ifndef TB_WATCHPOST_H
#define TB_WATCHPOST_H

#include "buildings_list.h"


class TB_Watchpost : public TBuilding
{
public:
	TB_Watchpost();
	TBuilding* clone() const;	
	void initialize(Info const* source);
	
    ClassId getClass() const;
	const string& getMessageBubbleName() const;
	void setMessageBubbleName(const string& value);
	void setMessage(const string& value);
	const string& getMessage() const;	
	
	void setSelection(bool value);
	void updateParameters();
private:
	typedef TBuilding parent_type;
protected:
	string messageBubbleName;
	string message;
	
	void loadAnimation();
	void loadBubble();	
	void loadSelection();

	TMessageBubble const* getBubble() const;
	TMessageBubble* getBubble();

	void checkBubblePosition();

	void updateBehaviour();
};

#endif //TB_WATCHPOST_H
