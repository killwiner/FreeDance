#include "skeleton.h"
#include <stdio.h>

void Skeleton::search_partitions() {

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

            // si la couleur du point se situe en dehors de la zone de filtrage
            // after the filter, the color is out
            if (((uint8_t)buffer_img->imageData[coord_gbr<int>(v)] > green_color)
             || ((uint8_t)buffer_img->imageData[coord_gbr<int>(v) + 1] < 255 - blue_color)) {
                // l'identifiant de la partition est donc 0
                partition->at(coord_gray<int>(v)) = 0;
                // la surface de la zone noire augmente de 1
                id_area.at(0) +=1;
                continue;
            }

            // nous tournons autour du point v pour le fusionner à une partition.
            // we turn around the same point v, and obtains a new id for a new area
            if(!fusion(v)) {
                // we got a new identitiy for the new partition
                // nouvel identifiant pour la nouvelle partition
                id_partition += 1;
                partition->at(coord_gray<int>(v)) = id_partition;
                id_area.push_back(1);
            }
        }

}

void Skeleton::search_human(Vect<int> v) {

    int a0 = scan_pixel(v);

    int a1 = scan_pixel(Vect<int> (v.x - 1, v.y - 1, 0));
    int a2 = scan_pixel(Vect<int> (v.x, v.y -1, 0));
    int a3 = scan_pixel(Vect<int> (v.x + 1, v.y - 1, 0));
    int a4 = scan_pixel(Vect<int> (v.x + 1, v.y, 0));
    int a5 = scan_pixel(Vect<int> (v.x + 1, v.y + 1, 0));
    int a6 = scan_pixel(Vect<int> (v.x, v.y + 1, 0));
    int a7 = scan_pixel(Vect<int> (v.x - 1, v.y + 1, 0));
    int a8 = scan_pixel(Vect<int> (v.x - 1, v.y, 0));

    if(a1 <= 0 && a2 <= 0 && a3 <= 0 && a4 <= 0 && a5 <= 0 && a6 <= 0 && a7 <= 0 && a8 <= 0)
        return;

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

int Skeleton::scan_pixel(Vect<int> v) {

    if(control<int>(v)) {

        return -1;
    }


    if(partition->at(coord_gray<int>(v)) == 1)
        if (((uint8_t)buffer_img->imageData[coord_gbr<int>(v)] <= green_color)
        && ((uint8_t)buffer_img->imageData[coord_gbr<int>(v) + 1] >= 255 - blue_color))
            return -1;

    if(partition->at(coord_gray<int>(v)) == 0) {

        if (((uint8_t)buffer_img->imageData[coord_gbr<int>(v)] <= green_color)
        && ((uint8_t)buffer_img->imageData[coord_gbr<int>(v) + 1] >= 255 - blue_color)) {

            partition->at(coord_gray<int>(v)) = 1;
            centroid.x += (long int)v.x;
            centroid.y += (long int)v.y;
            ++surface;

            // the human area is colored
            // La partition représentant l'humain est colorisé
            frame->PIXEL_COLOR_RED(v.x, v.y) = 255;
        }
        else
            partition->at(coord_gray<int>(v)) = -1;
    }

    return partition->at(coord_gray<int>(v));

}

// nous tournons autour du point v et cherchons à fusionner les partitions qui se juxtaposent
// we turn around the same point v, and we try to fuse areas which are juxtaposed
bool Skeleton::fusion(Vect<int> const& v0) {

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

    if (id0 > 0) {
        // fusion des pixels pour étendre la partition
        // fusion for the two pixels to extend the area
        partition->at(coord_gray(v0)) = partition->at(coord_gray(v1));
        // la surface de la partition augmente de 1
        // the surface increase by one
        id_area.at(partition->at(coord_gray(v0))) += 1;
        inf = partition->at(coord_gray(v0));
    }

    if (id1 > 0) {
        partition->at(coord_gray(v0)) = partition->at(coord_gray(v2));
        id_area.at(partition->at(coord_gray(v0))) += 1;
        // la partition avec l'identifiant le plus petit absorbe la partition la plus grande
        // the area with the identifier smallest absorbs the largest area
        if (inf > 0 && inf < partition->at(coord_gray(v0))) {
            // la surface de la partition augmente
            // the surface increase by the other surface
            id_area.at(inf) += id_area.at(partition->at(coord_gray(v0)));
            // l'ancienne partition est supprimée
            // the old area is erased
            id_area.at(partition->at(coord_gray(v0))) = 0;
            // tous les points de l'ancienne partition prennent la valeur de l'identifiant de la nouvelle partition
            // all points of the old area have the value of the identifier of the new area
            replace(partition->at(coord_gray(v0)), inf);

        }
        inf = partition->at(coord_gray(v0));
    }

    if (id2 > 0) {
        partition->at(coord_gray(v0)) = partition->at(coord_gray(v3));
        id_area.at(partition->at(coord_gray(v0))) += 1;
        if (inf > 0 && inf < partition->at(coord_gray(v0))) {
            id_area.at(inf) += id_area.at(partition->at(coord_gray(v0)));
            id_area.at(partition->at(coord_gray(v0))) = 0;
            replace(partition->at(coord_gray(v0)), inf);
        }
        inf = partition->at(coord_gray(v0));
    }

    if (id3 > 0) {
        partition->at(coord_gray(v0)) = partition->at(coord_gray(v4));
        id_area.at(partition->at(coord_gray(v0))) += 1;
        if (inf > 0 && inf < partition->at(coord_gray(v0))) {
            id_area.at(inf) += id_area.at(partition->at(coord_gray(v0)));
            id_area.at(partition->at(coord_gray(v0))) = 0;
            replace(partition->at(coord_gray(v0)), inf);
        }
        inf = partition->at(coord_gray(v0));

    }

    if(inf > 0)
        return true;

    return false;
}
