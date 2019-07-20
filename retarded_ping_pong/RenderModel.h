#pragma once

#include <string>
#include <GLIncludes.h>
#include <openvr.h>

class RenderModel
{

public:
	RenderModel(const std::string& sRenderModelName);
	~RenderModel();

	bool BInit(const vr::RenderModel_t& vrModel, const vr::RenderModel_TextureMap_t& vrDiffuseTexture);
	void Cleanup();
	void Draw();
	const std::string& GetName() const { return m_sModelName; }

private:
	GLuint m_glVertBuffer;
	GLuint m_glIndexBuffer;
	GLuint m_glVertArray;
	GLuint m_glTexture;
	GLsizei m_unVertexCount;
	std::string m_sModelName;

};

