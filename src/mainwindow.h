#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QFileDialog>
#include <QImageWriter>
#include <QLineEdit>
#include <QMainWindow>
#include <QMesh>
#include <QScreen>

#include "settingswindow.h"

extern "C" int start_parsing();
extern "C" void object_parser(FILE *, s21_object *, s21_vertex *, int);
extern "C" int parser_counter(FILE *, s21_object *);
extern "C" void printPolygon(s21_object *object);

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void open_object_file(Qt3DExtras::Qt3DWindow *, QLineEdit *,
                        QPushButton *);        //
  void object_info(s21_object, const char *);  //
  void settings(Qt3DExtras::Qt3DWindow *);     //

  s21_object start_parsing(const char *);
  void image_render();

 private:
  Ui::MainWindow *ui;
  Qt3DCore::QEntity *parentWin = nullptr;    // корневое окно
  Qt3DRender::QCamera *cameraObj = nullptr;  // камера
  Qt3DCore::QEntity *sceneLoader = nullptr;  // базовая сущность
  Qt3DRender::QSceneLoader *loader = nullptr;  // для загрузки файлов
  Qt3DRender::QMesh *mesh = nullptr;
  Qt3DCore::QEntity *object = nullptr;
  Qt3DCore::QTransform *transform = nullptr;
  QVBoxLayout *layout = nullptr;
  QPushButton *settingsButton = nullptr;
  Qt3DRender::QRenderCapture *capture;
  SettingsWindow *settingsWin;
  Qt3DRender::QRenderCaptureReply *captureReply;
  Qt3DExtras::Qt3DWindow *view;
  QWidget *widget;
  QSettings re_settings;
  Qt3DExtras::QDiffuseSpecularMaterial *line_material;
  s21_object objInfo;
  QLabel *fileLabel = nullptr;
  QLabel *verticesLabel = nullptr;
  QLabel *polygonsLabel = nullptr;
  QString prevModel;
  bool settings_flag = false;
};
#endif  // MAINWINDOW_H
