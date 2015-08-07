#include <vect.h>

Vect<float> operator/(Vect<float> const& a, float const& s) {

    Vect<float> c = a;

    if(s == 0.0) {
        c.x = 0;
        c.y = 0;
        c.z = 0;
    }
    else {
        c.x = a.x / s;
        c.y = a.y / s;
        c.z = a.z / s;
    }
    return c;
}

Vect<int> operator+(Vect<int> const& a, Vect<int> const& b) {

    Vect<int> n(a.width, a.height, 0);
    Vect<int> c(a.x + b.x, a.y + b.y, a.z + b.z);

    if (c.x >= c.width || c.x < 0)
        return n;

    if (c.y >= c.height || c.y < 0)
        return n;

    return c;
}

Vect<float> operator+(Vect<float> const& a, Vect<float> const& b) {

    Vect<float> c(a.x + b.x, a.y + b.y, a.z + b.z);

    return c;
}

Vect<int> operator-(Vect<int> const& a, Vect<int> const& b) {

    Vect<int> n(a.width, a.height, 0);

    if (a.x < b.x)
        return n;

    if (a.y < b.y)
        return n;

    Vect<int> c(a.x - b.x, a.y - b.y, a.z - b.z);

    return c;
}

Vect<float> operator-(Vect<float> const& a, Vect<float> const& b) {

    Vect<float> c(a.x - b.x, a.y - b.y, a.z - b.z);

    return c;
}
