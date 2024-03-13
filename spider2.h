#ifndef SPIDER2_H
#define SPIDER2_H

#include <QWidget>
//#include <QPoint>

class Spider2 : public QWidget
{
    Q_OBJECT
    bool isDrawing;
    QPoint mousePoint;
    QCursor cursor;

public:
    Spider2(QWidget *parent = nullptr, bool draw = false);
    ~Spider2();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
};
#endif // SPIDER2_H
