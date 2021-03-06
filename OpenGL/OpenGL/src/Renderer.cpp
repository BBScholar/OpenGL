#include "Renderer.h"

#include "ErrorManager.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"



Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}


void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}


