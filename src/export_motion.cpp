#ifndef EXPORT_MOTION_CPP
#define EXPORT_MOTION_CPP

#include "export_motion.h"

using namespace std;

ExportMotion::ExportMotion() : imbricate(0) {
}

void ExportMotion::write_0_chan(ofstream &f, int const &channels) {
    if(channels)
        f << "0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 ";
    else
        f << "0.000000 0.000000 0.000000 ";
}

void ExportMotion::save(const QString &fileName,const QSharedPointer<Skeleton> &SP_skeleton, const int &nbr_frames) {

    try {
        // open the file
        ofstream file(fileName.toStdString().c_str(), ofstream::out);
        if (!file)
            throw "(ofstream) error while opening file.";

        file << setprecision(6) << fixed; // show 16 digits

        file << "HIERARCHY\n";

        //write_new_root(file, string("ROOT hips"), SP_skeleton->hips->s, false, true);
        write_new_root(file, string("ROOT hips"), Vect<float>(hips_offset), false, hips_channels);
        write_new_root(file, string("JOINT thigh_L"), Vect<float>(thigh_L_offset), false, thigh_L_channels);
        write_new_root(file, string("JOINT shin_L"), Vect<float>(shin_L_offset), false, shin_L_channels);
        write_new_root(file, string("JOINT foot_L"), Vect<float>(foot_L_offset), false, foot_L_channels);
        write_new_root(file, string("JOINT toe_L"), Vect<float>(toe_L_offset), false, toe_L_channels);
        write_new_root(file, string("End Site"), Vect<float>(Site_toe_L_offset), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT thigh_R"), Vect<float>(thigh_R_offset), false, thigh_R_channels);
        write_new_root(file, string("JOINT shin_R"), Vect<float>(shin_R_offset), false, shin_R_channels);
        write_new_root(file, string("JOINT foot_R"), Vect<float>(foot_R_offset), false, foot_R_channels);
        write_new_root(file, string("JOINT toe_R"), Vect<float>(toe_R_offset), false, toe_R_channels);
        write_new_root(file, string("End Site"), Vect<float>(Site_toe_R_offset), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT spine"), Vect<float>(spine_offset), false, spine_channels);
        write_new_root(file, string("JOINT chest"), Vect<float>(chest_offset), false, chest_channels);
        write_new_root(file, string("JOINT clavicle_R"), Vect<float>(clavicle_R_offset), false, clavicle_R_channels);
        write_new_root(file, string("JOINT upper_arm_R"), Vect<float>(upper_arm_R_offset), false, upper_arm_R_channels);
        write_new_root(file, string("JOINT forearm_R"), Vect<float>(forearm_R_offset), false, forearm_R_channels);
        //write_new_root(file, string("JOINT hand_R"), SP_skeleton->hand_r->s, false, true);
        write_new_root(file, string("JOINT hand_R"), Vect<float>(hand_R_offset), false, hand_R_channels);
        write_new_root(file, string("JOINT thumb_02_R"), Vect<float>(thumb_02_R_offset), false, thumb_02_R_channels);
        write_new_root(file, string("JOINT thumb_03_R"), Vect<float>(thumb_03_R_offset), false, thumb_03_R_channels);
        write_new_root(file, string("End Site"), Vect<float>(Site_thumb_03_R_offset), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT f_ring_01_R"), Vect<float>(f_ring_01_R_offset), false, f_ring_01_R_channels);
        write_new_root(file, string("End Site"), Vect<float>(Site_f_ring_01_R_offset), true, false);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT f_index_01_R"), Vect<float>(f_index_01_R_offset), false, f_index_01_R_channels);
        write_new_root(file, string("End Site"), Vect<float>(Site_f_ring_01_R_offset), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT clavicle_L"), Vect<float>(clavicle_L_offset), false, clavicle_L_channels);
        write_new_root(file, string("JOINT upper_arm_L"), Vect<float>(upper_arm_L_offset), false, upper_arm_L_channels);
        write_new_root(file, string("JOINT forearm_L"), Vect<float>(forearm_L_offset), false, forearm_L_channels);
        //write_new_root(file, string("JOINT hand_L"), SP_skeleton->hand_l->s, false, true);
        write_new_root(file, string("JOINT hand_L"), Vect<float>(hand_L_offset), false, hand_L_channels);
        write_new_root(file, string("JOINT thumb_02_L"), Vect<float>(thumb_02_L_offset), false, thumb_02_L_channels);
        write_new_root(file, string("JOINT thumb_03_L"), Vect<float>(thumb_03_L_offset), false, thumb_03_L_channels);
        write_new_root(file, string("End Site"), Vect<float>(Site_thumb_03_L_offset), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT f_ring_01_L"), Vect<float>(f_ring_01_L_offset), false, f_ring_01_L_channels);
        write_new_root(file, string("End Site"), Vect<float>(Site_f_ring_01_L_offset), true, false);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT f_index_01_L"), Vect<float>(f_index_01_L_offset), false, f_index_01_L_channels);
        write_new_root(file, string("End Site"), Vect<float>(Site_f_index_01_L_offset), true, false);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        write_close_root(file);
        //write_new_root(file, string("JOINT neck"), SP_skeleton->neck->s, false, true);
        write_new_root(file, string("JOINT neck"), Vect<float>(neck_offset), false, neck_channels);
        //write_new_root(file, string("JOINT head"), SP_skeleton->head->s, false, false);
        write_new_root(file, string("JOINT head"), Vect<float>(head_offset), false, head_channels);
        write_new_root(file, string("JOINT jaw"), Vect<float>(jaw_offset), false, jaw_channels);
        write_new_root(file, string("End Site"), Vect<float>(Site_jaw_offset), true, false);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT eye_R"), Vect<float>(eye_R_offset), false, eye_R_channels);
        write_new_root(file, string("End Site"), Vect<float>(Site_eye_R_offset), true, false);
        write_close_root(file);
        write_close_root(file);
        write_new_root(file, string("JOINT eye_L"), Vect<float>(eye_L_offset), false, eye_L_channels);
        write_new_root(file, string("End Site"), Vect<float>(Site_eye_L_offset), true, false);
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
            //file << SP_skeleton->hips->vect_offset.at(i).x << " " << SP_skeleton->hips->vect_offset.at(i).y << " " << SP_skeleton->hips->vect_offset.at(i).z << " ";
            file << Vect<float>(hips_offset).x << " " << Vect<float>(hips_offset).y << " " << Vect<float>(hips_offset).z << " ";
            file << "0.000000 0.000000 0.000000 ";

            file << Vect<float>(thigh_L_offset).x << " " << Vect<float>(thigh_L_offset).y << " " << Vect<float>(thigh_L_offset).z << " ";
            file << "0.000000 0.000000 0.000000 ";
            // shin_L rotation
            write_0_chan(file, shin_L_channels);
            // foot_L rotation
            write_0_chan(file, foot_L_channels);
            // toe_L rotation
            write_0_chan(file, toe_L_channels);

            file << Vect<float>(thigh_R_offset).x << " " << Vect<float>(thigh_R_offset).y << " " << Vect<float>(thigh_R_offset).z << " ";
            file << "0.000000 0.000000 0.000000 ";
            // shin_R rotation
            write_0_chan(file, shin_R_channels);
            // foot_R rotation
            write_0_chan(file, foot_R_channels);
            // toe_R rotation
            write_0_chan(file, toe_R_channels);

            file << Vect<float>(spine_offset).x << " " << Vect<float>(spine_offset).y << " " << Vect<float>(spine_offset).z << " ";
            file << "0.000000 0.000000 0.000000 ";
            // chest rotation
            write_0_chan(file, chest_channels);

            file << Vect<float>(clavicle_R_offset).x << " " << Vect<float>(clavicle_R_offset).y << " " << Vect<float>(clavicle_R_offset).z << " ";
            file << "0.000000 0.000000 0.000000 ";
            // upper_arm_R rotation
            write_0_chan(file, upper_arm_R_channels);
            // forearm_R rotation
            write_0_chan(file, forearm_R_channels);
            // hand_R rotation
            write_0_chan(file, hand_R_channels);
            // thumb_02_R rotation
            write_0_chan(file, thumb_02_R_channels);
            // thumb_03_R rotation
            write_0_chan(file, thumb_03_R_channels);
            // f_ring_01_R rotation
            write_0_chan(file, f_ring_01_R_channels);
            // f_index_01_R rotation
            write_0_chan(file, f_index_01_R_channels);

            file << Vect<float>(clavicle_L_offset).x << " " << Vect<float>(clavicle_L_offset).y << " " << Vect<float>(clavicle_L_offset).z << " ";
            file << "0.000000 0.000000 0.000000 ";
            // upper_arm_L rotation
            write_0_chan(file, upper_arm_L_channels);
            // forearm L rotation
            write_0_chan(file, forearm_L_channels);
            // hand_L rotation
            write_0_chan(file, hand_L_channels);
            // thumb_02_L rotation
            write_0_chan(file, thumb_02_L_channels);
            // thumb_03_L rotation
            write_0_chan(file, thumb_03_L_channels);
            // f_ring_01_L rotation
            write_0_chan(file, f_ring_01_L_channels);
            // f_index_01_L rotation
            write_0_chan(file, f_index_01_L_channels);

            file << Vect<float>(neck_offset).x << " " << Vect<float>(neck_offset).y << " " << Vect<float>(neck_offset).z << " ";
            file << "0.000000 0.000000 0.000000 ";
            // head rotation
            write_0_chan(file, head_channels);
            // jaw rotation
            write_0_chan(file, jaw_channels);
            // eye_R rotation
            write_0_chan(file, eye_R_channels);
            // eye_L rotation
            write_0_chan(file, eye_L_channels);

            //file << SP_skeleton->hips->vect_rot.at(i).x << " " << SP_skeleton->hips->vect_rot.at(i).y << " " << SP_skeleton->hips->vect_rot.at(i).z << " ";
            //file << SP_skeleton->shoulder_r->vect_rot.at(i).x << " " << SP_skeleton->shoulder_r->vect_rot.at(i).y << " " << SP_skeleton->shoulder_r->vect_rot.at(i).z << " ";
            //file << SP_skeleton->elbow_r->vect_rot.at(i).x << " " << SP_skeleton->elbow_r->vect_rot.at(i).y << " " << SP_skeleton->elbow_r->vect_rot.at(i).z << " ";
            //file << SP_skeleton->hand_r->vect_rot.at(i).x << " " << SP_skeleton->hand_r->vect_rot.at(i).y << " " << SP_skeleton->hand_r->vect_rot.at(i).z << " ";
            //file << SP_skeleton->shoulder_l->vect_rot.at(i).x << " " << SP_skeleton->shoulder_l->vect_rot.at(i).y << " " << SP_skeleton->shoulder_l->vect_rot.at(i).z << " ";
            //file << SP_skeleton->elbow_l->vect_rot.at(i).x << " " << SP_skeleton->elbow_l->vect_rot.at(i).y << " " << SP_skeleton->elbow_l->vect_rot.at(i).z << " ";
            //file << SP_skeleton->hand_l->vect_rot.at(i).x << " " << SP_skeleton->hand_l->vect_rot.at(i).y << " " << SP_skeleton->hand_l->vect_rot.at(i).z << " ";
            //file << SP_skeleton->head->vect_rot.at(i).x << " " << SP_skeleton->head->vect_rot.at(i).y << " " << SP_skeleton->head->vect_rot.at(i).z << " ";

            file << endl;
            break;
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
