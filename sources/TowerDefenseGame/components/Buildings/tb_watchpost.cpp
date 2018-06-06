#include "tb_watchpost.h"

TB_Watchpost::TB_Watchpost() :
	parent_type(),
	messageBubbleName(),
	message(),
	buildState(BuildState::Complete)
{}

TBuilding* TB_Watchpost::clone() const {
    return new TB_Watchpost(*this);
}
	
void TB_Watchpost::initialize() {
	parent_type::initialize();
	loadBubble();
}
	
void TB_Watchpost::loadBubble() {
	if (messageBubbleName.empty() == true) {
		return;
	}
		
	TMessageBubble* bubble = getBubble();
	if (bubble == nullptr) {
		return;
	}
	bubble->SetText(message);
}

TBuilding::ClassId TB_Watchpost::getClass() const {
	return BuildingClass::Watchpost;
}
	
const string& TB_Watchpost::getMessageBubbleName() const {
	return messageBubbleName;
}	
void TB_Watchpost::setMessageBubbleName(const string& value) {
	messageBubbleName = value;
}
	
void TB_Watchpost::setMessage(const string& value) {
	if (message != value) {
		TMessageBubble* bubble = getBubble();
		if (bubble != nullptr) {
			bubble->SetText(value);
		}
		message = value;
	}
}
	
const string& TB_Watchpost::getMessage() const {
	return message;
}
	
	
void TB_Watchpost::setSelection(bool value) {
	if (selected != value) {
		TMessageBubble* bubble = getBubble();
		if (bubble != nullptr) {
			if (value == true) {
				checkBubblePosition(); 
			}
			bubble->SetVisibility(value);
		}
		parent_type::setSelection(value);
	}
}

void TB_Watchpost::loadAnimation() {
	animation = new Animation(getClass());
	animation->setAction(BuildingAnimationGroup::Normal);
}
	
void TB_Watchpost::loadSelection() {
	/*none*/
}	

TMessageBubble const* TB_Watchpost::getBubble() const {
	return UIParent().FindChild<TMessageBubble const*>(messageBubbleName);
}
TMessageBubble* TB_Watchpost::getBubble() {
	return UIParent().FindChild<TMessageBubble*>(messageBubbleName);
}

void TB_Watchpost::checkBubblePosition() {
	getBubble()->SetPosition(Point2ui(xAbs(), yAbs() - getBubble()->getHeight()));
}

void TB_Watchpost::updateBehaviour() {
	// update as building
		
	// update gui object
	TGameEvent const* evt = getCurrentEvent();
	if (evt != nullptr) {
		if (evt.getType() == EventType::GameStarted) {
			TMessageBubble* bubble = getBubble();
			if (bubble != nullptr) {
				checkBubblePosition();
				bubble->SetText(message);
				bubble->Show();
			}
		}
	}
}

void TB_Watchpost::updateParameters() {
	//none
}
