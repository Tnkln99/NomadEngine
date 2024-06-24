#include "Mesh.h"



Mesh::Mesh(std::vector<Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures) : IMesh(vertices, indices, textures)
{
	mVao.bind();
	// Generates Vertex Buffer Object and links it to vertices
	Vbo vbo{};
	vbo.init(vertices);
	// Generates Element Buffer Object and links it to indices
	Ebo ebo{};
	ebo.init(indices);
	// Links vbo attributes such as coordinates and colors to VAO
	mVao.linkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, mPosition));
	mVao.linkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));
	mVao.linkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, mColor));
	mVao.linkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, mTexUv));
	// Unbind all to prevent accidentally modifying them
	mVao.unbind();
	vbo.unbind();
	ebo.unbind();
}


void Mesh::draw(std::shared_ptr<Shader> shader, glm::mat4 modelMatrix)
{
	mVao.bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	if(!mTextures.empty())
	{
		glUniform1i(glGetUniformLocation(shader->mId, "haveTextures"), 1);
	}
	else
	{
		glUniform1i(glGetUniformLocation(shader->mId, "haveTextures"), 0);
	}

	for (unsigned int i = 0; i < mTextures.size(); i++)
	{
		//mTextures[i].bind();
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
