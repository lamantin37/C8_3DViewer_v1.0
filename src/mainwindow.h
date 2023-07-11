#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <QMesh>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>

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
  void open_object_file(QVBoxLayout*, QLineEdit*, QPushButton*);
  void add_move_sliders(QVBoxLayout*, Qt3DCore::QTransform *);
  void add_rotate_sliders(QVBoxLayout*, Qt3DCore::QTransform *);
  void add_scale_slider(QVBoxLayout*, Qt3DCore::QTransform *);
  void object_info(QVBoxLayout*, Qt3DRender::QMesh *, QString);

private:
  Ui::MainWindow *ui;
  Qt3DCore::QEntity *rootWin = nullptr;     // корневое окно
  Qt3DRender::QCamera *cameraObj = nullptr; // камера
  Qt3DCore::QEntity *sceneLoader = nullptr; // базовая сущность
  Qt3DRender::QSceneLoader *loader = nullptr; // для загрузки файлов
};
#endif // MAINWINDOW_H
