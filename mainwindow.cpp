#include "diagramview.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "select_item.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new DiagramScene(this);
    //scene->setSceneRect(QRectF(0, 0,QSizePolicy::Preferred, QSizePolicy::Preferred));

    QHBoxLayout *layout = new QHBoxLayout;
    view = new DiagramView(scene);
    view->setAlignment(Qt::AlignTop);
    layout->addWidget(view);
    ui->widget_Graphics->setLayout(layout);

    SelectItem = new select_item();
    SelectItem->ItemDock = ui->tabWidget;
    SelectItem->CreateTop();
}

/*bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == centralWidget() && event->type() == QEvent::Resize) {
        // 获取centralWidget的大小
        QSize newSize = static_cast<QResizeEvent*>(event)->size();

        // 调整QGraphicsScene的大小为centralWidget的大小
        //QGraphicsScene *scene = static_cast<QGraphicsScene*>(centralWidget()->layout()->itemAt(0)->widget());
        scene->setSceneRect(QRect(QPoint(0, 0), newSize));
    }

    return QObject::eventFilter(obj, event);
}*/

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // 获取centralWidget的大小
    QSize newSize = centralWidget()->size();

    // 调整QGraphicsScene的宽度为centralWidget的宽度
    //scene->setSceneRect(QRect(QPoint(0, 0), QSize(newSize.width(), scene->sceneRect().height())));
}

MainWindow::~MainWindow()
{
    delete ui;
}
