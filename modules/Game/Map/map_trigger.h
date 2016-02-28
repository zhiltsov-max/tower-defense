#ifndef MAP_TRIGGER_H
#define MAP_TRIGGER_H

#include "../../../Core/core.h"
#include "../Scene/scene_object.h"


class TMapTrigger : public TSceneObject
{
public:	
	void setPos(const Point2ui& value);
	const Point2ui& getPos() const;
		
	void setSize(const Point2ui& value);
	const Point2ui& getSize() const;
	
    virtual void update() override;

#if _DEBUG_
	const Graphics::ARGB color = 0x88888888;
    virtual void draw(Graphics::TRenderTarget) override;
#endif

private:
	Point2ui pos;
	Point2ui size;
};

#endif // MAP_TRIGGER_H
