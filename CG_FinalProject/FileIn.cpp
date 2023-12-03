#include "FileIn.h"


int CFileIn::loadObj(const char* fileName)
{
    FILE* objFile;

    fopen_s(&objFile, fileName, "rb");

    if (objFile == NULL){
        cout << "error" << endl;
        return false;
    }

    while (true){
        char lineHeader[65535];

        int res{ fscanf(objFile, "%s", lineHeader) };
        if (EOF==res)
            break;

        if (0==strcmp(lineHeader, "v") ){
            vec3 vertex;
            fscanf(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (0==strcmp(lineHeader, "vt") ){
            vec2 uv;
            fscanf(objFile, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if (0==strcmp(lineHeader, "vn") ){
            vec3 normal;
            fscanf(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (0==strcmp(lineHeader, "f") ) {
            string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches{ fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]) };
            if (9!=matches )
            {
                cout << "error" << endl;
                assert(false);
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }

        for (unsigned int i{}; i < vertexIndices.size(); ++i){
            unsigned int vertexIndex{ vertexIndices[i] };
            vec3 vertex{ temp_vertices[vertexIndex - 1] };
            out_vertices.push_back(vertex);
        }
        for (unsigned int i{}; i < uvIndices.size(); ++i){
            unsigned int uvIndex{ uvIndices[i] };
            vec2 uv{ temp_uvs[uvIndex - 1] };
            out_uvs.push_back(uv);
        }
        for (unsigned int i{}; i < normalIndices.size(); ++i){
            unsigned int normalIndex{ normalIndices[i] };
            vec3 normal{ temp_normals[normalIndex - 1] };
            out_normals.push_back(normal);
        }
    }
}
