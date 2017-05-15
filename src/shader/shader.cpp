#include "shader.h"

namespace shader {

Shader::Shader(const QString &vertexSource, const QString &fragmentSource,
           const quint16 &framesPerSecond, const quint16 &interval_time):
    vertexID(0), fragmentID(0), programID(0),
    vertexSource_(vertexSource), fragmentSource_(fragmentSource),
    rendering::Render(framesPerSecond, interval_time)
{}

Shader::~Shader() {
    glDetachShader(programID, vertexID);
    glDetachShader(programID, fragmentID);
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
    glDeleteProgram(programID);
}

quint32 Shader::getProgramID() const {
    return programID;
}

void Shader::load() {

    try {
        //compile les sources shader vertex
        buildShader(vertexID, GL_VERTEX_SHADER, vertexSource_);
        controlBuild(vertexID);

        //compile les sources shader fragments
        buildShader(fragmentID, GL_FRAGMENT_SHADER, fragmentSource_);
        controlBuild(fragmentID);

        //création du programme
        programID = glCreateProgram();

        //association des shaders
        glAttachShader(programID, vertexID);
        glAttachShader(programID, fragmentID);

        // Verrouillage des entrées shader
        glBindAttribLocation(programID, 0, "position");
        glBindAttribLocation(programID, 1, "outColor");
        glBindAttribLocation(programID, 2, "texCoord");
        // Linkage du programme
        glLinkProgram(programID);
        controlLink();
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
}

void Shader::buildShader(quint32 &shader, GLenum type, const QString &file_name) {

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

    try {
        loadFile(file_name);
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
        glGetProgramiv(programID, GL_LINK_STATUS, &linkError);

        if(linkError != GL_TRUE) {
            int lengthMessage = 0;
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &lengthMessage);
            char message[512];

            //Récupération de l'erreur
            if(lengthMessage < 512 && lengthMessage > 0) {
                glGetProgramInfoLog(programID, lengthMessage, &lengthMessage, message);
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

void Shader::loadFile(const QString &file_name) {

    QString Line;
    Source = QString("");

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
}
}
