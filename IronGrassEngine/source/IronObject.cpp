#include "IronGrassEngine.h"
#include "IronObject.h"

IronObject::IronObject(bool useEBO)
{
	uEBO = useEBO;
	set = false;
	//初始化buffer
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	if (uEBO)
		glGenBuffers(1, &EBO);
	else
		EBO = 0;
}

IronObject::~IronObject()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void IronObject::addVertices(float x, float y, float z)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

void IronObject::addVertices(float pos[3])
{
	addVertices(pos[0], pos[1], pos[2]);
}

void IronObject::setVertices(float v[])
{
  	clearVertices();
	for (int i = 0; i < sizeof(v); i++)
	{
		vertices.push_back(v[i]);
	}
}

void IronObject::clearVertices()
{
	vertices.clear();
}

void IronObject::addIndices(int one, int two, int three)
{
	indices.push_back(one);
	indices.push_back(two);
	indices.push_back(three);
}

void IronObject::addIndices(int pos[3])
{
	addIndices(pos[0], pos[1], pos[2]);
}

void IronObject::setIndices(int i[])
{
}

void IronObject::clearIndices()
{
}

void IronObject::done(GLenum usage)
{
	//第一次先绑定在设置
	glBindVertexArray(VAO);

	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices.data()), vertices.data(), usage);

	//EBO
	if (uEBO) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices.data()), indices.data(), usage);
	}

	//Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	set = true;
}

void IronObject::draw()
{
	glBindVertexArray(VAO);
	/*
	if (uEBO)
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0,
			static_cast<GLsizei>(vertices.size()) //消除C4267
		);
	*/
	glDrawArrays(GL_TRIANGLES, 0, 9);
}