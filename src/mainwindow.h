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
extern "C" int start_parsing();
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
  void display_circles(Qt3DRender::QMesh::Status status);
  void background_settings(Qt3DExtras::Qt3DWindow *, QVBoxLayout *);
  void line_color_settings(Qt3DExtras::Qt3DWindow *, QVBoxLayout *);
  void line_type_settings(QVBoxLayout *);
  void create_primitive_around_vertex(Qt3DCore::QEntity* rootEntity, Qt3DRender::QGeometry *geometry, const QString& primitiveType, float size);
  void image_render(Qt3DExtras::Qt3DWindow *);
  void record();

private:
  Ui::MainWindow *ui;
  Qt3DCore::QEntity *rootWin = nullptr;     // корневое окно
  Qt3DRender::QCamera *cameraObj = nullptr; // камера
  Qt3DCore::QEntity *sceneLoader = nullptr; // базовая сущность
  Qt3DRender::QSceneLoader *loader = nullptr; // для загрузки файлов
  Qt3DRender::QMesh *mesh = nullptr;
  Qt3DCore::QEntity *object = nullptr;
  Qt3DCore::QTransform *transform = nullptr;
  QVBoxLayout *layout = nullptr;

  QSlider *moveX = nullptr;
  QSlider *moveY = nullptr;
  QSlider *moveZ = nullptr;
  QLabel *moveXlabel = nullptr;
  QLabel *moveYlabel = nullptr;
  QLabel *moveZlabel = nullptr;
  QPushButton *showSlidersButton = nullptr;

  QSlider *rotateX = nullptr;
  QSlider *rotateY = nullptr;
  QSlider *rotateZ = nullptr;
  QLabel *rotateXlabel = nullptr;
  QLabel *rotateYlabel = nullptr;
  QLabel *rotateZlabel = nullptr;
  QPushButton *showSlidersButton2 = nullptr;

  QSlider *scaleObject = nullptr;
  QLabel *scaleObjectLabel = nullptr;

  QPushButton *settingsButton = nullptr;
  QPushButton *parallelProjection = nullptr;
  QPushButton *centralProjection = nullptr;
  QPushButton *backgroundColor = nullptr;
  QPushButton *lineColor = nullptr;
  QPushButton *lineType = nullptr;
  QPushButton *pointType = nullptr;
  Qt3DRender::QRenderCapture *capture;

};
#endif // MAINWINDOW_H
