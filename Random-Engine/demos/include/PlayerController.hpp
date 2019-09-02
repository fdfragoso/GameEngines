#include "ScriptableCmp.hpp"

class PlayerController : public ScriptableCmp {
public:
	PlayerController(GameObject* gameobject);
	void Start() override;
	void Update(float dt) override;
	void OnGUI() override;
	void OnCollisionEnter(GameObject * other) override;
	void OnCollisionExit(GameObject * other) override;

private:
	float jumpImpulse;
	float score;
	bool canJump;
	bool gameOver;
	void setGameOver();
};


