#ifndef GAME_ENGINE_NAMED_DATA_H
#define GAME_ENGINE_NAMED_DATA_H

#include <iostream>
#include <initializer_list>
#include <map>
#include <utility>

#include "GameEngine/Utility/common.h"
#include "GameEngine/Infrastructure/string.h"


GE_BEGIN_ENGINE_NAMESPACE

/*
 * Represents a hierarchical dictonary with string keys and values of some type.
 * Supports splicing and indexing. Useful as a configuration storage.
 */
template<class Value_>
class TNamedData
{
public:
	typedef TString TKey;
	typedef Value_ TValue;

private:
    TString::value_type keySeparator;

	typedef std::map<TKey, TValue> TStorage;
	TStorage storage;

public:
	typedef typename TStorage::const_iterator const_iterator;
	typedef typename TStorage::iterator iterator;
	typedef typename TStorage::reverse_iterator reverse_iterator;
	typedef typename TStorage::const_reverse_iterator const_reverse_iterator;


	TNamedData(char keySeparator_ = ':') :
        storage(),
        keySeparator(keySeparator_)
	{}

    TNamedData(std::initializer_list< std::pair<const TKey, TValue> > list) :
        storage(std::move(list)),
        keySeparator(':')
    {}

	bool contains(const TKey& key) const {
		return storage.count(key) != 0;
	}

	bool empty() const {
		return storage.empty();
	}

	size_t size() const {
		return storage.size();
	}

	char keySep() const {
		return keySeparator;
	}

	const T& at(const TKey& key) const {
		return storage.at(key);
	}

	T& at(const TKey& key) {
		return storage.at(key);
	}

	const T& operator[](const TKey& key) const {
		return at(key);
	}

	T& operator[](const TKey& key) {
		return storage.operator[](key);
	}

	void insert(const TKey& key, const T& value) {
		storage.insert( std::pair<TKey, T>(key, value) );
	}

	void erase(const TKey& key) {
		storage.erase(key);
	}

	void clear() {
		storage.clear();
	}

	const_iterator cbegin() const {
		return storage.cbegin();
	}

	const_iterator cend() const {
		return storage.cend();
	}

    const_iterator begin() const {
        return storage.begin();
    }

    const_iterator end() const {
        return storage.end();
    }

    iterator begin() {
		return storage.begin();
	}

    iterator end() {
		return storage.end();
	}

    reverse_iterator rbegin() {
		return storage.rbegin();
	}

    reverse_iterator rend() {
		return storage.rend();
	}

	const_reverse_iterator crbegin() const {
		return storage.crbegin();
	}

	const_reverse_iterator crend() const {
		return storage.crend();
	}

    const_reverse_iterator rbegin() const {
        return storage.rbegin();
    }

    const_reverse_iterator rend() const {
        return storage.rend();
    }

	T& front() {
		return storage.front();
	}

	const T& front() const {
		return storage.front();
	}

	T& back() {
		return storage.back();
	}

	const T& back() const {
		return sotrage.back();
	}

	/*
	 * Returns subtree for key
	*/
    TNamedData slice(const TKey& key) const {
		TNamedData result;

		for(auto it = cbegin(); it != cend(); ++it) {
			if (String::startsWith((*it).first, key)) {
                result.emplace((*it).first, (*it).second);
			}
		}

        return result;
	}

	/*
	 * Imports all data from other
	*/
	void import(const TNamedData& other) {
		for(auto it = other.cbegin(); it != other.cend(); ++it) {
            insert((*it).first, (*it).second);
        }
	}

	/*
	 * Updates keys data with data from other
	*/
	void update(const TNamedData& other) {
		for(auto it = cbegin(); it != cend(); ++it) {
			if (other.contains((*it).first) == true) {
                emplace((*it).first, other[(*it).first]);
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const TNamedData& data) {
		for(auto it = data.cbegin(); it != data.cend(); ++it){
            os	<< "(Key: " << ((*it).first)
				<< ", "
                << "Value: " << ((*it).second)
				<< ")"
				<< std::endl;
		}
		return os;
	}
};

GE_END_ENGINE_NAMESPACE

#endif //GAME_ENGINE_NAMED_DATA_H
