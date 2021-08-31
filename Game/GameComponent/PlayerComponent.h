#pragma once
#include "Math/Component/Component.h"
#include "Framework/EventSystem.h"

class PlayerComponent : public rj::Component {
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<PlayerComponent>(*this); }
	
	virtual ~PlayerComponent();
	
	void Create() override;
	virtual void Update() override;

	virtual void OnCollisionEnter(const rj::Event& event);
	virtual void OnCollisionExit(const rj::Event& event);

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

public:
	float speed{ 0 };

private:
	std::list<rj::Actor*> contacts;
};