#include "hitdata.h"

hitData::hitData(int X, int Y, int sX, int sY)
  :posX(X)
  ,posY(Y)
  ,speedX(sX)
  ,speedY(sY)

{

}

hitData::hitData(QStringList list)
{

}


QTextStream &operator<<(QTextStream &out, const hitData data)
{
    out << data.posX;
    out << ",";
    out << data.posY;
    out << ",";
    out << data.speedX;
    out << ",";
    out << data.speedY;
    out << Qt::endl;
    return out;
}


