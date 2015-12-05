#ifndef EXPORT_MOTION_H
#define EXPORT_MOTION_H

#include <fstream>
#include <QString>
#include <string>
#include <iomanip>
#include <vector>
#include "vect.h"
#include "skeleton.h"

// write the motion in the file

class ExportMotion
{

public:
    explicit ExportMotion();
    void save(const QString &, const Skeleton &, const int &);

private:
    // write a new root in the file
    // écrit une nouvelle articulation dans le fichier
    void write_new_root(std::ofstream &, const std::string &, const Vect<float> &, bool const &, bool const &);
    // write the end of a root and the bloc
    // écrit la fermeture d'un noeud et du bloc qui va avec
    void write_close_root(std::ofstream &);
    // indent the bloc to imbricate a bloc inside another bloc
    // indentation d'un bloc pour respecter l'héritage
    int imbricate;
    // coordinate for the roots
    // coordonnées des noeuds
    std::vector< Vect< float > > vect_offset;
    // True : channel is offset and rotation
    // False : channel is only offset
    // True : channel comporte l'offset et la rotation
    // False : channel ne comporte que l'offset
    std::vector<bool> vect_channel;
};

#endif // EXPORT_MOTION_H
