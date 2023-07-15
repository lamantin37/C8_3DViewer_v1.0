#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent, Qt3DCore::QTransform *transform)
    : QWidget(parent) {
  setWindowFlags(Qt::Window);
  setFixedSize(QSize(400, 600));
  layout = new QVBoxLayout();
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

  backgroundColor = new QPushButton("Change background color", this);
  lineColor = new QPushButton("Change line color", this);
  setLayout(layout);
}

void SettingsWindow::add_move_sliders(Qt3DCore::QTransform *transform) {
  moveXlabel->setMaximumSize(150, 15);
  moveXlabel->setVisible(false);
  moveYlabel->setMaximumSize(150, 15);
  moveYlabel->setVisible(false);
  moveZlabel->setMaximumSize(150, 15);
  moveZlabel->setVisible(false);

  moveX->setRange(-100, 100); // задаем диапазон слайдера
  moveX->setTickInterval(1); // интервал изменения значения слайдера
  moveX->setVisible(false);
  moveY->setRange(-100, 100);
  moveY->setTickInterval(1);
  moveY->setVisible(false);
  moveZ->setRange(-100, 100);
  moveZ->setTickInterval(1);
  moveZ->setVisible(false);

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

void SettingsWindow::add_rotate_sliders(Qt3DCore::QTransform *transform) {
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

  rotateX->setVisible(false);
  rotateY->setVisible(false);
  rotateZ->setVisible(false);
  rotateXlabel->setVisible(false);
  rotateYlabel->setVisible(false);
  rotateZlabel->setVisible(false);

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

void SettingsWindow::add_scale_slider(Qt3DCore::QTransform *transform) {
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

void SettingsWindow::projection_settings(Qt3DRender::QCamera *cameraObj) {
  QLabel *projLabel = new QLabel("Select projection:", this);
  QRadioButton *parallelProjectionRadioButton =
      new QRadioButton("Parallel projection", this);
  QRadioButton *centralProjectionRadioButton =
      new QRadioButton("Central projection", this);
  QHBoxLayout *hLayout = new QHBoxLayout();
  hLayout->addWidget(parallelProjectionRadioButton);
  hLayout->addWidget(centralProjectionRadioButton);
  layout->addWidget(projLabel);
  layout->addLayout(hLayout);

  connect(parallelProjectionRadioButton, &QRadioButton::clicked, this, [=]() {
    float aspectRatio = float(window()->width()) / window()->height();
    cameraObj->lens()->setPerspectiveProjection(45.0f, aspectRatio, 0.1f,
                                                10000.0f);
  });

  connect(centralProjectionRadioButton, &QRadioButton::clicked, this, [=]() {
    float aspectRatio = float(window()->width()) / window()->height();
    cameraObj->lens()->setOrthographicProjection(-aspectRatio, aspectRatio,
                                                 -1.0, 1.0, 0.1f, 10000.0f);
  });
}

void SettingsWindow::line_type_settings(Qt3DRender::QMesh *mesh) {
  QLabel *typeLabel = new QLabel("Select line type:", this);
  QRadioButton *lineTypeRadioButton = new QRadioButton("Solid line", this);
  QRadioButton *dotTypeRadioButton = new QRadioButton("Dotted line", this);
  QHBoxLayout *hLayout = new QHBoxLayout();
  hLayout->addWidget(lineTypeRadioButton);
  hLayout->addWidget(dotTypeRadioButton);
  layout->addWidget(typeLabel);
  layout->addLayout(hLayout);
  connect(lineTypeRadioButton, &QRadioButton::clicked, this, [=]() {
    mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
  });
  connect(dotTypeRadioButton, &QRadioButton::clicked, this, [=]() {
    mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Points);
  });
}

void SettingsWindow::line_color_settings(Qt3DCore::QEntity *parentWin,
                                         Qt3DCore::QEntity *object) {
  layout->addWidget(lineColor);
  connect(lineColor, &QPushButton::clicked, this, [=]() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose line color");
    if (color.isValid()) {
      Qt3DExtras::QDiffuseSpecularMaterial *line_material =
          new Qt3DExtras::QDiffuseSpecularMaterial(parentWin);
      line_material->setAmbient(color);
      object->addComponent(line_material);
    }
  });
}

void SettingsWindow::background_settings(Qt3DExtras::Qt3DWindow *view) {
  layout->addWidget(backgroundColor);
  connect(backgroundColor, &QPushButton::clicked, this, [=]() {
    QColor color =
        QColorDialog::getColor(Qt::white, this, "Choose background color");
    if (color.isValid()) {
      view->defaultFrameGraph()->setClearColor(QColor(color));
    }
  });
}
