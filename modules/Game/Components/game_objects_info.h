#ifndef GAME_OBJECTS_INFO_H
#define GAME_OBJECTS_INFO_H

#include "GameEngine/registry.h"



namespace TD {


using TGameObjectClassId = uint;

template< class Entry >
using TGameObjectsRegistry = TRegistry<Entry, TGameObjectClassId>;


} // namesoace TD

#endif // GAME_OBJECTS_INFO_H
