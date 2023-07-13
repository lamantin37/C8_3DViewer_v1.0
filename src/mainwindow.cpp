#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  moveX = new QSlider(Qt::Horizontal, this);
  moveZ = new QSlider(Qt::Horizontal, this);
  moveY = new QSlider(Qt::Horizontal, this);
  moveXlabel = new QLabel("X-axis movement", this);
  moveYlabel = new QLabel("Y-axis movement", this);
  moveZlabel = new QLabel("Z-axis movement", this);
  showSlidersButton = new QPushButton("Move object", this);

  rotateX = new QSlider(Qt::Horizontal, this);
  rotateY = new QSlider(Qt::Horizontal, this);
  rotateZ = new QSlider(Qt::Horizontal, this);
  rotateXlabel = new QLabel("X-axis rotation", this);
  rotateYlabel = new QLabel("Y-axis rotation", this);
  rotateZlabel = new QLabel("Z-axis rotation", this);
  showSlidersButton2 = new QPushButton("Rotate object", this);

  scaleObject = new QSlider(Qt::Horizontal, this);
  scaleObjectLabel = new QLabel("Scale object");

  settingsButton = new QPushButton("Settings", this);
  parallelProjection = new QPushButton("Central projection", this);
  centralProjection = new QPushButton("Parallel projection", this);
  backgroundColor = new QPushButton("Change background color", this);
  lineColor = new QPushButton("Change line color", this);

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
  QPushButton *button = new QPushButton("Choose file", this);
  QLineEdit *lineEdit = new QLineEdit(this);

  QVBoxLayout *layout = new QVBoxLayout(); // добавление виджета, кнопки и
                                           // текстового поля в лейаут
  layout->addWidget(widget);
  layout->addWidget(button);
  layout->addWidget(lineEdit);
  this->centralWidget()->setLayout(
      layout); // установка его в качестве центрального виджета

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

  object = new Qt3DCore::QEntity(rootWin);
  // открытие файла и его загрузка
  open_object_file(object, layout, lineEdit, button);
  settings(view, object, layout);
}

void MainWindow::open_object_file(Qt3DCore::QEntity* object, QVBoxLayout *layout, QLineEdit *lineEdit,
                                  QPushButton *button) {



  connect(button, &QPushButton::clicked, this, [=]() {
    QString filename = QFileDialog::getOpenFileName(this, "Open a file", "",
                                                    "Obj Files (*.obj)");
    lineEdit->setText(filename);
    if (mesh != nullptr) {
        object->removeComponent(mesh);
        delete mesh;
    }
    mesh = new Qt3DRender::QMesh(rootWin);
    mesh->setSource(QUrl::fromLocalFile(filename));
    mesh->setPrimitiveType(
        Qt3DRender::QGeometryRenderer::Lines); // Установка режима отображения
                                               // каркаса
    Qt3DExtras::QPerVertexColorMaterial *material =
        new Qt3DExtras::QPerVertexColorMaterial(rootWin);

//    Qt3DExtras::QDiffuseSpecularMaterial *line_material = new Qt3DExtras::QDiffuseSpecularMaterial(rootWin);
//    line_material->setAmbient(QColor(Qt::red));
    object->addComponent(material);
//    object->addComponent(line_material);

    object->addComponent(mesh);
    transform = new Qt3DCore::QTransform();
    object->addComponent(transform);
//    add_scale_slider(layout, transform);
//    add_move_sliders(layout, transform);
//    add_rotate_sliders(layout, transform);
//    object_info(layout, mesh, filename);
  });
}

void MainWindow::add_move_sliders(QVBoxLayout *layout,
                                  Qt3DCore::QTransform *transform) {
  moveXlabel->setMaximumSize(150, 15);
  moveYlabel->setMaximumSize(150, 15);
  moveZlabel->setMaximumSize(150, 15);

  moveX->setRange(-100, 100); // задаем диапазон слайдера
  moveX->setTickInterval(1); // интервал изменения значения слайдера
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
  layout->addWidget(showSlidersButton);

  connect(showSlidersButton, &QPushButton::clicked, this,
          [=]() { // показать слайдер при нажатии на кнопку
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

void MainWindow::add_rotate_sliders(QVBoxLayout *layout,
                                    Qt3DCore::QTransform *transform) {
  rotateXlabel->setMaximumSize(150, 15);
  rotateYlabel->setMaximumSize(150, 15);
  rotateZlabel->setMaximumSize(150, 15);

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
  layout->addWidget(showSlidersButton2);

  connect(showSlidersButton2, &QPushButton::clicked, this, [=]() {
    rotateX->setVisible(!rotateX->isVisible());
    rotateY->setVisible(!rotateY->isVisible());
    rotateZ->setVisible(!rotateZ->isVisible());
    rotateXlabel->setVisible(!rotateXlabel->isVisible());
    rotateYlabel->setVisible(!rotateYlabel->isVisible());
    rotateZlabel->setVisible(!rotateZlabel->isVisible());
  });
  connect(rotateX, &QSlider::valueChanged, this, [=]() {
    float angle = rotateX->value(); // угол поворота
    transform->setRotationX(angle); // поворот вокруг оси X на заданный угол
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

void MainWindow::object_info(QVBoxLayout *layout, Qt3DRender::QMesh *mesh,
                             const QString &filename) {
  connect(mesh, &Qt3DRender::QMesh::geometryChanged, this, [=]() {
    Qt3DRender::QGeometry *geometry = mesh->geometry();
    // Подсчет вершин
    Qt3DRender::QAttribute *vertexAttribute = nullptr;
    for (auto attr : geometry->attributes()) {
      if (attr->name() ==
          Qt3DRender::QAttribute::defaultPositionAttributeName()) {
        vertexAttribute = attr;
        break;
      }
    }
    // Подсчет ребер
    Qt3DRender::QAttribute *indexAttribute = nullptr;
    for (auto attr : geometry->attributes()) {
      if (attr->attributeType() == Qt3DRender::QAttribute::IndexAttribute) {
        indexAttribute = attr;
        break;
      }
    }
    if (vertexAttribute != nullptr) {
      int vertexCount = vertexAttribute->count();
      qDebug() << "Number of vertices in" << filename << ":" << vertexCount;
    }
    if (indexAttribute != nullptr) {
      int edgeCount = indexAttribute->count() / 3 *
                      2;    // т.к. полигоны - треугольники
      qDebug() << "Number of edges in" << filename << ":" << edgeCount;
    }
  });
}

void MainWindow::add_scale_slider(QVBoxLayout *layout,
                                  Qt3DCore::QTransform *transform) {
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

void MainWindow::settings(Qt3DExtras::Qt3DWindow * view, Qt3DCore::QEntity* object, QVBoxLayout *layout) {
    layout->addWidget(settingsButton);
    connect(settingsButton, &QPushButton::clicked, this,
            [=]() {
        projection_settings(layout);
        background_settings(view, layout);
        line_color_settings(view, layout);
            });
}

void MainWindow::projection_settings(QVBoxLayout *layout) {
    layout->addWidget(parallelProjection);
    connect(parallelProjection, &QPushButton::clicked, this,
            [=]() {
        cameraObj->lens()->setPerspectiveProjection(
            45.0f, 16.0f / 9.0f, 0.1f,
            10000.0f);            });
    layout->addWidget(centralProjection);
    float aspectRatio = float(window()->width()) / window()->height();
    connect(centralProjection, &QPushButton::clicked, this, [=]() {
        cameraObj->lens()->setOrthographicProjection(-aspectRatio, aspectRatio, -1.0, 1.0, 0.1f, 10000.0f);
    });
}

void MainWindow::background_settings(Qt3DExtras::Qt3DWindow *view, QVBoxLayout * layout) {
    layout->addWidget(backgroundColor);
    connect(backgroundColor, &QPushButton::clicked, this, [=]() {
        QColor color = QColorDialog::getColor(Qt::white, this, "Choose background color");
        if (color.isValid()) {
            view->defaultFrameGraph()->setClearColor(QColor(color));
        }
    });
}

void MainWindow::line_color_settings(Qt3DExtras::Qt3DWindow *view, QVBoxLayout * layout) {
    layout->addWidget(lineColor);
    connect(lineColor, &QPushButton::clicked, this, [=]() {
        QColor color = QColorDialog::getColor(Qt::white, this, "Choose line color");
        if (color.isValid()) {
            Qt3DExtras::QDiffuseSpecularMaterial *line_material = new Qt3DExtras::QDiffuseSpecularMaterial(rootWin);
            line_material->setAmbient(color);
            object->addComponent(line_material);
        }
    });
}

MainWindow::~MainWindow() { delete ui; }
