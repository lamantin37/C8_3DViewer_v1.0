#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rootWin = new Qt3DCore::QEntity();
    rootWin = new Qt3DCore::QEntity();   // конктруктор корневого окна
    rootWin->setObjectName("Root window");
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();    // создаем окно для отображения сцены
    view->defaultFrameGraph()->setClearColor(QRgb(0xffffff));   // стандартный фон
    view->setRootEntity(rootWin);    // устанавливаем корневое окно

    QWidget *widget = QWidget::createWindowContainer(view);  // встраивание виджета view в окно приложения
    widget->setMinimumSize(QSize(100, 100));
    QSize screenSize = view->screen()->size();  // получение размера окна
    widget->setMaximumSize(screenSize);  // и установка его как максимального
    widget->setFocusPolicy(Qt::NoFocus);

    setCentralWidget(widget);    // установка widget в качестве центрального объекта

    cameraObj = view->camera(); // создаем объект камеры
    cameraObj->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 10000.0f); // устанавливаем параметры проекции камеры
    cameraObj->setPosition(QVector3D(0, 2, 0));     // позиция камеры в трехмерном пространстве
    cameraObj->setUpVector(QVector3D(0, 0, 1));     // вектор верха камеры (x, y, z)
    cameraObj->setViewCenter(QVector3D(0, 0, 0));   // центр обзора камеры

    Qt3DExtras::QOrbitCameraController *cameraController = new Qt3DExtras::QOrbitCameraController(rootWin);
    cameraController->setCamera(cameraObj);

    sceneLoader = new Qt3DCore::QEntity(rootWin);
    loader = new Qt3DRender::QSceneLoader(sceneLoader);
    loader->setObjectName("cube.obj");
    sceneLoader->addComponent(loader);
    loader->setSource(
        QUrl(QString("file:cube.obj")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

