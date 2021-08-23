#include "IronGrassEngine.h"
#include "IronObject.h"

IronObject::IronObject(bool useEBO)
{
	uEBO = useEBO;
	//初始化buffer
	glGenVertexArrays(1, &VAO);
}

IronObject::~IronObject()
{
	glDeleteVertexArrays(1, &VAO);
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
	for (int i = 0; i < sizeof(v)+1; i++)
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
	clearIndices();
	for (int j = 0; j < sizeof(i) + 1; j++)
	{
		indices.push_back(i[j]);
	}
}

void IronObject::clearIndices()
{
	indices.clear();
}

void IronObject::SetUpVertexAttributes()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
}

void IronObject::done(GLenum usage)
{
	if (uEBO)
		doneWith(usage, vertices.data(), vertices.size() * sizeof(float), indices.data(), indices.size() * sizeof(int)); //使用EBO的情况
	else
		doneWith(usage, vertices.data(), vertices.size() * sizeof(float)); //不使用EBO的情况
}

void IronObject::doneWith(GLenum usage, float vertices[], __int64 size)
{
	std::cout << "this";
	unsigned int VBO;

	uEBO = false;

	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	//VBO
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
	

	SetUpVertexAttributes();

	//解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//清理
	glDeleteBuffers(1, &VBO);
}

void IronObject::doneWith(GLenum usage, float vertices[], __int64 verticesSize, int indices[], __int64 indicesSize)
{
	unsigned int VBO, EBO;

	uEBO = true;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, usage);

	//EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, usage);

	SetUpVertexAttributes();


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//清理
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void IronObject::draw()
{
	glBindVertexArray(VAO);
	if (uEBO)
		glDrawElements(GL_TRIANGLES, 
			6, //消除C4267
			GL_UNSIGNED_INT,
			0
		);
	else
		glDrawArrays(
			GL_TRIANGLES, 
			0,
			static_cast<GLsizei>(vertices.size()) //消除C4267
		);
	glBindVertexArray(0);
}