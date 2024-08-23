QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adduser.cpp \
    audio.cpp \
    device.cpp \
    main.cpp \
    mainwindow.cpp \
    menuwindow.cpp \
    mypushbutton.cpp \
    video.cpp

HEADERS += \
    adduser.h \
    audio.h \
    config.h \
    device.h \
    mainwindow.h \
    menuwindow.h \
    mypushbutton.h \
    video.h \
    rc522.h


#LIBS += -L/home/topeet/sortware/HyperLPR-feature-deploy/Prj-Linux/hyperlpr3/lib -lhyperlpr3
#LIBS += -L/usr/local/opencv4.5.5/lib -lopencv_core -lopencv_videoio -lopencv_imgproc -lopencv_highgui
#LIBS += `pkg-config --libs opencv4`


INCLUDEPATH += /usr/local/opencv4.5.5/include/opencv4
INCLUDEPATH += /usr/local/opencv4.5.5/include/opencv4/opencv2
INCLUDEPATH += /usr/local/opencv4.5.5/include
INCLUDEPATH += /home/topeet/sortware/HyperLPR-feature-deploy/Prj-Linux/hyperlpr3/include

LIBS += -L/home/topeet/sortware/HyperLPR-feature-deploy/Prj-Linux/hyperlpr3_arm64/lib -lhyperlpr3
LIBS += -L/home/topeet/sortware/opencv-4.5.5/install/lib -lopencv_core -lopencv_videoio -lopencv_imgproc -lopencv_highgui
LIBS += `pkg-config --libs opencv-arm`

INCLUDEPATH += /home/topeet/sortware/opencv-4.5.5/install/include/opencv4
INCLUDEPATH += /home/topeet/sortware/opencv-4.5.5/install/include/opencv4/opencv2
INCLUDEPATH += /home/topeet/sortware/opencv-4.5.5/install/include
INCLUDEPATH += /home/topeet/sortware/HyperLPR-feature-deploy/Prj-Linux/hyperlpr3_arm64/include
FORMS += \
    adduser.ui \
    mainwindow.ui
include     ($$PWD/easyInput/easyInput.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc

