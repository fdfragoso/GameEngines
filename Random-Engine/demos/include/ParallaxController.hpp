#include "ScriptableCmp.hpp"

class ParallaxController : public ScriptableCmp {
public:
	ParallaxController(GameObject* gameobject);
	void Start() override;
	void Update(float dt) override;
	void OnCollisionEnter(GameObject * other) override;
	
	float movVel;
	float maxVel;
	bool haveToReset;
	glm::vec3 initPos;
};


