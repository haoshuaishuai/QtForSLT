#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "diagramscene.h"
#include "select_item.h"
#include <QGraphicsView>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:

    void resizeEvent(QResizeEvent *event) override;

public slots:

private:

    Ui::MainWindow *ui;
    QMenu *itemMenu;
    select_item *SelectItem;

    DiagramScene *scene;
    QGraphicsView *view;
};

#endif // MAINWINDOW_H
