#include "player_statistics.h"



namespace TD {


TStatistics::TStatistics() :
    m_metrics()
{
    for (uchar key = Metric::_min; key < (uchar)Metric::_count; ++key) {
        addMetric(key, Value());
	}
}

void TStatistics::addMetric(const Key& key, const Value& value) {
    m_metrics[key] = value;
}
	
void TStatistics::removeMetric(const Key& key) {
    m_metrics.erase(key);
}
	
const TStatistics::Value& TStatistics::getMetric(const Key& key) const {
    return m_metrics[key];
}

TStatistics::Value& TStatistics::getMetric(const Key& key) {
    return m_metrics[key];
}
	
void TStatistics::clear() {
    m_metrics.clear();
}
	
void TStatistics::setMetric(const Key& key, const Value& value) {
    m_metrics[key] = value;
}

const TStatistics::Value& TStatistics::operator[](const Key& key) const {
    return m_metrics[key];
}

TStatistics::Value& TStatistics::operator[](const Key& key) {
    return m_metrics[key];
}
	
bool TStatistics::contains(const Key& key) const {
    return m_metrics.count(key) != 0;
}
	
size_t TStatistics::count() const {
    return m_metrics.size();
}


} // namespace TD
