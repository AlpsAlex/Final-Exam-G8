#pragma once
#include "Application/Layers/PostProcessingLayer.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Textures/Texture3D.h"

class Bloom : public PostProcessingLayer::Effect {
public:
	MAKE_PTRS(Bloom);

	Bloom();
	virtual ~Bloom();

	virtual void Apply(const Framebuffer::Sptr& gBuffer) override;
	virtual void RenderImGui() override;

	Bloom::Sptr FromJson(const nlohmann::json& data);
	virtual nlohmann::json ToJson() const override;

protected:
	ShaderProgram::Sptr _shader;

	float _bloomSpread;
	float _bloomIntensity;
};