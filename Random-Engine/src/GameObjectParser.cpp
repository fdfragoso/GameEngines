#include "GameObjectParser.hpp"
#include <fstream>
#include "picojson.h"

glm::vec4 to_vec4(picojson::value v){
    glm::vec4 res;
    auto array = v.get<picojson::array>();
    for (int i=0;i<4;i++){
        res[i] = (float)array[i].get<double>();
    }
    return res;
}

glm::vec3 to_vec3(picojson::value v){
    glm::vec3 res;
    auto array = v.get<picojson::array>();
    for (int i=0;i<3;i++){
        res[i] = (float)array[i].get<double>();
    }
    return res;
}

std::vector<GameObjectDescriptor> GameObjectParser::parseFile(std::string filename){
    std::fstream file(filename);
    picojson::value v;
    file >> v;

    std::vector<GameObjectDescriptor> res;
	picojson::array objectsArray;
	if (!v.is<picojson::object>()) {
		std::cerr << "JSON is not an object" << std::endl;
	}
	objectsArray = v.get("gameobjects").get<picojson::array>();

    for (auto i = objectsArray.begin(); i != objectsArray.end(); i++) {
		auto asdwew = i->get("name");
        GameObjectDescriptor d;
		//Id
        d.uniqueId = (int)i->get("uniqueId").get<double>();
		//Game object name
		d.name = i->get("name").get<std::string>();
		//Transform
		d.position = to_vec3(i->get("position"));
		d.rotationEuler = to_vec3(i->get("rotationEuler"));
		d.scale = to_vec3(i->get("scale"));
		d.parentId = (int)i->get("parentId").get<double>();
		//Body2D
        d.bodyShape = i->get("bodyShape").get<std::string>();
		if (d.bodyShape != "") {
			std::string auxBodyType = i->get("bodyType").get<std::string>();
			d.bodyType = auxBodyType == "static" ? b2BodyType(0) : auxBodyType == "kinematic" ? b2BodyType(1) : auxBodyType == "dynamic" ? b2BodyType(2) : b2BodyType(0);
		}
		//SpriteRenderer
		d.spriteNameInAtlas = i->get("spriteNameInAtlas").get<std::string>();
		if (d.spriteNameInAtlas != "") {
			d.spriteColor = to_vec4(i->get("spriteColor"));
			d.spriteScale = to_vec3(i->get("spriteScale"));
		}
        res.push_back(d);
    }
    return res;
}
