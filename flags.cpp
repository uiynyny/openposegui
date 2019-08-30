#include "flags.h"
#include<QString>

#include <sstream>

#define GET_VARIABLE_NAME(Variable) (#Variable)

Flags *Flags::flagManager=0;

Flags *Flags::getInstance(){
    if(!flagManager)
        flagManager=new Flags();
    return flagManager;
}

Flags::Flags(){
    logging_level=3; disable_multi_thread=false; profile_speed=1000;
    camera=-1;
    camera_resolution="-1x-1";
    video="";
    image_dir="";
    flir_camera=false;flir_camera_index=-1;ip_camera="";
    frame_first=0; frame_step=1; frame_last=-1; frame_flip=false;
    frame_rotate=0; frames_repeat=false; process_real_time=false;
    frame_undistort=false;
    camera_parameter_path="model/cameraParameters/flir/";
    model_folder="models/";
    prototxt_path="";
    output_resolution="-1x-1";
    num_gpu=-1;num_gpu_start=0;
    keypoint_scale=0;number_people_max=-1;
    maximize_positives=false;fps_max=-1.0;
    body=1;model_pose="BODY_25"; net_resolution="-1x368";scale_number=1;scale_gap=0.25;
    heatmaps_add_parts=false;heatmaps_add_bkg=false;heatmaps_add_PAFs=false;part_candidates=false;
    heatmaps_scale=2;upsampling_ratio=0.;
    face=false;face_detector=0;face_net_resolution="368x368";
    hand=false;hand_detector=0;hand_net_resolution="368x368";
    hand_scale_number=1;hand_scale_range=0.4;
    d3d=false;d3d_min_views=-1;d3d_views=-1;
    part_to_show=0; disable_blending=false;
    render_threshold=0.05;render_pose=-1;alpha_pose=0.6;alpha_heatmap=0.7;

    write_images="";write_images_format="png";write_video="";write_video_fps=-1;
    write_video_with_audio=false;write_video_3d="";write_json="";
    write_coco_json="";write_coco_json_variants=1;write_heatmaps="";
    write_heatmaps_format="png";
}

void Flags::configFlags(QString config){
    Flags *f= flagManager;
    if(config=="default"){
        f->logging_level=3; f->disable_multi_thread=false; f->profile_speed=1000;
        f->camera=-1;
        f->camera_resolution="-1x-1";
        f->video="";
        f->image_dir="";
        f->flir_camera=false;f->flir_camera_index=-1;f->ip_camera="";
        f->frame_first=0; f->frame_step=1; f->frame_last=-1; f->frame_flip=false;
        f->frame_rotate=0; f->frames_repeat=false; f->process_real_time=false;
        f->frame_undistort=false;
        f->camera_parameter_path="model/cameraParameters/flir/";
        f->model_folder="models/";
        f->prototxt_path="";
        f->output_resolution="-1x-1";
        f->num_gpu=-1;num_gpu_start=0;
        f->keypoint_scale=0;number_people_max=-1;
        f->maximize_positives=false;fps_max=-1.0;
        f->body=1;f->model_pose="BODY_25"; f->net_resolution="-1x368";f->scale_number=1;f->scale_gap=0.25;
        f->heatmaps_add_parts=false;f->heatmaps_add_bkg=false;f->heatmaps_add_PAFs=false;f->part_candidates=false;
        f->heatmaps_scale=2;upsampling_ratio=0.;
        f->face=false;f->face_detector=0;f->face_net_resolution="368x368";
        f->hand=false;f->hand_detector=0;f->hand_net_resolution="368x368";
        f->hand_scale_number=1;f->hand_scale_range=0.4;
        f->d3d=false;f->d3d_min_views=-1;f->d3d_views=-1;
        f->part_to_show=0; f->disable_blending=false;
        f->render_threshold=0.05;f->render_pose=-1;f->alpha_pose=0.6;f->alpha_heatmap=0.7;

        f->write_images="";f->write_images_format="png";f->write_video="";f->write_video_fps=-1;
        f->write_video_with_audio=false;f->write_video_3d="";f->write_json="";
        f->write_coco_json="";f->write_coco_json_variants=1;f->write_heatmaps="";
        f->write_heatmaps_format="png";
    }else if(config=="video"){
         f->logging_level=3; f->disable_multi_thread=false; f->profile_speed=1000;
         f->camera=-1;
         f->camera_resolution="-1x-1";
         f->video="";
         f->image_dir="";
         f->flir_camera=false;f->flir_camera_index=-1;f->ip_camera="";
         f->frame_first=0; f->frame_step=1; f->frame_last=-1; f->frame_flip=false;
         f->frame_rotate=0; f->frames_repeat=false; f->process_real_time=false;
         f->frame_undistort=false;
         f->camera_parameter_path="model/cameraParameters/flir/";
         f->model_folder="models/";
         f->prototxt_path="";
         f->output_resolution="-1x-1";
         f->num_gpu=-1;num_gpu_start=0;
         f->keypoint_scale=0;number_people_max=-1;
         f->maximize_positives=false;fps_max=-1.0;
         f->body=1;f->model_pose="BODY_25"; f->net_resolution="-1x368";f->scale_number=1;f->scale_gap=0.25;
         f->heatmaps_add_parts=false;f->heatmaps_add_bkg=false;f->heatmaps_add_PAFs=false;f->part_candidates=false;
         f->heatmaps_scale=2;upsampling_ratio=0.;
         f->face=false;f->face_detector=0;f->face_net_resolution="368x368";
         f->hand=false;f->hand_detector=0;f->hand_net_resolution="368x368";
         f->hand_scale_number=1;f->hand_scale_range=0.4;
         f->d3d=false;f->d3d_min_views=-1;f->d3d_views=-1;
         f->part_to_show=0; f->disable_blending=false;
         f->render_threshold=0.05;f->render_pose=-1;f->alpha_pose=0.6;f->alpha_heatmap=0.7;

         f->write_images="";f->write_images_format="png";f->write_video="";f->write_video_fps=-1;
         f->write_video_with_audio=false;f->write_video_3d="";f->write_json="out_json";
         f->write_coco_json="";f->write_coco_json_variants=1;f->write_heatmaps="";
         f->write_heatmaps_format="png";
    }
}

template <class T> QString Flags::parseArgument(T arg,std::string var_name) const{
    std::ostringstream convert;
    convert<<"--"<<var_name<<" \""<<arg<<"\" ";
    std::string result= convert.str();
    return QString::fromStdString(result);
}

QString Flags::getCmd() const
{
    QString temp;
    //debugging config
    if(logging_level!=3)
        temp += parseArgument(logging_level,GET_VARIABLE_NAME(logging_level));
    if(disable_multi_thread!=false)
        temp += parseArgument(disable_multi_thread,GET_VARIABLE_NAME(disable_multi_thread));
    if(profile_speed!=1000)
        temp += parseArgument(profile_speed,GET_VARIABLE_NAME(profile_speed));

    //source config
    if(camera!=-1){
        temp += parseArgument(camera,GET_VARIABLE_NAME(camera));
        if(camera_resolution!="-1x-1")
            temp += parseArgument(camera_resolution,GET_VARIABLE_NAME(camera_resolution));
    }else if(!video.empty())
        temp += parseArgument(video,GET_VARIABLE_NAME(video));
    else if (!image_dir.empty())
        temp += parseArgument(image_dir,GET_VARIABLE_NAME(image_dir));
    else if (!ip_camera.empty())
        temp += parseArgument(ip_camera,GET_VARIABLE_NAME(ip_camera));
    else if (flir_camera==true)
        temp += parseArgument(flir_camera,GET_VARIABLE_NAME(flir_camera))+
                parseArgument(camera_parameter_path,GET_VARIABLE_NAME(camera_parameter_path))+
                parseArgument(flir_camera_index,GET_VARIABLE_NAME(flir_camera_index));

    // frame config
    if(frame_first!=0)
        temp += parseArgument(frame_first,GET_VARIABLE_NAME(frame_first));
    if(frame_step!=1)
        temp += parseArgument(frame_step,GET_VARIABLE_NAME(frame_step));
    if(frame_last!=(uint64_t)0-1)
        temp += parseArgument(frame_last,GET_VARIABLE_NAME(frame_last));
    if(frame_flip!=false)
        temp += parseArgument(frame_flip,GET_VARIABLE_NAME(frame_flip));
    if(frame_rotate!=0)
        temp += parseArgument(frame_rotate,GET_VARIABLE_NAME(frame_rotate));
    if(frames_repeat!=false)
        temp += parseArgument(frames_repeat,GET_VARIABLE_NAME(frames_repeat));
    if(process_real_time!=false)
        temp += parseArgument(process_real_time,GET_VARIABLE_NAME(process_real_time));
    if(frame_undistort!=false)
        temp += parseArgument(frame_undistort,GET_VARIABLE_NAME(frame_undistort));

    //openpose model config
    if(model_folder!="models/")
        temp += parseArgument(model_folder,GET_VARIABLE_NAME(model_folder));
    if(!prototxt_path.empty())
        temp += parseArgument(prototxt_path,GET_VARIABLE_NAME(prototxt_path));
    if(!caffemodel_path.empty())
        temp += parseArgument(caffemodel_path,GET_VARIABLE_NAME(caffemodel_path));
    if(output_resolution!="-1x-1")
        temp += parseArgument(output_resolution,GET_VARIABLE_NAME(output_resolution));
    if(num_gpu!=-1)
        temp += parseArgument(num_gpu,GET_VARIABLE_NAME(num_gpu));
    if(num_gpu_start!=0)
        temp += parseArgument(num_gpu_start,GET_VARIABLE_NAME(num_gpu_start));
    if(keypoint_scale!=0)
        temp += parseArgument(keypoint_scale,GET_VARIABLE_NAME(keypoint_scale));
    if(number_people_max!=-1)
        temp += parseArgument(number_people_max,GET_VARIABLE_NAME(number_people_max));
    if(maximize_positives!=false)
        temp += parseArgument(maximize_positives,GET_VARIABLE_NAME(maximize_positives));
    if(fps_max!=-1.0)
        temp += parseArgument(fps_max,GET_VARIABLE_NAME(fps_max));

    //openpose body pose
    if(body!=1) temp += parseArgument(body,GET_VARIABLE_NAME(body));
    if(model_pose!="BODY_25") temp += parseArgument(model_pose,GET_VARIABLE_NAME(model_pose));
    if(net_resolution!="-1x368") temp += parseArgument(net_resolution,GET_VARIABLE_NAME(net_resolution));
    if(scale_number!=1) temp += parseArgument(scale_number,GET_VARIABLE_NAME(scale_number));
    if(scale_gap!=0.25) temp += parseArgument(scale_gap,GET_VARIABLE_NAME(scale_gap));

    // OpenPose Body Pose Heatmaps and Part Candidates
    if(heatmaps_add_parts!=false) temp += parseArgument(heatmaps_add_parts,GET_VARIABLE_NAME(heatmaps_add_parts));
    if(heatmaps_add_bkg!=false) temp += parseArgument(heatmaps_add_bkg,GET_VARIABLE_NAME(heatmaps_add_bkg));
    if(heatmaps_add_PAFs!=false) temp += parseArgument(heatmaps_add_PAFs,GET_VARIABLE_NAME(heatmaps_add_PAFs));
    if(heatmaps_scale!=2) temp += parseArgument(heatmaps_scale,GET_VARIABLE_NAME(heatmaps_scale));
    if(upsampling_ratio!=0.) temp += parseArgument(upsampling_ratio,GET_VARIABLE_NAME(upsampling_ratio));

    //openpose face
    if(face!=false) temp += parseArgument(face,GET_VARIABLE_NAME(face));
    if(face_detector!=0) temp += parseArgument(face_detector,GET_VARIABLE_NAME(face_detector));
    if(face_net_resolution!="368x368") temp += parseArgument(face_net_resolution,GET_VARIABLE_NAME(face_net_resolution));

    //openpose hand
    if(hand!=false) temp += parseArgument(hand,GET_VARIABLE_NAME(hand));
    if(hand_detector!=0) temp += parseArgument(hand_detector,GET_VARIABLE_NAME(hand_detector));
    if(hand_net_resolution!="368x368") temp += parseArgument(hand_net_resolution,GET_VARIABLE_NAME(hand_net_resolution));
    if(hand_scale_number!=1) temp +=parseArgument(hand_scale_number,GET_VARIABLE_NAME(hand_scale_number));
    if(hand_scale_range!=0.4) temp += parseArgument(hand_scale_range,GET_VARIABLE_NAME(hand_scale_range));

    //openpose 3-D reconstruction
    if(d3d!=false) temp += parseArgument(d3d,"3d");
    if(d3d_min_views!=-1) temp += parseArgument(d3d_min_views,"3d_min_views");
    if(d3d_views!=-1) temp += parseArgument(d3d_views,"3d_views");

    //Rendering
    if(part_to_show!=0) temp += parseArgument(part_to_show,GET_VARIABLE_NAME(part_to_show));
    if(disable_blending!=0) temp += parseArgument(disable_blending,GET_VARIABLE_NAME(disable_blending));

    //Rendering Pose
    if(render_threshold!=0.05) temp += parseArgument(render_threshold,GET_VARIABLE_NAME(render_threshold));
    if(render_pose!=-1) temp += parseArgument(render_pose,GET_VARIABLE_NAME(render_pose));
    if(alpha_pose!=0.6) temp += parseArgument(alpha_pose,GET_VARIABLE_NAME(alpha_pose));
    if(alpha_heatmap!=0.7) temp += parseArgument(alpha_heatmap,GET_VARIABLE_NAME(alpha_heatmap));

    //Result Saving
    if(!write_images.empty()) temp += parseArgument(write_images,GET_VARIABLE_NAME(write_images));
    if(write_images_format!="png") temp += parseArgument(write_images_format,GET_VARIABLE_NAME(write_images_format));
    if(!write_video.empty()) temp += parseArgument(write_video,GET_VARIABLE_NAME(write_video));
    if(write_video_fps!=-1.0) temp += parseArgument(write_video_fps,GET_VARIABLE_NAME(write_video_fps));
    if(write_video_with_audio!=false) temp += parseArgument(write_video_with_audio,GET_VARIABLE_NAME(write_video_with_audio));
    if(!write_video_3d.empty()) temp += parseArgument(write_video_3d,GET_VARIABLE_NAME(write_video_3d));
    if(!write_json.empty()) temp += parseArgument(write_json,GET_VARIABLE_NAME(write_json));
    if(!write_coco_json.empty()) temp += parseArgument(write_coco_json,GET_VARIABLE_NAME(write_coco_json));
    if(write_coco_json_variants!=1) temp += parseArgument(write_coco_json_variants,GET_VARIABLE_NAME(write_coco_json_variants));
    if(!write_heatmaps.empty()) temp += parseArgument(write_heatmaps,GET_VARIABLE_NAME(write_heatmaps));
    if(write_heatmaps_format!="png") temp += parseArgument(write_heatmaps_format,GET_VARIABLE_NAME(write_heatmaps_format));
    return temp;
}

int32_t Flags::getPart_to_show() const
{
    return part_to_show;
}

void Flags::setPart_to_show(const int32_t &value)
{
    part_to_show = value;
}

bool Flags::getDisable_blending() const
{
    return disable_blending;
}

void Flags::setDisable_blending(bool value)
{
    disable_blending = value;
}

double Flags::getRender_threshold() const
{
    return render_threshold;
}

void Flags::setRender_threshold(double value)
{
    render_threshold = value;
}

int32_t Flags::getRender_pose() const
{
    return render_pose;
}

void Flags::setRender_pose(const int32_t &value)
{
    render_pose = value;
}

double Flags::getAlpha_pose() const
{
    return alpha_pose;
}

void Flags::setAlpha_pose(double value)
{
    alpha_pose = value;
}

double Flags::getAlpha_heatmap() const
{
    return alpha_heatmap;
}

void Flags::setAlpha_heatmap(double value)
{
    alpha_heatmap = value;
}

std::string Flags::getWrite_images() const
{
    return write_images;
}

void Flags::setWrite_images(const std::string &value)
{
    write_images = value;
}

std::string Flags::getWrite_images_format() const
{
    return write_images_format;
}

void Flags::setWrite_images_format(const std::string &value)
{
    write_images_format = value;
}

std::string Flags::getWrite_video() const
{
    return write_video;
}

void Flags::setWrite_video(const std::string &value)
{
    write_video = value;
}

double Flags::getWrite_video_fps() const
{
    return write_video_fps;
}

void Flags::setWrite_video_fps(const double &value)
{
    write_video_fps = value;
}

bool Flags::getWrite_video_with_audio() const
{
    return write_video_with_audio;
}

void Flags::setWrite_video_with_audio(bool value)
{
    write_video_with_audio = value;
}

std::string Flags::getWrite_video_3d() const
{
    return write_video_3d;
}

void Flags::setWrite_video_3d(const std::string &value)
{
    write_video_3d = value;
}

std::string Flags::getWrite_json() const
{
    return write_json;
}

void Flags::setWrite_json(const std::string &value)
{
    write_json = value;
}

std::string Flags::getWrite_coco_json() const
{
    return write_coco_json;
}

void Flags::setWrite_coco_json(const std::string &value)
{
    write_coco_json = value;
}

int32_t Flags::getWrite_coco_json_variants() const
{
    return write_coco_json_variants;
}

void Flags::setWrite_coco_json_variants(const int32_t &value)
{
    write_coco_json_variants = value;
}

std::string Flags::getWrite_heatmaps() const
{
    return write_heatmaps;
}

void Flags::setWrite_heatmaps(const std::string &value)
{
    write_heatmaps = value;
}

std::string Flags::getWrite_heatmaps_format() const
{
    return write_heatmaps_format;
}

void Flags::setWrite_heatmaps_format(const std::string &value)
{
    write_heatmaps_format = value;
}

bool Flags::getDisable_multi_thread() const
{
    return disable_multi_thread;
}

void Flags::setDisable_multi_thread(bool value)
{
    disable_multi_thread = value;
}

int32_t Flags::getProfile_speed() const
{
return profile_speed;
}

void Flags::setProfile_speed(const int32_t &value)
{
profile_speed = value;
}

int32_t Flags::getCamera() const
{
return camera;
}

void Flags::setCamera(const int32_t &value)
{
camera = value;
}

std::string Flags::getCamera_resolution() const
{
return camera_resolution;
}

void Flags::setCamera_resolution(const std::string &value)
{
camera_resolution = value;
}

std::string Flags::getVideo() const
{
return video;
}

void Flags::setVideo(const std::string &value)
{
video = value;
}

std::string Flags::getImage_dir() const
{
return image_dir;
}

void Flags::setImage_dir(const std::string &value)
{
image_dir = value;
}

bool Flags::getFlir_camera() const
{
return flir_camera;
}

void Flags::setFlir_camera(bool value)
{
flir_camera = value;
}

int32_t Flags::getFlir_camera_index() const
{
return flir_camera_index;
}

void Flags::setFlir_camera_index(const int32_t &value)
{
flir_camera_index = value;
}

std::string Flags::getIp_camera() const
{
return ip_camera;
}

void Flags::setIp_camera(const std::string &value)
{
ip_camera = value;
}

uint64_t Flags::getFrame_first() const
{
return frame_first;
}

void Flags::setFrame_first(const uint64_t &value)
{
frame_first = value;
}

uint64_t Flags::getFrame_step() const
{
return frame_step;
}

void Flags::setFrame_step(const uint64_t &value)
{
frame_step = value;
}

uint64_t Flags::getFrame_last() const
{
return frame_last;
}

void Flags::setFrame_last(const uint64_t &value)
{
frame_last = value;
}

bool Flags::getFrame_flip() const
{
return frame_flip;
}

void Flags::setFrame_flip(bool value)
{
frame_flip = value;
}

int32_t Flags::getFrame_rotate() const
{
return frame_rotate;
}

void Flags::setFrame_rotate(const int32_t &value)
{
frame_rotate = value;
}

bool Flags::getFrames_repeat() const
{
return frames_repeat;
}

void Flags::setFrames_repeat(bool value)
{
frames_repeat = value;
}

bool Flags::getProcess_real_time() const
{
return process_real_time;
}

void Flags::setProcess_real_time(bool value)
{
process_real_time = value;
}

std::string Flags::getCamera_parameter_path() const
{
return camera_parameter_path;
}

void Flags::setCamera_parameter_path(const std::string &value)
{
camera_parameter_path = value;
}

bool Flags::getFrame_undistort() const
{
return frame_undistort;
}

void Flags::setFrame_undistort(bool value)
{
frame_undistort = value;
}

std::string Flags::getModel_folder() const
{
return model_folder;
}

void Flags::setModel_folder(const std::string &value)
{
model_folder = value;
}

std::string Flags::getPrototxt_path() const
{
return prototxt_path;
}

void Flags::setPrototxt_path(const std::string &value)
{
prototxt_path = value;
}

std::string Flags::getCaffemodel_path() const
{
return caffemodel_path;
}

void Flags::setCaffemodel_path(const std::string &value)
{
caffemodel_path = value;
}

std::string Flags::getOutput_resolution() const
{
return output_resolution;
}

void Flags::setOutput_resolution(const std::string &value)
{
output_resolution = value;
}

int32_t Flags::getNum_gpu() const
{
return num_gpu;
}

void Flags::setNum_gpu(const int32_t &value)
{
num_gpu = value;
}

int32_t Flags::getNum_gpu_start() const
{
return num_gpu_start;
}

void Flags::setNum_gpu_start(const int32_t &value)
{
num_gpu_start = value;
}

int32_t Flags::getKeypoint_scale() const
{
return keypoint_scale;
}

void Flags::setKeypoint_scale(const int32_t &value)
{
keypoint_scale = value;
}

int32_t Flags::getNumber_people_max() const
{
return number_people_max;
}

void Flags::setNumber_people_max(const int32_t &value)
{
number_people_max = value;
}

bool Flags::getMaximize_positives() const
{
return maximize_positives;
}

void Flags::setMaximize_positives(bool value)
{
maximize_positives = value;
}

double Flags::getFps_max() const
{
return fps_max;
}

void Flags::setFps_max(double value)
{
fps_max = value;
}

int32_t Flags::getBody() const
{
return body;
}

void Flags::setBody(const int32_t &value)
{
body = value;
}

std::string Flags::getModel_pose() const
{
return model_pose;
}

void Flags::setModel_pose(const std::string &value)
{
model_pose = value;
}

std::string Flags::getNet_resolution() const
{
return net_resolution;
}

void Flags::setNet_resolution(const std::string &value)
{
net_resolution = value;
}

int32_t Flags::getScale_number() const
{
return scale_number;
}

void Flags::setScale_number(const int32_t &value)
{
scale_number = value;
}

double Flags::getScale_gap() const
{
return scale_gap;
}

void Flags::setScale_gap(double value)
{
scale_gap = value;
}

bool Flags::getHeatmaps_add_parts() const
{
return heatmaps_add_parts;
}

void Flags::setHeatmaps_add_parts(bool value)
{
heatmaps_add_parts = value;
}

bool Flags::getHeatmaps_add_bkg() const
{
return heatmaps_add_bkg;
}

void Flags::setHeatmaps_add_bkg(bool value)
{
heatmaps_add_bkg = value;
}

bool Flags::getHeatmaps_add_PAFs() const
{
return heatmaps_add_PAFs;
}

void Flags::setHeatmaps_add_PAFs(bool value)
{
heatmaps_add_PAFs = value;
}

int32_t Flags::getHeatmaps_scale() const
{
return heatmaps_scale;
}

void Flags::setHeatmaps_scale(const int32_t &value)
{
heatmaps_scale = value;
}

bool Flags::getPart_candidates() const
{
return part_candidates;
}

void Flags::setPart_candidates(bool value)
{
part_candidates = value;
}

double Flags::getUpsampling_ratio() const
{
return upsampling_ratio;
}

void Flags::setUpsampling_ratio(double value)
{
upsampling_ratio = value;
}

bool Flags::getFace() const
{
return face;
}

void Flags::setFace(bool value)
{
face = value;
}

int32_t Flags::getFace_detector() const
{
return face_detector;
}

void Flags::setFace_detector(const int32_t &value)
{
face_detector = value;
}

std::string Flags::getFace_net_resolution() const
{
return face_net_resolution;
}

void Flags::setFace_net_resolution(const std::string &value)
{
face_net_resolution = value;
}

bool Flags::getHand() const
{
return hand;
}

void Flags::setHand(bool value)
{
hand = value;
}

int32_t Flags::getHand_detector() const
{
return hand_detector;
}

void Flags::setHand_detector(const int32_t &value)
{
hand_detector = value;
}

std::string Flags::getHand_net_resolution() const
{
return hand_net_resolution;
}

void Flags::setHand_net_resolution(const std::string &value)
{
hand_net_resolution = value;
}

int32_t Flags::getHand_scale_number() const
{
return hand_scale_number;
}

void Flags::setHand_scale_number(const int32_t &value)
{
hand_scale_number = value;
}

double Flags::getHand_scale_range() const
{
return hand_scale_range;
}

void Flags::setHand_scale_range(double value)
{
hand_scale_range = value;
}

bool Flags::getD3d() const
{
return d3d;
}

void Flags::setD3d(bool value)
{
d3d = value;
}

int32_t Flags::getD3d_min_views() const
{
return d3d_min_views;
}

void Flags::setD3d_min_views(const int32_t &value)
{
d3d_min_views = value;
}

int32_t Flags::getD3d_views() const
{
return d3d_views;
}

void Flags::setD3d_views(const int32_t &value)
{
d3d_views = value;
}

int32_t Flags::getLogging_level() const
{
    return logging_level;
}

void Flags::setLogging_level(const int32_t &value)
{
    logging_level = value;
}
