#include "Mesh.h"



Mesh::Mesh(std::vector<Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures) : mVertices(vertices), mIndices(indices), mTextures(textures)
{
	mVao.bind();
	// Generates Vertex Buffer Object and links it to vertices
	Vbo VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	Ebo EBO(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	mVao.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	mVao.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	mVao.linkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	mVao.linkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	mVao.unbind();
	VBO.unbind();
	EBO.unbind();
}

Mesh::Mesh(MeshShape shape)
{
	switch (shape)
	{
	case CUBE:
		mVertices =
		{ //     COORDINATES     //
			Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},
			Vertex{glm::vec3(-1.0f, -1.0f, -1.0f)},
			Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
			Vertex{glm::vec3(1.0f, -1.0f,  1.0f)},
			Vertex{glm::vec3(-1.0f,  1.0f,  1.0f)},
			Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},
			Vertex{glm::vec3(1.0f,  1.0f, -1.0f)},
			Vertex{glm::vec3(1.0f,  1.0f,  1.0f)}
		};

		mIndices =
		{
			0, 1, 2,
			0, 2, 3,
			0, 4, 7,
			0, 7, 3,
			3, 7, 6,
			3, 6, 2,
			2, 6, 5,
			2, 5, 1,
			1, 5, 4,
			1, 4, 0,
			4, 5, 6,
			4, 6, 7
		};
		break;
	case SPHERE:
		mVertices = createSphereVertices(10, 10);
		mIndices = createSphereIndices(10, 10);
		break;
	}

	mVao.bind();
	// Generates Vertex Buffer Object and links it to vertices
	Vbo VBO(mVertices);
	// Generates Element Buffer Object and links it to indices
	Ebo EBO(mIndices);
	// Links VBO attributes such as coordinates and colors to VAO
	mVao.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	// Unbind all to prevent accidentally modifying them
	mVao.unbind();
	VBO.unbind();
	EBO.unbind();
}


void Mesh::draw(std::shared_ptr<Shader> shader)
{
	mVao.bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < mTextures.size(); i++)
	{
		std::string num;
		std::string type = mTextures[i].mType;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		mTextures[i].texUnit(shader, (type + num).c_str(), i);
		mTextures[i].bind();
	}
	

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	mVao.unbind();
}
