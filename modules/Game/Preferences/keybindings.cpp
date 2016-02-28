#include "keybindings.h"


static const string keyBindingKeys[] = {"KB_Increase", "KB_Decrease", "KB_Pause", "KB_SelectAll", "KB_Repair"};
static const size_t keyBindingKeys_size = 5;
static const ushort defaultKeyBindings[] = {KEY_Z, KEY_X, KEY_Space, KEY_S, KEY_D};

const string NOT_FOUND_ERROR = "Key binding not found.";


TKeyBindings::TKeyBindings(bool useDefault) 
{
	if (useDefault == true) {
		loadDefault();
	} else {
		loadFromFile(GamePreferences::dataPath());
		if (data.empty() == true) {
			loadDefault();
		}
	}
}

const TKeyBindings::TKeyBinding& TKeyBindings::getBinding(const Key& key) const {
	return data.at(key);
}

	
void TKeyBindings::loadDefault() {
	for(size_t i = 0; i < keyBindingKeys_size; ++i) {
		data[i] = TKeyBinding(defaultKeyBindings[i]);
	}
}
	
void TKeyBindings::loadFromFile(const string& source) {
	std::ifstream* is = new std::ifstream(source);
	if (is == nullptr) {
		return;
	}

	string buffer;
		
	while (is->good()) {
		std::getline(*is, buffer);

		std::vector<string> parts = String::split(buffer, " "); // "KEY VALUE" -> [key, value]
		if (parts.size() != 2) {
			throw_("Unable to load key binding: unexpected data at pos. " + std::to_string(is->tellg()) + ".", "TKeyBindings::loadFromFile");
		}
		//check if key is known
		size_t i = 0;
		for(; i < keyBindingKeys_size; ++i) {
			if (keyBindingKeys[i] == parts[0]) {
				break;
			}
		}
		if (i == keyBindingKeys_size) {
			throw_("Unable to load key binding: unexpected key '" + parts[0] + "'.", "TKeyBindings::loadFromFile");
		}

		data[i] = TKeyBinding(std::stoi(parts[1]));
	}
	is->close();
}