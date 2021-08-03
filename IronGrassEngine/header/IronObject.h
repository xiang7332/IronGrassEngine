#pragma once
class IronObject
{
private:
	unsigned int VAO, VBO, EBO;
	std::vector<float[3]> vertices;
	std::vector<int[3]> indices;

public:
	IronObject(const char* verticesFilePath, const char* indicesFilePath, GLenum usage);
	~IronObject();

public:
	void draw();
	void addVertices(float x, float y, float z);
	void addIndices(float one, float two, float three);
};

