#ifndef NAMEDDATA_H
#define NAMEDDATA_H

#include <iostream>
#include <initializer_list>
#include <map>
#include <utility>

#include "string.h"


template< class T >
class TNamedData : public std::map<string, T>
{
private:
    char keySeparator;
public:
	typedef std::map<string, T> parent_type;
	typedef typename parent_type::const_iterator const_iterator;
	typedef typename parent_type::iterator iterator;
	typedef typename parent_type::reverse_iterator reverse_iterator;
	typedef typename parent_type::const_reverse_iterator const_reverse_iterator;


	TNamedData(char keySeparator_ = ':') :
        parent_type(),
        keySeparator(keySeparator_)
	{}
	TNamedData(const TNamedData& other) :
        parent_type(other),
        keySeparator(other.keySeparator)
	{}
	TNamedData(TNamedData&& other) :
        parent_type(std::move(other)),
        keySeparator(std::move(other.keySeparator))
	{}
    TNamedData(std::initializer_list< std::pair<const string, T> > list) :
        parent_type(list),
        keySeparator(':')
    {}
	TNamedData& operator=(const TNamedData& other) {
		if (this != &other) {
			clear();
			parent_type::operator=(other);
			keySeparator = other.keySeparator;
		}	
		return *this;
	}
    TNamedData& operator=(TNamedData&& prot) {
        if (this != &prot) {
            clear();
            parent_type::operator=(prot);
            keySeparator = std::move(prot.keySeparator);
        }
        return *this;
    }
    ~TNamedData() = default;

	bool contains(const string& key) const {
		return parent_type::count(key) != 0; 
	}
	bool empty() const {
		return parent_type::empty();
	}
	size_t size() const { 
		return parent_type::size();
	}
	
	char keySep() const {
		return keySeparator; 
	}

	const T& at(const string& key) const {
		return parent_type::at(key);
	}
	T& at(const string& key) {
		return parent_type::at(key);
	}
	const T& operator[](const string& key) const {
		return at(key); 
	}
	T& operator[](const string& key) {
		return parent_type::operator[](key); 
	}

	void insert(const string& key, const T& value) {
		parent_type::insert( std::pair<string, T>(key, value) );
	}

	void erase(const string& key) {
		parent_type::erase(key);
	}
	void clear() {
		parent_type::clear();
	}

	const_iterator cbegin() const {
		return parent_type::cbegin();
	}
	const_iterator cend() const {
		return parent_type::cend();
	}

    const_iterator begin() const {
        return parent_type::begin();
    }
    const_iterator end() const {
        return parent_type::end();
    }

    iterator begin() {
		return parent_type::begin();
	}
    iterator end() {
		return parent_type::end();
	}

    reverse_iterator rbegin() {
		return parent_type::rbegin();
	}
    reverse_iterator rend() {
		return parent_type::rend();
	}

	const_reverse_iterator crbegin() const {
		return parent_type::crbegin();
	}
	const_reverse_iterator crend() const {
		return parent_type::crend();
	}

    const_reverse_iterator rbegin() const {
        return parent_type::rbegin();
    }
    const_reverse_iterator rend() const {
        return parent_type::rend();
    }
	
	T& front() {
		return *begin();
	}
	const T& front() const {
		return *cbegin();
	}
	T& back() {
		return *end();
	}
	const T& back() const {
		return *cend();
	}

	/*
		Returns subtree for key
	*/
    TNamedData slice(const string& key) const {
		TNamedData result;

		for(auto it = cbegin(); it != cend(); ++it) {
			if (String::startsWith((*it).first, key)) {
                result.emplace((*it).first, (*it).second);
			}
		}

        return result;
	}

	/*
		Imports all data from other
	*/
	void import(const TNamedData& other) {
		for(auto it = other.cbegin(); it != other.cend(); ++it) {
            insert((*it).first, (*it).second);
        }
	}

	/*
		Updates keys data with data from other
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

#endif //NAMEDDATA_H
