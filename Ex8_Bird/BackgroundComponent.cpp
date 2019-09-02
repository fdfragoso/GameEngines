
#include <sre/SpriteAtlas.hpp>
#include <sre/Texture.hpp>
#include <glm/gtx/transform.hpp>
#include "BackgroundComponent.hpp"
#include "BirdGame.hpp"

using namespace sre;
using namespace glm;

BackgroundComponent::BackgroundComponent()
{
}

void BackgroundComponent::renderBackground(sre::RenderPass &renderPass, float offset) {
    renderPass.draw(batch, glm::translate(vec3(offset,0,0)));
}

void BackgroundComponent::init(std::string filename) {
    tex = Texture::create().withFile(filename)
            .withFilterSampling(false)
            .build();

    auto atlas = SpriteAtlas::createSingleSprite(tex,"background", vec2(0,0));
    auto sprite = atlas->get("background");
    float scale = BirdGame::windowSize.y / tex->getHeight();
    sprite.setScale({scale,scale});
    auto batchBuilder = SpriteBatch::create();
    for (int i=0;i<100;i++){
        sprite.setPosition(vec2(tex->getWidth() * (i-1) * scale, 0));
        batchBuilder.addSprite(sprite);
    }
    batch = batchBuilder.build();
}

