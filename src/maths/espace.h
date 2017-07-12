/*************************************************************************/
/* This file is part of FreeDance.                                       */
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

#ifndef ESPACE_H
#define ESPACE_H

#include <QtGlobal>
#include <QSharedPointer>

#define QSPEspace QSharedPointer<Espace>
#define MQSPEspace QSharedPointer<maths::Espace>

template <typename T_Scalar>
struct components {
    T_Scalar x, y, z;
};

namespace maths {

class Espace
{
public:

    // constructor to define a limited vector space
    // constructeur pour déterminer un espace vectoriel définit
    explicit Espace(const quint16&, const quint16&, const quint16&, const qint32&);
    explicit Espace();
    ~Espace();

    // accesseurs
    void get_max(components<quint16> &size) const;
    qint16 get_prec() const;
private:

    //bornes de l'espace vectoriel
    components<quint16> size_;
    //précision des composantes sous forme de puissance de 10
    qint16 precision_;

};

}

#endif // ESPACE_H
