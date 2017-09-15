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

#ifndef CIRCULARVECTOR_H
#define CIRCULARVECTOR_H

#include <vector>

namespace tools {

template <typename T_Obj>
class CircularVector : public std::vector<T_Obj>
{

public:
    CircularVector();
    CircularVector(const quint32 &size);
    void push_back(T_Obj obj);
    T_Obj &at(const qint32 &adr);
    quint32 length(const qint32 &adrA, const qint32 &adrB) const;
    void setSize(const quint32 &size);

private:
    quint32 size_, cursor;
};
}

#include "circularvector.tpp"

#endif // CIRCULARVECTOR_H
