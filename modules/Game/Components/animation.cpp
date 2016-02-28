#include "animation.h"
#include "..\..\Application\application.h"


TAnimation::TAnimation() :
	frameWidth(0),
	frameHeight(0),
	actionFrame(0),
	actionIndex(0),
	framesCount(0),
	frames(),
	image(nullptr)
{}

TAnimation::TAnimation(const string& source)
{
	recognizeFrames(source);
}
	
TAnimation::~TAnimation() 
{
	image.release();
}

void TAnimation::recognizeFrames(const string& source_) {
	if ((String::left(source_, 1) == "[") && (String::right(source_, 1) == "]") == false) {
		throw_("Wrong metadata for animation.", "TAnimation::TAnimation");
	}

	const string source = source_.substr(2, source_.size() - 2);
	const std::vector<string> groups = String::split(source, animationGroups_separator);
	for(auto it = groups.cbegin(); it != groups.cend(); ++it) {
		const std::vector<string> pairs = String::split(*it, animationGroupKey_separator);
		const std::vector<string> values = String::split(pairs[1], animationGroupValues_separator);
		int repeats = 0;
		if (4 <= values.size()) {
			repeats = std::stoi(values[3]);
		}
		TAnimationGroup entry = TAnimationGroup(std::stoi(values[0]), std::stoi(values[1]), std::stoi(values[2]), repeats);
		frames[std::stoul(pairs[0])] = entry;
	}
}
	
	
ushort TAnimation::actionLength(uint index) const {
	const TAnimationGroup& value = frames[index];
	return value.end - value.start;
}	
ushort TAnimation::framesPerActionFrame(uint index) const {
	return frames[index].speed;
}	
bool TAnimation::isActionRepeatable(uint index) const {
	return frames[index].repeats != 0;
}
int TAnimation::getActionRepeats(uint index) const {
	return frames[index].repeats;
}
	
void TAnimation::setActionIndex(uint value) {
	actionIndex = value;
	actionFrame = 0;
}
	
	
uint TAnimation::getHeight() const {
	return frameHeight;
}	
uint TAnimation::getWidth() const {
	return frameWidth;
}
const Point2ui TAnimation::getSize() const {
	return Point2ui(frameWidth, frameHeight);
}
	
uint TAnimation::getActionIndex() const {
	return actionIndex;
}	
uint TAnimation::getFrame() const {
	return actionFrame;
}
uint TAnimation::getCurrentFrame() const {
	return getGroup(actionIndex).start + actionFrame;
}
	
const TAnimationGroup& TAnimation::getGroup(uint index) const {
	return frames[index];
}	
TAnimationGroup& TAnimation::getGroup(uint index) {
	return frames[index];
}
		
bool TAnimation::isCurrentActionCompleted() const {
	return getFrame() == actionLength(getActionIndex());
}
	
	
void TAnimation::update() {
	//Step to the next frame
	framesCount++;
	if (framesPerActionFrame(actionIndex) < framesCount) {
		actionFrame += (actionIndex < actionLength(actionIndex));
	}
		
	//Repeat
	if (isActionRepeatable(actionIndex) == false) { return; }
	if (actionLength(actionIndex) < actionFrame) {
		actionFrame = 0;
	}
}