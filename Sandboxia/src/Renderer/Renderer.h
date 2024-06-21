#pragma once
#include "../Mesh/Mesher.h"
#include "../World/ClientChunk.h"

class Renderer {
public:
	Renderer() = default;
	~Renderer() = default;

	/// <summary>
	/// Renders a chunk mesh. chunk.Mesh must exist
	/// </summary>
	/// <param name="chunk"></param>
	/// <returns>True, if chunk was rendered. False, otherwise</returns>
	bool RenderChunk(ClientChunk& chunk);
private:
};

inline Renderer GRenderer;