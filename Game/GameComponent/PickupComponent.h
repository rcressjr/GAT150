#pragma once
#include "PlayerComponent.h"
#include "Framework/EventSystem.h"

class PickupComponent : public PlayerComponent {
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<PickupComponent>(*this); }

	virtual ~PickupComponent();

	void Create() override;
	void Update() override;

	void OnCollisionEnter(const rj::Event& event) override;
	void OnCollisionExit(const rj::Event& event) override;

	bool Write(const rapidjson::Value& value) const override;
	bool Read(const rapidjson::Value& value) override;

private:
	int coins{ 0 };
};