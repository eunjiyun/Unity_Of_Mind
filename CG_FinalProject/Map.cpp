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

	//color = glm::vec3(153/255, 204,1);
	vector<float> pv;
	vector< GLubyte>pi;
	in.readObj("fbxToObj/Scene.obj");
	float max_abs_coord;
	for (int i{}; i < in.out_vertices.size(); ++i) {
		pv.push_back(in.out_vertices[i].x);
		pv.push_back(in.out_vertices[i].y);
		pv.push_back(in.out_vertices[i].z);

		// Á¤±ÔÈ­µÈ UV ÁÂÇ¥ °è»ê
		in.out_uvs[i].x = (in.out_vertices[i].x + 3.f) * 0.5f;  // [-1, 1] -> [0, 1]
		in.out_uvs[i].y = (in.out_vertices[i].y + 3.f) * 0.5f;  // [-1, 1] -> [0, 1]
		uvs.push_back(in.out_uvs[i]);

		//// Assuming in.out_vertices[i] represents a 3D vertex
		//max_abs_coord = std::max({ std::abs(in.out_vertices[i].x), std::abs(in.out_vertices[i].y), std::abs(in.out_vertices[i].z) });

		////// Normalize X, Y, and Z coordinates
		////in.out_uvs[i].x = (in.out_vertices[i].x + max_abs_coord) / (2.0f * max_abs_coord);
		////in.out_uvs[i].y = (in.out_vertices[i].y + max_abs_coord) / (2.0f * max_abs_coord);
		////uvs.push_back(in.out_uvs[i]);
	}

	//for (int i{}; i < in.out_vertices.size(); ++i) {
	//	// Normalize X, Y, and Z coordinates
	//	in.out_uvs[i].x = (in.out_vertices[i].x + max_abs_coord) / (2.0f * max_abs_coord);
	//	in.out_uvs[i].y = (in.out_vertices[i].y + max_abs_coord) / (2.0f * max_abs_coord);
	//	uvs.push_back(in.out_uvs[i]);
	//}

	for (int i{}; i < in.out_normals.size(); ++i)
		normals.push_back(in.out_normals[i]);

	for (int i{}; i < in.vertexIndices.size(); ++i)
		pi.push_back(in.vertexIndices[i]);

	/*for (int i{}; i < in.out_uvs.size(); ++i)
		uvs.push_back(in.out_uvs[i]);*/

	initModel(pv, playerColors, pi);
	initBuf();
	initTexture();
}
void CMap::initBuf()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/*vector<float>tv;
	for (const auto& v : vertices) {
		tv.push_back(v / 1000.f);
	}*/

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &tv[0], GL_STATIC_DRAW);
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
	//model = glm::translate(model, pos);
	//scale = glm::vec3(1 / 2, 1 / 2, 1 /2);
	//model = glm::scale(model, scale);
	//model = glm::scale(model, vec3(0.001f, 0.001f, 0.001f));

	glBindTexture(GL_TEXTURE_2D, texId);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	//glm::mat4 modelMatrix = glm::mat4(1.0f);
	//modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));

	drawS(shaderProgramID);
}

void CMap::drawS(GLuint shaderProgramID)
{
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	//glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color.r, color.g, color.b);

	//if (crashOnce) 
	/*{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}*/
	glBindTexture(GL_TEXTURE_2D, texId);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	//glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), 1, 0, 0);
	//glDrawArrays(GL_TRIANGLES, 5000, vertices.size());

	//if (crashOnce)
		//glDisable(GL_BLEND);



	/*glUseProgram(ID);

	model = mat4(1.0);
	model = translate(model, pos);
	model = glm::scale(model, scale);

	glUniformMatrix4fv(glGetUniformLocation(ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(vao);

	glBindTexture(GL_TEXTURE_2D, texId);
	glDrawArrays(GL_TRIANGLES, 0, vert.size());*/
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
	data = stbi_load("texture/texture_main.png", &width, &height, &nrChannels, 0);//texture_main
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}





