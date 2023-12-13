#include "Map.h"


void CMap::init()
{
	
	vector<float> playerColors;

	for (int i = 0; i < 8; i++)
	{
		playerColors.push_back(1.f);
		playerColors.push_back(0.f);
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

	/*color = glm::vec3(153/255, 204,1);
	vector<float> pv;
	vector< GLubyte>pi;
	in.readObj("fbxToObj/Scene.obj",);

	for (int i{}; i < in.out_vertices.size(); ++i) {
		pv.push_back(in.out_vertices[i].x);
		pv.push_back(in.out_vertices[i].y);
		pv.push_back(in.out_vertices[i].z);
	}

	for (int i{}; i < in.out_normals.size(); ++i)
		normals.push_back(in.out_normals[i]);

	for (int i{}; i < in.vertexIndices.size(); ++i)
		pi.push_back(in.vertexIndices[i]);

	initModel(pv, playerColors, pi);
	initBuf();*/
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
}


void CMap::render(GLuint shaderProgramID)
{
	glBindVertexArray(vao);

	model = glm::mat4(1.f);
	model = glm::translate(model, pos);
	model = glm::scale(model, scale);

	drawS(shaderProgramID);
}

void CMap::drawS(GLuint shaderProgramID)
{
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color.r, color.g, color.b);

	//if (crashOnce) 
	/*{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}*/

	glDrawArrays(GL_TRIANGLES, 0, 5000);

	glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), 1, 0, 0);
	glDrawArrays(GL_TRIANGLES, 5000, vertices.size());

	//if (crashOnce)
		//glDisable(GL_BLEND);
}




