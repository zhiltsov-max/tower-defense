#ifndef TB_CASTLE_H
#define TB_CASTLE_H

#include "building.h"


class TB_Castle : public TBuilding
{
public:
	TB_Castle();	
    void initialize(const Info& info);
	TBuilding* clone() const;

	bool isAlive() const;
	bool needsRepair() const;
	bool isSelected() const;
	bool isRepairable() const;
		
	void repair(int amount) const;	
	void hurt(int amount);
	
	int getHealth() const;
	int getMaxHealth() const;	
    ClassId getClass() const;
	
	void setHealth(int value);
	
	void updateParameters();
private:
	typedef TBuilding parent_type;
protected:
	int health;
	int maxHealth;
	
    class Animation;
	void loadSelection();
	void loadAnimation();

	void updateBehaviour();

    static void TB_Castle::InfoLoader(Info& info, std::istream& source);
};

class TB_Castle::Animation : public TBuilding::Animation {
private:
    typedef TBuilding::Animation parent_type;
};

#endif //TB_CASTLE_H
