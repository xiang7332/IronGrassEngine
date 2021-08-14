#pragma once

class IronObject
{
private:
	unsigned int VAO, VBO, EBO;
	bool uEBO, set;
	std::vector<float> vertices;
	std::vector<int> indices;

public:
	IronObject(bool useEBO = false);
	~IronObject();

public:
	void addVertices(float x, float y, float z);
	void addVertices(float pos[3]);
	void setVertices(float vertices[]);
	void clearVertices();

	void addIndices(int one, int two, int three);
	void addIndices(int pos[3]);
	void setIndices(int indices[]);
	void clearIndices();

	void done(GLenum usage);
	void draw();
};
