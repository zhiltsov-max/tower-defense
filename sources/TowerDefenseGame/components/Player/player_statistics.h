#ifndef PLAYER_STATISTICS_H
#define PLAYER_STATISTICS_H

#include "Game/Components/components_list.h"


namespace TD {

enum class Metric : uchar {
	_min = 0,

	TotalTime = 0, 
	MobsPassed, 
	MobsKilled, 
	CreditsSpent, 
	CreditsEarned, 
	BuildingsCreated, 
	BuildingsSold, 
	Upgrades,

    _count
};

class CPlayerStatistics : public CLogicsComponent
{
public:
    typedef Metric Key;
    typedef double Value;

    TStatistics();
    ~TStatistics() = default;

	void addMetric(const Key& key, const Value& value);	
	void removeMetric(const Key& key);

	const Value& getMetric(const Key& key) const;
	Value& getMetric(const Key& key);

	void setMetric(const Key& key, const Value& value);	

    const Value& operator[](const Key& key) const;
    Value& operator[](const Key& key);

	void clear();
	bool contains(const Key& key) const;
	size_t count() const;

private:
    map<Key, Value> m_metrics;
};

template<>
struct ComponentID< CPlayerStatistics > {
    static constexpr GE::ComponentIDs value = GE::ComponentIDs::PlayerStatistics;
};

template<>
struct ComponentClass< CPlayerStatistics > {
    static constexpr GE::ComponentClass value =
        GE::ComponentClassForId[GE::ComponentIDs::PlayerStatistics];
};

} // namespace TD

#endif // PLAYER_STATISTICS_H
