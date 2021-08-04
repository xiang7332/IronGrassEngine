#pragma once
class IronObject
{
private:
	unsigned int VAO, VBO, EBO;
	std::vector<std::vector<float>> vertices;
	std::vector<std::vector<int>> indices;

public:
	IronObject();
	~IronObject();

public:
	void draw();
	void addVertices(float x, float y, float z);
	void addVertices(float pos[3]);
	void addIndices(int one, int two, int three);
	void addIndices(int pos[3]);
	void done(GLenum usage);
};

