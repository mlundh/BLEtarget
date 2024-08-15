#ifndef BULLSEYE_H
#define BULLSEYE_H

#include <QWidget>
#include <qvector.h>

class Bullseye : public QWidget
{
    Q_OBJECT
public:
    explicit Bullseye(QWidget *parent = nullptr);
    /**
     * @brief addHit add a new hit to the target.
     * @param x x position in mm from the center.
     * @param y y position in mm from the center.
     * @param speed speed of the pellet.
     */
    void addHit(int x, int y, int speedX, int speedY);

    /**
     * @brief clear clear the vector used to show hits.
     */
    void clear();

protected:
    void paintEvent(QPaintEvent *event) override;
    QVector<QPoint> mHits;
    QVector<int32_t> mSpeedX;
    QVector<int32_t> mSpeedY;


signals:

};

#endif // BULLSEYE_H
