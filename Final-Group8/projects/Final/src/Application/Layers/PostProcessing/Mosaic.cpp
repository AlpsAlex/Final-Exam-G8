#include "Mosaic.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/Material.h"

Mosaic::Mosaic() :
	PostProcessingLayer::Effect(),
	_amount(512.0f)
{
	Name = "Mosaic Effect";
	_format = RenderTargetType::ColorRgb8;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },
		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/mosaic.glsl" }
	});  
} 

Mosaic::~Mosaic() = default;

void Mosaic::Apply(const Framebuffer::Sptr & gBuffer)
{
	_shader->Bind();
	_shader->SetUniform("u_amount", _amount);
}

void Mosaic::RenderImGui()
{
	LABEL_LEFT(ImGui::SliderFloat, "Mosaic Amount", &_amount, 0.0f, 1024.0f);
}

Mosaic::Sptr Mosaic::FromJson(const nlohmann::json & data)
{
	Mosaic::Sptr result = std::make_shared<Mosaic>();
	result->Enabled = JsonGet(data, "enabled", true);
	return result;
}

nlohmann::json Mosaic::ToJson() const
{
	return { };
}
