#include "ScriptableCmp.hpp"

class SpawnController : public ScriptableCmp {
public:
	SpawnController(GameObject* gameobject);
	void Start() override;
	void Update(float dt) override;
	void OnCollisionEnter(GameObject * other) override;
	
	float minVel;
	float maxVel;
	bool haveToReset;
	glm::vec3 initPos;
	void setVel(float newMinVel, float newMaxVel);
private:
	void spawn();
};


