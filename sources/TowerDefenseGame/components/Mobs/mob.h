#ifndef MOB_H
#define MOB_H

#include "../../../Core/core.h"
#include "../Scene/scene_object.h"
#include "mob_path.h"
#include "../gameobjects_info.h"

class TMob : public TSceneObject
{
public:
    using ClassId = TGameObjectClassId;
    using Info = TObjectInfo;
    using Path = TMobPath;
    using Appearance = Altitude;


	TMob();
	TMob(const TMob& other);	
	~TMob();
	virtual TMob* clone() = 0;
	virtual void initialize(Info const* source);

	virtual void checkPath();
	virtual void update();
	virtual void draw();
	
	void setPos(const Point2ui& value);
	void setZIndex(int value);
	void setHealth(int value);
	
	const Path& getPath() const;
	int getReward() const;
	int getPoints() const;
    Graphics::ZIndex getZIndex() const;
    virtual ClassId getClass() const = 0;
    virtual Appearance getAppearance() const = 0;
	const string& getDescription() const;
	virtual int getHealth() const;
	virtual int getMaxHealth() const;
	virtual float getSpeed() const;
	const Point2ui& getSize() const;
	const Point2ui& getPos() const;
	
	bool isOnTile(const Point2ui& tilePos, int tileAppearance = MobAppearance::Ground) const;		
	bool isAlive() const;
	bool hasReachedPathEnd() const;

	static int CmpGetFastest(TMob const* m1, TMob const* m2);	
	static int CmpGetMostDamaged(TMob const* m1, TMob const* m2);	
	static int CmpGetClosest(TMob const* m1, TMob const* m2);
private:
    typedef TSceneObject parent_type;
protected:
	class Animation;
	class HealthBar;

	Path path;
	std::unique_ptr<Animation> animation;
	std::unique_ptr<HealthBar> healthBar;
	
	float speed;
	int health;
	int maxHealth;
	
	Point2ui pos;


	virtual void loadHealthBar();	
	virtual void loadAnimation(Info const* source);

	void findPath();

	virtual void updatePosition();
	virtual void updateTarget();
	virtual void updateAnimation();
			
	bool hasCrossedNode() const;
			
	void die();	
	void hurtBase();
};

#endif //MOB_H
