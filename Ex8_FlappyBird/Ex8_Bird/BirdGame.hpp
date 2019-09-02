#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include <vector>
#include "Box2D/Dynamics/b2World.h"
#include "GameObject.hpp"
#include "SideScrollingCamera.hpp"
#include "BackgroundComponent.hpp"
#include "Box2DDebugDraw.hpp"
#include "SDL_mixer.h"

class PhysicsComponent;

enum class GameState{
    Ready,
    Running,
    GameOver
};

class BirdGame : public b2ContactListener {
public:
    BirdGame();

    std::shared_ptr<GameObject> createGameObject();
    static const glm::vec2 windowSize;

    void BeginContact(b2Contact *contact) override;

    void EndContact(b2Contact *contact) override;

    static BirdGame* instance;

    void setGameState(GameState newState);

	void coinCollected();
private:
    sre::SDLRenderer r;

    void init();
    void initPhysics();

    void update(float time);

    void render();

    void onKey(SDL_Event &event);

    void handleContact(b2Contact *contact, bool begin);

    std::shared_ptr<SideScrollingCamera> camera;
    std::shared_ptr<sre::SpriteAtlas> spriteAtlas;

    std::vector<std::shared_ptr<GameObject>> sceneObjects;
    BackgroundComponent background1Component;
    BackgroundComponent background2Component;

    void updatePhysics();
    b2World * world = nullptr;
    const float physicsScale = 100;
    void registerPhysicsComponent(PhysicsComponent *r);
    void deregisterPhysicsComponent(PhysicsComponent *r);
    std::map<b2Fixture*,PhysicsComponent *> physicsComponentLookup;
    Box2DDebugDraw debugDraw;
    bool doDebugDraw = false;
    GameState gameState = GameState::Ready;
    friend class PhysicsComponent;
	std::shared_ptr<GameObject> myBird;
	int coinCount = 0;
	int highScore = 0;

	Mix_Chunk* coinSound = nullptr;
};



