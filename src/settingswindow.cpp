#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent, Qt3DCore::QTransform *transform)
    : QWidget(parent) {
  setWindowFlags(Qt::Window);
  setFixedSize(QSize(400, 600));
  layout = new QVBoxLayout();
  moveX = new QSlider(Qt::Horizontal, this);
  moveZ = new QSlider(Qt::Horizontal, this);
  moveY = new QSlider(Qt::Horizontal, this);
  lineEditX = new QLineEdit(this);
  lineEditX->setValidator(new QDoubleValidator(this));
  lineEditY = new QLineEdit(this);
  lineEditY->setValidator(new QDoubleValidator(this));
  lineEditZ = new QLineEdit(this);
  lineEditZ->setValidator(new QDoubleValidator(this));
  moveXlabel = new QLabel("X-axis movement", this);
  moveYlabel = new QLabel("Y-axis movement", this);
  moveZlabel = new QLabel("Z-axis movement", this);

  rotateX = new QSlider(Qt::Horizontal, this);
  lineEditRX = new QLineEdit(this);
  lineEditRX->setValidator(new QDoubleValidator(this));
  rotateY = new QSlider(Qt::Horizontal, this);
  lineEditRY = new QLineEdit(this);
  lineEditRY->setValidator(new QDoubleValidator(this));
  rotateZ = new QSlider(Qt::Horizontal, this);
  lineEditRZ = new QLineEdit(this);
  lineEditRZ->setValidator(new QDoubleValidator(this));
  rotateXlabel = new QLabel("X-axis rotation", this);
  rotateYlabel = new QLabel("Y-axis rotation", this);
  rotateZlabel = new QLabel("Z-axis rotation", this);

  scaleObject = new QSlider(Qt::Horizontal, this);
  scaleObjectLabel = new QLabel("Scale object");

  backgroundColor = new QPushButton("Change background color", this);
  pointColor = new QPushButton("Change point color", this);
  lineColor = new QPushButton("Change line color", this);
  setLayout(layout);
}

void SettingsWindow::add_move_sliders(Qt3DCore::QTransform *transform) {
  moveXlabel->setMaximumSize(150, 15);
  moveYlabel->setMaximumSize(150, 15);
  moveZlabel->setMaximumSize(150, 15);

  moveX->setRange(-100, 100); // задаем диапазон слайдера
  moveX->setTickInterval(1); // интервал изменения значения слайдера
  moveY->setRange(-100, 100);
  moveY->setTickInterval(1);
  moveZ->setRange(-100, 100);
  moveZ->setTickInterval(1);

  QHBoxLayout *xLayout = new QHBoxLayout();
  xLayout->addWidget(moveX);
  xLayout->addWidget(lineEditX);

  QHBoxLayout *yLayout = new QHBoxLayout();
  yLayout->addWidget(moveY);
  yLayout->addWidget(lineEditY);

  QHBoxLayout *zLayout = new QHBoxLayout();
  zLayout->addWidget(moveZ);
  zLayout->addWidget(lineEditZ);

  layout->addWidget(moveXlabel);
  layout->addLayout(xLayout);
  layout->addWidget(moveYlabel);
  layout->addLayout(yLayout);
  layout->addWidget(moveZlabel);
  layout->addLayout(zLayout);

  connect(moveX, &QSlider::valueChanged, this, [=]() {
    float x = moveX->value();
    float y = moveY->value();
    float z = moveZ->value();
    transform->setTranslation(QVector3D(x, y, z));
    lineEditX->setText(QString::number(x));
  });
  connect(moveY, &QSlider::valueChanged, this, [=]() {
    float x = moveX->value();
    float y = moveY->value();
    float z = moveZ->value();
    transform->setTranslation(QVector3D(x, y, z));
    lineEditY->setText(QString::number(y));
  });
  connect(moveZ, &QSlider::valueChanged, this, [=]() {
    float x = moveX->value();
    float y = moveY->value();
    float z = moveZ->value();
    transform->setTranslation(QVector3D(x, y, z));
    lineEditZ->setText(QString::number(z));
  });
  connect(lineEditX, &QLineEdit::returnPressed, this, [=]() {
    float x = lineEditX->text().toFloat();
    float y = moveY->value();
    float z = moveZ->value();
    transform->setTranslation(QVector3D(x, y, z));
    moveX->setValue(x);
  });
  connect(lineEditY, &QLineEdit::returnPressed, this, [=]() {
    float x = moveX->value();
    float y = lineEditY->text().toFloat();
    float z = moveZ->value();
    transform->setTranslation(QVector3D(x, y, z));
    moveY->setValue(y);
  });
  connect(lineEditZ, &QLineEdit::returnPressed, this, [=]() {
    float x = moveX->value();
    float y = moveY->value();
    float z = lineEditZ->text().toFloat();
    transform->setTranslation(QVector3D(x, y, z));
    moveZ->setValue(z);
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

  QHBoxLayout *xLayout = new QHBoxLayout();
  xLayout->addWidget(rotateX);
  xLayout->addWidget(lineEditRX);

  QHBoxLayout *yLayout = new QHBoxLayout();
  yLayout->addWidget(rotateY);
  yLayout->addWidget(lineEditRY);

  QHBoxLayout *zLayout = new QHBoxLayout();
  zLayout->addWidget(rotateZ);
  zLayout->addWidget(lineEditRZ);

  layout->addWidget(rotateXlabel);
  layout->addLayout(xLayout);
  layout->addWidget(rotateYlabel);
  layout->addLayout(yLayout);
  layout->addWidget(rotateZlabel);
  layout->addLayout(zLayout);

  connect(rotateX, &QSlider::valueChanged, this, [=]() {
    float angle = rotateX->value();
    transform->setRotationX(angle);
    lineEditRX->setText(QString::number(angle));
  });

  connect(rotateY, &QSlider::valueChanged, this, [=]() {
    float angle = rotateY->value();
    transform->setRotationY(angle);
    lineEditRY->setText(QString::number(angle));
  });

  connect(rotateZ, &QSlider::valueChanged, this, [=]() {
    float angle = rotateZ->value();
    transform->setRotationZ(angle);
    lineEditRZ->setText(QString::number(angle));
  });

  connect(lineEditRX, &QLineEdit::returnPressed, this, [=]() {
    float angle = lineEditRX->text().toFloat();
    transform->setRotationX(angle);
    rotateX->setValue(angle);
  });

  connect(lineEditRY, &QLineEdit::returnPressed, this, [=]() {
    float angle = lineEditRY->text().toFloat();
    transform->setRotationY(angle);
    rotateY->setValue(angle);
  });

  connect(lineEditRZ, &QLineEdit::returnPressed, this, [=]() {
    float angle = lineEditRZ->text().toFloat();
    transform->setRotationZ(angle);
    rotateZ->setValue(angle);
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

void SettingsWindow::point_settings(Qt3DCore::QEntity *parentWin,
                                    s21_object objInf) {
  float radius = 0.03;
  QLabel *typeLabel = new QLabel("Select point type:", this);
  QRadioButton *noneTypeRadioButton = new QRadioButton("None", this);
  QRadioButton *circleTypeRadioButton = new QRadioButton("Circle", this);
  QRadioButton *squareTypeRadioButton = new QRadioButton("Square", this);
  QHBoxLayout *hLayout = new QHBoxLayout();
  hLayout->addWidget(noneTypeRadioButton);
  hLayout->addWidget(circleTypeRadioButton);
  hLayout->addWidget(squareTypeRadioButton);
  layout->addWidget(typeLabel);
  layout->addLayout(hLayout);

  connect(noneTypeRadioButton, &QRadioButton::clicked, this, [=]() {
    qDeleteAll(pointEntities);
    pointEntities.clear();
  });
  connect(circleTypeRadioButton, &QRadioButton::clicked, this, [=]() {
    qDeleteAll(pointEntities);
    pointEntities.clear();
    circle_point(parentWin, objInf, radius);
  });
  connect(squareTypeRadioButton, &QRadioButton::clicked, this, [=]() {
    qDeleteAll(pointEntities);
    pointEntities.clear();
    square_point(parentWin, objInf, radius);
  });
  layout->addWidget(pointColor);
  connect(pointColor, &QPushButton::clicked, this, [=]() {
    QColor color =
        QColorDialog::getColor(Qt::white, this, "Choose point color");
    if (color.isValid()) {
      for (auto &entity : pointEntities) {
        Qt3DExtras::QDiffuseSpecularMaterial *point_material =
            new Qt3DExtras::QDiffuseSpecularMaterial(parentWin);
        point_material->setAmbient(color);
        entity->addComponent(point_material);
      }
    }
  });
}

void SettingsWindow::circle_point(Qt3DCore::QEntity *parentWin,
                                  s21_object object, float radius) {
  for (int i = 0; i < object.num_of_polygons; i++) {
    for (int j = 0; j < POLYGON_SIZE; j++) {
      Qt3DExtras::QCylinderMesh *circleMesh =
          new Qt3DExtras::QCylinderMesh(parentWin);
      circleMesh->setRadius(radius);
      circleMesh->setLength(0);

      Qt3DCore::QTransform *sphere_transform =
          new Qt3DCore::QTransform(parentWin);
      float xpos = object.polygons[i].vertices[j].x;
      float ypos = object.polygons[i].vertices[j].y;
      float zpos = object.polygons[i].vertices[j].z;
      sphere_transform->setTranslation(QVector3D(xpos, ypos, zpos));

      Qt3DExtras::QPhongMaterial *sphere_material =
          new Qt3DExtras::QPhongMaterial(parentWin);

      Qt3DCore::QEntity *sphereEntity = new Qt3DCore::QEntity(parentWin);
      sphereEntity->addComponent(circleMesh);
      sphereEntity->addComponent(sphere_transform);
      sphereEntity->addComponent(sphere_material);

      pointEntities.append(sphereEntity);
    }
  }
}

void SettingsWindow::square_point(Qt3DCore::QEntity *parentWin,
                                  s21_object object, float side) {
  for (int i = 0; i < object.num_of_polygons; i++) {
    for (int j = 0; j < POLYGON_SIZE; j++) {
      Qt3DExtras::QPlaneMesh *squareMesh =
          new Qt3DExtras::QPlaneMesh(parentWin);
      squareMesh->setWidth(side);
      squareMesh->setHeight(side);

      Qt3DCore::QTransform *square_transform =
          new Qt3DCore::QTransform(parentWin);
      float xpos = object.polygons[i].vertices[j].x;
      float ypos = object.polygons[i].vertices[j].y;
      float zpos = object.polygons[i].vertices[j].z;
      square_transform->setTranslation(QVector3D(xpos, ypos, zpos));

      Qt3DExtras::QPhongMaterial *sphere_material =
          new Qt3DExtras::QPhongMaterial(parentWin);

      Qt3DCore::QEntity *squareEntity = new Qt3DCore::QEntity(parentWin);
      squareEntity->addComponent(squareMesh);
      squareEntity->addComponent(square_transform);
      squareEntity->addComponent(sphere_material);

      pointEntities.append(squareEntity);
    }
  }
}