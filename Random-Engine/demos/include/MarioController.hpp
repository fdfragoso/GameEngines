#include "ScriptableCmp.hpp"

class MarioController : public ScriptableCmp {
public:
	MarioController(GameObject* gameobject);
	void Start() override;
	void Update(float dt) override;
	void OnGUI() override;
	void OnCollisionEnter(GameObject * other) override;
	void OnCollisionExit(GameObject * other) override;

private:
	float movVel;
	float rotVel;
	float animSpeedRate;
};


