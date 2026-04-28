#include "Object3D.h"
#include "EventManager.h"
#include <algorithm>
Object3D::Object3D()
{
    objectId = idCounter++;

    vertexList =
    {
        {{ -0.5,  0.5 , 0, 1 },{1,0,0,1}}, //vertice superior izquierda de triangulo
        {{  0.5,  0.5 , 0, 1 },{1,0,0,1}}, //vertice superior derecha de triangulo
        {{ -0.5, -0.5 , 0, 1 },{1,1,0,1}}, // vertice inferior izquierda
        {{  0.5, -0.5 , 0, 1 },{0,0,1,1}}// vertice inferior derecha
    };

    indexList = { 0,1,2 , 2,1,3 };

    prg = new Shader();
    prg->addShaderProgram("data/shader.vertex");
    prg->addShaderProgram("data/shader.fragment");
    prg->linkProgram();

    computeNormals();

}

Object3D::Object3D(string frsModel) {
    objectId = idCounter++;

    this->frsModel = frsModel;
    loadFromFile();
}

matrix4x4f Object3D::computeModelMatrix()
{
    matrix4x4f model = make_scale(escalado.x, escalado.y, escalado.z)*
        make_traslate(posicion.x, posicion.y, posicion.z) *
        make_rotate(posicion.x, posicion.y, posicion.z);
    return model;
}

// void Object3D::moveObject(double timeStep)
// {
//     float speed = 0;
//     if (EventManager::keyMap[GLFW_KEY_A])
//         posicion.x -= speed * timeStep;
//
//     if (EventManager::keyMap[GLFW_KEY_D])
//         posicion.x += speed * timeStep;
//     if (EventManager::keyMap[GLFW_KEY_Q]) {
//         this->mat->usaTextura = false;
//     }
//     if (EventManager::keyMap[GLFW_KEY_E]) {
//         this->mat->usaTextura = true;
//     }
//
// }

void Object3D::computeNormals()
{
    //reset de normales de vertices
    for (auto& v : vertexList) {
        v.normal = { 0,0,0,0 };
    }

    //por cada cara
    auto it = indexList.begin();
    while (it != indexList.end()){
        int v1 = *it; it++;
        int v2 = *it; it++;
        int v3 = *it; it++;

        vec4float arista1 = normalize(vertexList[v2].posicion - vertexList[v1].posicion);
        vec4float arista3 = normalize(vertexList[v3].posicion - vertexList[v1].posicion);
        //calcular normal
        vec4float normal = cross(arista1, arista3);
        //interpolar con normales de vertices compartidos por cara

        vertexList[v1].normal = vertexList[v1].normal + normal;
        vertexList[v2].normal = vertexList[v2].normal + normal;
        vertexList[v3].normal = vertexList[v3].normal + normal;
    }


    //normalizacion de normales de vertices
    for (auto& v : vertexList) {
        v.normal = normalize(v.normal);
    }
}

#include "System.h"
void Ship::moveObject(double timeStep) {
    float speed = 3.0f;
    if (EventManager::keyMap[GLFW_KEY_A])
        posicion.x -= speed * timeStep;

    if (EventManager::keyMap[GLFW_KEY_D])
        posicion.x += speed * timeStep;

    if (EventManager::keyMap[GLFW_KEY_SPACE]) {
        //Añadir bala
        Bullet* b = new Bullet("./data/ship.frs");
        b->posicion = this->posicion;
        b->rotacion.z = 90;
        b->escalado = {0.25, 0.25,0.25,1.0f};
        b->direccion = {0,1,0,0};
        System::render->addObject(b);
    }

}

void Bullet::moveObject(double timeStep) {
    float speed = 5.0f;
    this->posicion = posicion + direccion * speed * timeStep;

    if (posicion.y > 10) {
        this->shouldDelete = true;
    }

    //Si hay colision borrar
}

void Enemy::moveObject(double timeStep) {

    float speed = 1.0f;
    this->posicion.x += speed * timeStep;

    if (posicion.x > 5) {
        this->posicion.x = -5;
    }

    // if (std::rand()%180 == 0) { //Si debo crear bala
    //     //Añadir bala
    //     Bullet* b = new Bullet("./data/ship.frs");
    //     b->posicion = this->posicion;
    //     b->rotacion.z = 90;
    //     b->escalado = {0.25, 0.25,0.25,1.0f};
    //     b->direccion = {0,-1,0,0};
    //     System::render->addObject(b);
    // }

}


void Object3D::loadFromFile()
{
    typedef enum {
        vertices,faces,normals,colors,textureCoords, done
    }dataTypesReading;
    string textureFile;
    string vertexShader;
    string fragmentShader;

    istringstream lineReader;
    std::ifstream f(frsModel);
    if (!f.is_open()) {
        cout << "ERROR: no se pudo abrir el fichero FRS: " << frsModel << "\n";
        return;
    }

    dataTypesReading mode = vertices;
    string line = "";

    auto skipComments = [&]() {
        line.clear();
        while (std::getline(f >> std::ws, line)) {
            if (line.empty()) {
                continue;
            }
            const unsigned char first = static_cast<unsigned char>(line[0]);
            if (first == 35 || first == 59 || first == 0xE2 || first == 0x80) {
                continue;
            }
            break;
        }
        lineReader = istringstream(line);
    };

    auto readMultipleData = [&]() {
        vector<float> data;
        std::replace(line.begin(), line.end(), ',', ' ');
        std::replace(line.begin(), line.end(), 'f', ' ');
        std::replace(line.begin(), line.end(), 'F', ' ');
        lineReader = istringstream(line);

        float d = 0.0f;
        while (lineReader >> d) {
            data.push_back(d);
        }
        return data;
    };

    do {
       switch (mode)
            {
            case vertices: {
                //leer numVertices
                int numVertex = 0;
                skipComments();
                lineReader >> numVertex;
                vertexList.resize(numVertex);
                for (int i = 0;i < numVertex;i++) {
                    skipComments();
                    lineReader = istringstream(line);
                    lineReader >> vertexList[i].posicion.x;
                    lineReader >> vertexList[i].posicion.y;
                    lineReader >> vertexList[i].posicion.z;
                    vertexList[i].posicion.w = 1.0f;
                }
                mode = faces;
            }break;
            case faces: {
                //leer numVertices
                int numFaces = 0;
                skipComments();
                lineReader >> numFaces;
                indexList.resize(numFaces * 3);
                for (int i = 0;i < numFaces;i++) {
                    skipComments();
                    lineReader = istringstream(line);
                    lineReader >> indexList[i * 3] >> indexList[i * 3 + 1] >> indexList[i * 3 + 2];
                }
                mode = colors;
            }break;

            case colors: {
                //leer numVertices
                int numColors = 0;
                skipComments();
                lineReader >> numColors;
                for (int i = 0;i < numColors;i++) {
                    skipComments();
                    auto data = readMultipleData();
                    int numVertexIds = data.size() - 4;
                    vec4float color = make_vec4float(
                        data[numVertexIds],
                        data[numVertexIds + 1],
                        data[numVertexIds + 2],
                        data[numVertexIds + 3]
                    );
                    for (int j = 0;j < numVertexIds;j++) {
                        vertexList[data[j]].color = color;
                    }
                }
                mode = normals;
            }break;


            case normals: {
                //leer numVertices
                int numNormals = 0;
                skipComments();
                lineReader >> numNormals;
                for (int i = 0;i < numNormals;i++) {
                    skipComments();
                    auto data = readMultipleData();

                    int numVertexIds = data.size() - 4;
                    vec4float normal = make_vec4float(
                        data[numVertexIds],
                        data[numVertexIds + 1],
                        data[numVertexIds + 2],
                        data[numVertexIds + 3]
                    );
                    for (int j = 0;j < numVertexIds;j++) {
                        vertexList[data[j]].normal = normal;
                    }
                }
                mode = textureCoords;
            }break;

            case textureCoords: {
                //leer numVertices
                int numTC = 0;
                skipComments();
                lineReader >> numTC;
                for (int i = 0;i < numTC;i++) {
                    skipComments();
                    auto data = readMultipleData();
                    int numVertexIds = data.size() - 2;
                    float textureCoord[2] = {
                        data[numVertexIds],
                        data[numVertexIds + 1] };
                    for (int j = 0;j < numVertexIds;j++) {
                        vertexList[data[j]].texturaCoords.x = textureCoord[0];
                        vertexList[data[j]].texturaCoords.y = textureCoord[1];
                    }
                }
                skipComments();
                lineReader >> textureFile;
                skipComments();
                lineReader >> vertexShader;
                skipComments();
                lineReader >> fragmentShader;

                mode = done;
            }break;
        };

    } while (!f.eof()&&mode!=done); //Saltar comentarios iniciales

    if (vertexShader.empty()) {
        vertexShader = "data/shader.vertex";
    }
    if (fragmentShader.empty()) {
        fragmentShader = "data/shader.fragment";
    }

    prg = new Shader();
    prg->addShaderProgram(vertexShader);
    prg->addShaderProgram(fragmentShader);
    prg->linkProgram();
    this->mat->textura = new Texture(textureFile);
    mat->usaTextura = true;
}


