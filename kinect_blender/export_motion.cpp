#ifndef EXPORT_MOTION_CPP
#define EXPORT_MOTION_CPP

#include "export_motion.h"

ExportMotion::ExportMotion() : imbricate(0) {
}

void ExportMotion::save(const QString &fileName,const Skeleton &skel, const int &nbr_frames) {

    std::ofstream file(fileName.toStdString().c_str(), std::ofstream::out);
    file << std::setprecision(6) << std::fixed; // show 16 digits
    file << "HIERARCHY\n";  
    new_root(file, std::string("ROOT hips"), skel.hips->s, false, true);
    new_root(file, std::string("JOINT thigh_L"), Vect<float>(1.084882, 0.106374, -0.050324), false, true);
    new_root(file, std::string("JOINT shin_L"), Vect<float>(0.428269, -0.345176, -4.139606), false, false);
    new_root(file, std::string("JOINT foot_L"), Vect<float>(0.464369, 0.117003, -4.335488), false, false);
    new_root(file, std::string("JOINT toe_L"), Vect<float>(0.040781, -1.254992, -0.632071), false, false);
    new_root(file, std::string("End Site"), Vect<float>(-0.003283, -0.414396, -0.000014), true, false);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    new_root(file, std::string("JOINT thigh_R"), Vect<float>(-1.084882, 0.106374, -0.050324), false, true);
    new_root(file, std::string("JOINT shin_R"), Vect<float>(-0.428269, -0.345176, -4.139606), false, false);
    new_root(file, std::string("JOINT foot_R"), Vect<float>(-0.464369, 0.117003, -4.335488), false, false);
    new_root(file, std::string("JOINT toe_R"), Vect<float>(-0.040781, -1.254992, -0.632071), false, false);
    new_root(file, std::string("End Site"), Vect<float>(-0.003283, -0.414396, -0.000014), true, false);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    new_root(file, std::string("JOINT spine"), Vect<float>(0.000000, 0.228833, 1.572143), false, true);
    new_root(file, std::string("JOINT chest"), Vect<float>(0.000000, 0.087254, 0.599468), false, true);
    new_root(file, std::string("JOINT clavicle_R"), Vect<float>(-0.227391, -0.803817, 2.683225), false, true); // 11
    new_root(file, std::string("JOINT upper_arm_R"), Vect<float>(-1.637361, 0.340290, -0.300515), false, true); // 12
    new_root(file, std::string("JOINT forearm_R"), Vect<float>(-1.657613, 0.021382, -1.898825), false, true); // 13
    new_root(file, std::string("JOINT hand_R"), skel.hand_r->s, false, true); // 14
    new_root(file, std::string("JOINT thumb_02_R"), Vect<float>(0.206955, -0.234199, -0.708880), false, true); // 15
    new_root(file, std::string("JOINT thumb_03_R"), Vect<float>(0.127764, -0.047279, -0.391377), false, true); // 16
    new_root(file, std::string("End Site"), Vect<float>(0.119884, -0.018095, -0.396276), true, false);
    close_root(file);
    close_root(file);
    close_root(file);
    new_root(file, std::string("JOINT f_ring_01_R"), Vect<float>(-0.487513, 0.225084, -0.910926), false, true); // 17
    new_root(file, std::string("End Site"), Vect<float>(-0.169222, 0.140269, -0.351316), true, false);
    close_root(file);
    close_root(file);
    new_root(file, std::string("JOINT f_index_01_R"), Vect<float>(-0.254855, -0.180597, -1.111484), false, true); // 18
    new_root(file, std::string("End Site"), Vect<float>(-0.059301, 0.005064, -0.410113), true, false);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    new_root(file, std::string("JOINT clavicle_L"), Vect<float>(0.227391, -0.803817, 2.683225), false, true); // 19
    new_root(file, std::string("JOINT upper_arm_L"), Vect<float>(1.637361, 0.340290, -0.300515), false, true); // NILL
    new_root(file, std::string("JOINT forearm_L"), Vect<float>(1.657613, 0.021382, -1.898825), false, true); // 20
    new_root(file, std::string("JOINT hand_L"), skel.hand_l->s, false, true); // 21
    new_root(file, std::string("JOINT thumb_02_L"), Vect<float>(-0.207201, -0.236211, -0.708153), false, true); // 22
    new_root(file, std::string("JOINT thumb_03_L"), Vect<float>(-0.127731, -0.048245, -0.391277), false, true); // 23
    new_root(file, std::string("End Site"), Vect<float>(-0.119884, -0.019162, -0.396226), true, false);
    close_root(file);
    close_root(file);
    close_root(file);
    new_root(file, std::string("JOINT f_ring_01_L"), Vect<float>(0.487513, 0.222631, -0.911529), false, true); // 24
    new_root(file, std::string("End Site"), Vect<float>(0.169222, 0.139323, -0.351693), true, false);
    close_root(file);
    close_root(file);
    new_root(file, std::string("JOINT f_index_01_L"), Vect<float>(0.254856, -0.183589, -1.110993), false, true); // 25
    new_root(file, std::string("End Site"), Vect<float>(0.059301, 0.003960, -0.410126), true, false);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    new_root(file, std::string("JOINT neck"), skel.neck->s, false, true); // 26
    new_root(file, std::string("JOINT head"), skel.head->s, false, false); // 27
    new_root(file, std::string("JOINT jaw"), Vect<float>(0.000000, -0.556994, -0.046074), false, true);
    new_root(file, std::string("End Site"), Vect<float>(0.000000, -0.295137, -0.290915), true, false);
    close_root(file);
    close_root(file);
    new_root(file, std::string("JOINT eye_R"), Vect<float>(-0.293725, -1.232862, 0.285738), false, true);
    new_root(file, std::string("End Site"), Vect<float>(-0.039113, -0.411569, -0.028574), true, false);
    close_root(file);
    close_root(file);
    new_root(file, std::string("JOINT eye_L"), Vect<float>(0.293725, -1.232862, 0.285738), false, true);
    new_root(file, std::string("End Site"), Vect<float>(0.039113, -0.411569, -0.028574), true, false);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);
    close_root(file);

    file << "MOTION\n";
    std::stringstream ss;
    ss << nbr_frames;
    file << "Frames: " + ss.str() << std::endl;
    file << "Frame Time: 0.041667\n";

    for(int i = 0; i < nbr_frames; ++i) {
        for(std::vector< Vect< float > >::iterator it = vect_offset.begin(); it != vect_offset.end(); ++it) {
            if(vect_channel.at(it - vect_offset.begin()))
                file << it->x << " " << it->y << " " << it->z << " ";
            else
                file << "0.000000 0.000000 0.000000 ";

            switch(it - vect_offset.begin()) {

                case 11:
                    file << skel.shoulder_r->vect_rot.at(i).x << " " << skel.shoulder_r->vect_rot.at(i).y << " " << skel.shoulder_r->vect_rot.at(i).z << " ";
                    break;

                case 12:
                    file << skel.elbow_r->vect_rot.at(i).x << " " << skel.elbow_r->vect_rot.at(i).y << " " << skel.elbow_r->vect_rot.at(i).z << " ";
                    break;

                case 19:
                    file << skel.shoulder_l->vect_rot.at(i).x << " " << skel.shoulder_l->vect_rot.at(i).y << " " << skel.shoulder_l->vect_rot.at(i).z << " ";
                    break;

                case 20:
                    file << skel.elbow_l->vect_rot.at(i).x << " " << skel.elbow_l->vect_rot.at(i).y << " " << skel.elbow_l->vect_rot.at(i).z << " ";
                    break;

                case 27:
                    file << skel.head->vect_rot.at(i).x << " " << skel.head->vect_rot.at(i).y << " " << skel.head->vect_rot.at(i).z << " ";
                    break;

                default:
                    if(vect_channel.at(it - vect_offset.begin()))
                        file << "0.000000 0.000000 0.000000 ";
            }


        }
        file << std::endl;
    }

    file.close();
}

void ExportMotion::new_root(std::ofstream &file, std::string const root, const Vect<float> &v, bool const &end, bool const &offset)
{
    if(!end) {
        vect_offset.push_back(v);
        vect_channel.push_back(offset);
    }

    for(int i = 0; i < imbricate; ++i)
        file << "\t";
    file << root.c_str() << std::endl;
    for(int i = 0; i < imbricate; ++i)
        file << "\t";
    file << "{\n";
    ++imbricate;
    for(int i = 0; i < imbricate; ++i)
        file << "\t";

    file << "OFFSET " << v.x << " " << v.y << " " << v.z << std::endl;
    if(end)
        return;

    for(int i = 0; i < imbricate; ++i)
        file << "\t";
    if(offset)
        file << "CHANNELS 6 Xposition Yposition Zposition Xrotation Yrotation Zrotation\n";
    else
        file << "CHANNELS 3 Xrotation Yrotation Zrotation\n";
}

void ExportMotion::close_root(std::ofstream &file) {
    --imbricate;
    for(int i = 0; i < imbricate; ++i)
        file << "\t";
    file << "}\n";
}

#endif // EXPORT_MOTION_CPP
