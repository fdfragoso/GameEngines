#include "WorldMap.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>

using namespace std;

void WorldMap::loadMap(std::string filename) {
    
	 ifstream fis(filename);
	 rapidjson::IStreamWrapper isw(fis);
	 rapidjson::Document d;
	 d.ParseStream(isw);
	 int fileRowCount;
	 
	 fileRowCount = d["tileMap"].Size();
	 cout << "ROW COUNT: " << fileRowCount;
	 
	 for (int i = 0; i < fileRowCount; i++) 
	 {
		 std::vector<int> newRow;
		 for (int j = 0; j < d["tileMap"][i].Size(); j++) 
		 {
			 newRow.push_back(d["tileMap"][i][j].GetInt());
			 cout << "PUSHING BACK: " << d["tileMap"][i][j].GetInt();
		 }
		 cout << std::endl;
		 values.push_back(newRow);
	 }

	 startingPosition.x = d["spawn"]["x"].GetDouble();
	 startingPosition.y = d["spawn"]["y"].GetDouble();
	 startingRotation = d["spawn"]["angle"].GetDouble();

     //IStreamWrapper isw(fis);
     //Document d;
     //d.ParseStream(isw);
}

int WorldMap::getTile(int x, int y) {
    return values.at(y).at(x);
}

int WorldMap::getWidth() {
    return values[0].size();
}

int WorldMap::getHeight() {
    return values.size();
}

glm::vec2 WorldMap::getStartingPosition() {
    return startingPosition;
}

float WorldMap::getStartingRotation() {
    return startingRotation;
}

glm::vec4 WorldMap::getFloorColor() {
    return floorColor;
}

glm::vec4 WorldMap::getCeilColor() {
    return ceilColor;
}
