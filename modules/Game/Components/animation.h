#ifndef ANIMATION_H
#define ANIMATION_H

#include "../../Core/core.h"


struct TAnimationGroup
{	
	static const int UnlimitedRepeats = -1;

	TAnimationGroup(ushort start_, ushort end_, ushort speed_, int repeats_ = UnlimitedRepeats) :
		start(start_),
		end(end_),
		speed(speed_),
		repeats(repeats_)
	{}

	ushort start;
	ushort end;
	ushort speed; //number of draw frames per one frame of animation
	int repeats;
};

/*
	bbdoc: Base class for game objects animation
*/
class TAnimation
{
public:
	TAnimation();
	TAnimation(const string& source);	
	virtual ~TAnimation();

	ushort actionLength(uint index) const;	
	ushort framesPerActionFrame(uint index) const;
	bool isActionRepeatable(uint index) const;
	int getActionRepeats(uint index) const;
	
	void setActionIndex(uint value);
		
	uint getHeight() const;
	uint getWidth() const;
	const Point2ui getSize() const ;
	
	uint getActionIndex() const;
	uint getFrame() const;
	uint getCurrentFrame() const;
	
	const TAnimationGroup& getGroup(uint index) const;
	TAnimationGroup& getGroup(uint index);
		
	bool isCurrentActionCompleted() const;
	
	void update();
protected:
	static const char animationGroups_separator = ';';
	static const char animationGroupKey_separator = ':';
	static const char animationGroupValues_separator = '-';
	
	uint frameWidth;
	uint frameHeight;
	std::map<uint, TAnimationGroup> frames;	
	std::unique_ptr<TImage> image;

	uint actionFrame;
	uint actionIndex;	
	uint framesCount;

	void recognizeFrames(const string& source);
};

#endif //ANIMATION_H
