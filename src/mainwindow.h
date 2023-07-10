#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QForwardRenderer>
#include <QScreen>

#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QAttribute>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QTransform>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#include <Qt3DRender/QCamera>
#include <Qt3DRender/QSceneLoader>
#include <Qt3DCore/QEntity>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Qt3DCore::QEntity *rootWin = nullptr;    // корневое окно
    Qt3DRender::QCamera *cameraObj = nullptr;    // камера
    Qt3DCore::QEntity *sceneLoader = nullptr; // базовая сущность
    Qt3DRender::QSceneLoader *loader = nullptr; // для загрузки файлов
};
#endif // MAINWINDOW_H
