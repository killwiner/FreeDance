#include "humanShape.h"

namespace armature {

HumanShape::HumanShape(cv::Mat *Image) : Armature(Image, NULL), id(1)
{
    // chaque pixel sélectionné obtient un identifiant désignant une partition unique
    idObjects_ = new cv::Mat_<quint16>(Image_->size().height, Image_->size().width);

    // les identifiants 0 et 1 ne sont pas comptabilisés
    VSum_Ids.push_back(0);
    VSum_Ids.push_back(0);
}

HumanShape::~HumanShape() {
    delete idObjects_;
}

void HumanShape::pixelOut(const quint16 &x, const quint16 &y, const qint16 &color_min, const qint16 &color_max, const qint8 &type_color) {
    if(color_min != color_max) {
        // calcule l'identifiant du pixel dans la matrice
        quint32 id_pixel = y * Image_->size().width + x;
        if(Image_->data[3 * id_pixel + type_color] > color_min && Image_->data[3 * id_pixel + type_color] < color_max) {
            // le pixel en dehors d'une partition devient noir
            Image_->data[3 * id_pixel] = Image_->data[3 * id_pixel + 1] = Image_->data[3 * id_pixel + 2] = 0;
            // l'identifiant d'un pixel en dehors d'une partition devient zero
            idObjects_->at<qint16>(y, x) = 0;
        }
    }
}

void HumanShape::filter(const qint16 &red_min, const qint16 &red_max, const qint16 &green_min, const qint16 &green_max, const qint16 &blue_min, const qint16 &blue_max) {

    // parcourt de chaque pixel de l'image
    for (quint16 y = 0; y < Image_->size().height; ++y)
        for (quint16 x = 0; x < Image_->size().width; ++x) {

            // par défaut le pixel appartient à une partition
            idObjects_->at<quint16>(y, x) = 1;

            // l'identifiant devient zero s'il n'appartient pas à une partition 
            pixelOut(x, y, red_min, red_max, RED);
            pixelOut(x, y, green_min, green_max, GREEN);
            pixelOut(x, y, blue_min, blue_max, BLUE);
        }
}

void HumanShape::linkId(const quint16 &id1, const quint16 &id2) {
    // permet de faire corespondre deux partitions en contact avec des identifiants différents
    // la partition id1 est en contact avec la partition id2

    if(id1 == id2)
        return;

    if(!VId_1.empty())
        if(VId_1.back() == id1 || id1 == id2)
            return;

    for(std::vector<quint16>::iterator it = VId_1.begin(); it != VId_1.end(); ++it)
        if(id1 == *it && id2 == VId_2.at(it - VId_1.begin()))
            return;

    VId_1.push_back(id1);
    VId_2.push_back(id2);
}

void HumanShape::changeId(const quint16 &x, const quint16 &y, const quint16 &central_id) {

    // le pixel a déjà obtenu un identifiant ? Alors les deux partitions en contact doivent fusionner plus tard
    if(idObjects_->at<quint16>(y, x) > 1) {
        linkId(central_id, idObjects_->at<quint16>(y, x));
        return;
    }

    // attribue un identifiant à un pixel appartenant à une partition
    if(idObjects_->at<quint16>(y, x) == 1) {
        idObjects_->at<quint16>(y, x) = central_id;
        ++VSum_Ids.at(central_id);
    }

}

void HumanShape::searchAroundPixel(const quint16 &x, const quint16 &y) {


    // on scanne tous les pixels qui n'ont pas été scanné autour du pixel (x, y)
    if(y > 0) {

        if(x > 0)
            changeId(x - 1, y - 1, idObjects_->at<quint16>(y, x));

        changeId(x , y - 1, idObjects_->at<quint16>(y, x));

        if(x < Image_->size().width - 1)
            changeId(x + 1, y - 1, idObjects_->at<quint16>(y, x));
    }

    if(x < Image_->size().width - 1)
        changeId(x + 1 , y, idObjects_->at<quint16>(y, x));

    if(y < Image_->size().height - 1) {
        if(x < Image_->size().width - 1)
            changeId(x + 1 , y + 1, idObjects_->at<quint16>(y, x));

        changeId(x, y + 1, idObjects_->at<quint16>(y, x));

        if(x > 0)
            changeId(x - 1, y + 1, idObjects_->at<quint16>(y, x));
    }
}

void HumanShape::searchPartitions() {

    for(quint16 y = 0; y < Image_->size().height; ++y)
        for(quint16 x = 0; x < Image_->size().width; ++x) {
            if(idObjects_->at<quint16>(y, x) == 1) {
                id++;
                // le pixel appartent à une nouvelle partition, on lui attribue un nouvel identifiant
                idObjects_->at<quint16>(y, x) = id;

                VSum_Ids.push_back(1);
                //++VSum_Ids.at(id);
            }
            // on cherche à étendre la partiton autour dudit pixel en fonction des pixels périphériques
            if(idObjects_->at<quint16>(y, x) > 1)
                searchAroundPixel(x, y);
        }

    VId_check.resize(VId_1.size(), false);
}

void HumanShape::connectIds() {

    for(std::vector<quint16>::iterator it_1 = VId_1.begin(); it_1 != VId_1.end(); ++it_1)
        for(std::vector<quint16>::iterator it_2 = VId_2.begin(); it_2 != VId_2.end(); ++it_2)
            if(*it_1 == *it_2)
                *it_2 = VId_2.at(it_1 - VId_1.begin());
}

void HumanShape::attribIds() {
    for (quint16 y = 0; y < Image_->size().height; ++y)
        for (quint16 x = 0; x < Image_->size().width; ++x)
            if(idObjects_->at<quint16>(y, x))
                for(std::vector<quint16>::iterator it = VId_1.begin(); it != VId_1.end(); ++it)
                    if(idObjects_->at<quint16>(y, x) == *it) {
                        VId_check.at(it - VId_1.begin()) = true;
                        idObjects_->at<quint16>(y, x) = VId_2.at(it - VId_1.begin());
                        VSum_Ids.at(VId_2.at(it - VId_1.begin())) += 1;
                        break;
                    }
}

void HumanShape::detectObjects()
{
    // recherche de nouvelles partitions sur toute l'image
    searchPartitions();

    // connecte les identifiants en cascade. Si id_A = 5 -> id_B = 8 -> id_C = 3, alors
    // on doit obtenir id_A = 5 -> id_B = 5 -> id_C = 5 puisque touts ces pixels en
    // contact les uns avec les autres doivent avoir les mêmes identifiants
    connectIds();

    // attribution des nouveaux identifiants à tous les pixels de l'image
    attribIds();

    for(std::vector<bool>::iterator it = VId_check.begin(); it != VId_check.end(); ++it)
        if(!(*it)) {
            VId_1.clear();
            VId_2.clear();
            VSum_Ids.resize(VSum_Ids.size(), 0);
            detectObjects();
            break;
        }
}

quint32 HumanShape::largestPartition() {

    quint32 sumIds = 0, idLargestPart;

    for(std::vector<quint32>::iterator it = VSum_Ids.begin(); it != VSum_Ids.end(); ++it)
        if (sumIds < *it) {
            sumIds = *it;
            idLargestPart = it - VSum_Ids.begin();
        }
    
    return idLargestPart;
}

void HumanShape::erazeSmallPartitions() {

    quint16 idLargestPart = largestPartition();

    for (quint16 y = 0; y < Image_->size().height; ++y)
        for (quint16 x = 0; x < Image_->size().width; ++x)
            if(idObjects_->at<quint16>(y, x) != idLargestPart && idObjects_->at<quint16>(y, x) > 0) {
                quint32 id_pixel = y * Image_->size().width + x;
                idObjects_->at<quint16>(y, x) = 0;
                Image_->data[3 * id_pixel + RED] = 0;
                Image_->data[3 * id_pixel + GREEN] = 0;
                Image_->data[3 * id_pixel + BLUE] = 0;
            }
}
}
