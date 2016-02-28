#ifndef MOB_PATH_H
#define MOB_PATH_H

#include "../../../Core/core.h"
#include "../Map/nodemap.h"


enum class PathSelectionPolicy {
    Undefined = 0,
    Static,
    Dynamic
};

class TMobPath 
{
public:
	typedef TPathNode Node;
	typedef TNodeMap::Path Path;


    const TPathNode& getNextNode() const;
	
	bool exists() const;
	bool empty() const ;
	
	uint getPosition() const;
	uint length() const ;
	float getPercentage() const;

	void setPosition(uint value);
	void set(const Path& newPath);
	
	void removeFirst();
	
	void refresh();
	
	void makeStep();
protected:
	Path path;
	uint position;
};

/*
	Used A* algorithm.
*/
class TPathCreator
{
public:
    static TMobPath::Path CreatePath(const Point2ui& from, const Point2ui& to, ushort const** costs);
private:
	ushort const** moveCosts;
	ushort** usedVertexes; //weights of pathes to these points
	
	TMobPath::Path path;
	
	Point2ui begin;
	Point2ui end;

	uint width;
	uint height;

	Point2ui* buffer;
	size_t bufferPosition;
	size_t bufferSize;	
	size_t bufferLength;

	
	TPathCreator(const Point2ui& from, const Point2ui& to, ushort const** costs);
	~TPathCreator();

    TMobPath::Path findPath();
	void push(uint x, uint y, uint pathWeight);	
	Point2ui* pop();
};

#endif //MOB_PATH_H
