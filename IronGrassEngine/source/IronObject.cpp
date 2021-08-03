#include "IronGrassEngine.h"
#include "IronObject.h"

IronObject::IronObject(const char* verticesFilePath,const char* indicesFilePath, GLenum usage)
{
	/*
	std::ifstream verticesFile, indicesFile;
	std::stringstream _verticesStream, _indicesStream;
	verticesFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	indicesFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//打开文件
		verticesFile.open(verticesFilePath);
		indicesFile.open(indicesFilePath);

		indicesFile >> indicesSize;
		verticesFile >> verticesSize;

		
		std::cout << "Object File Open" << std::endl;
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Object File Open Failed" << "\nVertices File Path  >" << verticesFilePath
			<< "\nIndices File Path  >" << indicesFilePath << std::endl << std::endl;
	}

	//获取顶点、三角形  (花了我五天)
	std::vector<float> vertices;
	float x, y, z;
	for (int i = 0; i < verticesSize; i++)
	{
		verticesFile >> x >> y >> z;
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
	}
	std::vector<int> indices;
	int nx, ny, nz;
	for (int i = 0; i < indicesSize; i++)
	{
		indicesFile >> nx >> ny >> nz;
		indices.push_back(nx);
		indices.push_back(ny);
		indices.push_back(nz);
	}

	indicesFile.close();
	verticesFile.close();
	*/


	//转换顶点
	
	//设置顶点
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);//第一次先绑定在设置
	 //VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices.data()), vertices.data(), usage);
	//EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices.data()), indices.data(), usage);
	//Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//解除绑定
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);


	
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
