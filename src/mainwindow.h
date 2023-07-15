#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "auxiliary_modules.h"
#include "settingswindow.h"
#include <QColor>
#include <QFileDialog>
#include <QLineEdit>
#include <QMainWindow>
#include <QMesh>
#include <QScreen>

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
  void open_object_file(Qt3DExtras::Qt3DWindow *, Qt3DCore::QEntity *,
                        QVBoxLayout *, QLineEdit *, QPushButton *);
  void object_info(s21_object, const char *);
  void settings(Qt3DExtras::Qt3DWindow *, Qt3DCore::QEntity *, QVBoxLayout *);
  void projection_settings(QVBoxLayout *);
  void edges_settings(Qt3DCore::QEntity *, QVBoxLayout *);
  void vertecies_settings(QVBoxLayout *);
  void display_circles(Qt3DRender::QMesh::Status status);
  void background_settings(Qt3DExtras::Qt3DWindow *, QVBoxLayout *);
  void line_color_settings(Qt3DExtras::Qt3DWindow *, QVBoxLayout *);
  void line_type_settings(QVBoxLayout *);
  void create_primitive_around_vertex(Qt3DCore::QEntity *rootEntity,
                                      Qt3DRender::QGeometry *geometry,
                                      const QString &primitiveType, float size);
  void image_render(Qt3DExtras::Qt3DWindow *);
  void circle_point(s21_object, float);
  void square_point(s21_object, float);
  int start_parsing(const char *);
  void record();

private:
  Ui::MainWindow *ui;
  Qt3DCore::QEntity *parentWin = nullptr;   // корневое окно
  Qt3DRender::QCamera *cameraObj = nullptr; // камера
  Qt3DCore::QEntity *sceneLoader = nullptr; // базовая сущность
  Qt3DRender::QSceneLoader *loader = nullptr; // для загрузки файлов
  Qt3DRender::QMesh *mesh = nullptr;
  Qt3DCore::QEntity *object = nullptr;
  Qt3DCore::QTransform *transform = nullptr;
  QVBoxLayout *layout = nullptr;
  QPushButton *settingsButton = nullptr;
  Qt3DRender::QRenderCapture *capture;
  SettingsWindow *settingsWin;
};
#endif // MAINWINDOW_H
