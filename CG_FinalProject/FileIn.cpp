#include "FileIn.h"

int CFileIn::readObj(const char* fileName)
{
	FILE* objFile;
	vector<vector<float>> tmp;
	vector<int> id;

	fopen_s(&objFile, fileName, "rb");

	if (NULL == objFile) {
		cout << "error" << endl;
		return false;
	}

	while (true) {

		char lineHeader[65535];

		int res = fscanf(objFile, "%s", lineHeader);
		if (EOF == res)
			break;

		if (not strcmp(lineHeader, "v")) {
			glm::vec3 vertex;
			fscanf(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertex.x /= 200.f;
			vertex.y /= 200.f;
			vertex.z /= 200.f;
			vertex.z += 0.8f;

			temp_vertices.push_back(vertex);
		}
		else if (not strcmp(lineHeader, "vn")) {
			glm::vec3 normal;
			fscanf(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (not strcmp(lineHeader, "f")) {

			float vertexIndex[4];
			vector<float>t;

			int matches = fscanf(objFile, "%f//%*f %f//%*f %f//%*f %f//%*f", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2], &vertexIndex[3]);

			if (3 == matches) {

				vertexIndices.push_back(vertexIndex[0] - 1);
				vertexIndices.push_back(vertexIndex[1] - 1);
				vertexIndices.push_back(vertexIndex[2] - 1);


				t.push_back(vertexIndex[0] - 1);
				t.push_back(vertexIndex[1] - 1);
				t.push_back(vertexIndex[2] - 1);
				id.push_back(3);

			}
			else if (4 == matches) {
				// 사각형의 경우
				vertexIndices.push_back(vertexIndex[0] - 1);
				vertexIndices.push_back(vertexIndex[1] - 1);
				vertexIndices.push_back(vertexIndex[2] - 1);

				vertexIndices.push_back(vertexIndex[0] - 1);
				vertexIndices.push_back(vertexIndex[2] - 1);
				vertexIndices.push_back(vertexIndex[3] - 1);


				t.push_back(vertexIndex[0] - 1);
				t.push_back(vertexIndex[1] - 1);
				t.push_back(vertexIndex[2] - 1);

				t.push_back(vertexIndex[0] - 1);
				t.push_back(vertexIndex[2] - 1);
				t.push_back(vertexIndex[3] - 1);
				id.push_back(6);
			}
			tmp.push_back(t);
		}
	}

	for (int i{}; i < tmp.size(); ++i) {
		for (int j{}; j < id[i]; ++j) {
			out_vertices.push_back(temp_vertices[tmp[i][j]]);
			out_normals.push_back(temp_normals[tmp[i][j]]);
		}
	}
}
