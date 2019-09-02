#include "ScriptableCmp.hpp"

class ParticleController : public ScriptableCmp {
public:
	ParticleController(GameObject* gameobject);
	void Start() override;
	void Update(float dt) override;
	void OnGUI() override;
private:

};


