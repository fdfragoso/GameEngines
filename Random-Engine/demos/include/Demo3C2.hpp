#include "ScriptableCmp.hpp"

class Demo3C2 : public ScriptableCmp {
public:
	Demo3C2(GameObject* gameobject);
	void Start() override;
	void Update(float dt) override;
	void OnGUI() override;
	void OnCollisionEnter(GameObject * other) override;
	void OnCollisionExit(GameObject * other) override;
};


