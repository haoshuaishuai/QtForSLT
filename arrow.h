#ifndef ARROW_H
#define ARROW_H

#include <QObject>
#include <QGraphicsLineItem>
#include <QGraphicsProxyWidget>

class arrow : QObject,public QGraphicsLineItem{

    Q_OBJECT

public:

    explicit arrow(const QLineF &line, QGraphicsItem *parent = nullptr);


public:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:

    static const int arrowSize = 10;
    QGraphicsProxyWidget *proxyWidget;

};



#endif // ARROW_H
