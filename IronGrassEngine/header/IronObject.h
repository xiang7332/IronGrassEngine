#pragma once

class IronObject
{
private:
	unsigned int VAO;
	bool uEBO;
	std::vector<float> vertices;
	std::vector<int> indices;

private:
	void SetUpVertexAttributes();

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

	//done()无法使用时手动设置顶点(三角形位置)
	void doneWith(GLenum usage, float vertices[],__int64 size);
	void doneWith(GLenum usage, float vertices[], __int64 verticesSize, int indices[], __int64 indicesSize);

	void draw();
};
