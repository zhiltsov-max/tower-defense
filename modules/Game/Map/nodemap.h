#ifndef NODEMAP_H
#define NODEMAP_H

#include "..\..\..\Core\core.h"
#include "pathnode.h"


class TNodeMap
{
public:
    using Path = std::vector<TPathNode>;


    TNodeMap(const TNamedData<string>& source);

	void updateData(const TNamedData<string>& source);
	
	Path& addPath(uint x, uint y);	
	TPathNode& addEnter(uint x, uint y);	
	TPathNode& addExit(uint x, uint y);
	
	const TPathNode& getEnter(size_t index = 0) const;
	TPathNode& getEnter(size_t index = 0);

	const TPathNode& getExit(size_t index) const;
	TPathNode& getExit(size_t index);

	const Path& getPath(size_t index) const;
	Path& getPath(size_t index);

	size_t getPathCount() const;
	size_t getEnterCount() const;	
	size_t getExitCount() const;
	
	const TPathNode& findNearestExit(uint x, uint y) const;
		
	bool isExit(const TPathNode& node) const;
	bool isEnter(const TPathNode& node) const;
private:
	std::vector<Path> pathes;
	std::vector<TPathNode> enters;
    std::vector<TPathNode> exits;


	void loadData(const TNamedData<string>& source);
	void loadPathes(const TNamedData<string>& source);
	void loadEnters(const TNamedData<string>& source);
	void loadExits(const TNamedData<string>& source);
};

#endif // NODEMAP_H
