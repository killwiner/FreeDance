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

#include "functions.h"

using namespace std;

template <typename T_Scalar>
Vector<T_Scalar> cross_2Dxy(const Vector<T_Scalar> &vector_v_start, const Vector<T_Scalar> &vector_w_start, const Vector<T_Scalar> &vector_v_end, const Vector<T_Scalar> &vector_w_end) {

    qint16 prec = vector_v_start.get_espace()->get_prec();

    Vector<T_Scalar> nil(-1.0f, -1.0f, -1.0f, vector_v_start.get_espace());
    nil.Null();

    T_Scalar z;
    T_Scalar v_a, v_b;
    T_Scalar w_a, w_b;
    T_Scalar v_endX, v_endY;
    T_Scalar w_endX, w_endY;

    vector_v_start.get_comp(v_a, v_b, z);
    vector_w_start.get_comp(w_a, w_b, z);
    vector_v_end.get_comp(v_endX, v_endY, z);
    vector_w_end.get_comp(w_endX, w_endY, z);

    T_Scalar v_x = v_endX - v_a;
    T_Scalar v_y = v_endY - v_b;
    T_Scalar w_x = w_endX - w_a;
    T_Scalar w_y = w_endY - w_b;

    quint8 t = 0;
    if(!COMP(v_x, 0, prec))
        ++t;
    if(!COMP(v_y, 0, prec))
        ++t;
    if(!COMP(w_x, 0, prec))
        ++t;
    if(!COMP(w_y, 0, prec))
        ++t;

    // On teste toutes les possibilitées où des composantes v_x, v_y, w_x, w_y seraient égales à zéro.
    switch(t) {

    case(4) :
        // 0 & 0 & 0 & 0
        // cas de deux points
        if(!COMP(v_a, w_a, prec) && !COMP(v_b, w_b, prec))
            return Vector<T_Scalar>(v_a, v_b, 0, vector_v_start.get_espace());
        return nil;

    case(3) :

        // X & 0 & 0 & 0
        if(COMP(v_x, 0, prec) && !COMP(v_b, w_b, prec))
            return Vector<T_Scalar>(w_a, w_b, 0, vector_v_start.get_espace());
        // 0 & X & 0 & 0
        if(COMP(v_y, 0, prec) && !COMP(v_a, w_a, prec))
            return Vector<T_Scalar>(w_a, w_b, 0, vector_v_start.get_espace());
        // 0 & 0 & X & 0
        if(COMP(w_x, 0, prec) && !COMP(w_b, v_b, prec))
            return Vector<T_Scalar>(v_a, v_b, 0, vector_v_start.get_espace());
        // 0 & 0 & 0 & X
        if(COMP(w_y, 0, prec) && !COMP(w_a, v_a, prec))
            return Vector<T_Scalar>(v_a, v_b, 0, vector_v_start.get_espace());
        return nil;
        break;

    case(2) :
        // X & 0 & X & 0
        // 0 & X & 0 & X
        if(!COMP(v_x, 0, prec) && !COMP(w_x, 0, prec))
            return nil;
        if(!COMP(v_y, 0, prec) && !COMP(w_y, 0, prec))
            return nil;

        // X & X & 0 & 0
        // 0 & 0 & X & X
        // X & 0 & 0 & X
        // 0 & X & X & 0
        if(!COMP(v_a, w_a, prec) && !COMP(v_b, w_b, prec))
            return Vector<T_Scalar>(v_a, v_b, 0, vector_v_start.get_espace());

        return nil;

        break;

        // X & X & X & 0
        // X & X & 0 & X
        // X & 0 & X & X
        // 0 & X & X & X
    case(1) :
        if(!COMP(v_x, 0, prec)) {
            T_Scalar phi = (v_a - w_a) / w_x;
            T_Scalar gamma = (w_b + phi * w_y - v_b) / v_y;

            return Vector<T_Scalar>(v_a, v_b + gamma * v_y, 0, vector_v_start.get_espace());
        }
        if(!COMP(v_y, 0, prec)) {
            T_Scalar phi = (v_b - w_b) / w_y;
            T_Scalar gamma = (w_a + phi * w_x - v_a) / v_x;

            return Vector<T_Scalar>(v_b, v_a + gamma * v_x, 0, vector_v_start.get_espace());
        }
        if(!COMP(w_x, 0, prec)) {
            T_Scalar phi = (w_a - v_a) / v_x;
            T_Scalar gamma = (v_b + phi * v_y - w_b) / w_y;

            return Vector<T_Scalar>(w_a, w_b + gamma * w_y, 0, vector_v_start.get_espace());
        }
        if(!COMP(w_y, 0, prec)) {
            T_Scalar phi = (w_b - v_b) / v_y;
            T_Scalar gamma = (v_a + phi * v_x - w_a) / w_x;

            return Vector<T_Scalar>(w_b, w_a + gamma * w_x, 0, vector_v_start.get_espace());
        }
        break;

        // X & X & X & X
    case(0) :
        if(!COMP(w_x * v_y - w_y * v_x, 0, prec))
            return nil;
        T_Scalar gamma = (w_b * w_x - v_b * w_x + w_y * v_a - w_y * v_a) / (w_x * v_y - w_y * v_x);
        return Vector<T_Scalar>(v_a + gamma * v_x, v_b + gamma * v_y, 0, vector_v_start.get_espace());
        break;

    }
    return nil;
}

template <typename T_Scalar>
T_Scalar normal(const Vector<T_Scalar> &vector) {

    T_Scalar x, y, z;
    vector.get_comp(x, y, z);

    if(typeid(double) == typeid(T_Scalar))
        return (T_Scalar)sqrt((double)(x * x + y * y + z * z));

    if(typeid(float) == typeid(T_Scalar))
        return (T_Scalar)sqrtf((float)(x * x + y * y + z * z));

    return (T_Scalar)sqrtl((long double)(x * x + y * y + z * z));
}

template <typename T_Scalar>
T_Scalar lenght(const Vector<T_Scalar> &vector_a, const Vector<T_Scalar> &vector_b) {

    T_Scalar ax, ay, az;
    T_Scalar bx, by, bz;
    vector_a.get_comp(ax, ay, az);
    vector_b.get_comp(bx, by, bz);

    return maths::normal(Vector<T_Scalar>(bx - ax, by - ay, bz - az, vector_a.get_espace()));

}

template <typename T_Scalar>
Vector<T_Scalar> prod_mat_3x3_3x1(const Vector<T_Scalar> &matrix, const Vector<T_Scalar> &vector) {

    T_Scalar v_x, v_y, v_z;
    vector.get_comp(v_x, v_y, v_z);

    Vector<T_Scalar> col_1, col_2, col_3;
    matrix.get_comp(col_1, col_2, col_3);

    T_Scalar m11, m12, m13;
    T_Scalar m21, m22, m23;
    T_Scalar m31, m32, m33;
    col_1.get_comp(m11, m21, m31);
    col_2.get_comp(m12, m22, m32);
    col_3.get_comp(m13, m23, m33);

    return Vector<T_Scalar>(m11 * v_x + m12 * v_y + m13 * v_z, m21 * v_x + m22 * v_y + m23 * v_z, m31 * v_x + m32 * v_y + m33 * v_z, vector.get_espace());
}


template <typename T_Scalar>
T_Scalar angle_vectors(Vector<T_Scalar> const &a, Vector<T_Scalar> const &b) {

    T_Scalar na_nb = maths::normal(a) * maths::normal(b);

    if(!COMP(na_nb, 0, a.get_espace()->get_prec()))
        return 0;

    T_Scalar a_x, a_y, a_z;
    T_Scalar b_x, b_y, b_z;

    a.get_comp(a_x, a_y, a_z);
    b.get_comp(b_x, b_y, b_z);

    if(typeid(float) == typeid(T_Scalar))
        return (float)std::abs(acosf((a_x * b_x + a_y * b_y + a_z * b_z) / na_nb));
    if(typeid(double) == typeid(T_Scalar))
        return (double)std::abs(acos((a_x * b_x + a_y * b_y + a_z * b_z) / na_nb));
    return (long double)std::abs(acosl((a_x * b_x + a_y * b_y + a_z * b_z) / na_nb));

}

template <typename T_Scalar>
Vector<T_Scalar> _3D_to_2D_xy(const Vector<T_Scalar> &v) {

    T_Scalar x, y, z;
    v.get_comp(x, y, z);

    return Vector<T_Scalar>(x, y, 0, v.get_espace());
}

template <typename T_Scalar>
Vector<T_Scalar> quick_rotation(const Vector<T_Scalar> &vector, const quint16 &number_of_steps) {

    T_Scalar x, y, z;
    vector.get_comp(x, y, z);

    quint16 n = number_of_steps % 4;

    switch(n) {
    case 0:

        std::swap(x, y);
        x = -x;
        break;

    case 1:
        x = -x;
        y = -y;
        break;

    default:
        std::swap(x, y);
        y = -y;
    }
    return Vector<T_Scalar>(x, y, z, vector.get_espace());
}

template <typename T_Scalar>
Vector<T_Scalar> angle_rotation(const Vector<T_Scalar> &vector, const T_Scalar &angle) {

    T_Scalar n = maths::normal(vector);
    T_Scalar x, y, z;
    vector.get_comp(x, y, z);

    if(typeid(float) == typeid(T_Scalar)) {
        float alphaf = acosf(x / n);
        return Vector<T_Scalar>(n * cosf(angle + alphaf), n * sinf(angle + alphaf), .0, vector.get_espace());
    }
    if(typeid(double) == typeid(T_Scalar)) {
        double alpha = acos(x / n);
        return Vector<T_Scalar>(n * cos(angle + alpha), n * sin(angle + alpha), .0, vector.get_espace());
    }

    double alphal = acosl(x / n);
    return Vector<T_Scalar>(n * cosl(angle + alphal), n * sinl(angle + alphal), .0, vector.get_espace());
}
