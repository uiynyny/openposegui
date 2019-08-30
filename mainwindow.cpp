#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>

#include <QDir>
#include <QFileDialog>
#include <QFormLayout>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>

static QString CurrentPath=QDir::currentPath();
static QString ExeFile=CurrentPath + "/openpose/OpenPoseDemo.exe";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    watcher = new QFileSystemWatcher(this);
    ui->setupUi(this);
    setContextMenuPolicy(Qt::NoContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete flags;
}

void MainWindow::setModel(Flags *model)
{
    this->flags=model;
    updateView();
}
//updating
void MainWindow::updateBody()
{
    ui->comboBox_body->setCurrentIndex(flags->getBody());
    ui->lineEdit_scale_number->setText(QString::number(flags->getScale_number()));
    ui->lineEdit_net_resolution->setText(QString::fromStdString(flags->getNet_resolution()));
    ui->comboBox_model_pose->setCurrentText(QString::fromStdString(flags->getModel_pose()));
    ui->lineEdit_scale_gap->setText(QString::number(flags->getScale_gap()));
}

void MainWindow::updateDebugging()
{
    ui->spinBox_logging_level->setValue(flags->getLogging_level());
    ui->spinBox_profile_speed->setValue(flags->getProfile_speed());
    ui->checkBox_disable_blending->setChecked(flags->getDisable_multi_thread());
}

void MainWindow::updateCmd()
{
    ui->plainTextEdit_cmd->setPlainText(ExeFile+" "+flags->getCmd());
}

void MainWindow::updateResult()
{
    QString label = "write video fps";
    QString ask = "<font color=\"red\">*</font>";
    ui->lineEdit_write_images->setText(QString::fromStdString(flags->getWrite_images()));
    ui->comboBox_write_images_format->setCurrentText(QString::fromStdString(flags->getWrite_images_format()));
    ui->lineEdit_write_video->setText(QString::fromStdString(flags->getWrite_video()));

    if(!flags->getWrite_video().empty()){
        ui->label_write_video_fps->setText(label+ask);
    }else{
        ui->label_write_video_fps->setText(label);
    }
    ui->doubleSpinBox_write_video_fps->setValue(flags->getWrite_video_fps());
    ui->checkBox_write_video_with_audio->setChecked(flags->getWrite_video_with_audio());
    ui->lineEdit_write_video_3d->setText(QString::fromStdString(flags->getWrite_video_3d()));
    ui->lineEdit_write_json->setText(QString::fromStdString(flags->getWrite_json()));
    ui->lineEdit_write_coco_json->setText(QString::fromStdString(flags->getWrite_coco_json()));
    ui->lineEdit_write_heatmaps->setText(QString::fromStdString(flags->getWrite_heatmaps()));
    ui->comboBox_write_heatmaps_format->setCurrentText(QString::fromStdString(flags->getWrite_heatmaps()));
    int temp = flags->getWrite_coco_json_variants();
    if(temp>0){
        ui->checkBox_body->setCheckState(Qt::CheckState::Checked);
        temp-=1;
    }
    if(temp>=2){
        ui->checkBox_feet->setCheckState(Qt::CheckState::Checked);
        temp-=2;
    }
    if(temp>=4){
        ui->checkBox_face->setCheckState(Qt::CheckState::Checked);
        temp-=4;
    }
    if(temp>=8){
        ui->checkBox_hands->setCheckState(Qt::CheckState::Checked);
    }
}

void MainWindow::updateProducer()
{
    ui->lineEdit_camera_resolution->setText(QString::fromStdString(flags->getCamera_resolution()));
    if(ui->radioButton_flir_camera->isChecked()||ui->radioButton_ip_camera->isChecked()||ui->radioButton_camera->isChecked()){
        ui->lineEdit_camera_parameter_path->setEnabled(true);
        ui->lineEdit_camera_resolution->setEnabled(true);
        ui->pushButton_open_dir->setEnabled(false);
    }else if(ui->radioButton_image_dir->isChecked()||ui->radioButton_video->isChecked()){
        ui->lineEdit_camera_parameter_path->setEnabled(false);
        ui->lineEdit_camera_resolution->setEnabled(false);
        ui->pushButton_open_dir->setEnabled(true);
    }else{
        ui->radioButton_camera->click();
    }
    ui->lineEdit_dir->setEnabled(true);
    ui->lineEdit_camera_parameter_path->setText(QString::fromStdString(flags->getCamera_parameter_path()));
}

void MainWindow::updateGeneral()
{
    ui->lineEdit_model_folder->setText(QString::fromStdString(flags->getModel_folder()));
    ui->lineEdit_prototxt_path->setText(QString::fromStdString(flags->getPrototxt_path()));
    ui->lineEdit_caffemodel_path->setText(QString::fromStdString(flags->getCaffemodel_path()));
    ui->lineEdit_output_resolution->setText(QString::fromStdString(flags->getOutput_resolution()));
    ui->spinBox_num_gpu->setValue(flags->getNum_gpu());
    ui->spinBox_num_gpu_start->setValue(flags->getNum_gpu_start());
    ui->spinBox_number_people_max->setValue(flags->getNumber_people_max());
    ui->checkBox_maximize_positives->setChecked(flags->getMaximize_positives());
    ui->doubleSpinBox_fps_max->setValue(flags->getFps_max());
}

void MainWindow::updateView(){
    updateDebugging();
    updateProducer();

    ui->lineEdit_frame_first->setText(QString::number(flags->getFrame_first()));
    ui->lineEdit_frame_step->setText(QString::number(flags->getFrame_step()));
    ui->checkBox_frame_undistort->setChecked(flags->getFrame_undistort());

    updateGeneral();

    updateBody();

    ui->checkBox_heatmaps_add_parts->setChecked(flags->getHeatmaps_add_parts());
    ui->checkBox_heatmaps_add_PAFs->setChecked(flags->getHeatmaps_add_PAFs());
    ui->checkBox_heatmaps_add_bkg->setChecked(flags->getHeatmaps_add_bkg());
    ui->lineEdit_upsampling_ratio->setText(QString::number(flags->getUpsampling_ratio()));

    ui->groupBox_face->setChecked(flags->getFace());
    ui->lineEdit_face_net_resolution->setText(QString::fromStdString(flags->getFace_net_resolution()));

    ui->groupBox_hand->setChecked(flags->getHand());

    ui->lineEdit_hand_net_resolution->setText(QString::fromStdString(flags->getHand_net_resolution()));
    ui->lineEdit_hand_scale_number->setText(QString::number(flags->getHand_scale_number()));
    ui->lineEdit_hand_scale_range->setText(QString::number(flags->getHand_scale_range()));

    ui->groupBox_3d->setChecked(flags->getD3d());
    ui->lineEdit_3d_min_views->setText(QString::number(flags->getD3d_min_views()));
    ui->lineEdit_3d_views->setText(QString::number(flags->getD3d_views()));
    updateCmd();

    ui->lineEdit_part_to_show->setText(QString::number(flags->getPart_to_show()));
    ui->checkBox_disable_blending->setChecked(flags->getDisable_blending());

    //Render pose
    ui->doubleSpinBox_alpha_heatmap->setValue(flags->getAlpha_heatmap());
    ui->doubleSpinBox_render_threshold->setValue(flags->getRender_threshold());
    ui->doubleSpinBox_alpha_pose->setValue(flags->getAlpha_pose());

    updateResult();
}

void MainWindow::on_actionrun_triggered()
{
    QProcess *p = new QProcess(this);
    p->setProcessChannelMode(QProcess::MergedChannels);
    disconnect(p,SIGNAL(finished(int)),this,SLOT(showState(int)));
    connect(p,SIGNAL(finished(int)),this,SLOT(showState(int)));
    p->setWorkingDirectory(QDir::currentPath());
//    p->start(QString("cmd.exe /C start  %1 %2").arg(ExeFile).arg(flags->getCmd()));
    qDebug()<<"start";
//    p->start("D:/yanzhang/project/build-OpenPoseGUI-Desktop_Qt_5_11_1_MSVC2015_64bit-Debug/openpose/OpenPoseDemo.exe --video D:/OpenPose/China.mp4");
    p->start(("\""+ExeFile+"\" %1").arg(flags->getCmd()));
    p->waitForFinished();
    QString result = QString(p->readAllStandardOutput());
    qDebug()<<result;
    if(!result.isNull()){
        QMessageBox(QMessageBox::NoIcon,"result",result,QMessageBox::Ok,this,Qt::Dialog).exec();
    }
}

void MainWindow::on_actionconfiguration_triggered()
{
    QString openPose=QFileDialog::getOpenFileName(this,tr("OpenPoseDemo path"),CurrentPath,tr("exe(*.exe);;All files(*)"));
    if(!openPose.isNull()){
        CurrentPath=QFileInfo(openPose).absolutePath();
        ExeFile=openPose;
    }
}

void MainWindow::on_actionuse_default_profile_triggered()
{
    flags->configFlags("default");
    ui->radioButton_camera->click();
    updateView();
}

void MainWindow::on_actionvideo_triggered()
{
    flags->configFlags("video");
    ui->radioButton_video->click();
    updateView();
}

void MainWindow::showState(int arg){
    qDebug()<<"finish:"<<arg;

    if(ui->CheckBox_json2csv->isChecked()){
        QFileInfoList::iterator it;
        QFileInfoList qil = QDir(QString::fromStdString(flags->getWrite_json())).entryInfoList({"VID_*.json"},QDir::NoDotAndDotDot|QDir::AllEntries);
        std::ofstream of(flags->getWrite_json()+"/final.json",std::ios_base::binary);
        of<<"[";
        for(it=qil.begin();it!=qil.end();it++){
            std::ifstream ifs(it->filePath().toStdString(),std::ios_base::binary);
            of<<ifs.rdbuf();
            if(it+1!=qil.end()) of<<",";
        }
        of<<"]";
        of.close();

        QProcess *ps = new QProcess(this);
        ps->start("openpose/json2csv.exe",{QString::fromStdString(flags->getWrite_json())+"/final.json",
                                           QString::fromStdString(flags->getWrite_json())+"/final.csv"});
        ps->waitForFinished();
        QString result = QString(ps->readAllStandardOutput());
        qDebug()<<result;
        if(!result.isNull()&&!result.isEmpty()){
            QMessageBox(QMessageBox::NoIcon,tr("Convert result"),result).exec();
        }
    }
}

void MainWindow::on_pushButton_generate_clicked()
{
    ui->plainTextEdit_cmd->setPlainText(ExeFile+" "+flags->getCmd());
    updateCmd();
    on_actionrun_triggered();
}

void MainWindow::on_pushButton_open_model_folder_clicked()
{
    QString model_folder = QFileDialog::getExistingDirectory(this,tr("open model folder"),CurrentPath,QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(!model_folder.isNull()){
        flags->setModel_folder(model_folder.toStdString());
        updateCmd();
        updateGeneral();
    }
}

void MainWindow::on_lineEdit_model_folder_textEdited(const QString &arg1)
{
    QString def_arg = "models/";
    flags->setModel_folder(arg1.isEmpty()? def_arg.toStdString():arg1.toStdString());
    updateCmd();
}

void MainWindow::on_pushButton_open_prototxt_path_clicked()
{
    QString prototxt_folder=QFileDialog::getExistingDirectory(this,tr("open prototxt folder"),CurrentPath,QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(!prototxt_folder.isNull()){
        flags->setPrototxt_path(prototxt_folder.toStdString());
        updateCmd();
        updateGeneral();
    }
}

void MainWindow::on_lineEdit_prototxt_path_textEdited(const QString &arg1)
{
    flags->setPrototxt_path(arg1.toStdString());
    updateCmd();
}

void MainWindow::on_pushButton_open_caffemodel_path_clicked()
{
    QString caffe_model=QFileDialog::getExistingDirectory(this,tr("open caffe model folder"),CurrentPath,QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);

    if(!caffe_model.isNull()){
        flags->setCaffemodel_path(caffe_model.toStdString());
        updateCmd();
        updateGeneral();
    }
}

void MainWindow::on_lineEdit_caffemodel_path_textEdited(const QString &arg1)
{
    flags->setCaffemodel_path(arg1.toStdString());
    updateCmd();
}

void MainWindow::on_lineEdit_output_resolution_textEdited(const QString &arg1)
{
    QString def_arg="-1x-1";
    flags->setOutput_resolution(arg1.isEmpty()? def_arg.toStdString():arg1.toStdString());
    updateCmd();
}

void MainWindow::on_spinBox_number_people_max_valueChanged(int arg1)
{
    flags->setNumber_people_max(arg1);
    updateCmd();
}

void MainWindow::on_comboBox_keypoint_scale_currentIndexChanged(int index)
{
    flags->setKeypoint_scale(index);
    updateCmd();
}

void MainWindow::on_radioButton_flir_camera_clicked(bool checked)
{
    if(checked){
        ui->label_dir->setText(tr("index"));
        ui->lineEdit_dir->setText(QString::number(flags->getFlir_camera_index()));
    }
    flags->setCamera(-1);
    flags->setFlir_camera(checked);
    flags->setIp_camera("");
    flags->setImage_dir("");
    flags->setVideo("");
    updateProducer();
    updateCmd();
}

void MainWindow::on_radioButton_ip_camera_clicked(bool checked)
{
     if(checked){
         ui->label_dir->setText("path<font color=\"red\">*</font>");
         ui->lineEdit_dir->setText(QString::fromStdString(flags->getIp_camera()));
     }
     flags->setCamera(-1);
     flags->setFlir_camera(false);
     flags->setFlir_camera_index(-1);
     flags->setImage_dir("");
     flags->setVideo("");
     updateProducer();
     updateCmd();
}

void MainWindow::on_radioButton_video_clicked(bool checked)
{
    if(checked){
        ui->label_dir->setText("video<font color=\"red\">*</font>");
        ui->lineEdit_dir->setText(QString::fromStdString(flags->getVideo()));
    }
    flags->setCamera(-1);
    flags->setFlir_camera(false);
    flags->setFlir_camera_index(-1);
    flags->setIp_camera("");
    flags->setImage_dir("");
    flags->setVideo("");
    updateProducer();
    updateCmd();
}

void MainWindow::on_radioButton_image_dir_clicked()
{
    ui->label_dir->setText("directory<font color=\"red\">*</font>");
    ui->lineEdit_dir->setText(QString::fromStdString(flags->getImage_dir()));
    flags->setCamera(-1);
    flags->setFlir_camera(false);
    flags->setFlir_camera_index(-1);
    flags->setIp_camera("");
    flags->setVideo("");
    updateProducer();
    updateCmd();
}

void MainWindow::on_radioButton_camera_clicked(bool checked)
{
    if(checked){
        ui->label_dir->setText(tr("index"));
        ui->lineEdit_dir->setText(QString::number(flags->getCamera()));
    }
    flags->setFlir_camera(false);
    flags->setFlir_camera_index(-1);
    flags->setIp_camera("");
    flags->setImage_dir("");
    flags->setVideo("");
    updateProducer();
    updateCmd();
}

void MainWindow::on_pushButton_open_dir_clicked()
{
    QString title;
    QString result;
    if(ui->radioButton_image_dir->isChecked()){
        result=QFileDialog::getExistingDirectory(this,tr("open image directory"),CurrentPath,QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    }else if(ui->radioButton_video->isChecked()){
        result=QFileDialog::getOpenFileName(this,tr("open video"),CurrentPath,tr("Videos (*.avi *.mp4 *.mov *.mpg);;All files(*)"));
    }
    if(!result.isNull()){
        ui->lineEdit_dir->setText(result);
        if(ui->radioButton_image_dir->isChecked())
            flags->setImage_dir(result.toStdString());
        else if(ui->radioButton_video->isChecked())
            flags->setVideo(result.toStdString());
    }
    updateCmd();
}

void MainWindow::on_lineEdit_dir_textEdited(const QString &arg1)
{
    if(ui->radioButton_camera->isChecked()){
        flags->setCamera(arg1.toInt());
    }
    if(ui->radioButton_flir_camera->isChecked()){
        flags->setFlir_camera_index(arg1.toInt());
    }else if(ui->radioButton_image_dir->isChecked()){
        flags->setImage_dir(arg1.toStdString());
    }else if(ui->radioButton_video->isChecked()){
        flags->setVideo(arg1.toStdString());
    }else if(ui->radioButton_ip_camera->isChecked()){
        flags->setIp_camera(arg1.toStdString());
    }
    updateCmd();
}

void MainWindow::on_lineEdit_frame_first_textEdited(const QString &arg1)
{
    flags->setFrame_first(arg1.toUInt());
    updateCmd();
}

void MainWindow::on_lineEdit_frame_last_textEdited(const QString &arg1)
{
    flags->setFrame_last(arg1.toUInt());
    updateCmd();
}

void MainWindow::on_lineEdit_frame_step_textEdited(const QString &arg1)
{
    flags->setFrame_step(arg1.toUInt());
    updateCmd();
}

void MainWindow::on_lineEdit_camera_parameter_path_textEdited(const QString &arg1)
{
    QString def_arg = "models/cameraParameters/flir/";
    flags->setCamera_parameter_path(arg1.isEmpty()? def_arg.toStdString():arg1.toStdString());
    updateCmd();
}

void MainWindow::on_comboBox_frame_rotate_currentIndexChanged(const QString &arg1)
{
    flags->setFrame_rotate(arg1.toInt());
    updateCmd();
}

void MainWindow::on_checkBox_maximize_positives_stateChanged(int arg1)
{
    flags->setMaximize_positives(arg1);
    updateCmd();
}

void MainWindow::on_checkBox_frame_repeat_stateChanged(int arg1)
{
    flags->setFrames_repeat(arg1);
    updateCmd();
}

void MainWindow::on_checkBox_process_ream_time_stateChanged(int arg1)
{
    flags->setProcess_real_time(arg1);
    updateCmd();
}

void MainWindow::on_checkBox_frame_undistort_stateChanged(int arg1)
{
    flags->setFrame_undistort(arg1);
    updateCmd();
}

void MainWindow::on_checkBox_frame_flip_stateChanged(int arg1)
{
    flags->setFrame_flip(arg1);
    updateCmd();
}

void MainWindow::on_comboBox_body_currentIndexChanged(int index)
{
    flags->setBody(index);
    updateCmd();
}

void MainWindow::on_comboBox_heatmaps_scale_currentIndexChanged(int index)
{
    flags->setHeatmaps_scale(index);
    updateCmd();
}

void MainWindow::on_comboBox_model_pose_currentIndexChanged(const QString &arg1)
{
    flags->setModel_pose(arg1.toStdString());
    updateCmd();
}

void MainWindow::on_lineEdit_net_resolution_textEdited(const QString &arg1)
{
    QString def_arg = "-1x368";
    flags->setNet_resolution(arg1.isEmpty()? def_arg.toStdString():arg1.toStdString());
    updateCmd();
}

void MainWindow::on_lineEdit_scale_number_textEdited(const QString &arg1)
{
    flags->setScale_number(arg1.toInt());
    updateCmd();
}

void MainWindow::on_lineEdit_scale_gap_textEdited(const QString &arg1)
{
    flags->setScale_gap(arg1.toDouble());
    updateCmd();
}

void MainWindow::on_lineEdit_upsampling_ratio_textEdited(const QString &arg1)
{
    flags->setUpsampling_ratio(arg1.toDouble());
    updateCmd();
}

void MainWindow::on_checkBox_heatmaps_add_parts_stateChanged(int arg1)
{
    flags->setHeatmaps_add_parts(arg1);
    updateCmd();
}

void MainWindow::on_checkBox_heatmaps_add_bkg_stateChanged(int arg1)
{
    flags->setHeatmaps_add_bkg(arg1);
    updateCmd();

}

void MainWindow::on_checkBox_heatmaps_add_PAFs_stateChanged(int arg1)
{
    flags->setHeatmaps_add_PAFs(arg1);
    updateCmd();

}

void MainWindow::on_checkBox_part_candidates_stateChanged(int arg1)
{
    flags->setPart_candidates(arg1);
    updateCmd();
}

void MainWindow::on_groupBox_face_toggled(bool arg1)
{
    flags->setFace(arg1);
    updateCmd();
}

void MainWindow::on_comboBox_face_detector_currentIndexChanged(int index)
{
    flags->setFace_detector(index);
    updateCmd();
}



void MainWindow::on_lineEdit_face_net_resolution_textEdited(const QString &arg1)
{
    QString def_arg = "368x368";
    flags->setFace_net_resolution(arg1.isEmpty()? def_arg.toStdString():arg1.toStdString());
    updateView();
}

void MainWindow::on_comboBox_hand_detector_currentIndexChanged(int index)
{
    flags->setHand_detector(index);
    updateView();
}

void MainWindow::on_groupBox_hand_toggled(bool arg1)
{
    flags->setHand(arg1);
    updateCmd();
}

void MainWindow::on_lineEdit_hand_net_resolution_textEdited(const QString &arg1)
{
    QString def_arg = "368x368";
    flags->setHand_net_resolution(arg1.isEmpty()? def_arg.toStdString():arg1.toStdString());
    updateCmd();
}

void MainWindow::on_lineEdit_hand_scale_number_textEdited(const QString &arg1)
{
    flags->setHand_scale_number(arg1.toInt());
    updateCmd();
}

void MainWindow::on_lineEdit_hand_scale_range_textEdited(const QString &arg1)
{
    flags->setHand_scale_range(arg1.toDouble());
    updateCmd();
}

void MainWindow::on_groupBox_3d_toggled(bool arg1)
{
    flags->setD3d(arg1);
    updateCmd();
}

void MainWindow::on_lineEdit_3d_min_views_textEdited(const QString &arg1)
{
    flags->setD3d_min_views(arg1.toInt());
    updateCmd();
}

void MainWindow::on_lineEdit_3d_views_textEdited(const QString &arg1)
{
    flags->setD3d_views(arg1.toInt());
    updateCmd();
}

void MainWindow::on_checkBox_disable_blending_stateChanged(int arg1)
{
    flags->setDisable_blending(arg1);
    updateCmd();
}

void MainWindow::on_lineEdit_part_to_show_textEdited(const QString &arg1)
{
    flags->setPart_to_show(arg1.toInt());
    updateCmd();
}


//logging
void MainWindow::on_spinBox_logging_level_valueChanged(int arg1)
{
    flags->setLogging_level(arg1);
    updateCmd();
}

void MainWindow::on_spinBox_profile_speed_valueChanged(int arg1)
{
    flags->setProfile_speed(arg1);
    updateCmd();
}

void MainWindow::on_Checkbox_multi_thread_stateChanged(int arg1)
{
    flags->setDisable_multi_thread(arg1);
    updateCmd();
}

//Render Pose
void MainWindow::on_comboBox_render_pose_currentIndexChanged(int index)
{
    flags->setRender_pose(index-1);
    updateCmd();
}

void MainWindow::on_doubleSpinBox_render_threshold_valueChanged(double arg1)
{
    flags->setRender_threshold(arg1);
    updateCmd();
}

void MainWindow::on_doubleSpinBox_alpha_pose_valueChanged(double arg1)
{
    flags->setAlpha_pose(arg1);
    updateCmd();
}

void MainWindow::on_doubleSpinBox_alpha_heatmap_valueChanged(double arg1)
{
    flags->setAlpha_heatmap(arg1);
    updateCmd();
}

void MainWindow::on_pushButton_write_images_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,tr("save images"),CurrentPath,QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(!dir.isNull()){
        flags->setWrite_images(dir.toStdString());
    }
    updateResult();
    updateCmd();
}

void MainWindow::on_lineEdit_write_images_textEdited(const QString &arg1)
{
    flags->setWrite_images(arg1.toStdString());
    updateCmd();
}

void MainWindow::on_comboBox_write_images_format_currentIndexChanged(const QString &arg1)
{
    flags->setWrite_images_format(arg1.toStdString());
    updateCmd();
}

void MainWindow::on_lineEdit_write_video_textEdited(const QString &arg1)
{
    flags->setWrite_video(arg1.toStdString());
    updateResult();
    updateCmd();
}

void MainWindow::on_lineEdit_write_video_3d_textEdited(const QString &arg1)
{
    flags->setWrite_video_3d(arg1.toStdString());
    updateCmd();
}

void MainWindow::on_lineEdit_write_json_textEdited(const QString &arg1)
{
    flags->setWrite_json(arg1.toStdString());

    updateCmd();
}

void MainWindow::on_lineEdit_write_coco_json_textEdited(const QString &arg1)
{
    flags->setWrite_coco_json(arg1.toStdString());
    updateCmd();
}

void MainWindow::on_comboBox_write_heatmaps_format_currentIndexChanged(const QString &arg1)
{
    flags->setWrite_heatmaps_format(arg1.toStdString());
    updateCmd();
}

void MainWindow::on_lineEdit_write_heatmaps_textEdited(const QString &arg1)
{
    flags->setWrite_heatmaps(arg1.toStdString());
    updateCmd();
}

void MainWindow::on_checkBox_write_video_with_audio_stateChanged(int arg1)
{
    flags->setWrite_video_with_audio(arg1);
    updateCmd();
}

//general
void MainWindow::on_doubleSpinBox_fps_max_valueChanged(double arg1)
{
   flags->setFps_max(arg1);
   updateCmd();
}

void MainWindow::on_spinBox_num_gpu_start_valueChanged(int arg1)
{
    flags->setNum_gpu_start(arg1);
    updateCmd();
}

void MainWindow::on_spinBox_num_gpu_valueChanged(int arg1)
{
    flags->setNum_gpu(arg1);
    updateCmd();
}

void MainWindow::on_doubleSpinBox_write_video_fps_valueChanged(double arg1)
{
    flags->setWrite_video_fps(arg1);
    updateCmd();
}

void MainWindow::on_checkBox_body_stateChanged(int arg1)
{
    int variant = flags->getWrite_coco_json_variants();
    if(arg1==Qt::CheckState::Checked){
        variant= variant == 1? variant: variant+=1;
    }else{
        variant-=1;
    }
    flags->setWrite_coco_json_variants(variant);
    updateCmd();
}

void MainWindow::on_checkBox_feet_stateChanged(int arg1)
{
    int variant = flags->getWrite_coco_json_variants();
    if(arg1==Qt::CheckState::Checked){
        variant+=2;
    }else{
        variant-=2;
    }
    flags->setWrite_coco_json_variants(variant);
    updateCmd();
}

void MainWindow::on_checkBox_face_stateChanged(int arg1)
{
    int variant = flags->getWrite_coco_json_variants();
    if(arg1==Qt::CheckState::Checked){
        variant+=4;
    }else{
        variant-=4;
    }
    flags->setWrite_coco_json_variants(variant);
    updateCmd();
}

void MainWindow::on_checkBox_hands_stateChanged(int arg1)
{
    int variant = flags->getWrite_coco_json_variants();
    if(arg1==Qt::CheckState::Checked){
        variant+=8;
    }else{
        variant-=8;
    }
    flags->setWrite_coco_json_variants(variant);
    updateCmd();
}

void MainWindow::on_lineEdit_camera_resolution_textEdited(const QString &arg1)
{
    QString def_arg ="-1x-1";
    flags->setCamera_resolution(arg1.isEmpty()? def_arg.toStdString():arg1.toStdString());
    updateCmd();
}

void MainWindow::on_pushButton_write_video_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,tr("save video"),CurrentPath,QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);

    if(!dir.isNull()&&!dir.isEmpty()){
        dir+="/compose.avi";
        flags->setWrite_video(dir.toStdString());
    }
    updateResult();
    updateCmd();
}

