#ifndef TURRET_BULLET_H
#define TURRET_BULLET_H

#include "../../../Core/core.h"
#include "../Scene/gameobject.h"
#include "../Mobs/mob.h"


class TTurret::Bullet : public TGameObject
{
public:
	Bullet(const Point2f& pos_, float damage_, float acceleration_, TMob const* target_, ushort size_);

	Graphics::ZIndex getZIndex() const;
	void setZIndex(Graphics::ZIndex value);

	const Point2f getPos() const;
	void setPos(float x, float y);
	void setPos(const Point2f& pos_);
	
	bool isCloseToTarget() const;

	void update();

	void draw();
private:
	Point2f pos;
	float speed;
	float acceleration;
	
	TMob const* target;
	float damage;
	ushort size;
	Graphics::ARGB color;

	const Graphics::ARGB DEFAULT_COLOR = 0xffffffff;
	
	void move();
	void hurt();
};

#endif //TURRET_BULLET_H
