#ifndef HITDATA_H
#define HITDATA_H
#include <QTextStream>
#include <QStringList>

class hitData
{
    hitData();
public:
    hitData(int X, int Y, int sX, int sY);
    hitData(QStringList list);

    friend QTextStream &operator<<(QTextStream &out, const hitData data);

private:
    int posX, posY, speedX, speedY;
};

#endif // HITDATA_H
