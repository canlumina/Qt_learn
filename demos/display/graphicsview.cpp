#include "graphicsview.h"

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

GraphicsView::GraphicsView(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);

    auto *description = new QLabel(tr("可拖动的矩形与椭圆，提供放大、缩小和复位。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);

    auto *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 420, 240);
    /* 创建矩形和椭圆 */
    auto *rectangle = scene->addRect(30, 40, 120, 70, QPen(Qt::darkBlue), QBrush(QColor("#8bdce0")));
    auto *ellipse = scene->addEllipse(180, 40, 120, 70, QPen(Qt::darkRed), QBrush(QColor("#f0c0c0")));
    /* 两个图形均可用鼠标选择、拖动，生命周期由 scene 管理。 */
    rectangle->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    ellipse->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    auto *view = new QGraphicsView(scene, this);
    /* 启用反锯齿 */
    view->setRenderHint(QPainter::Antialiasing);
    auto *zoomIn = new QPushButton(tr("放大"), this);
    auto *zoomOut = new QPushButton(tr("缩小"), this);
    auto *reset = new QPushButton(tr("复位"), this);
    auto *buttons = new QHBoxLayout;
    buttons->addWidget(zoomIn);
    buttons->addWidget(zoomOut);
    buttons->addWidget(reset);
    layout->addLayout(buttons);
    layout->addWidget(view, 1);

    /**
     * @brief 当前缩放小于 4 倍时，将视图等比例放大 1.2 倍
     * @note 无参数、无返回值；在 GUI 线程执行，阈值在缩放前判断，最后一步可略超 4 倍。
     */
    connect(zoomIn, &QPushButton::clicked, this, [view]() {
        if (view->transform().m11() < 4.0)
            view->scale(1.2, 1.2);
    });

    /**
     * @brief 当前缩放大于 0.3 倍时，将视图等比例缩小为原来的 1/1.2
     * @note 无参数、无返回值；在 GUI 线程执行，阈值在缩放前判断，最后一步可略低于 0.3 倍。
     */
    connect(zoomOut, &QPushButton::clicked, this, [view]() {
        if (view->transform().m11() > 0.3)
            view->scale(1.0 / 1.2, 1.0 / 1.2);
    });

    /* 只清除视图变换，恢复原始比例；不恢复图形被拖动前的位置。 */
    connect(reset, &QPushButton::clicked, view, &QGraphicsView::resetTransform);
}
