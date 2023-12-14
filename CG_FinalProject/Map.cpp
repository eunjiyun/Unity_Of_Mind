#include "Map.h"
#include "stb_image.h"

void CMap::init()
{
	
	vector<float> playerColors;

	for (int i = 0; i < 8; i++)
	{
		playerColors.push_back(1.f);
		playerColors.push_back(1.f);
		playerColors.push_back(0.f);
	}

	const vector<GLubyte> playerIndices = {
		// ¾Õ¸é
		4 , 5 , 7,
		7 , 6 , 4,
		// µÞ¸é
		1 , 0 , 3,
		0 , 2 , 3,
		// ¹Ù´Ú¸é
		1 , 5 , 4,
		4 , 0 , 1,
		// À­¸é
		3 , 2 , 6,
		6 , 7 , 3,
		// ¿À¸¥ÂÊ¸é
		1 , 3 , 7,
		7 , 5 , 1,
		// ¿ÞÂÊ¸é
		6 , 2 , 0,
		0 , 4 , 6,
	};

	vector<float> pv;
	vector< GLubyte>pi;
	in.readObj("object/Scene.obj");
	float max_abs_coord;
	for (int i{}; i < in.out_vertices.size(); ++i) {
		pv.push_back(in.out_vertices[i].x);
		pv.push_back(in.out_vertices[i].y);
		pv.push_back(in.out_vertices[i].z);

		// Á¤±ÔÈ­µÈ UV ÁÂÇ¥ °è»ê
		in.out_uvs[i].x = (in.out_vertices[i].x + 5.f) * 0.5f;  // [-1, 1] -> [0, 1]
		in.out_uvs[i].y = (in.out_vertices[i].y -1.f) * 0.5f;  // [-1, 1] -> [0, 1]
		
		uvs.push_back(in.out_uvs[i]);
	}



	for (int i{}; i < in.out_normals.size(); ++i)
		normals.push_back(in.out_normals[i]);

	for (int i{}; i < in.vertexIndices.size(); ++i)
		pi.push_back(in.vertexIndices[i]);

	initModel(pv, playerColors, pi);
	initBuf();
	initTexture();
}
void CMap::initBuf()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &normBo);
	glBindBuffer(GL_ARRAY_BUFFER, normBo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &texBo);
	glBindBuffer(GL_ARRAY_BUFFER, texBo);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
}


void CMap::render(GLuint shaderProgramID)
{
	glBindVertexArray(vao);

	model = glm::mat4(1.f);
	

	glBindTexture(GL_TEXTURE_2D, texId);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	drawS(shaderProgramID);
}

void CMap::drawS(GLuint shaderProgramID)
{
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	
	glBindTexture(GL_TEXTURE_2D, texId);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

}

void CMap::initTexture()
{
	glGenTextures(1, &texId);

	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data;

	glBindTexture(GL_TEXTURE_2D, texId);
	data = stbi_load("texture/map.png", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}





