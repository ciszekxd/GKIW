#include "ModelCtrl.h"

ModelCtrl::ModelCtrl(float x, float y, float z) {
    this->ModelPosition = glm::mat4(1.0f);
    this->ModelPosition = glm::translate(this->ModelPosition, glm::vec3(x, y, z));
}

void ModelCtrl::loadModel(const std::string& path) {
    Assimp::Importer importer;
    this->path = path;
    const aiScene* scene = importer.ReadFile(this->path,
        aiProcess_Triangulate |
        //     aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs);
    //aiProcess_CalcTangentSpace);
    processNode(scene->mRootNode, scene);
    setupForLLD(1.0f, 0.0f, 0.0f, 1.0f);
}
void ModelCtrl::processNode(aiNode* node, const aiScene* scene)
{
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        //meshes.push_back(processMesh(mesh, scene));
        this->meshes.push_back(processMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene);
    }

}
Mesh ModelCtrl::processMesh(aiMesh* mesh, const aiScene* scene)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            //vector.x = mesh->mTangents[i].x;
            //vector.y = mesh->mTangents[i].y;
            //vector.z = mesh->mTangents[i].z;
           // vertex.Tangent = vector;
            // bitangent
            //vector.x = mesh->mBitangents[i].x;
         //   vector.y = mesh->mBitangents[i].y;
         //   vector.z = mesh->mBitangents[i].z;
           /// vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    //// 1. diffuse maps
    //std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    //textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    //// 2. specular maps
    //std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    //textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    //// 3. normal maps
    //std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    //textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    //// 4. height maps
    //std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    //textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    std::cout << "mesh set" << std::endl;
    return Mesh(vertices, indices, textures);
}

void ModelCtrl::setupForLLD(float colR, float colG, float colB, float colAlpha) {
    //z wektora siatek iterujemy po kolejnych siatkach
    for (int i = 0; i < this->meshes.size(); i++) {
        Mesh temp = this->meshes[i];
        //dla ka¿dej siatki iterujemy po wszystkich wierzcho³kach wchodz¹cych w jej sk³ad
        for (int k = 0; k < temp.vertices.size(); k++) {
            //przepisujemy koordynaty z ka¿dego wierzcho³ka
            for (int j = 0; j < 3; j++)
            {
                this->verticesLLD.push_back(temp.vertices[k].Position[j]);
                this->normalsLLD.push_back(temp.vertices[k].Normal[j]);
            }
            this->verticesLLD.push_back(1.0f);
            this->normalsLLD.push_back(0.0f);
            //przepisujemy koordynaty tekstur
            for (int j = 0; j < 2; j++) {
                this->texCordsLLD.push_back(temp.vertices[k].TexCoords[j]);
            }
        }
    }
    this->vertexCount = verticesLLD.size() / 4;
    for (int i = 0; i < vertexCount; i++) {
        this->colorLLD.push_back(colR);
        this->colorLLD.push_back(colG);
        this->colorLLD.push_back(colB);
        this->colorLLD.push_back(colAlpha);
    }
    std::cout << "reload done" << std::endl;
}

void ModelCtrl::drawLLD() {

    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(this->ModelPosition));

    float* vertexLLD = &this->verticesLLD[0];
    float* normalLLD = &this->normalsLLD[0];
    float* texCordLLD = &this->texCordsLLD[0];
    float* colorLLD = &this->colorLLD[0];


    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    //std::cout << "1"<< std::endl;

    glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertexLLD);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    //std::cout << "2" << std::endl;

    //if (!smooth) glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normals);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normalLLD);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    //std::cout << "3" << std::endl;

    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, texCordLLD);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    //std::cout << "4" << std::endl;

    glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, colorLLD);

    //std::cout << "5" << std::endl;


    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}

float* ModelCtrl::getVerticesLLD()
{
    return &this->verticesLLD[0];
}

float* ModelCtrl::getNormalsLLD()
{
    return &this->normalsLLD[0];
}

int ModelCtrl::getVertexCount()
{
    return this->vertexCount;
}

glm::mat4 ModelCtrl::getModelPosition()
{
    return this->ModelPosition;
}



void ModelCtrl::Draw() {
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(this->ModelPosition));
    for (int j = 0; j < this->meshes.size(); j++) {
        this->meshes[j].Draw();
    }
}
//std::vector<Texture> ModelCtrl::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName){
//    std::vector<Texture> textures;
//    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
//    {
//        aiString str;
//        mat->GetTexture(type, i, &str);
//        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
//        bool skip = false;
//        for (unsigned int j = 0; j < textures_loaded.size(); j++)
//        {
//            if (std::strcmp(this->textures_loaded[j].path.data(), str.C_Str()) == 0)
//            {
//                textures.push_back(textures_loaded[j]);
//                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
//                break;
//            }
//        }
//        if (!skip)
//        {   // if texture hasn't been loaded already, load it
//            Texture texture;
//            texture.id = TextureFromFile(str.C_Str(),0);
//            texture.type = typeName;
//            texture.path = str.C_Str();
//            textures.push_back(texture);
//            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
//        }
//    }
//    return textures;
//}
//
//unsigned int ModelCtrl::TextureFromFile(const char* path, bool gamma)
//{
//    std::string filename = std::string(path);
//    //filename = directory + '/' + filename;
//
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
//            format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        stbi_image_free(data);
//    }
//
//    return textureID;
//}
////
