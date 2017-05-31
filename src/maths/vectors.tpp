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

template <typename T_Scalar>
Vector<T_Scalar>::Vector(const components<T_Scalar> &comp, const QSPEspace &espace) : nil(false) {
    espace_ = QSPEspace(espace);
    set(comp_);
}

template <typename T_Scalar>
Vector<T_Scalar>::Vector(const T_Scalar &x, const T_Scalar &y, const T_Scalar &z, const QSPEspace &espace) : nil(false) {
    espace_ = QSPEspace(espace);
    set(x, y, z);
}

template <typename T_Scalar>
Vector<T_Scalar>::Vector(const Vector<T_Scalar> &v) {
    espace_ = v.get_espace();
    nil = v.isNull();
    v.get_comp(comp_);
}

template <typename T_Scalar>
Vector<T_Scalar>::Vector(const Vector<T_Scalar> &vx, const Vector<T_Scalar> &vy, const Vector<T_Scalar> &vz) {
    PVectorX = QSharedPointer< Vector<T_Scalar> >(new Vector<T_Scalar>(vx));
    PVectorY = QSharedPointer< Vector<T_Scalar> >(new Vector<T_Scalar>(vy));
    PVectorZ = QSharedPointer< Vector<T_Scalar> >(new Vector<T_Scalar>(vz));
}

template <typename T_Scalar>
Vector<T_Scalar>::Vector() {
}

template <typename T_Scalar>
Vector<T_Scalar>::~Vector() {
}

template <typename T_Scalar>
bool operator==(const Vector<T_Scalar>& vector_a, const Vector<T_Scalar>& vector_b) {

    // vérifie si les vecteurs sont tous deux nuls
    if((vector_a.isNull() == true) && (vector_b.isNull() == true))
        return true;

    // récupère les composantes des vecteurs
    components<T_Scalar> compA;
    components<T_Scalar> compB;
    vector_a.get_comp(compA);
    vector_b.get_comp(compB);

    // conversion des flottants/doubles ... en entiers pour effectuer une comparaison
    quint32 dif_x = COMP(compA.x, compB.x, vector_a.get_espace()->get_prec());
    quint32 dif_y = COMP(compA.y, compB.y, vector_a.get_espace()->get_prec());
    quint32 dif_z = COMP(compA.z, compB.z, vector_a.get_espace()->get_prec());

    // vérifie si les vecteurs non nuls sont identiques
    if (dif_x == 0 && dif_y == 0 && dif_z == 0)
        return true;
    else
        return false;
}

template <typename T_Scalar>
bool operator!=(Vector<T_Scalar> const& vector_a, Vector<T_Scalar> const& vector_b) {

    if (vector_a == vector_b)
        return false;
    else
        return true;
}

template <typename T_Scalar>
void Vector<T_Scalar>::operator+=(const Vector<T_Scalar>& vector) {

    components<T_Scalar> comp;
    vector.get_comp(comp);

    set(comp_.x + comp.x, comp_.y + comp.y, comp_.z + comp.z);
}

template <typename T_Scalar>
void Vector<T_Scalar>::operator-=(const Vector<T_Scalar>& vector) {

    components<T_Scalar> comp;
    vector.get_comp(comp);

    set(comp_.x - comp.x, comp_.y - comp.y, comp_.z - comp.z);
}

template <typename T_Scalar>
void Vector<T_Scalar>::operator*=(const T_Scalar& scalar) {

    set(comp_.x * scalar, comp_.y * scalar, comp_.z * scalar);
}

template <typename T_Scalar>
void Vector<T_Scalar>::operator/=(const T_Scalar& scalar) {

    if(!scalar) {
        this->nil = true;
        return;
    }

    set(comp_.x / scalar, comp_.y / scalar, comp_.z / scalar);
}

template <typename T_Scalar>
QSPEspace Vector<T_Scalar>::get_espace() const {
    return espace_;
}

template <typename T_Scalar>
void Vector<T_Scalar>::get_comp(components<T_Scalar> &comp) const {
    comp = comp_;
}

template <typename T_Scalar>
void Vector<T_Scalar>::get_comp(T_Scalar &x, T_Scalar &y, T_Scalar &z) const {
    x = comp_.x;
    y = comp_.y;
    z = comp_.z;
}

template <typename T_Scalar>
void Vector<T_Scalar>::get_comp(Vector<T_Scalar> &x, Vector<T_Scalar> &y, Vector<T_Scalar> &z) const {
    x = *PVectorX.data();
    y = *PVectorY.data();
    z = *PVectorZ.data();
}

template <typename T_Scalar>
void Vector<T_Scalar>::get_max(components<quint16> &size) const {
    espace_->get_max(size);
}


template <typename T_Scalar>
void Vector<T_Scalar>::set(const components<T_Scalar> &comp) {
    comp_ = comp;

}

template <typename T_Scalar>
void Vector<T_Scalar>::set(const T_Scalar &x, const T_Scalar &y, const T_Scalar &z) {

    comp_.x = x;
    comp_.y = y;
    comp_.z = z;
}

template <typename T_Scalar>
bool Vector<T_Scalar>::isNull() const {
    return nil;
}

template <typename T_Scalar>
void Vector<T_Scalar>::Null() {

    components<quint16> size;
    espace_->get_max(size);

    if(comp_.x > size.x || comp_.y > size.y || comp_.z > size.z)
        nil = true;
    if(comp_.x < 0 || comp_.y < 0 || comp_.z < 0)
        nil = true;
}

template <typename T_Scalar1, typename T_Scalar2>
Vector<T_Scalar1> operator/(Vector<T_Scalar1> const& a, T_Scalar2 const& s) {

    components<T_Scalar1> comp;
    Vector<T_Scalar1> c(-1.0f, -1.0f, -1.0f, a.get_espace());

    if(!s)
        c.Null();
    else {
        a.get_comp(comp);
        c.set(comp.x/s, comp.y/s, comp.z/s);
    }
    return c;
}

template <typename T_Scalar>
Vector<T_Scalar> operator*(T_Scalar const& s, Vector<T_Scalar> const& vector) {

    Vector<T_Scalar> r = vector;

    components<T_Scalar> comp;
    vector.get_comp(comp);

    r.set(comp.x * s, comp.y * s, comp.z * s);

    return r;
}

template <typename T_Scalar>
Vector<T_Scalar> operator*(Vector<T_Scalar> const& vector, T_Scalar const& s) {

    Vector<T_Scalar> r = vector;

    components<T_Scalar> comp;
    vector.get_comp(comp);

    r.set(comp.x * s, comp.y * s, comp.z * s);

    return r;
}

template <typename T_Scalar>
T_Scalar operator*(Vector<T_Scalar> const& vector_a, Vector<T_Scalar> const& vector_b) {

    if(vector_a.isNull() == true || vector_b.isNull() == true)
        return 0;

    components<T_Scalar> compA;
    components<T_Scalar> compB;

    vector_a.get_comp(compA);
    vector_b.get_comp(compB);

    return compA.x * compB.x + compA.y * compB.y + compA.z * compB.z;
}

template <typename T_Scalar>
Vector<T_Scalar> operator+(Vector<T_Scalar> const& vector_a, Vector<T_Scalar> const& vector_b) {

    if(vector_a.isNull() == true || vector_b.isNull() == true) {
        Vector<T_Scalar> nil(-1.0, -1.0, -1.0, vector_a.get_espace());
        nil.Null();
        return nil;
    }

    components<T_Scalar> compA;
    components<T_Scalar> compB;

    vector_a.get_comp(compA);
    vector_b.get_comp(compB);

    Vector<T_Scalar> r(0, 0, 0, vector_a.get_espace());
    r.set(compA.x + compB.x, compA.y + compB.y, compA.z + compB.z);
    return r;

}

template <typename T_Scalar>
Vector<T_Scalar> operator-(Vector<T_Scalar> const& vector_a, Vector<T_Scalar> const& vector_b) {

    if(vector_a.isNull() == true || vector_b.isNull() == true) {
        Vector<T_Scalar> nil(-1.0, -1.0, -1.0, vector_a.get_espace());
        nil.Null();
        return nil;
    }

    components<T_Scalar> compA;
    components<T_Scalar> compB;

    vector_a.get_comp(compA);
    vector_b.get_comp(compB);

    Vector<T_Scalar> r(0, 0, 0, vector_a.get_espace());
    r.set(compA.x - compB.x, compA.y - compB.y, compA.z - compB.z);
    return r;
}

template <typename T_Scalar>
Vector<T_Scalar> operator^(const Vector<T_Scalar>& vector_a, const Vector<T_Scalar>& vector_b) {

    if(vector_a.isNull() == true || vector_b.isNull() == true) {
        Vector<T_Scalar> nil(-1.0, -1.0, -1.0, vector_a.get_espace());
        nil.Null();
        return nil;
    }

    components<T_Scalar> compA;
    components<T_Scalar> compB;

    vector_a.get_comp(compA);
    vector_b.get_comp(compB);

    Vector<T_Scalar> r(0, 0, 0, vector_a.get_espace());
    r.set(compA.y * compB.z - compA.z * compB.y, compA.z * compB.x - compA.x * compB.z, compA.x * compB.y - compA.y * compB.x);
    return r;
}
