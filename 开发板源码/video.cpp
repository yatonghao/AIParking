#include "video.h"
#include <string>


Video::Video(QObject *parent)
{
    //打开摄像头
    cap.open(9);//dev/video

    if (!cap.isOpened()) {
        qDebug() << "Error: Could not open camera.";
        return;
    }

    regExp = new QRegExp("^[\u4e00-\u9fa5][A-Z0-9]{6}$");
    cap_timer = new QTimer(this);
    connect(cap_timer,&QTimer::timeout,this,&Video::getOneFrame);
    cap_timer->start(50);
}

Video::~Video()
{
    cap.release();
    if(regExp)
        delete regExp;
}


void Video::identify()
{
    // 读取图像
        cv::Mat image = srcImage;
        // 创建ImageData
        HLPR_ImageData data = {0};
        data.data = image.ptr<uint8_t>(0);      // 设置图像数据流
        data.width = image.cols;                   // 设置图像宽
        data.height = image.rows;                  // 设置图像高
        data.format = STREAM_BGR;                  // 设置当前图像编码格式
        data.rotation = CAMERA_ROTATION_0;         // 设置当前图像转角
        // 创建数据Buffer
        P_HLPR_DataBuffer buffer = HLPR_CreateDataBuffer(&data);

        // 配置车牌识别参数
        HLPR_ContextConfiguration configuration = {0};
        configuration.models_path = (char*)"./hyperlpr3/resource/models/r2_mobile";         // 模型文件夹路径
        configuration.max_num = 5;                      // 最大识别车牌数量
        configuration.det_level = DETECT_LEVEL_LOW;     // 检测器等级
        configuration.use_half = false;
        configuration.nms_threshold = 0.5f;             // 非极大值抑制置信度阈值
        configuration.rec_confidence_threshold = 0.5f;  // 车牌号文本阈值
        configuration.box_conf_threshold = 0.30f;       // 检测器阈值
        configuration.threads = 1;
        // 实例化车牌识别算法Context
        P_HLPR_Context ctx = HLPR_CreateContext(&configuration);
        // 查询实例化状态
        HREESULT ret = HLPR_ContextQueryStatus(ctx);
        if (ret != HResultCode::Ok) {
            printf("create error.\n");
            return;
        }
        HLPR_PlateResultList results = {0};
        // 执行车牌识别算法
        HLPR_ContextUpdateStream(ctx, buffer, &results);

        for (int i = 0; i < results.plate_size; ++i) {
            qDebug() << results.plates[i].code << results.plates[i].text_confidence;
            processLicensePlate(QString(results.plates[i].code));
        }

        // 销毁Buffer
        HLPR_ReleaseDataBuffer(buffer);
        // 销毁Context
        HLPR_ReleaseContext(ctx);
}

void Video::getOneFrame()
{
    //采集数据
    if(cap.grab())
    {
        cap.read(srcImage);//读取一帧数据
        cvtColor(srcImage,srcImage, COLOR_BGR2RGB);
        QImage image(srcImage.data,srcImage.cols, srcImage.rows,srcImage.step1(),QImage::Format_RGB888);
        mmp = QPixmap::fromImage(image);
    }
}

void Video::getFrame()
{
    emit sendFrame(mmp);
}

bool Video::isDuplicate(const QString &plateNumber, const QDateTime &now)
{
    if (lastPlateNumber==plateNumber) {
        if (lastRecognized.secsTo(now) < timeWindowSeconds) {
            // 时间窗口内的重复识别
            return true;
        }
    }
    return false;
}

void Video::processLicensePlate(const QString &plateNumber)
{
    QDateTime now = QDateTime::currentDateTime();

    if (!regExp->exactMatch(plateNumber)||isDuplicate(plateNumber, now)) {
        // 忽略重复识别
        return;
    }

    // 处理新的车牌识别
    lastPlateNumber = plateNumber;
    lastRecognized = now;
    emit sendCarID(plateNumber);
}
