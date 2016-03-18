#include "search_human.h"

using namespace std;

SearchHuman::SearchHuman(std::vector< cv::Mat > &vect_imgs_, cv::Mat &mat_frame_, int &green_color_, int &blue_color_) :
                         green_color(green_color_), blue_color(blue_color_), s(0), surface(0), vect_imgs(vect_imgs_),
                         mat_frame(mat_frame_), id_img(0) {
    // Les partitions sont représentées dans une matrice 2D par des identifiants
    // We find areas in a 2D matrix with identities
    partition = new std::vector<int>(WIDTH*HEIGHT, 0);
}

SearchHuman::~SearchHuman() {
    vector<int>().swap(*partition);
    delete partition;
}

// tous les points de l'ancienne partition prennent la valeur de l'identifiant de la nouvelle partition
// all points of the old area have the value of the identifier of the new area
void SearchHuman::replace(int const &a, int const &b) {
    for (int i = 0; i < WIDTH * HEIGHT; ++i)
        if (partition->at(i) == a)
            partition->at(i) = b;
}

int SearchHuman::at(int const &p) {
    return partition->at(p);
}

void SearchHuman::clear_partition() {
    // id_area contains all partition surfaces
    // id_area contient les surfaces des partitions
    std::vector<int>().swap(id_area);
    id_area.resize(0);
    //delete partition;
    //partition = new std::vector<int>(WIDTH*HEIGHT, 0);
    for(int ii = 0; ii < WIDTH*HEIGHT; ++ii)
        partition->at(ii) = 0;
}

void SearchHuman::unification() {
    for(int y = 0; y < HEIGHT; ++y)
        for(int x = 0; x < WIDTH; ++x) {

            if(partition->at(coord_gray(Vect<int>(x, y, 0))) == max - id_area.begin()) {

                // the human area is colored
                // La partition représentant l'humain est colorisé
                mat_frame.PIXEL_COLOR_RED(x, y) = 255;

                ++s;

                // réécrire le vecter partition
                // rewrite the vector partitions
                partition->at(coord_gray(Vect<int>(x, y, 0))) = 1;

                centroid.x += (long int)x;
                centroid.y += (long int)y;

            }
            else
                partition->at(coord_gray(Vect<int>(x, y, 0))) = 0;

        }
        centroid.x = centroid.x / s;
        centroid.y = centroid.y / s;
}

void SearchHuman::first_search() {
    // recherche les partitions avec les surfaces
    // search areas with surfaces
    search_partitions();

    // Recherche la plus grosse partition
    // Search the largest area
    // id_area is the vector with all partition's areas
    // id_area contient toutes les aires de toutes les partitions
    max = id_area.begin() + 1;
    for (std::vector<int>::iterator it = id_area.begin() + 1 ; it != id_area.end(); ++it)
        if (*it > *max)
            max = it;
    surface = (long int)*max;
}

// si la couleur du point se situe en dehors de la zone de filtrage
// after the filter, the color is out
bool SearchHuman::out_zone(Vect<int> const &v) {

    if (((uint8_t)vect_imgs[id_img].PIXEL_COLOR_BLUE_VECT(v) > green_color)
     || ((uint8_t)vect_imgs[id_img].PIXEL_COLOR_GREEN_VECT(v) < 255 - blue_color)) {
        // l'identifiant de la partition est donc 0
        // the id of the area si 0
        partition->at(coord_gray<int>(v)) = 0;
        // la surface de la zone noire augmente de 1
        // the surface of the black zone increase with 1
        id_area.at(0) +=1;
        return true;
    }
    return false;
}

void SearchHuman::search() {
    Vect<int> v;
    v.x = centroid.x;
    v.y = centroid.y;
    surface = 0;
    centroid.x = 0;
    centroid.y = 0;

    search_human(v);

    if(surface) {
        centroid.x = centroid.x / surface;
        centroid.y = centroid.y / surface;
    }
    else
        centroid.x = centroid.y = 0;

    ++id_img;
}

// we got a new identitiy for the new partition
// nouvel identifiant pour la nouvelle partition
void SearchHuman::new_id(Vect<int> const &v, int &id_partition) {
    id_partition += 1;
    partition->at(coord_gray<int>(v)) = id_partition;
    id_area.push_back(1);
}

void SearchHuman::search_partitions() {

    Vect<int> v;

    // identifiant des partitions
    // is for areas
    int id_partition = 0;

    //the first point starts with the id at 0;
    // le premier point obtient l'identifiant 0
    id_area.push_back(0);

    for(int y = 0; y < HEIGHT; ++y)
        for(int x = 0; x < WIDTH; ++x) {

            v.x = x;
            v.y = y;

            if(out_zone(v))
                continue;

            // nous tournons autour du point v pour le fusionner à une partition.
            // we turn around the same point v, and obtains a new id for a new area
            if(!fusion(v))
                new_id(v, id_partition);
        }
}

void SearchHuman::search_human(Vect<int> v) {

    // we scan the pixel do add it or not at the human area
    // nous scannons le pixel pour l'ajouter ou non à la partition intéressée
    int a0 = scan_pixel(v);
    // we turn around the pixel v
    // nous faisons le tour du pixel v
    int a1 = scan_pixel(Vect<int> (v.x - 1, v.y - 1, 0));
    int a2 = scan_pixel(Vect<int> (v.x, v.y -1, 0));
    int a3 = scan_pixel(Vect<int> (v.x + 1, v.y - 1, 0));
    int a4 = scan_pixel(Vect<int> (v.x + 1, v.y, 0));
    int a5 = scan_pixel(Vect<int> (v.x + 1, v.y + 1, 0));
    int a6 = scan_pixel(Vect<int> (v.x, v.y + 1, 0));
    int a7 = scan_pixel(Vect<int> (v.x - 1, v.y + 1, 0));
    int a8 = scan_pixel(Vect<int> (v.x - 1, v.y, 0));

    // all points around v are not in the human area, then v is a bad pixel
    // tous les points autour de v ne font pas partie de la partition intéressée, nous excluons donc le pixel v 
    if(a1 <= 0 && a2 <= 0 && a3 <= 0 && a4 <= 0 && a5 <= 0 && a6 <= 0 && a7 <= 0 && a8 <= 0)
        return;

    // new recursive search
    // nouvelle recherche récurssive
    if(a1 == 1)
        search_human(Vect<int> (v.x - 1, v.y - 1, 0));

    if(a2 == 1)
        search_human(Vect<int> (v.x, v.y - 1, 0));

    if(a3 == 1)
        search_human(Vect<int> (v.x + 1, v.y - 1, 0));

    if(a4 == 1)
        search_human(Vect<int> (v.x + 1, v.y, 0));

    if(a5 == 1)
        search_human(Vect<int> (v.x + 1, v.y + 1, 0));

    if(a6 == 1)
        search_human(Vect<int> (v.x, v.y + 1, 0));

    if(a7 == 1)
        search_human(Vect<int> (v.x - 1, v.y + 1, 0));

    if(a8 == 1)
        search_human(Vect<int> (v.x - 1, v.y, 0));

}

int SearchHuman::scan_pixel(Vect<int> v) {

    // the pixel is out of the window, we stop
    // le pixel est en dehors de la fenêtre, nous arrêtons
    if(control<int>(v))
        return -1;

    // the pixel was already scanned,  we stop
    // le pixel a déjà été scanné, nous arrêtons
    if(partition->at(coord_gray<int>(v)) == 1)
        if (((uint8_t)vect_imgs[id_img].PIXEL_COLOR_BLUE_VECT(v) <= green_color)
        && ((uint8_t)vect_imgs[id_img].PIXEL_COLOR_GREEN_VECT(v) >= 255 - blue_color))
            return -1;

    // we found a new pixel to attach to the human area
    // nous avons trouvé un nouveau pixel à ajouter à la partition intéressée
    if(partition->at(coord_gray<int>(v)) == 0) {

        if (((uint8_t)vect_imgs[id_img].data[coord_gbr<int>(v)] <= green_color)
        && ((uint8_t)vect_imgs[id_img].data[coord_gbr<int>(v) + 1] >= 255 - blue_color)) {

            partition->at(coord_gray<int>(v)) = 1;
            centroid.x += (long int)v.x;
            centroid.y += (long int)v.y;
            ++surface;

            // the human area is colored
            // La partition représentant l'humain est colorisé
            mat_frame.PIXEL_COLOR_RED(v.x, v.y) = 255;
        }
        else
            partition->at(coord_gray<int>(v)) = -1;
    }

    return partition->at(coord_gray<int>(v));

}

void SearchHuman::new_value(Vect<int> const &a, Vect<int> const &b, int &inf) {

    // fusion des pixels pour étendre la partition
    // fusion for the two pixels to extend the area
    partition->at(coord_gray(a)) = partition->at(coord_gray(b));
    // la surface de la partition augmente de 1
    // the surface increase by one
    id_area.at(partition->at(coord_gray(a))) += 1;
    // la partition avec l'identifiant le plus petit absorbe la partition la plus grande
    // the area with the identifier smallest absorbs the largest area
    if (inf > 0 && inf < partition->at(coord_gray(a))) {
        // la surface de la partition augmente
        // the surface increase by the other surface
        id_area.at(inf) += id_area.at(partition->at(coord_gray(a)));
        // l'ancienne partition est supprimée
        // the old area is erased
        id_area.at(partition->at(coord_gray(a))) = 0;
        // tous les points de l'ancienne partition prennent la valeur de l'identifiant de la nouvelle partition
        // all points of the old area have the value of the identifier of the new area
        replace(partition->at(coord_gray(a)), inf);
    }
    inf = partition->at(coord_gray(a));
}

// nous tournons autour du point v et cherchons à fusionner les partitions qui se juxtaposent
// we turn around the same point v, and we try to fuse areas which are juxtaposed
bool SearchHuman::fusion(Vect<int> const& v0) {

    int id0, id1, id2, id3;

    // on compare le pixel actuel aux autres pixels déjà étudiés
    // we compare the pixel with other pixels already compared
    Vect<int> v1 = v0 + Vect<int>(-1, 0, 0);
    id0 = id_non_null(v1);

    Vect<int> v2 = v0 + Vect<int>(-1, -1, 0);
    id1 = id_non_null(v2);

    Vect<int> v3 = v0 + Vect<int>(0, -1, 0);
    id2 = id_non_null(v3);

    Vect<int> v4 = v0 + Vect<int>(1, -1, 0);
    id3 = id_non_null(v4);

    int inf = 0;

    if (id0 > 0)
        new_value(v0, v1, inf);

    if (id1 > 0)
        new_value(v0, v2, inf);

    if (id2 > 0)
        new_value(v0, v3, inf);

    if (id3 > 0)
        new_value(v0, v4, inf);

    if(inf > 0)
        return true;

    return false;
}
