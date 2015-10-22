#ifndef EXPORT_MOTION_H
#define EXPORT_MOTION_H

#include <fstream>
#include <QString>
#include <string>
#include <iomanip>
#include <vector>
#include "vect.h"
#include "skeleton.h"

class ExportMotion
{

public:
    explicit ExportMotion();
    void save(const QString &, const Skeleton &, const int &);

private:
    void new_root( std::ofstream &, std::string const, const Vect<float> &, bool const &, bool const &);
    void close_root(std::ofstream &file);
    int imbricate;
    std::vector< Vect< float > > vect_offset;
    //std::vector< Vect< float > > vect_rot;
    std::vector<bool> vect_channel;
};

#endif // EXPORT_MOTION_H
