#include "SpriteAnimationComponent.h"
#include "Engine.h"

namespace rj {
	void SpriteAnimationComponent::Update() {

		owner->transform.position.x = rj::Wrap(owner->transform.position.x, 0.0f, 800.0f);
		owner->transform.position.y = rj::Wrap(owner->transform.position.y, 0.0f, 800.0f);

		frameTime = 1 / fps;

		frameTimer += owner->scene->engine->time.deltaTime;
		
		if (frameTimer >= frameTime) {
			frameTimer = 0;
			frame++;

			if (frame > endFrame) frame = startFrame;
		}

		Vector2 size = texture->GetSize();
		Vector2 frameCount{ numFramesX, numFramesY };
		Vector2 frameSize = size / frameCount;

		rect.x = static_cast<int>((frame % numFramesX) * frameSize.x);
		rect.y = static_cast<int>((frame / numFramesX) * frameSize.y);
		rect.w = static_cast<int>(frameSize.x);
		rect.h = static_cast<int>(frameSize.y);
	}

	void SpriteAnimationComponent::Draw(Renderer* renderer) {
		renderer->Draw(texture, rect, owner->transform);
	}

	bool SpriteAnimationComponent::Write(const rapidjson::Value& value) const {
		return false;
	}

	bool SpriteAnimationComponent::Read(const rapidjson::Value& value) {
		SpriteComponent::Read(value);
		JSON_READ(value, fps);
		JSON_READ(value, numFramesX);
		JSON_READ(value, numFramesY);
		JSON_READ(value, startFrame);
		JSON_READ(value, endFrame);

		if (startFrame == 0 && endFrame == 0) endFrame = numFramesX * numFramesY;
		frame = startFrame;

		return true;
	}
}