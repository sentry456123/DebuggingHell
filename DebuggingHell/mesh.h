#pragma once

#include "gl.h"
#include "uarray.h"

/*! @brief An object that handles vertices and indices.
 */
class Mesh
{
public:
	/*! @brief Creates a mesh with vertices and indices.
	 *
	 */
	Mesh(DynamicArray<float> vertices, DynamicArray<unsigned int> indices) noexcept;

	/*! @brief Create a mesh with a model.
	 *
	 */
	Mesh(const char* modelPath) noexcept; //TODO: Implement this function

	virtual ~Mesh(void) noexcept;
	void Bind(void) noexcept;
	void Draw(void) noexcept;

protected:
	DynamicArray<float> mVertices;
	DynamicArray<unsigned int> mIndices;
	unsigned int mVao;
	unsigned int mVbo;
	unsigned int mEbo;

};
