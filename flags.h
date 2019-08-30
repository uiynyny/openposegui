#ifndef FLAGS_H
#define FLAGS_H
#include <QObject>
#include <string>

class Flags: public QObject{
    Q_OBJECT
private:
    // Debugging
    int32_t logging_level;
    bool disable_multi_thread;
    int32_t profile_speed;

    // Producer
    int32_t camera;
    std::string camera_resolution;
    std::string video;
    std::string image_dir;
    bool flir_camera;
    int32_t flir_camera_index;
    std::string ip_camera;
    uint64_t frame_first;
    uint64_t frame_step;
    uint64_t frame_last;
    bool frame_flip;
    int32_t frame_rotate;
    bool frames_repeat;
    bool process_real_time;
    std::string camera_parameter_path;
    bool frame_undistort;

    // OpenPose
    std::string model_folder;
    std::string prototxt_path;
    std::string caffemodel_path;
    std::string output_resolution;
    int32_t num_gpu;
    int32_t num_gpu_start;
    int32_t keypoint_scale;
    int32_t number_people_max;
    bool maximize_positives;
    double fps_max;


    //OpenPose Body Pose
    int32_t body;
    std::string model_pose;
    std::string net_resolution;
    int32_t scale_number;
    double scale_gap;

    // OpenPose Body Pose Heatmaps and Part Candidates
    bool heatmaps_add_parts;
    bool heatmaps_add_bkg;
    bool heatmaps_add_PAFs;
    int32_t heatmaps_scale;
    bool part_candidates;
    double upsampling_ratio;

    // OpenPose Face
    bool face;
    int32_t face_detector;
    std::string face_net_resolution;

    // OpenPose Hand
    bool hand;
    int32_t hand_detector;
    std::string hand_net_resolution;
    int32_t hand_scale_number;
    double hand_scale_range;

    // OpenPose 3-D Reconstruction
    bool d3d;
    int32_t d3d_min_views;
    int32_t d3d_views;

    //Rendering
    int32_t part_to_show;
    bool disable_blending;

    //Rendering Pose
    double render_threshold;
    int32_t render_pose;
    double alpha_pose;
    double alpha_heatmap;

    //Result Saving
    std::string write_images;
    std::string write_images_format;
    std::string write_video;
    double write_video_fps;
    bool write_video_with_audio;
    std::string write_video_3d;
    std::string write_json;
    std::string write_coco_json;
    int32_t write_coco_json_variants;
    std::string write_heatmaps;
    std::string write_heatmaps_format;

    std::string cmd;

    static Flags *flagManager;
    Flags();

public:
    static Flags *getInstance();

    void configFlags(QString config);
    template <class T> QString parseArgument(T arg,std::string name) const;
    QString getCmd() const;
    int32_t getLogging_level() const;
    void setLogging_level(const int32_t &value);
    bool getDisable_multi_thread() const;
    void setDisable_multi_thread(bool value);
    int32_t getProfile_speed() const;
    void setProfile_speed(const int32_t &value);
    int32_t getCamera() const;
    void setCamera(const int32_t &value);
    std::string getCamera_resolution() const;
    void setCamera_resolution(const std::string &value);
    std::string getVideo() const;
    void setVideo(const std::string &value);
    std::string getImage_dir() const;
    void setImage_dir(const std::string &value);
    bool getFlir_camera() const;
    void setFlir_camera(bool value);
    int32_t getFlir_camera_index() const;
    void setFlir_camera_index(const int32_t &value);
    std::string getIp_camera() const;
    void setIp_camera(const std::string &value);
    uint64_t getFrame_first() const;
    void setFrame_first(const uint64_t &value);
    uint64_t getFrame_step() const;
    void setFrame_step(const uint64_t &value);
    uint64_t getFrame_last() const;
    void setFrame_last(const uint64_t &value);
    bool getFrame_flip() const;
    void setFrame_flip(bool value);
    int32_t getFrame_rotate() const;
    void setFrame_rotate(const int32_t &value);
    bool getFrames_repeat() const;
    void setFrames_repeat(bool value);
    bool getProcess_real_time() const;
    void setProcess_real_time(bool value);
    std::string getCamera_parameter_path() const;
    void setCamera_parameter_path(const std::string &value);
    bool getFrame_undistort() const;
    void setFrame_undistort(bool value);
    std::string getModel_folder() const;
    void setModel_folder(const std::string &value);
    std::string getPrototxt_path() const;
    void setPrototxt_path(const std::string &value);
    std::string getCaffemodel_path() const;
    void setCaffemodel_path(const std::string &value);
    std::string getOutput_resolution() const;
    void setOutput_resolution(const std::string &value);
    int32_t getNum_gpu() const;
    void setNum_gpu(const int32_t &value);
    int32_t getNum_gpu_start() const;
    void setNum_gpu_start(const int32_t &value);
    int32_t getKeypoint_scale() const;
    void setKeypoint_scale(const int32_t &value);
    int32_t getNumber_people_max() const;
    void setNumber_people_max(const int32_t &value);
    bool getMaximize_positives() const;
    void setMaximize_positives(bool value);
    double getFps_max() const;
    void setFps_max(double value);
    int32_t getBody() const;
    void setBody(const int32_t &value);
    std::string getModel_pose() const;
    void setModel_pose(const std::string &value);
    std::string getNet_resolution() const;
    void setNet_resolution(const std::string &value);
    int32_t getScale_number() const;
    void setScale_number(const int32_t &value);
    double getScale_gap() const;
    void setScale_gap(double value);
    bool getHeatmaps_add_parts() const;
    void setHeatmaps_add_parts(bool value);
    bool getHeatmaps_add_bkg() const;
    void setHeatmaps_add_bkg(bool value);
    bool getHeatmaps_add_PAFs() const;
    void setHeatmaps_add_PAFs(bool value);
    int32_t getHeatmaps_scale() const;
    void setHeatmaps_scale(const int32_t &value);
    bool getPart_candidates() const;
    void setPart_candidates(bool value);
    double getUpsampling_ratio() const;
    void setUpsampling_ratio(double value);
    bool getFace() const;
    void setFace(bool value);
    int32_t getFace_detector() const;
    void setFace_detector(const int32_t &value);
    std::string getFace_net_resolution() const;
    void setFace_net_resolution(const std::string &value);
    bool getHand() const;
    void setHand(bool value);
    int32_t getHand_detector() const;
    void setHand_detector(const int32_t &value);
    std::string getHand_net_resolution() const;
    void setHand_net_resolution(const std::string &value);
    int32_t getHand_scale_number() const;
    void setHand_scale_number(const int32_t &value);
    double getHand_scale_range() const;
    void setHand_scale_range(double value);
    bool getD3d() const;
    void setD3d(bool value);
    int32_t getD3d_min_views() const;
    void setD3d_min_views(const int32_t &value);
    int32_t getD3d_views() const;
    void setD3d_views(const int32_t &value);
    int32_t getPart_to_show() const;
    void setPart_to_show(const int32_t &value);
    bool getDisable_blending() const;
    void setDisable_blending(bool value);
    double getRender_threshold() const;
    void setRender_threshold(double value);
    int32_t getRender_pose() const;
    void setRender_pose(const int32_t &value);
    double getAlpha_pose() const;
    void setAlpha_pose(double value);
    double getAlpha_heatmap() const;
    void setAlpha_heatmap(double value);
    std::string getWrite_images() const;
    void setWrite_images(const std::string &value);
    std::string getWrite_images_format() const;
    void setWrite_images_format(const std::string &value);
    std::string getWrite_video() const;
    void setWrite_video(const std::string &value);
    double getWrite_video_fps() const;
    void setWrite_video_fps(const double &value);
    bool getWrite_video_with_audio() const;
    void setWrite_video_with_audio(bool value);
    std::string getWrite_video_3d() const;
    void setWrite_video_3d(const std::string &value);
    std::string getWrite_json() const;
    void setWrite_json(const std::string &value);
    std::string getWrite_coco_json() const;
    void setWrite_coco_json(const std::string &value);
    int32_t getWrite_coco_json_variants() const;
    void setWrite_coco_json_variants(const int32_t &value);
    std::string getWrite_heatmaps() const;
    void setWrite_heatmaps(const std::string &value);
    std::string getWrite_heatmaps_format() const;
    void setWrite_heatmaps_format(const std::string &value);
};
#endif // FLAGS_H
