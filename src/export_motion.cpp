#ifndef EXPORT_MOTION_CPP
#define EXPORT_MOTION_CPP

#include "export_motion.h"

using namespace std;

ExportMotion::ExportMotion() : imbricate(0) {
}

void ExportMotion::save(const QString &fileName,const QSharedPointer<Skeleton> &SP_skeleton, const int &nbr_frames) {

    try {
        // open the file
        ofstream file(fileName.toStdString().c_str(), ofstream::out);
        if (!file)
            throw "(ofstream) error while opening file.";

        file << setprecision(6) << fixed; // show 16 digits

        file << "HIERARCHY\n";

        write_new_root(file, string("ROOT hips"), SP_skeleton->hips->s, false, true);
        write_new_root(file, string("JOINT thigh_L"), Vect<float>(1.084882, 0.106374, -0.050324), false, true);
        write_new_root(file, string("JOINT shin_L"), Vect<float>(0.428269, -0.345176, -4.139606), false, false);
        write_new_root(file, string("JOINT foot_L"), Vect<float>(0.464369, 0.117003, -4.335488), false, false);
        write_new_root(file, string("JOINT toe_L"), Vect<float>(0.040781, -1.254992, -0.632071), false, false);
        write_new_root(file, string("End Site"), Vect<float>(-0.003283, -0.414396, -0.000014), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT thigh_R"), Vect<float>(-1.084882, 0.106374, -0.050324), false, true);
        write_new_root(file, string("JOINT shin_R"), Vect<float>(-0.428269, -0.345176, -4.139606), false, false);
        write_new_root(file, string("JOINT foot_R"), Vect<float>(-0.464369, 0.117003, -4.335488), false, false);
        write_new_root(file, string("JOINT toe_R"), Vect<float>(-0.040781, -1.254992, -0.632071), false, false);
        write_new_root(file, string("End Site"), Vect<float>(-0.003283, -0.414396, -0.000014), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT spine"), Vect<float>(0.000000, 0.228833, 1.572143), false, true); // 9
        write_new_root(file, string("JOINT chest"), Vect<float>(0.000000, 0.087254, 0.599468), false, true); // 10
        write_new_root(file, string("JOINT clavicle_R"), Vect<float>(-0.227391, -0.803817, 2.683225), false, true); // 11
        write_new_root(file, string("JOINT upper_arm_R"), Vect<float>(-1.637361, 0.340290, -0.300515), false, true); // 12
        write_new_root(file, string("JOINT forearm_R"), Vect<float>(-1.657613, 0.021382, -1.898825), false, true); // 13
        write_new_root(file, string("JOINT hand_R"), SP_skeleton->hand_r->s, false, true); // 14
        write_new_root(file, string("JOINT thumb_02_R"), Vect<float>(0.206955, -0.234199, -0.708880), false, true); // 15
        write_new_root(file, string("JOINT thumb_03_R"), Vect<float>(0.127764, -0.047279, -0.391377), false, true); // 16
        write_new_root(file, string("End Site"), Vect<float>(0.119884, -0.018095, -0.396276), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT f_ring_01_R"), Vect<float>(-0.487513, 0.225084, -0.910926), false, true); // 17
        write_new_root(file, string("End Site"), Vect<float>(-0.169222, 0.140269, -0.351316), true, false);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT f_index_01_R"), Vect<float>(-0.254855, -0.180597, -1.111484), false, true); // 18
        write_new_root(file, string("End Site"), Vect<float>(-0.059301, 0.005064, -0.410113), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT clavicle_L"), Vect<float>(0.227391, -0.803817, 2.683225), false, true); // 19
        write_new_root(file, string("JOINT upper_arm_L"), Vect<float>(1.637361, 0.340290, -0.300515), false, true); // 20
        write_new_root(file, string("JOINT forearm_L"), Vect<float>(1.657613, 0.021382, -1.898825), false, true); // 21
        write_new_root(file, string("JOINT hand_L"), SP_skeleton->hand_l->s, false, true); // 22
        write_new_root(file, string("JOINT thumb_02_L"), Vect<float>(-0.207201, -0.236211, -0.708153), false, true); // 23
        write_new_root(file, string("JOINT thumb_03_L"), Vect<float>(-0.127731, -0.048245, -0.391277), false, true); // 24
        write_new_root(file, string("End Site"), Vect<float>(-0.119884, -0.019162, -0.396226), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT f_ring_01_L"), Vect<float>(0.487513, 0.222631, -0.911529), false, true); // 24
        write_new_root(file, string("End Site"), Vect<float>(0.169222, 0.139323, -0.351693), true, false);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT f_index_01_L"), Vect<float>(0.254856, -0.183589, -1.110993), false, true); // 25
        write_new_root(file, string("End Site"), Vect<float>(0.059301, 0.003960, -0.410126), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT neck"), SP_skeleton->neck->s, false, true); // 26
        write_new_root(file, string("JOINT head"), SP_skeleton->head->s, false, false); // 27
        write_new_root(file, string("JOINT jaw"), Vect<float>(0.000000, -0.556994, -0.046074), false, true);
        write_new_root(file, string("End Site"), Vect<float>(0.000000, -0.295137, -0.290915), true, false);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT eye_R"), Vect<float>(-0.293725, -1.232862, 0.285738), false, true);
        write_new_root(file, string("End Site"), Vect<float>(-0.039113, -0.411569, -0.028574), true, false);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT eye_L"), Vect<float>(0.293725, -1.232862, 0.285738), false, true);
        write_new_root(file, string("End Site"), Vect<float>(0.039113, -0.411569, -0.028574), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);

        file << "MOTION\n";
        stringstream ss; // to convert the number into string
        ss << nbr_frames;
        file << "Frames: " + ss.str() << std::endl;
        file << "Frame Time: 0.041667\n";

        for(int i = 0; i < nbr_frames; ++i) {

            // write the hips offset and rotation
            // on écrit le déplacement des hanches et la rotation
            file << SP_skeleton->hips->vect_offset.at(i).x << " " << SP_skeleton->hips->vect_offset.at(i).y << " " << SP_skeleton->hips->vect_offset.at(i).z << " ";
            file << "0.000000 0.000000 0.000000 ";

            // for others roots
            // pour les autres noeuds
            for(vector< Vect< float > >::iterator it = vect_offset.begin() + 1; it != vect_offset.end(); ++it) {

                // offsets and rotations in first case, only offset in other case
                // déplacements et rotations dans le premier cas, uniquement les déplacements dans le second cas
                if(vect_channel.at(it - vect_offset.begin()))
                    file << it->x << " " << it->y << " " << it->z << " ";
                else
                    file << "0.000000 0.000000 0.000000 ";

                // write the roots rotations for each frame
                // écrit les rotations pour chaque frame
                switch(it - vect_offset.begin()) {

                    case 9:
                        file << SP_skeleton->hips->vect_rot.at(i).x << " " << SP_skeleton->hips->vect_rot.at(i).y << " " << SP_skeleton->hips->vect_rot.at(i).z << " ";
                        break;

                    case 11:
                        file << SP_skeleton->shoulder_r->vect_rot.at(i).x << " " << SP_skeleton->shoulder_r->vect_rot.at(i).y << " " << SP_skeleton->shoulder_r->vect_rot.at(i).z << " ";
                        break;

                    case 12:
                        file << SP_skeleton->elbow_r->vect_rot.at(i).x << " " << SP_skeleton->elbow_r->vect_rot.at(i).y << " " << SP_skeleton->elbow_r->vect_rot.at(i).z << " ";
                        break;

                    case 13:
                        file << SP_skeleton->hand_r->vect_rot.at(i).x << " " << SP_skeleton->hand_r->vect_rot.at(i).y << " " << SP_skeleton->hand_r->vect_rot.at(i).z << " ";
                    break;

                    case 19:
                        file << SP_skeleton->shoulder_l->vect_rot.at(i).x << " " << SP_skeleton->shoulder_l->vect_rot.at(i).y << " " << SP_skeleton->shoulder_l->vect_rot.at(i).z << " ";
                        break;

                    case 20:
                        file << SP_skeleton->elbow_l->vect_rot.at(i).x << " " << SP_skeleton->elbow_l->vect_rot.at(i).y << " " << SP_skeleton->elbow_l->vect_rot.at(i).z << " ";
                        break;

                    case 21:
                        file << SP_skeleton->elbow_r->vect_rot.at(i).x << " " << SP_skeleton->elbow_r->vect_rot.at(i).y << " " << SP_skeleton->elbow_r->vect_rot.at(i).z << " ";
                    break;

                    case 27:
                        file << SP_skeleton->head->vect_rot.at(i).x << " " << SP_skeleton->head->vect_rot.at(i).y << " " << SP_skeleton->head->vect_rot.at(i).z << " ";
                        break;

                    default:
                        // we write the rotation only if channel is for offsets and rotations
                        // nous écrivons la rotation seulement si le channel concerne les déplacements et les rotations
                        if(vect_channel.at(it - vect_offset.begin()))
                            file << "0.000000 0.000000 0.000000 ";
                }
            }
            file << endl;
        }
        file.close();
    }
    catch (const char& strException)
    {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
        throw;
    }


}

void ExportMotion::write_new_root(ofstream &file, const string &root_name, const Vect<float> &offset, bool const &termination, bool const &channel)
{

    //it's not the root termination, we get the offset and the channel (offset) or (offset with rotation)
    // ce n'est pas la terminaison du noeud, nous récupérons le déplacement et le channel (déplacement) ou (déplacement avec rotation)
    if(!termination) {
        vect_offset.push_back(offset);
        vect_channel.push_back(channel);
    }

    // we indent the bloc
    // tabulation par bloc imbriqué
    for(int i = 0; i < imbricate; ++i)
        file << "\t";

    file << root_name.c_str() << endl;
    for(int i = 0; i < imbricate; ++i)
        file << "\t";

    file << "{\n";
    ++imbricate;

    for(int i = 0; i < imbricate; ++i)
        file << "\t";

    file << "OFFSET " << offset.x << " " << offset.y << " " << offset.z << endl;

    // it's a termination, nothing to do
    // c'est une terminaison, rien d'autre à faire
    if(termination)
        return;

    for(int i = 0; i < imbricate; ++i)
        file << "\t";

    if(channel)
        file << "CHANNELS 6 Xposition Yposition Zposition Xrotation Yrotation Zrotation\n";
    else
        file << "CHANNELS 3 Xrotation Yrotation Zrotation\n";

}

void ExportMotion::write_close_root(std::ofstream &file) {

    --imbricate;
    for(int i = 0; i < imbricate; ++i)
        file << "\t";
    file << "}\n";

}

#endif // EXPORT_MOTION_CPP
