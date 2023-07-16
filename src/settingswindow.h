#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H
#include "auxiliary_modules.h"
#include <QColorDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <QFileDialog>
#include <QApplication>

class SettingsWindow : public QWidget {
  Q_OBJECT
public:
  explicit SettingsWindow(QWidget *parent = nullptr,
                          Qt3DCore::QTransform *transform = nullptr);
  void add_move_sliders(Qt3DCore::QTransform *);
  void add_rotate_sliders(Qt3DCore::QTransform *);
  void add_scale_slider(Qt3DCore::QTransform *);
  void projection_settings(Qt3DRender::QCamera *);
  void line_type_settings(Qt3DRender::QMesh *);
  void line_color_settings(Qt3DCore::QEntity *, Qt3DCore::QEntity *);
  void background_settings(Qt3DExtras::Qt3DWindow *);
  void circle_point(Qt3DCore::QEntity *, s21_object, float);
  void square_point(Qt3DCore::QEntity *, s21_object, float);
  void point_settings(Qt3DCore::QEntity *, s21_object);
  void removePoints(Qt3DCore::QEntity *parentWin);
private:
  QLabel *label;
  QVBoxLayout *layout = nullptr;
  QSlider *moveX = nullptr;
  QSlider *moveY = nullptr;
  QSlider *moveZ = nullptr;
  QLabel *moveXlabel = nullptr;
  QLabel *moveYlabel = nullptr;
  QLabel *moveZlabel = nullptr;
  QLineEdit *lineEditX = nullptr;
  QLineEdit *lineEditY = nullptr;
  QLineEdit *lineEditZ = nullptr;

  QSlider *rotateX = nullptr;
  QSlider *rotateY = nullptr;
  QSlider *rotateZ = nullptr;
  QLabel *rotateXlabel = nullptr;
  QLabel *rotateYlabel = nullptr;
  QLabel *rotateZlabel = nullptr;
  QLineEdit *lineEditRX = nullptr;
  QLineEdit *lineEditRY = nullptr;
  QLineEdit *lineEditRZ = nullptr;

  QSlider *scaleObject = nullptr;
  QLabel *scaleObjectLabel = nullptr;

  QPushButton *parallelProjection = nullptr;
  QPushButton *centralProjection = nullptr;
  QPushButton *backgroundColor = nullptr;
  QPushButton *lineColor = nullptr;
  QPushButton *lineType = nullptr;
  QPushButton *pointType = nullptr;
  QList<Qt3DCore::QEntity *> pointEntities;
  QPushButton *pointColor = nullptr;
  QColor currentColor = QColor(Qt::black);
};

#endif // SETTINGSWINDOW_H
