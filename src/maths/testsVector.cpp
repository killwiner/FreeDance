#ifdef TESTS

#include "testsVector.h"
#include <iostream>

namespace maths {

TestsVector::TestsVector() {

    loadFile(FILE_DATA);

}

void TestsVector::getComp()
{
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création du vecteur
    Vector<float> vecteur(5.4f, 2.2f, 8.6f, espace);

    // obention des composantes du vecteur
    components<float> comp;
    vecteur.get_comp(comp);

    // résultats attendus
    QCOMPARE(comp.x, 5.4f);
    QCOMPARE(comp.y, 2.2f);
    QCOMPARE(comp.z, 8.6f);

}

void TestsVector::getMax()
{
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 300, 400, 1000));

    // création du vecteur
    Vector<float> vecteur(5.4f, 2.2f, 8.6f, espace);

    // obention des bornes du vecteur
    components<quint16> comp;
    vecteur.get_max(comp);

    // résultats attendus
    QCOMPARE(comp.x, (quint16)200);
    QCOMPARE(comp.y, (quint16)300);
    QCOMPARE(comp.z, (quint16)400);

}

void TestsVector::comparaison_equivalence_de_deux_vecteurs() {

    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création de deux vecteurs différents internes
    Vector<float> va(6.5, 4.3, 5.6, espace);
    Vector<float> vb(5.4, 6.7, 5.5, espace);

    // création de deux vecteurs identiques
    Vector<float> vc(3.3, 5.4, 5.3, espace);
    Vector<float> vd(3.3, 5.4, 5.3, espace);

    // création de deux vecteurs différents externes
    Vector<float> ve(204.5, 33.5, 21.4, espace);
    Vector<float> vf(1.4, 3.0, 302.3, espace);

    // prend en compte les vecteur en dehors de l'espace euclidien
    ve.Null();
    vf.Null();

    // vérifie l'opérateur ==
    QVERIFY((va == vb) == false);
    QVERIFY(vc == vd);
    QVERIFY(ve == vf);

}

void TestsVector::comparaison_difference_de_deux_vecteurs() {

    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création de deux vecteurs différents internes
    Vector<float> va(6.5, 4.3, 5.6, espace);
    Vector<float> vb(5.4, 6.7, 5.5, espace);

    // création de deux vecteurs différents externes
    Vector<float> vc(410.4, 300.5, 404.5, espace);
    Vector<float> vd(450.4, 202.5, 103.5, espace);

    // création de deux vecteurs identiques
    Vector<float> ve(3.5, 4.2, 5.9, espace);
    Vector<float> vf(3.5, 4.2, 5.9, espace);

    // prend en compte les vecteur en dehors de l'espace euclidien
    vc.Null();
    vd.Null();

    // vérifie l'opérateur !=
    QVERIFY(va != vb);
    QVERIFY((vc != vd) == false);
    QVERIFY((ve != vf) == false);
}

void TestsVector::division_du_vecteur_par_un_scalaire() {

    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création du vecteur
    Vector<float> vecteur(9.9, 12, 15.3, espace);

    // création du scalaire
    float scalar = 3.0f;

    // création du résultat attendu
    Vector<float> vector_expected(3.3, 4.0, 5.1, espace);

    // teste la division du vecteur par un scalaire non nul
    QVERIFY((Vector<float>(vecteur / scalar)) == vector_expected);

    // teste la division par zéro, doit renvoyer un vecteur null
    QCOMPARE((vector_expected/0).isNull(), true);
}

void TestsVector::produit_d_un_vecteur_par_un_scalaire() {

    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création du vecteur
    Vector<float> vector(9.0, 10.1, .3, espace);

    // création du scalaire
    float scalar = 2.0f;

    // création du résultat attendu
    Vector<float> vector_expected(18.0, 20.2, .6, espace);

    // teste l'opération vecteur * scalaire
    QVERIFY(vector * scalar == vector_expected);

    // teste l'opération scalaire * vecteur
    QVERIFY(scalar * vector == vector_expected);
}

void TestsVector::produit_scalaire() {

    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création des vecteurs
    Vector<float> vector_a(6.5, 4.3, 5.6, espace);
    Vector<float> vector_b(5.4, 6.7, 5.5, espace);

    // création du résultat attendu
    float expected_scalar = 94.71;

    // teste l'opération vecteur * vecteur
    QVERIFY(COMP(vector_a * vector_b, expected_scalar, vector_a.get_espace()->get_prec()) == (quint32)0);
}

void TestsVector::somme_de_deux_vecteurs()
{

    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création des vecteurs
    Vector<float> vector_a(6.5, 4.3, 5.6, espace);
    Vector<float> vector_b(5.4, 6.7, 5.5, espace);

    // création du résultat attendu
    Vector<float> expected_vector(11.9,11.0,11.1, espace);

    // teste l'opération vecteur + vecteur
    QVERIFY((vector_a + vector_b) == expected_vector);
}

void TestsVector::soustraction_de_deux_vecteurs()
{

    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création des vecteurs
    Vector<float> vector_a(6.5, 4.3, 5.6, espace);
    Vector<float> vector_b(5.4, 6.7, 5.5, espace);

    // création du résultat attendu
    Vector<float> expected_vector(1.1, -2.4, .1, espace);

    // teste l'opération vecteur - vecteur
    QVERIFY((vector_a - vector_b) == expected_vector);
}

void TestsVector::produit_vectoriel()
{

    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création des vecteurs
    Vector<float> vector_a(3.5, 1.1, 6.5, espace);
    Vector<float> vector_b(2.1, 3.1, 4.0, espace);

    // création du résultat attendu
    Vector<float> expected_vector(-15.75, -.35, 8.54, espace);

    // teste l'opération vecteur ^ vecteur
    QVERIFY((vector_a ^ vector_b) == expected_vector);
}


void TestsVector::somme_dudit_vecteur_avec_un_autre_vecteur()
{
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création des vecteurs
    Vector<float> vector_a(6.0, 4.3, 5.6, espace);
    Vector<float> vector_b(6.0, 6.7, 5.5, espace);

    // création du résultat attendu
    Vector<float> expected_vector(12.0, 11.0, 11.1, espace);

    // teste l'opération +=
    vector_a += vector_b;
    QVERIFY( vector_a == expected_vector);
}

void TestsVector::soustraction_dudit_vecteur_avec_un_autre_vecteur()
{
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création des vecteurs
    Vector<float> vector_a(6.0, 4.3, 5.6, espace);
    Vector<float> vector_b(6.0, 6.7, 5.5, espace);

    // création du résultat attendu
    Vector<float> expected_vector(.0, -2.4, .1, espace);

    // teste l'opération -=
    vector_a -= vector_b;
    QVERIFY(vector_a == expected_vector);
}

void TestsVector::produit_dudit_vecteur_avec_un_scalaire()
{
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création du vecteur
    Vector<float> vector_a(9.0, 10.1, .3, espace);

    // création du scalaire
    float scalar = 2.0f;

    // création du résultat attendu
    Vector<float> expected_vector(18.0, 20.2, .6, espace);

    // teste l'opération *=
    vector_a *= scalar;
    QVERIFY(vector_a == expected_vector);
}

void TestsVector::division_dudit_vecteur_par_un_scalaire()
{
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création du vecteur
    Vector<float> vector_a(9.9, 12, 15.3, espace);

    // création du scalaire
    float scalar = 3.0f;

    // création du résultat attendu
    Vector<float> expected_vector(3.3, 4.0, 5.1, espace);

    // teste l'opération /=
    vector_a /= scalar;

    QVERIFY(vector_a == expected_vector);

    // teste la division par zéro, doit renvoyer le vecteur null
    vector_a /= 0;
    QVERIFY(vector_a == expected_vector);
}

void TestsVector::intersection_de_deux_vecteurs()
{
    // lecture à partir du fichier data, on saute la première ligne
    readFile(2);

    // création des bornes
    QSPEspace espace = QSPEspace(new Espace((++data.at(1))->toInt(), (++data.at(1))->toInt(), (++data.at(1))->toInt(), (++data.at(1))->toInt()));

    // on teste 9 cas d'intersections
    for(int i = 0; i <9; ++i) {

        readFile(3);

        // création des vecteurs
        Vector<float> vector_a1((++data.at(0))->toFloat(), (++data.at(0))->toFloat(), .0f, espace);
        Vector<float> vector_a2((++data.at(0))->toFloat(), (++data.at(0))->toFloat(), .0f, espace);

        Vector<float> vector_b1((++data.at(1))->toFloat(), (++data.at(1))->toFloat(), .0f, espace);
        Vector<float> vector_b2((++data.at(1))->toFloat(), (++data.at(1))->toFloat(), .0f, espace);

        // création du résultat attendu
        Vector<float> expected_vector((++data.at(2))->toFloat(), (++data.at(2))->toFloat(), .0f, espace);

        // détermine si le vecteur doit être nul
        expected_vector.Null();

        Vector<float> cr = maths::cross_2Dxy(vector_a1, vector_b1, vector_a2, vector_b2); 

        // teste d'obtenir le vecteur intersection
        QVERIFY(maths::cross_2Dxy(vector_a1, vector_b1, vector_a2, vector_b2) == expected_vector);
    }
}

void TestsVector::normale_d_un_vecteur()
{
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création du vecteur
    Vector<float> vector_a(6.5, 4.3, 5.6, espace);

    // création du résultat
    float expected_scalar = 9.5969;

    // teste le calcul de la normale du vecteur en fonction de la précision spécifiée
    QCOMPARE(COMP(maths::normal(vector_a), expected_scalar, espace->get_prec()), (int)0);
}

void TestsVector::distance_entre_deux_vecteurs()
{
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création des vecteurs
    Vector<float> vector_a(10.0, 12.0, 14.0, espace);
    Vector<float> vector_b(3.0, 2.0, 4.0, espace);

    // création du résultat
    float expected_scalar = 15.7797;

    // teste d'obtenir la distance entre deux vecteurs
    QCOMPARE(COMP(maths::lenght(vector_a, vector_b), expected_scalar, espace->get_prec()), (int)0);

}

void TestsVector::produit_de_deux_matrices_3x3_3x1()
{
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création des vecteurs pour la première matrice
    Vector<float> vector_col_1(5.2, 3.3, 4.1, espace);
    Vector<float> vector_col_2(2.2, 2.3, 4.0, espace);
    Vector<float> vector_col_3(1.0, .0, 1.1, espace);

    // création de la première matrice
    Vector<float> matrice1(vector_col_1, vector_col_2, vector_col_3);

    // création de la seconde matrice
    Vector<float> matrice2(4.2, 3.3, 1.2, espace);

    // création du vecteur résultat
    Vector<float> expected_vector(30.3, 21.45, 31.74, espace);

    // teste le produit des deux matrices
    QVERIFY(maths::prod_mat_3x3_3x1(matrice1, matrice2) == expected_vector);

}

void TestsVector::angle_entre_deux_vecteurs()
{
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

        // création des vecteurs
    Vector<float> vector_a(2.7, 1.0, 3.3, espace);
    Vector<float> vector_b(-3.0, -1.0, 1.1, espace);

    // création du résultat
    float expected_scalar = 1.9531;

    // teste le calcul de l'angle
    QCOMPARE(maths::angle_vectors(vector_a, vector_b), expected_scalar);
}

void TestsVector::projection_du_vecteur_sur_XY()
{
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création du vecteur
    Vector<float> vector_a(2.7, 1.0, 3.3, espace);

    // création du résultat attendu
    Vector<float> expected_vector(2.7, 1.0, .0, espace);

    // teste la projection
    QVERIFY(maths::_3D_to_2D_xy(vector_a) == expected_vector);
}

void TestsVector::quickRotation()
{
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création du vecteur
    Vector<float> vector(2.3, 5.5, 4.0, espace);

    // création du nombre de pas (PI/2 pour chaque pas)
    qint16 pas = 6;

    // création du résultat attendu
    Vector<float> expected_vector(-2.3, -5.5, 4.0, espace);

    // teste la rotation
    QVERIFY(maths::quick_rotation(vector, pas) == expected_vector);
}

void TestsVector::angleRotation() {
    // création des bornes
    QSPEspace espace = QSPEspace(new Espace(200, 200, 200, 1000));

    // création du vecteur
    Vector<float> vector(.866, .5, .0, espace);

    // création du résultat attendu
    Vector<float> expected_vector(-.866, .5, .0, espace);

    // teste la rotation
    QVERIFY(maths::angle_rotation(vector, (float)(2*PI/3)) == expected_vector);

}

}

#endif // TESTS
