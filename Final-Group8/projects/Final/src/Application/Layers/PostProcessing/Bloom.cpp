#include "Bloom.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/Material.h"

Bloom::Bloom() :
	PostProcessingLayer::Effect(),
	_bloomSpread(0.2f),
	_bloomIntensity(2.0f)
{
	Name = "Bloom Effect";
	_format = RenderTargetType::ColorRgb8;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },
		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/bloom.glsl" }
	});
}

Bloom::~Bloom() = default;

void Bloom::Apply(const Framebuffer::Sptr & gBuffer)
{
	_shader->Bind();
	_shader->SetUniform("u_spread", _bloomSpread);
	_shader->SetUniform("u_intens", -1.0f * _bloomIntensity);
}

void Bloom::RenderImGui()
{
	LABEL_LEFT(ImGui::SliderFloat, "Bloom Spread", &_bloomSpread, -10.0f, 10.0f);
	LABEL_LEFT(ImGui::SliderFloat, "Bloom Intensity", &_bloomIntensity, -10.0f, 10.0f);
}

Bloom::Sptr Bloom::FromJson(const nlohmann::json & data)
{
	Bloom::Sptr result = std::make_shared<Bloom>();
	result->Enabled = JsonGet(data, "enabled", true);
	return result;
}

nlohmann::json Bloom::ToJson() const
{
	return { };
}
