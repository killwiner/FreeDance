#include "shader.h"

namespace shader {

Shader::Shader(const quint16 &framesPerSecond, const quint16 &interval_time):
    rendering::Render(framesPerSecond, interval_time)
{}

Shader::~Shader() {

    std::vector<quint32>::iterator itV = VVertexID.begin();
    std::vector<quint32>::iterator itF = VFragmentID.begin();

    for(std::vector<quint32>::iterator itP = VProgramID.begin(); itP < VProgramID.end(); ++itP) {
        ++itV;
        ++itF;
        glDetachShader(*itP, *itV);
        glDetachShader(*itP, *itF);
        glDeleteProgram(*itP);
        glDeleteShader(*itV);
        glDeleteShader(*itF);
    }
}

void Shader::startShader() {
    glUseProgram(0);
}

bool Shader::useProgramID(const quint8 &id) {
    if(id >= VProgramID.end() - VProgramID.begin())
        return false;

    glUseProgram(VProgramID.at(id));
    return true;
}

quint32 Shader::getProgramID(const quint8 &id)
{
    if(id < VProgramID.end() - VProgramID.begin())
        return VProgramID.at(id);
    return 0;
}

void Shader::loadShader(const QString &file_name) {

    vertexSource_ = file_name + ".vp";
    fragmentSource_ = file_name + ".fp";

    VVertexID.push_back(0);
    VFragmentID.push_back(0);

    try {
            std::cout << VVertexID.size() << std::endl;
        //compile les sources shader vertex
        buildShader(VVertexID.back(), GL_VERTEX_SHADER, vertexSource_);
        controlBuild(VVertexID.back());

        //compile les sources shader fragments
        buildShader(VFragmentID.back(), GL_FRAGMENT_SHADER, fragmentSource_);
        controlBuild(VFragmentID.back());

        //création du programme
        VProgramID.push_back(glCreateProgram());

        //association des shaders
        glAttachShader(VProgramID.back(), VVertexID.back());
        glAttachShader(VProgramID.back(), VFragmentID.back());

        // Verrouillage des entrées shader
        glBindAttribLocation(VProgramID.back(), 0, "position");
        glBindAttribLocation(VProgramID.back(), 1, "texCoord");

        // Linkage du programme
        glLinkProgram(VProgramID.back());
        controlLink();

    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
}

void Shader::buildShader(quint32 &shader, GLenum type, const QString &file_name) {

    QString Source;
    // création du shader
    try {
        shader = glCreateShader(type);
        if(!shader)
            throw "(shader.cpp) error, bad type of shader";
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }

    // on charge le programme
    try {
        Source = loadFile(file_name);
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }

    // ne pas contactener les deux expressions car toStdString est temporaire
    std::string str = Source.toStdString();
    const char* pstr = str.c_str();

    glShaderSource(shader, 1, &pstr, 0);

    glCompileShader(shader);
}

void Shader::controlLink() {

    try {
        // Vérification du linkage
        qint32 linkError = 0;
        glGetProgramiv(VProgramID.back(), GL_LINK_STATUS, &linkError);

        if(linkError != GL_TRUE) {
            int lengthMessage = 0;
            glGetProgramiv(VProgramID.back(), GL_INFO_LOG_LENGTH, &lengthMessage);
            char message[512];

            //Récupération de l'erreur
            if(lengthMessage < 512 && lengthMessage > 0) {
                glGetProgramInfoLog(VProgramID.back(), lengthMessage, &lengthMessage, message);
                throw message;
            }
            throw "(shader.cpp) error control link without message";
        }
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
}
            
void Shader::controlBuild(const quint32 &shader) {

    try {

        // Vérification de la compilation
        qint32 buildError = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &buildError);

        if(buildError != GL_TRUE) {
            int lengthMessage = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &lengthMessage);
            char message[512];

            // Récupération de l'erreur
            if(lengthMessage < 512 && lengthMessage > 0) {
                glGetShaderInfoLog(shader, lengthMessage, &lengthMessage, message);
                throw message;
            }
            throw "(shader.cpp) error control build without message";
        }
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
}

QString Shader::loadFile(const QString &file_name) {

    QString Line;
    QString Source = QString("");

    try {
        QFile FileData(file_name);

        if (!FileData.open(QIODevice::ReadOnly | QIODevice::Text))
            throw "Ne peut lire le fichier data.";

        while (!FileData.atEnd()) {

            Line = FileData.readLine();
            Source += Line + '\n';

        }

        FileData.close();
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
    return Source;
}
}
