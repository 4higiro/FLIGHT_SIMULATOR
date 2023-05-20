#ifndef LOADER // Защита от повторного включения
#define LOADER

#include "engine.hpp" // Включение всех заголовочных файлов

// engine - пространство имен проекта

namespace engine
{
    // Класс загрузки модели
    class ModelLoader
    {
    private:
        // Извлечение данных о меше из структур данных assimp
        static void processMesh(aiMesh* mesh, const aiScene* scene, Mesh* output)
        {
            // mesh     - Меш из assimp
            // scene    - Сцена текущего меша
            // output   - Меш проекта

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

            // Заполнение меша извлеченными данными
            output->set(vertices, indices);
        }

        // Извлечение мешей из узла сцены
        static void processNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes)
        {
            // node     - текущий узел сцены 
            // scene    - сцена 
            // meshes   - результирующий массив мешей

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

        // Загрузка модели из файла в структуры assimp
        static void loadModel(std::string path, std::vector<Mesh*>& meshes)
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
    public:
        // Загрузка из файла и создание модели экземпляра
        static Model& loadFromFile(std::string path)
        {
            // path - путь к файлу модели
            std::vector<Mesh*> meshes;          // Массив мешей
            loadModel(path, meshes);            // Загрузка всех мешей
            Model* result = new Model(meshes);  // Создание экземпляра модели
            return *result;                     // Возврат собранной модели
        }
    };
}

#endif
