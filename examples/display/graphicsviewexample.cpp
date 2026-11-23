#include "graphicsviewexample.h"

#include <QBrush>
#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QPushButton>
#include <QVBoxLayout>

GraphicsViewExample::GraphicsViewExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("可拖动的矩形与椭圆，提供放大、缩小和复位。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 420, 240);
    auto *rectangle = scene->addRect(30, 40, 120, 70, QPen(Qt::darkBlue), QBrush(QColor("#8dbce0")));
    auto *ellipse = scene->addEllipse(220, 90, 100, 80, QPen(Qt::darkGreen), QBrush(QColor("#9fd4a8")));
    rectangle->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    ellipse->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    auto *view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    auto *zoomIn = new QPushButton(tr("放大"), this);
    auto *zoomOut = new QPushButton(tr("缩小"), this);
    auto *reset = new QPushButton(tr("复位缩放"), this);
    auto *buttons = new QHBoxLayout;
    buttons->addWidget(zoomIn);
    buttons->addWidget(zoomOut);
    buttons->addWidget(reset);
    layout->addLayout(buttons);
    layout->addWidget(view, 1);
    /** @brief 有界放大画布；无参数、无返回值；限制缩放倍数，避免无限放大。 */
    connect(zoomIn, &QPushButton::clicked, this, [view] {
        if (view->transform().m11() < 4.0)
            view->scale(1.2, 1.2);
    });
    /** @brief 有界缩小画布；无参数、无返回值；保留最低可见比例。 */
    connect(zoomOut, &QPushButton::clicked, this, [view] {
        if (view->transform().m11() > 0.3)
            view->scale(1.0 / 1.2, 1.0 / 1.2);
    });
    connect(reset, &QPushButton::clicked, view, &QGraphicsView::resetTransform);
}
