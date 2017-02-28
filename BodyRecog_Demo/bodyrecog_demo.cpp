#include "bodyrecog_demo.h"
#include <QGraphicsView>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>

BodyRecog_Demo::BodyRecog_Demo(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
    , m_pTimer(nullptr)
    , m_scene(nullptr)
    , m_view(nullptr)
{
    ui.setupUi(this);

    m_bDynUpdate = false;
    m_bConnected = false;
    m_bUserClicked = false;
    m_camera_para.cx = KINECT_COLOR_IMG_WIDTH/2 - 0.5;
    m_camera_para.cy = KINECT_COLOR_IMG_HEIGHT/2 - 0.5;
    m_camera_para.fx = 525.0;
    m_camera_para.fy = 525.0;
    m_camera_para.scale = 1.0;

    m_pTimer = new QTimer(this);
    m_scene = new QGraphicsScene;

    m_pImage = new QImage(KINECT_COLOR_IMG_WIDTH, KINECT_COLOR_IMG_HEIGHT, QImage::Format_RGB32);
    m_pDisImg = new cv::Mat(KINECT_COLOR_IMG_WIDTH, KINECT_COLOR_IMG_HEIGHT, CV_8UC3);
    m_pDepthImg = new cv::Mat(KINECT_COLOR_IMG_WIDTH, KINECT_COLOR_IMG_HEIGHT, CV_16UC1);

    m_view = new QGraphicsView(this);
    m_view->setObjectName(QString("colorLeftGraphicsView"));
    m_view->setMouseTracking(true);
    m_view->setFocusPolicy(Qt::NoFocus);
    this->ui.groupBox->layout()->addWidget(m_view);

    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(frameUpdate()));
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(onOpen()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(onClose()));

    this->ui.pushButton->setEnabled(true);
    this->ui.pushButton_2->setEnabled(true);
}

BodyRecog_Demo::~BodyRecog_Demo()
{
    SAFE_DELETE_PTR(m_pDepthImg);
    SAFE_DELETE_PTR(m_pDisImg);
    SAFE_DELETE_PTR(m_pImage);
    SAFE_DELETE_PTR(m_pTimer);
    SAFE_DELETE_PTR(m_view);
    SAFE_DELETE_PTR(m_scene);
}

void BodyRecog_Demo::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_D)
    {
        m_bDynUpdate ^= 1;
    }
}

void BodyRecog_Demo::mousePressEvent(QMouseEvent *event)
{
    if (!m_bConnected) return;
    if (event->button() == Qt::MiddleButton)
    {
        if (m_pTimer->isActive())
        {
            m_pTimer->stop();
            return;
        }
        else
        {
            m_pTimer->start(33);
            return;
        }
    }
    QPoint qtPt = event->pos();
    int x = qtPt.x();
    int y = qtPt.y();
    if(x>=40&&x<=680&&y>=58&&y<=538)
    {
        if(event->button()==Qt::LeftButton)
        {
            ui.textBrowser->append("Test");
        }
        if (event->button()==Qt::RightButton)
        {
            m_bUserClicked = true;
            int x_ = x - 40;
            int y_ = y - 58;
            m_SpecifiedPt = QPoint(x_, y_);
            // fresh text browser
            ui.textBrowser->clear();
            int iDepth = getDepthValue(x_, y_);
            cv::Point3f pt = UVd2Point3D(x_, y_, iDepth, m_camera_para);
            ui.textBrowser->append("x: " + QString::number(pt.x) 
                + " mm\ny: " + QString::number(pt.y)
                + " mm\nz: " + QString::number(pt.z) + " mm");
        }
    }
}

void BodyRecog_Demo::onOpen()
{
    m_capture.open(0);
    m_capture.setRegistration(true);
    m_pTimer->start(33);
    m_bConnected = true;
}

void BodyRecog_Demo::onClose()
{
    m_capture.release();
    m_pTimer->stop();
}

void BodyRecog_Demo::textBrowserUpdate()
{
    ui.textBrowser->clear();
    int iDepth = getDepthValue(m_SpecifiedPt.x(), m_SpecifiedPt.y());
    cv::Point3f pt = UVd2Point3D(m_SpecifiedPt.x(), m_SpecifiedPt.y(), iDepth, m_camera_para);
    ui.textBrowser->append("x: " + QString::number(pt.x) 
        + " mm\ny: " + QString::number(pt.y)
        + " mm\nz: " + QString::number(pt.z) + " mm");
}

void BodyRecog_Demo::frameUpdate()
{

    bool has_frame = m_capture.grab(*m_pDepthImg, *m_pDisImg);

	//cv::imshow("Depth Image", *m_pDepthImg);

    updateImageForDisplay(*m_pDisImg, 1, m_pImage);
    drawImage(*m_pImage);
    if(m_bDynUpdate)
    {
        textBrowserUpdate();
    }
}

void BodyRecog_Demo::drawImage(const QImage& img)
{
    m_scene->clear();
    m_scene->addPixmap(QPixmap::fromImage(img));
    ////Draw Specified Point
    if(m_bUserClicked)
    {
        //QRect rect = QRect(m_SpecifiedPt.x(), m_SpecifiedPt.y(), 5, 5);
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(2);
        //m_scene->addRect(rect, pen);
        m_scene->addEllipse(m_SpecifiedPt.x(), m_SpecifiedPt.y(), 2, 2, pen);
    }
    ////
    m_view->setScene(m_scene);
}

static int n = 0;
void BodyRecog_Demo::updateImageForDisplay(const cv::Mat &SrcImg, const int downscale, QImage* pDstImg)
{
    //assert(pSrcImg->type == CV_8UC4);
    if (pDstImg == NULL)
        return;
    //MONO
    for (int i = 0; i < SrcImg.rows; ++i)
    {
        cv::Vec3b stColorRow;
        //unsigned char ucMono;
        //RGBQUAD* pBuffer = pDstImg->data_ptr;

        for(int j = 0; j < SrcImg.cols; ++j)
        {
            if(i % downscale == 0 && j % downscale == 0)
            {
                stColorRow = SrcImg.at<cv::Vec3b>(i, j);
                pDstImg->setPixel(j/downscale, i/downscale, qRgb(stColorRow[2], stColorRow[1], stColorRow[0]));
            }
        }
    }
	if(n % 10 == 0)
		;
		//pDstImg->save("D://Kinect_Image//" + QString::number(n) + ".jpg");

	n++;
}

int BodyRecog_Demo::getDepthValue(const int u, const int v)
{
    if(u<0||v<0||v>=m_pDepthImg->rows||u>=m_pDepthImg->cols)
        return 0;
    int iMeanValue = 0;
    long lSum = 0;
    int iValidNum = 0;
    for(int i = -1; i < 2; i++) //size[3x3]
    {
        for(int j = -1; j < 2; j++)
        {
            if(u+i>=0&&u+i<m_pDepthImg->cols&&v+j>=0&&v+j<m_pDepthImg->rows)
            {
                iValidNum++;
                lSum += m_pDepthImg->at<ushort>(v+j, u+i);
            }
        }
    }
    iMeanValue = static_cast<int>((float)lSum/iValidNum);
	std::cout << iValidNum << std::endl;
    return iMeanValue;
}

cv::Point3f BodyRecog_Demo::UVd2Point3D(const int u, const int v, int const depth, CAMERA_INTRINSIC_PARAMETERS const CameraPara)
{
    cv::Point3f pt;
    pt.z = static_cast<double>(depth) / CameraPara.scale;
    pt.x = (u - CameraPara.cx) * pt.z / CameraPara.fx;
    pt.y = (v - CameraPara.cy) * pt.z / CameraPara.fy;
    return pt;
}