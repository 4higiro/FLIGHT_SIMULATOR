#ifndef LOADER
#define LOADER

#include "engine.hpp"

namespace engine
{
    void processMesh(aiMesh* mesh, const aiScene* scene, Mesh* output)
    {
        std::vector<Vertex> vertices;   // Извлеченные вершины
        std::vector<Uint> indices;      // Извлеченные индексы

        // Обработка координат вершин, нормалей, цвета и текстурных координат
        for (Size i = 0Ull; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            
            vertex.position.x = mesh->mVertices[i].x;
            vertex.position.y = mesh->mVertices[i].y;
            vertex.position.z = mesh->mVertices[i].z;

            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;

            if (mesh->mTextureCoords[0])
            {
                vertex.texel.x = mesh->mTextureCoords[0][i].x;
                vertex.texel.y = mesh->mTextureCoords[0][i].y;
            }

            vertices.push_back(vertex);
        }

        // Обработка индексов
        for (Size i = 0Ull; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (Size j = 0Ull; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        // Обработка материала
        if (mesh->mMaterialIndex >= 0)
        {
            
        }

        output->set(vertices, indices);
    }

    void processNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes)
    {
        // Обработка всех мешей (если они есть) у выбранного узла
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            Mesh* instance = new Mesh;
            processMesh(mesh, scene, instance);
            meshes.push_back(instance);
        }
        // То же самое для всех дочерних узлов
        for (unsigned int i = 0; i < node->mNumChildren; i++)
            processNode(node->mChildren[i], scene, meshes);
    }

    void loadModel(std::string path, std::vector<Mesh*>& meshes)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }

        processNode(scene->mRootNode, scene, meshes);
    }
}

#endif
