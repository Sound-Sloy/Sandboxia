#include "Renderer.h"

bool Renderer::RenderChunk(ClientChunk& chunk) {
	if (!chunk.Mesh.IndexCount) {
		return false;
	}

	glBindVertexArray(chunk.Mesh.vaoId);
	glDrawElements(GL_TRIANGLES, chunk.Mesh.IndexCount, GL_UNSIGNED_INT, 0);
}