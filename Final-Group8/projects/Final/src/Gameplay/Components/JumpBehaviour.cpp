#include "Gameplay/Components/JumpBehaviour.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/InputEngine.h"
#include "Gameplay/Physics/RigidBody.h"
void JumpBehaviour::Awake()
{
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if (_body == nullptr) {
		IsEnabled = false;
	}
}

void JumpBehaviour::RenderImGui() {
	LABEL_LEFT(ImGui::DragFloat, "Impulse", &_impulse, 1.0f);
}

nlohmann::json JumpBehaviour::ToJson() const {
	return {
		{ "impulse", _impulse }
	};
}

JumpBehaviour::JumpBehaviour() :
	IComponent(),
	_impulse(10.0f)
{ }

JumpBehaviour::~JumpBehaviour() = default;

JumpBehaviour::Sptr JumpBehaviour::FromJson(const nlohmann::json& blob) {
	JumpBehaviour::Sptr result = std::make_shared<JumpBehaviour>();
	result->_impulse = blob["impulse"];
	return result;
}

void JumpBehaviour::Update(float deltaTime) {
	bool _A = InputEngine::IsKeyDown(GLFW_KEY_A);
	bool _D = InputEngine::IsKeyDown(GLFW_KEY_D);
	bool _E = InputEngine::IsKeyDown(GLFW_KEY_E);
	bool _Q = InputEngine::IsKeyDown(GLFW_KEY_Q);
	_body->GetGameObject()->SetRotation(glm::vec3(0.0f, 0.0f, -90.f));

	if (InputEngine::GetKeyState(GLFW_KEY_SPACE) == ButtonState::Pressed) {
		_body->ApplyImpulse(glm::vec3(0.0f, 0.0f, _impulse));

		Gameplay::IComponent::Sptr ptr = Panel.lock();
		if (ptr != nullptr) {
			ptr->IsEnabled = !ptr->IsEnabled;
		}
	}
	if (_D) {

		_body->SetLinearVelocity(glm::vec3(-5.0f, 0.f, _body->GetLinearVelocity().z));
		
	}
	if (_A) {
		_body->SetLinearVelocity(glm::vec3(5.0f, 0.f, _body->GetLinearVelocity().z));
		
	}
	if (_E) {
		
		GetGameObject()->GetScene()->FindObjectByName("ball")->Get<Gameplay::Physics::RigidBody>()->ApplyImpulse(glm::vec3(0.0f, -1.0f, 0.0f));
	 }



}

