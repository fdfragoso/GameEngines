#include "SpriteAtlas.hpp"
#include "picojson.h"
#include <fstream>

SpriteAtlas::SpriteAtlas() {
	texture = nullptr;
}

void SpriteAtlas::addFromFile(std::string atlasJsonPath, std::string fileName) {
	std::fstream file(atlasJsonPath + fileName);
	picojson::value v;
	file >> v;

	picojson::array spritesArray;
	
	if (!v.is<picojson::object>()) {
		std::cerr << "JSON is not an object" << std::endl;
	}
	std::string auxS = atlasJsonPath + v.get("meta").get("image").get<std::string>();
	const char * spriteSheetPath = auxS.c_str();
	//Using SRE::Texture::createFromFile() creates one memory leak
	texture = SRE::Texture::createFromFile(spriteSheetPath, false);
	spritesArray = v.get("frames").get<picojson::array>();

	for (auto i = spritesArray.begin(); i != spritesArray.end(); i++) {
		std::string sName = i->get("filename").to_str();
		if (sprites.find(sName) != sprites.end()) {
			continue;
		}
		picojson::object sFrame = i->get("frame").get<picojson::object>();
		bool sRotated = i->get("rotated").get<bool>();
		bool sTrimmed = i->get("trimmed").get<bool>();
		picojson::object sSpriteSourceSize = i->get("spriteSourceSize").get<picojson::object>();
		picojson::object sSourceSize = i->get("sourceSize").get<picojson::object>();
		picojson::object sPivot = i->get("pivot").get<picojson::object>();

		sprites.emplace(sName, new Sprite(
			sFrame.find("x")->second.get<double>(),
			(texture->getHeight() - sFrame.find("y")->second.get<double>()) - sFrame.find("h")->second.get<double>(),
			sFrame.find("w")->second.get<double>(),
			sFrame.find("h")->second.get<double>(),
			sPivot.find("x")->second.get<double>(),
			sPivot.find("x")->second.get<double>(),
			texture
		));
	}
}

SpriteAtlas::~SpriteAtlas() {
	delete texture;
	for (auto e : sprites) {
		delete e.second;
	}
	sprites.clear();
}

Sprite * SpriteAtlas::getSprite(std::string name) {
	if (sprites.find(name) != sprites.end()) {
		return sprites.find(name)->second;
	}
	return nullptr;
}

void SpriteAtlas::clearAtlas() {
	for (auto e : sprites) {
		delete e.second;
	}
	sprites.clear();
}
