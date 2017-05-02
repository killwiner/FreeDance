#include "shader.h"

namespace shader {

Shader::Shader(const QString &vertexSource, const QString &fragmentSource, rendering::Render *render) :
    vertexID(0), fragmentID(0), programID(0),
    vertexSource_(vertexSource), fragmentSource_(fragmentSource),
    render_(render)
{}

Shader::~Shader() {}

quint32 Shader::getProgramID() const {
    return programID;
}

void Shader::load() {

    try {
        //compile les sources shader vertex
        buildShader(vertexID, GL_VERTEX_SHADER, vertexSource_);

        //compile les sources shader fragments
        buildShader(vertexID, GL_FRAGMENT_SHADER, fragmentSource_);
    }
    catch (const char& strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
}

void Shader::buildShader(quint32 &shader, GLenum type, const QString &file_name) {

    try {
        shader = render_->CreateShader(type);
        if(!shader)
            throw "(shader.cpp) error, bad type of shader";
    }
    catch (const char& strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }

    try {
        LoadFile(file_name);
    }
    catch (const char& strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }

    render_->ShaderSource(Source, shader);
    render_->CompileShader(shader);
    control(shader);
}

void Shader::control(const quint32 &shader) {

    // Vérification de la compilation
    int buildError = 0;
    render_->GetShaderiv(shader, GL_COMPILE_STATUS, &buildError);

    try {

        if(buildError != GL_TRUE) {
            int lengthMessage = 0;
            render_->GetShaderiv(shader, GL_INFO_LOG_LENGTH, &lengthMessage);
            char *message = new char[lengthMessage];

            // Récupération de l'erreur
            render_->GetShaderInfoLog(shader, lengthMessage, message);
            throw message;

            delete[] message;
        }
    }
    catch (const char& strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
}

void Shader::LoadFile(const QString &file_name) {

    QString Line;

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
    catch (const char& strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
}
}
