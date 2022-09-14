#include "mesh.h"

Mesh::Mesh(DynamicArray<float> vertices, DynamicArray<unsigned int> indices) noexcept
	:
	mVertices(vertices), mIndices(indices)
{
	// VAO
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	// EBO
	glGenBuffers(1, &mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.ByteSize(), mIndices.Data(), GL_STATIC_DRAW);

	// VBO
	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, mVertices.ByteSize(), vertices.Data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

Mesh::~Mesh(void) noexcept
{
	glDeleteVertexArrays(1, &mVao);
	glDeleteBuffers(1, &mVbo);
	glDeleteBuffers(1, &mEbo);
}

void Mesh::Bind(void) noexcept
{
	glBindVertexArray(mVao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
}

void Mesh::Draw(void) noexcept
{
	glDrawElements(GL_TRIANGLES, (int)mIndices.Size(), GL_UNSIGNED_INT, 0);
}
