/*************************************************************************/
/* This file is part of Tron.                                            */
/*                                                                       */
/*  Tron is free software: you can redistribute it and/or modify         */
/*  it under the terms of the GNU General Public License as published by */
/*  the Free Software Foundation, either version 3 of the License, or    */
/*  (at your option) any later version.                                  */
/*                                                                       */
/*  Tron is distributed in the hope that it will be useful,              */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/*  GNU General Public License for more details.                         */
/*                                                                       */
/*  You should have received a copy of the GNU General Public License    */
/*  along with Tron.  If not, see <http://www.gnu.org/licenses/>.        */
/*************************************************************************/

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
    bool save(const QString &, const QSharedPointer<Skeleton> &, const int &);

private:
    void write_0_chan(std::ofstream &, int const &);
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
