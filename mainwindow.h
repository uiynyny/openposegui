#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileInfoList>
#include <QFileSystemWatcher>
#include <QMainWindow>
#include "flags.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setModel(Flags* model);
    ~MainWindow();

private slots:

    //menu bar
    void on_actionrun_triggered();

    void on_actionconfiguration_triggered();

    void on_pushButton_open_model_folder_clicked();

    void on_pushButton_open_prototxt_path_clicked();

    void on_pushButton_open_caffemodel_path_clicked();

    void on_lineEdit_output_resolution_textEdited(const QString &arg1);

    void on_doubleSpinBox_fps_max_valueChanged(double arg1);

    void on_pushButton_generate_clicked();

    void on_lineEdit_model_folder_textEdited(const QString &arg1);

    void on_lineEdit_caffemodel_path_textEdited(const QString &arg1);

    void on_lineEdit_prototxt_path_textEdited(const QString &arg1);

    void on_spinBox_number_people_max_valueChanged(int arg1);

    void on_radioButton_flir_camera_clicked(bool checked);

    void on_radioButton_ip_camera_clicked(bool checked);

    void on_radioButton_video_clicked(bool checked);

    void on_radioButton_image_dir_clicked();

    void on_radioButton_camera_clicked(bool checked);

    void on_pushButton_open_dir_clicked();

    void on_lineEdit_dir_textEdited(const QString &arg1);

    void on_lineEdit_frame_first_textEdited(const QString &arg1);

    void on_lineEdit_frame_last_textEdited(const QString &arg1);

    void on_lineEdit_frame_step_textEdited(const QString &arg1);

    void on_lineEdit_camera_parameter_path_textEdited(const QString &arg1);

    void on_checkBox_maximize_positives_stateChanged(int arg1);

    void on_checkBox_frame_repeat_stateChanged(int arg1);

    void on_checkBox_process_ream_time_stateChanged(int arg1);

    void on_checkBox_frame_undistort_stateChanged(int arg1);

    void on_checkBox_frame_flip_stateChanged(int arg1);

    void on_comboBox_body_currentIndexChanged(int index);

    void on_comboBox_heatmaps_scale_currentIndexChanged(int index);

    void on_comboBox_model_pose_currentIndexChanged(const QString &arg1);

    void on_lineEdit_net_resolution_textEdited(const QString &arg1);

    void on_lineEdit_scale_number_textEdited(const QString &arg1);

    void on_lineEdit_scale_gap_textEdited(const QString &arg1);

    void on_lineEdit_upsampling_ratio_textEdited(const QString &arg1);

    void on_checkBox_heatmaps_add_parts_stateChanged(int arg1);

    void on_checkBox_heatmaps_add_bkg_stateChanged(int arg1);

    void on_checkBox_heatmaps_add_PAFs_stateChanged(int arg1);

    void on_checkBox_part_candidates_stateChanged(int arg1);

    void on_comboBox_face_detector_currentIndexChanged(int index);

    void on_groupBox_face_toggled(bool arg1);

    void on_lineEdit_face_net_resolution_textEdited(const QString &arg1);

    void on_comboBox_hand_detector_currentIndexChanged(int index);

    void on_groupBox_hand_toggled(bool arg1);

    void on_lineEdit_hand_net_resolution_textEdited(const QString &arg1);

    void on_lineEdit_hand_scale_number_textEdited(const QString &arg1);

    void on_lineEdit_hand_scale_range_textEdited(const QString &arg1);

    void on_groupBox_3d_toggled(bool arg1);

    void on_lineEdit_3d_min_views_textEdited(const QString &arg1);

    void on_lineEdit_3d_views_textEdited(const QString &arg1);

    void on_lineEdit_part_to_show_textEdited(const QString &arg1);

    void on_checkBox_disable_blending_stateChanged(int arg1);

    void on_comboBox_keypoint_scale_currentIndexChanged(int index);

    void on_comboBox_frame_rotate_currentIndexChanged(const QString &arg1);

    //logging
    void on_spinBox_logging_level_valueChanged(int arg1);

    void on_spinBox_profile_speed_valueChanged(int arg1);

    void on_Checkbox_multi_thread_stateChanged(int arg1);

    // render pose
    void on_comboBox_render_pose_currentIndexChanged(int index);

    void on_doubleSpinBox_render_threshold_valueChanged(double arg1);

    void on_doubleSpinBox_alpha_pose_valueChanged(double arg1);

    void on_doubleSpinBox_alpha_heatmap_valueChanged(double arg1);

    //save result
    void on_pushButton_write_images_clicked();

    void on_lineEdit_write_images_textEdited(const QString &arg1);

    void on_comboBox_write_images_format_currentIndexChanged(const QString &arg1);

    void on_lineEdit_write_video_textEdited(const QString &arg1);

    void on_lineEdit_write_video_3d_textEdited(const QString &arg1);

    void on_lineEdit_write_json_textEdited(const QString &arg1);

    void on_lineEdit_write_coco_json_textEdited(const QString &arg1);

    void on_comboBox_write_heatmaps_format_currentIndexChanged(const QString &arg1);

    void on_lineEdit_write_heatmaps_textEdited(const QString &arg1);

    void on_checkBox_write_video_with_audio_stateChanged(int arg1);

    void on_spinBox_num_gpu_start_valueChanged(int arg1);

    void on_spinBox_num_gpu_valueChanged(int arg1);

    void on_doubleSpinBox_write_video_fps_valueChanged(double arg1);

    void on_checkBox_feet_stateChanged(int arg1);

    void on_checkBox_body_stateChanged(int arg1);

    void on_checkBox_hands_stateChanged(int arg1);

    void on_checkBox_face_stateChanged(int arg1);

    void on_actionuse_default_profile_triggered();

    void on_lineEdit_camera_resolution_textEdited(const QString &arg1);

    void on_pushButton_write_video_clicked();

    void showState(int arg);

    void on_actionvideo_triggered();

private:
    Ui::MainWindow *ui;
    Flags *flags;
    QFileInfoList listFile;

    void updateView();
    void updateBody();
    void updateDebugging();
    void updateCmd();
    void updateResult();
    void updateProducer();

    void setWatcher(const QString &path);
    QFileSystemWatcher *watcher;

    void updateGeneral();
};

#endif // MAINWINDOW_H
