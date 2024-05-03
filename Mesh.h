#pragma once

#include "VAO.h"


#include"EBO.h"
#include"Texture.h"


#define _USE_MATH_DEFINES
#include <math.h>

class Mesh
{
public:
	enum MeshShape
	{
		SPHERE,
		CUBE
	};

    static std::vector<Vertex> createSphereVertices(int numLatitudes, int numLongitudes) {
        std::vector<Vertex> vertices;
        for (int i = 0; i <= numLatitudes; i++) {
            float theta = M_PI * i / numLatitudes;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);

            for (int j = 0; j <= numLongitudes; j++) {
                float phi = 2 * M_PI * j / numLongitudes;
                float sinPhi = sin(phi);
                float cosPhi = cos(phi);

                glm::vec3 position = glm::vec3(cosPhi * sinTheta, sinPhi * sinTheta, cosTheta);
                vertices.push_back(Vertex{ position });
            }
        }
        return vertices;
    }

    static std::vector<GLuint> createSphereIndices(int numLatitudes, int numLongitudes) {
        std::vector<GLuint> indices;
        for (int i = 0; i < numLatitudes; i++) {
            for (int j = 0; j < numLongitudes; j++) {
                int first = (i * (numLongitudes + 1)) + j;
                int second = first + numLongitudes + 1;

                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);

                indices.push_back(second);
                indices.push_back(second + 1);
                indices.push_back(first + 1);
            }
        }
        return indices;
    }

	std::vector <Vertex> mVertices;
	std::vector <GLuint> mIndices;
	std::vector <Texture> mTextures;
	// Store VAO in public so it can be used in the Draw function
	Vao mVao;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
	explicit Mesh(MeshShape shape);

	// Draws the mesh
	void draw(std::shared_ptr<Shader> shader);
};
