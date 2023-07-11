#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMesh>
#include <QPushButton>
#include <QScreen>
#include <QSlider>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <QColor>
#include <QColorDialog>

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
  void open_object_file(Qt3DCore::QEntity*, QVBoxLayout *, QLineEdit *, QPushButton *);
  void add_move_sliders(QVBoxLayout *, Qt3DCore::QTransform *);
  void add_rotate_sliders(QVBoxLayout *, Qt3DCore::QTransform *);
  void add_scale_slider(QVBoxLayout *, Qt3DCore::QTransform *);
  void object_info(QVBoxLayout *layout, Qt3DRender::QMesh *mesh,
                   const QString &filename);
  void settings(Qt3DExtras::Qt3DWindow *, Qt3DCore::QEntity*, QVBoxLayout *);
  void projection_settings(QVBoxLayout *);
  void edges_settings(Qt3DCore::QEntity*, QVBoxLayout *);
  void vertecies_settings(QVBoxLayout *);
  void background_settings(Qt3DExtras::Qt3DWindow *, QVBoxLayout *);
  void record();

private:
  Ui::MainWindow *ui;
  Qt3DCore::QEntity *rootWin = nullptr;     // корневое окно
  Qt3DRender::QCamera *cameraObj = nullptr; // камера
  Qt3DCore::QEntity *sceneLoader = nullptr; // базовая сущность
  Qt3DRender::QSceneLoader *loader = nullptr; // для загрузки файлов

};
#endif // MAINWINDOW_H
