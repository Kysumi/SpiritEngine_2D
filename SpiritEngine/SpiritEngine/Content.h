#ifndef SE_CONTENT_H
#define SE_CONTENT_H
#include "SFML/Audio.hpp"
#include "lua.hpp"

namespace se
{
	class Content
	{
	public:
		Content();
		~Content();

		//Loads an asset
		static void load(std::string assert);
		// Checks if an asset is loaded, if its not and load == true, it loads it
		static bool isLoaded(std::string asset, bool autoLoad = false);
		static void setup();
		static void reload()
		{
			_loaded = false;

			lua_close(_state);

			Tools::Print("Reloading Content loader", false);
			setup();

		};

		static sf::Texture * getTexture(std::string name) {
			for (auto texture : _textures)
				if (texture.first == name)
					return texture.second;

			return nullptr;
		}		
		
		static sf::Font * getFont(std::string name) {
			for (auto font : _fonts)
				if (font.first == name)
					return font.second;

			return nullptr;
		}		
		
		static sf::Sound * getSound(std::string name) {
			for (auto sound : _sounds)
				if (sound.first == name)
					return sound.second;

			return nullptr;
		}


	protected:
		//Handler for loading images and stores it as a texture
		static void loadImage(std::string name, std::string loc);
		//Handler for loading fonts
		static void loadFont(std::string name, std::string loc);
		//Handler for loading sounds
		static void loadSound(std::string name, std::string loc);

		static std::map<std::string, std::string> * getLoadedItems() {
			return &_itemsLoaded;
		}

		static std::map<std::string, sf::Texture *> _textures;
		static std::map<std::string, sf::Font *> _fonts;
		static std::map<std::string, sf::Sound *> _sounds;
		static std::map<std::string, std::string> _itemsLoaded;

	private:
	
		//Just to save re-typing stuff over and over.
		static int callHelper(int args, int ret);

		static lua_State * _state;
		static bool _loaded;	

		static bool errorCheck()
		{
			return _loaded;
		}
		
	};


}

#endif // !SE_CONTENT_H
