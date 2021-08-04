#include "IronGrassEngine.h"
#include "IronObject.h"

IronObject::IronObject()
{
	//初始化buffer
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
}

IronObject::~IronObject()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void IronObject::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}

void IronObject::addVertices(float x, float y, float z)
{
	std::vector<float> thisLine;
	thisLine.push_back(x);
	thisLine.push_back(y);
	thisLine.push_back(z);

	vertices.push_back(thisLine);
}

void IronObject::addVertices(float pos[3])
{
	addVertices(pos[0], pos[1], pos[2]);
}

void IronObject::addIndices(int one, int two, int three)
{
	std::vector<int> thisLine;
	thisLine.push_back(one);
	thisLine.push_back(two);
	thisLine.push_back(three);

	indices.push_back(thisLine);
}

void IronObject::addIndices(int pos[3])
{
	addIndices(pos[0], pos[1], pos[2]);
}

void IronObject::done(GLenum usage)
{
	std::vector<float> allverctives;
	std::vector<int> allIndices;
	for (int i = 0; i < vertices.size(); i++)
		for (int j = 0; j <= 2; j++)
			allverctives.push_back(vertices[i][j]);
	for (int i = 0; i < indices.size(); i++)
		for (int j = 0; j <= 2; j++)
			allIndices.push_back(indices[i][j]);

	//第一次先绑定在设置
	glBindVertexArray(VAO);
	
	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(allverctives.data()), allverctives.data(), usage);
	//EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(allIndices.data()), allIndices.data(), usage);
	//Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
