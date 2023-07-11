#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  rootWin = new Qt3DCore::QEntity(); // конктруктор корневого окна
  rootWin->setObjectName("Root window");
  Qt3DExtras::Qt3DWindow *view =
      new Qt3DExtras::Qt3DWindow(); // создаем окно для отображения сцены
  view->defaultFrameGraph()->setClearColor(QRgb(0xffffff)); // стандартный фон
  view->setRootEntity(rootWin); // устанавливаем корневое окно
  QWidget *widget = QWidget::createWindowContainer(
      view); // встраивание виджета view в окно приложения
  widget->setMinimumSize(QSize(100, 100));
  QSize screenSize = view->screen()->size(); // получение размера окна
  widget->setMaximumSize(screenSize); // и установка его как максимального
  widget->setFocusPolicy(Qt::NoFocus);
  QPushButton* button = new QPushButton("Choose file", this);
  QLineEdit* lineEdit = new QLineEdit(this);

  QVBoxLayout* layout = new QVBoxLayout();  // добавление виджета, кнопки и текстового поля в лейаут
  layout->addWidget(widget);
  layout->addWidget(button);
  layout->addWidget(lineEdit);
  this->centralWidget()->setLayout(layout); // установка его в качестве центрального виджета

  cameraObj = view->camera(); // создаем объект камеры
  cameraObj->lens()->setPerspectiveProjection(
      45.0f, 16.0f / 9.0f, 0.1f,
      10000.0f); // устанавливаем параметры проекции камеры
  cameraObj->setPosition(
      QVector3D(0, 2, 0)); // позиция камеры в трехмерном пространстве
  cameraObj->setUpVector(QVector3D(0, 0, 1)); // вектор верха камеры (x, y, z)
  cameraObj->setViewCenter(QVector3D(1, 0, 0)); // центр обзора камеры

  Qt3DExtras::QOrbitCameraController *cameraController =
      new Qt3DExtras::QOrbitCameraController(rootWin);
  cameraController->setCamera(cameraObj);
  cameraController->setLookSpeed(100.0f);  // Скорость вращения
  cameraController->setLinearSpeed(50.0f); // Линейная скорость

  Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootWin);
  Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
  light->setColor("white");
  light->setIntensity(10);
  lightEntity->addComponent(light);
  Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
  lightTransform->setTranslation(QVector3D(40, 0, 20));
  lightEntity->addComponent(lightTransform);

  // открытие файла и его загрузка
  open_object_file(layout, lineEdit, button);
}

void MainWindow::open_object_file(QVBoxLayout* layout, QLineEdit* lineEdit, QPushButton* button) {
    connect(button, &QPushButton::clicked, this, [=]() {
        QString filename = QFileDialog::getOpenFileName(this, "Open a file", "", "Obj Files (*.obj)");
        lineEdit->setText(filename);
        Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh(rootWin);
        mesh->setSource(QUrl::fromLocalFile(filename));
        mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);  // Установка режима отображения каркаса
        Qt3DExtras::QPerVertexColorMaterial *material = new Qt3DExtras::QPerVertexColorMaterial(rootWin);
        Qt3DCore::QEntity *object = new Qt3DCore::QEntity(rootWin);
        object->addComponent(mesh);
        object->addComponent(material);
        Qt3DCore::QTransform *transform = new Qt3DCore::QTransform();
        object->addComponent(transform);
//        object_info(layout, mesh, filename);
        add_scale_slider(layout, transform);
        add_move_sliders(layout, transform);
        add_rotate_sliders(layout, transform);
    });
}

void MainWindow::add_move_sliders(QVBoxLayout* layout, Qt3DCore::QTransform *transform) {
    QSlider* moveX = new QSlider(Qt::Horizontal, this);
    QSlider* moveY = new QSlider(Qt::Horizontal, this);
    QSlider* moveZ = new QSlider(Qt::Horizontal, this);
    QLabel* moveXlabel = new QLabel("X-axis movement", this);
    QLabel* moveYlabel = new QLabel("Y-axis movement", this);
    QLabel* moveZlabel = new QLabel("Z-axis movement", this);
    moveXlabel->setMaximumSize(150, 15);
    moveYlabel->setMaximumSize(150, 15);
    moveZlabel->setMaximumSize(150, 15);
    moveX->setVisible(false);
    moveY->setVisible(false);
    moveZ->setVisible(false);
    moveXlabel->setVisible(false);
    moveYlabel->setVisible(false);
    moveZlabel->setVisible(false);

    moveX->setRange(-100, 100);  // задаем диапазон слайдера
    moveX->setTickInterval(1);  // интервал изменения значения слайдера
    moveY->setRange(-100, 100);

    moveY->setTickInterval(1);
    moveZ->setRange(-100, 100);
    moveZ->setTickInterval(1);

    layout->addWidget(moveXlabel);
    layout->addWidget(moveX);
    layout->addWidget(moveYlabel);
    layout->addWidget(moveY);
    layout->addWidget(moveZlabel);
    layout->addWidget(moveZ);
    QPushButton* showSlidersButton = new QPushButton("Move object", this);
    layout->addWidget(showSlidersButton);

    connect(showSlidersButton, &QPushButton::clicked, this, [=]() {   // показать слайдер при нажатии на кнопку
        moveX->setVisible(!moveX->isVisible());
        moveY->setVisible(!moveY->isVisible());
        moveZ->setVisible(!moveZ->isVisible());
        moveXlabel->setVisible(!moveXlabel->isVisible());
        moveYlabel->setVisible(!moveYlabel->isVisible());
        moveZlabel->setVisible(!moveZlabel->isVisible());
    });

    connect(moveX, &QSlider::valueChanged, this, [=]() {
        float x = moveX->value();
        float y = moveY->value();
        float z = moveZ->value();
        transform->setTranslation(QVector3D(x, y, z));
    });
    connect(moveY, &QSlider::valueChanged, this, [=]() {
        float x = moveX->value();
        float y = moveY->value();
        float z = moveZ->value();
        transform->setTranslation(QVector3D(x, y, z));
    });
    connect(moveZ, &QSlider::valueChanged, this, [=]() {
        float x = moveX->value();
        float y = moveY->value();
        float z = moveZ->value();
        transform->setTranslation(QVector3D(x, y, z));
    });
}

void MainWindow::add_rotate_sliders(QVBoxLayout* layout, Qt3DCore::QTransform *transform) {
    QSlider* rotateX = new QSlider(Qt::Horizontal, this);
    QSlider* rotateY = new QSlider(Qt::Horizontal, this);
    QSlider* rotateZ = new QSlider(Qt::Horizontal, this);
    QLabel* rotateXlabel = new QLabel("X-axis rotation", this);
    QLabel* rotateYlabel = new QLabel("Y-axis rotation", this);
    QLabel* rotateZlabel = new QLabel("Z-axis rotation", this);
    rotateXlabel->setMaximumSize(150, 15);
    rotateYlabel->setMaximumSize(150, 15);
    rotateZlabel->setMaximumSize(150, 15);
    rotateX->setVisible(false);
    rotateY->setVisible(false);
    rotateZ->setVisible(false);
    rotateXlabel->setVisible(false);
    rotateYlabel->setVisible(false);
    rotateZlabel->setVisible(false);

    rotateX->setRange(0, 360);
    rotateX->setTickInterval(1);
    rotateY->setRange(0, 360);
    rotateY->setTickInterval(1);
    rotateZ->setRange(0, 360);
    rotateZ->setTickInterval(1);

    layout->addWidget(rotateXlabel);
    layout->addWidget(rotateX);
    layout->addWidget(rotateYlabel);
    layout->addWidget(rotateY);
    layout->addWidget(rotateZlabel);
    layout->addWidget(rotateZ);
    QPushButton* showSlidersButton = new QPushButton("Rotate object", this);
    layout->addWidget(showSlidersButton);

    connect(showSlidersButton, &QPushButton::clicked, this, [=]() {
        rotateX->setVisible(!rotateX->isVisible());
        rotateY->setVisible(!rotateY->isVisible());
        rotateZ->setVisible(!rotateZ->isVisible());
        rotateXlabel->setVisible(!rotateXlabel->isVisible());
        rotateYlabel->setVisible(!rotateYlabel->isVisible());
        rotateZlabel->setVisible(!rotateZlabel->isVisible());
    });
    connect(rotateX, &QSlider::valueChanged, this, [=]() {
        float angle = rotateX->value();  // угол поворота
        transform->setRotationX(angle);  // поворот вокруг оси X на заданный угол
    });
    connect(rotateY, &QSlider::valueChanged, this, [=]() {
        float angle = rotateY->value();
        transform->setRotationY(angle);
    });
    connect(rotateZ, &QSlider::valueChanged, this, [=]() {
        float angle = rotateZ->value();
        transform->setRotationZ(angle);
    });
}

void MainWindow::object_info(QVBoxLayout* layout, Qt3DRender::QMesh *mesh, QString filename) {
    int vertexCount = mesh->vertexCount();
    int edgesCount = vertexCount * (vertexCount - 1) / 2;
    QString info = "File: " + filename + "\n";
    info += "Vertex count: " + QString::number(vertexCount) + "\n";
    info += "Edges count: " + QString::number(edgesCount) + "\n";
    QLabel* object_inf = new QLabel(info);
    object_inf->setMaximumSize(800, 50);
    layout->addWidget(object_inf);
}

void MainWindow::add_scale_slider(QVBoxLayout* layout, Qt3DCore::QTransform * transform) {
    QSlider* scaleObject = new QSlider(Qt::Horizontal, this);
    QLabel* scaleObjectLabel = new QLabel("Scale object");
    scaleObjectLabel->setMaximumSize(150, 20);
    layout->addWidget(scaleObjectLabel);
    scaleObject->setRange(1, 100);
    scaleObject->setValue(10);
    layout->addWidget(scaleObject);
    connect(scaleObject, &QSlider::valueChanged, this, [=]() {
        float scale = scaleObject->value();
        transform->setScale(scale);
    });
}

MainWindow::~MainWindow() { delete ui; }
