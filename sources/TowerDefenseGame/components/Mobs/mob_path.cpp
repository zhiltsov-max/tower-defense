#include "mob_path.h"
#include "../../../Application/application.h"


const TPathNode& TMobPath::getNextNode() const {
	if (path == nullptr) {
        Throw("Mob path is empty!", "TMobPath::getNextNode");
	}
		
	return path->at(std::min(position + 1, length() - 1));
}
	
bool TMobPath::exists() const {
	return (path != nullptr);
}	
bool TMobPath::empty() const {
	return path->empty();
}
	
uint TMobPath::getPosition() const {
	return position;
}
uint TMobPath::length() const {
	return path->size();
}
float TMobPath::getPercentage() const {
	if ((path != nullptr) && (path->empty() == false)) {
		return position * 100.0 / length();
	} else {
		return 100.0;
	}
}

void TMobPath::setPosition(uint value) {
	position = value;
}	
void TMobPath::set(const std::shared_ptr<TNodePath>& newPath) {
	path = newPath;
	position = 0;
}
	
void TMobPath::removeFirst() {
	if (0 < length()) {
		path->erase(path->begin());
		position = 0;
	}
}
	
void TMobPath::refresh() {
	path = nullptr;
}
	
void TMobPath::makeStep() {
	if (position < length()) {
		++position;
	}
}



TMobPath::Path TPathCreator::CreatePath(const Point2ui& from, const Point2ui& to, ushort const** costs) {
	TPathCreator pc(from, to, costs);		
	TMobPath::Path result = pc.findPath();
    return result;
}

TPathCreator::TPathCreator(const Point2ui& from, const Point2ui& to, ushort const** costs) :
	begin(from), end(to), moveCosts(costs)
{
	width = MobsController::getPassabilityMap().getWidth();
	height = MobsController::getPassabilityMap().getHeight();		
}

TPathCreator::~TPathCreator() {
	if (buffer != nullptr) {
		delete[] buffer;
	}
	if (usedVertexes != nullptr) {
		for(size_t i = 0; i < height; ++i) {
			delete usedVertexes[i];
		}
		delete[] usedVertexes;
	}
}

TMobPath::Path TPathCreator::findPath() {
	bufferLength = width * height;
	buffer = new Point2ui[bufferLength];
	bufferPosition = 0;
	bufferSize = 0;

	usedVertexes = new ushort*[height];
	for(size_t i = 0; i < height; ++i) {
		usedVertexes[i] = new ushort[width]; 
		memset(usedVertexes[i], ushort(-1), sizeof(ushort) * width); // Вначале usedVertexes заполняется max значением
	}

	Point2ui point;
	uint pathWeight;
	uint time;
		
	push(begin.x(), begin.y(), 0);

	Point2ui* res;
	while (res != nullptr) {
		res = pop();
		if (res == nullptr) { continue; }
			
		point = *res;
		pathWeight = usedVertexes[point.x()][point.y()] + moveCosts[point.x()][point.y()];
			
		if ((point.y() + 1 < height) && (moveCosts[point.x()][point.y() + 1])) {
			push(point.x(), point.y() + 1, pathWeight);
		}

		if ((point.x() + 1 < width) && (moveCosts[point.x() + 1][point.y()])) {
			push(point.x() + 1, point.y(), pathWeight);
		}

		if ((0 <= point.y() - 1) && (moveCosts[point.x()][point.y() - 1])) {
			push(point.x(), point.y() - 1, pathWeight);
		}
			
		if ((0 <= point.x() - 1) && (moveCosts[point.x() - 1][point.y()])) {
			push(point.x() - 1, point.y(), pathWeight);
		}
	}

	if ((usedVertexes[end.x()][end.y()] != ushort(-1)) || (point == end)) {
		//Заливка закончена, пpойдемся по пути
		pathWeight = 0xFFFF;
		path->push_back(TPathNode((point.x() + 0.5) * GameMechanics::TILE_SIZE, (point.y() + 0.5) * GameMechanics::TILE_SIZE));
	} else {
        return nullptr; //Path does not exist
	}

	while (((point.x() = begin.x()) && (point.y() = begin.y())) == false) {
		if ((point.y() + 1 < height) && (usedVertexes[point.x()][point.y() + 1] < pathWeight)) {
			end.x() = point.x();
			end.y() = point.y() + 1;
			time = usedVertexes[point.x()][point.y() + 1];
		}
			
		if ((0 <= point.y() - 1) && (usedVertexes[point.x()][point.y() - 1] < pathWeight)) {
			end.x() = point.x();
			end.y() = point.y() - 1;
			time = usedVertexes[point.x()][point.y() - 1];
		}
			
		if ((point.x() + 1 < width) && (usedVertexes[point.x() + 1][point.y()] < pathWeight)) {
			end.x() = point.x() + 1;
			end.y() = point.y();
			time = usedVertexes[point.x() + 1][point.y()];
		}
			
		if ((0 <= point.x() - 1) && (usedVertexes[point.x() - 1][point.y()] < pathWeight)) {
			end.x() = point.x() - 1;
			end.y() = point.y();
			time = usedVertexes[point.x() - 1][point.y()];
		}
			
		point = end;
		pathWeight = time;
			
		path->insert(path->begin(), TPathNode((point.x() + 0.5) * GameMechanics::TILE_SIZE, (point.y() + 0.5) * GameMechanics::TILE_SIZE));
	}

    return path;
}

void TPathCreator::push(uint x, uint y, uint pathWeight) {
	if (usedVertexes[x][y] <= pathWeight) { return; }	
	usedVertexes[x][y] = pathWeight;
	buffer[bufferSize] = Point2ui(x, y);
	bufferPosition = (bufferSize + 1) % (bufferLength >> 1); //cycle
}
	
Point2ui* TPathCreator::pop() {
	if (bufferPosition == bufferSize) { return nullptr; }
	Point2ui& res = buffer[bufferPosition];
	bufferPosition = (bufferPosition + 1) % (bufferLength >> 1); //cycle
	return &res;
}
