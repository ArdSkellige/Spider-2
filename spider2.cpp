#include "spider2.h"

#include <QDebug>
#include <QIcon>
#include <QColorDialog>
#include <QMouseEvent>
#include <QString>
#include <QTextStream>
#include <QToolTip>
#include <QPainter>
#include <QRect>
#include <QPixmap>
#include <QBitmap>
#include <QSize>

Spider2::Spider2(QWidget *parent, bool draw)
    : QWidget(parent), isDrawing(draw)
{
    Qt::WindowFlags flags = Qt::Widget;
    flags |= Qt::CustomizeWindowHint;
    flags |= Qt::WindowTitleHint;
    flags |= Qt::WindowSystemMenuHint;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::WindowStaysOnTopHint;
    this->setWindowFlags(flags);

    QString title = "Spider 2";
    this->setWindowTitle(title);

    QIcon icon("Images_lab1/icon1.ico");
    this->setWindowIcon(icon);

    QPalette pal;
    QColorDialog colDia;
    QColor col = colDia.getColor();
    bool b = col.isValid();
    if(b)
    {
        pal.setColor(QPalette::Active, QPalette::Window, col);
    }
    else
    {
        pal.setColor(QPalette::Active, QPalette::Window, "DarkOliveGreen");
    }
    pal.setColor(QPalette::Inactive, QPalette::Window, "DarkKhaki");
    this->setPalette(pal);

    QPixmap pixCurs;
    bool b2 = pixCurs.load("Images_lab1/cursor1.cur");
    if(b2)
    {
        pixCurs.setMask(QBitmap("Images_lab1/cursor1.cur"));
        cursor = pixCurs;
    }
    else
    {
        cursor = Qt::ClosedHandCursor;
    }

    this->setCursor(Qt::CrossCursor);
}

Spider2::~Spider2()
{
}


// QWidget interface:
void Spider2::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        qDebug() << "Left Mouse Button";
        isDrawing = true;
        mousePoint = event->pos();
        this->repaint();
        this->setCursor(cursor);
    }
    if(event->buttons() == Qt::RightButton && event->modifiers() == Qt::ControlModifier)
    {
        qDebug() << "Right Mouse Button";
        // вывод координат курсора на виджет:
        QString txtCoord;
        QTextStream tstream(&txtCoord);
        tstream << "x=" << event->pos().rx() << "; y=" << event->pos().ry() << ";";
        QPoint point(event->globalPos().rx(), event->globalPos().ry());
        QToolTip::showText(point, txtCoord);
    }
}

void Spider2::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::NoButton)
    {
        qDebug() << "NO Left Mouse Button" << event->modifiers();
        isDrawing = false;
        this->setCursor(Qt::CrossCursor);
    }
}

void Spider2::mouseMoveEvent(QMouseEvent *event)
{
    if(isDrawing)
    {
        mousePoint = event->pos();
        this->repaint();

        QRect frame(this->rect());
        bool isCursor = frame.contains(mousePoint);
        if(isCursor)
        {
            this->setCursor(cursor);
        }
        else
        {
            this->setCursor(Qt::CrossCursor);
        }
    }
}

void Spider2::paintEvent(QPaintEvent *event)
{
    if(isDrawing)
    {
        QPainter paint(this);
        QRect frame(this->rect());
        paint.drawLine(frame.topLeft(), mousePoint);
        paint.drawLine(frame.topRight(), mousePoint);
        paint.drawLine(frame.bottomLeft(), mousePoint);
        paint.drawLine(frame.bottomRight(), mousePoint);
        paint.drawLine(QPoint(frame.width()/2, 0), mousePoint);
        paint.drawLine(QPoint(0, frame.height()/2), mousePoint);
        paint.drawLine(QPoint(frame.width()/2, frame.height()), mousePoint);
        paint.drawLine(QPoint(frame.width(), frame.height()/2), mousePoint);
    }
}


void Spider2::resizeEvent(QResizeEvent *event)
{
    QSize sizeFrame = event->size();
    QString newTitle("Spider 2: ");
    newTitle.append("height=");
    newTitle.append(QString().number(sizeFrame.height()));
    newTitle.append("; width=");
    newTitle.append(QString().number(sizeFrame.width()));
    this->setWindowTitle(newTitle);
}
