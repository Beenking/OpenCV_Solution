#ifndef BODYRECOG_DEMO_H
#define BODYRECOG_DEMO_H

#include <QtGui/QMainWindow>
#include "ui_bodyrecog_demo.h"
#include <QTimer>
#include "kinect/kinect.h"
#include "kinect/capture.hpp"

class BodyRecog_Demo : public QMainWindow
{
    Q_OBJECT

public:
    BodyRecog_Demo(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~BodyRecog_Demo();

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void updateImageForDisplay(const cv::Mat &SrcImg, const int downscale, QImage* pDstImg);
    void drawImage(const QImage& img);
    void textBrowserUpdate();
    int getDepthValue(const int u, const int v);
    cv::Point3f UVd2Point3D(const int u, const int v, int const depth, CAMERA_INTRINSIC_PARAMETERS const CameraPara);
private:
    Ui::BodyRecog_DemoClass ui;

    bool m_bDynUpdate;
    bool m_bUserClicked;
    bool m_bConnected;
    QTimer* m_pTimer;
    kfusion::OpenNISource m_capture;

    QGraphicsScene *m_scene;
    QGraphicsView *m_view;

    QImage* m_pImage;
    cv::Mat* m_pDisImg;
    cv::Mat* m_pDepthImg;
    CAMERA_INTRINSIC_PARAMETERS m_camera_para;
    QPoint m_SpecifiedPt;

private slots:
    void onOpen();
    void onClose();
    void frameUpdate();
};

#endif // BODYRECOG_DEMO_H
