#include "bullseye.h"
#include <QPainter>

Bullseye::Bullseye(QWidget *parent)
    : QWidget{parent}
{

}

void Bullseye::addHit(int x, int y, int speed)
{
    QPoint point(x,y); // scale in the paintEvent member.

    mHits.push_back(point);
    update();
}

void Bullseye::clear()
{
    mHits.clear();
    update();
}

void Bullseye::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);



    QPoint zero(0,0);

    int sizeOrig = qMin(width(),height());
    float size = sizeOrig/20.0;

    painter.setPen(Qt::SolidLine);

    // draw circles.

    painter.drawEllipse(zero, (int)(size*10), (int)(size*10));
    painter.drawEllipse(zero, (int)(size*9), (int)(size*9));
    painter.drawEllipse(zero, (int)(size*8), (int)(size*8));
    painter.drawEllipse(zero, (int)(size*7), (int)(size*7));
    painter.drawEllipse(zero, (int)(size*6), (int)(size*6));
    painter.drawEllipse(zero, (int)(size*5), (int)(size*5));
    painter.drawEllipse(zero, (int)(size*4), (int)(size*4));

    // draw middle black bullseye
    painter.save();
    painter.setPen(Qt::SolidLine);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::black);

    painter.drawEllipse(zero, (int)(size*3), (int)(size*3));
    painter.drawEllipse(zero, (int)(size*2), (int)(size*2));

    // Draw middle bullseye
    painter.setBrush(Qt::white);
    painter.drawEllipse(zero, (int)(size*1), (int)(size*1));

    painter.restore();



    painter.save();
    painter.setFont(QFont("System",size/2));
    painter.drawText(QRectF(-size, -size, size*2, size*2), Qt::AlignCenter, "10");
    painter.drawRect(QRectF(QPointF(-size/2.0 + size, -size/2.0)+ QPointF(0.5 * size, 0), QSizeF(size, size)));
    painter.setPen(Qt::white);
    for(int i = 1; i < 10; i++)
    {
        if(i==3)
        {
            painter.setPen(Qt::black);
        }
        painter.drawText(QRectF(QPointF(-size/2.0 + size*i, -size/2.0)+ QPointF(0.5 * size, 0), QSizeF(size, size)), Qt::AlignCenter, QString::number(10-i));
        painter.drawText(QRectF(QPointF(-size/2.0 - size*i, -size/2.0)+ QPointF(-0.5 * size, 0), QSizeF(size, size)), Qt::AlignCenter, QString::number(10-i));
        painter.drawText(QRectF(QPointF(-size/2.0, -size/2.0 + size*i)+ QPointF(0, 0.5 * size), QSizeF(size, size)), Qt::AlignCenter, QString::number(10-i));
        painter.drawText(QRectF(QPointF(-size/2.0, -size/2.0 - size*i)+ QPointF(0, -0.5 * size), QSizeF(size, size)), Qt::AlignCenter, QString::number(10-i));
    }
    painter.restore();


    painter.save();


    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::gray);
    // 10 rings with 5mm increase in radius => 50mm radius, scale accordingly.
    // the point is expressed in mm from center.

    const float scaleFactor = (((float)sizeOrig/2)/50); // radius of widget is size/2, radius of target is 50mm.
    foreach (auto point, mHits) {
        QPointF pointf(point);
        painter.drawEllipse(pointf*scaleFactor, size/3, size/3);
    }
    if(!mHits.empty())
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::magenta);
        QVector<QPoint>::reverse_iterator iter = mHits.rbegin();
        QPointF pointf(*iter);
        painter.drawEllipse(pointf*scaleFactor, size/2, size/2);
    }





    painter.restore();


}
