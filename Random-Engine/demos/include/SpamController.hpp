#include "ScriptableCmp.hpp"

class SpamController : public ScriptableCmp {
public:
	SpamController(GameObject* gameobject);
	void Start() override;
	void Update(float dt) override;
	void OnGUI() override;
	void OnCollisionEnter(GameObject * other) override;
	void OnCollisionExit(GameObject * other) override;
private:
	int nPlants;
	void spamPlant();
};


