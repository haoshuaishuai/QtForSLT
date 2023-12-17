#include "arrow.h"
#include <cmath>
#include <QGraphicsItem>
#include <QLineF>
#include <QPen>
#include <QPainter>
#include <QPushButton>
#include <QGraphicsProxyWidget>

arrow::arrow(const QLineF &line, QGraphicsItem *parent) : QGraphicsLineItem(line, parent){

    QPen pen = this->pen();
    pen.setWidth(2);
    setPen(pen);
    QPushButton *button = new QPushButton("P");
    button->setMinimumSize(16, 16);
    button->setMaximumSize(16, 16);
    button->setStyleSheet("QPushButton { width: 16px; height: 16px; font-size: 10px; }");
    button->setStyleSheet("QPushButton { background-color : #90EE90; }");
    proxyWidget = new QGraphicsProxyWidget(this);
    proxyWidget->setWidget(button);
   // proxyWidget->setPos(line.pointAt(0.5) - QPointF(button->sizeHint().width()/2, button->sizeHint().height()/2));
    proxyWidget->setPos(line.pointAt(0.6) - QPointF(8, 8));


}

void arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){

    painter->setPen(pen());
    painter->setBrush(pen().color());

    QLineF line = this->line();
    painter->drawLine(line);

    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);
    painter->drawPolygon(QPolygonF() << line.p1() << arrowP1 << arrowP2);

}
