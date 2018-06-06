#ifndef __KEYBINDINGS_H__
#define __KEYBINDINGS_H__

#include "..\Core\core.h"
#include "preferences.h"

class TKeyBindings
{
public:
	struct TKeyBinding;
	typedef ushort Key;


	TKeyBindings(bool useDefault = true);

	const TKeyBinding& getBinding(const Key& key) const;
private:
	std::map<Key, TKeyBinding> data;

	
	void loadDefault();	
	void loadFromFile(const string& source);
};

struct TKeyBindings::TKeyBinding
{
	ushort keyCode;
	
	TKeyBinding(ushort keyCode_) :
		keyCode(keyCode_)
	{}
};

#endif