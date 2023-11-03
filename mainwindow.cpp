#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(500, 500);
    QTimer *timer = new QTimer;
    connect (timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QTime time = QTime::currentTime();
    QPainter painter;
    painter.begin(this);
    //сглаживание
    painter.setRenderHint(QPainter::Antialiasing);
    //перенос координат в центр
    painter.translate(width() / 2, height() / 2);
    //радиус часов
    int R = 0.35 * qMin(width(), height());
    //отрисовка циферблата
    for (int i = 0; i < 60; ++i)
    {
        //рисуем засечку
        if (!(i % 5))
        {
            painter.drawLine(0, R, 0, R - 10);
        }
        else
        {
            painter.drawLine(0, R, 0, R - 4);
        }
        //поворачиваем
        painter.rotate(6);
    }
    painter.setPen(Qt::NoPen);
    //отрисовка часовой стрелки
    painter.save();
    QPolygon pol;
    pol << QPoint(-0.05 * R, 0) << QPoint(0.05 * R, 0) << QPoint(0, -0.4 * R);
    painter.rotate(30 * (time.hour() + time.minute() / 60. + time.second() / 3600.));
    painter.setBrush(QColor(45, 138, 64));
    painter.drawPolygon(pol);
    painter.restore();
    //отрисовка минутной стрелки
    painter.save();
    QPolygon pol2;
    pol2 << QPoint(-0.05 * R, 0) << QPoint(0.05 * R, 0) << QPoint(0, -0.7 * R);
    painter.rotate(6 * (time.minute() + time.second() / 60.));
    //последяя цифра отвечает за прозрачность
    painter.setBrush(QColor(0, 127, 127, 191));
    painter.drawPolygon(pol2);
    painter.restore();
    //отрисовка сукундной стрелки
    painter.save();
    QPolygon pol3;
    pol3 << QPoint(-0.03 * R, 0) << QPoint(0.03 * R, 0) << QPoint(0, -0.9 * R);
    painter.rotate(6 * time.second());
    painter.setBrush(QColor(202, 0, 0, 191));
    painter.drawPolygon(pol3);
    painter.restore();
    painter.end();
}

