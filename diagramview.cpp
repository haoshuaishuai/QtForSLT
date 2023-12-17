#include "diagramview.h"
#include <QKeyEvent>
#include <QDebug>
#include "diagramitem.h"
#include "diagramtextitem.h"

DiagramView::DiagramView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent) {

    setDragMode(QGraphicsView::RubberBandDrag);
    //setViewportMargins(0, 50, 0, 0);

}

void DiagramView::keyPressEvent(QKeyEvent* event) {

    if ((event->modifiers() & Qt::KeyboardModifier::ControlModifier) != 0) {
        setDragMode(DragMode::ScrollHandDrag);
    }
    QGraphicsView::keyPressEvent(event);

}

void DiagramView::keyReleaseEvent(QKeyEvent* event) {

    if ((event->modifiers() & Qt::KeyboardModifier::ControlModifier) == 0) {
        setDragMode(DragMode::RubberBandDrag);
    }

}

