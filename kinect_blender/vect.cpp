#include <vect.h>

Vect<float> operator/(Vect<float> const& a, float const& s) {

    Vect<float> c = a;

    if(s == 0.0) {
        c.x = 0;
        c.y = 0;
    }
    else {
        c.x = a.x / s;
        c.y = a.y / s;
    }
    return c;
}

Vect<int> operator+(Vect<int> const& a, Vect<int> const& b) {

    Vect<int> n(a.width, a.height);
    Vect<int> c(a.x + b.x, a.y + b.y);

    if (c.x >= c.width || c.x < 0)
        return n;

    if (c.y >= c.height || c.y < 0)
        return n;

    return c;
}

Vect<float> operator+(Vect<float> const& a, Vect<float> const& b) {

    Vect<float> c(a.x + b.x, a.y + b.y);

    return c;
}

Vect<int> operator-(Vect<int> const& a, Vect<int> const& b) {

    Vect<int> n(a.width, a.height);

    if (a.x < b.x)
        return n;

    if (a.y < b.y)
        return n;

    Vect<int> c(a.x - b.x, a.y - b.y);

    return c;
}

Vect<float> operator-(Vect<float> const& a, Vect<float> const& b) {

    Vect<float> c(a.x - b.x, a.y - b.y);

    return c;
}
