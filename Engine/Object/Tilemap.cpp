#include "Tilemap.h"
#include "Engine.h"

namespace rj {
	void Tilemap::Create() {
		for (size_t i = 0; i < tiles.size(); i++) {
			int index = tiles[i];
			if (index == 0) continue;

			auto actor = ObjectFactory::Instance().Create<Actor>(tileNames[index]);
			if (actor) {
				int x = i % numTilesX;
				int y = i / numTilesY;

				actor->transform.position = start + (Vector2{ x, y } * size);
				scene->AddActor(std::move(actor));
			}
		}
	}

	bool Tilemap::Write(const rapidjson::Value& value) const {

		return false;
	}

	bool Tilemap::Read(const rapidjson::Value& value) {
		JSON_READ(value, numTilesX);
		JSON_READ(value, numTilesY);
		JSON_READ(value, start);
		JSON_READ(value, size);
		JSON_READ(value, tileNames);
		JSON_READ(value, tiles);

		return true;
	}
}