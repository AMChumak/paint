#pragma once

#include <QPainter>
#include <QScrollArea>

class RenderArea final : public QWidget
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    QPoint getLastPressed() const;
    QPoint getCurrentPressed() const;

signals:
    void mousePressed(const QPoint &pos);
    void mouseMoved(const QPoint &pos);

public slots:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeImage(const QSize &size);
    void setColor(const QColor &color);
    void setPenWidth(const int &width);
    void drawLine(const QPoint &begin, const QPoint &end);
    void drawPolygon(const QPoint &center, const QPoint &vertex, const int &vertexCount);
    void drawStar(const QPoint &center, const QPoint &vertex, const int &limbCount);
    void fillArea(const QPoint &seed);
    void make_screenshot();
    void undo();
    void redo();
    void clean();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen m_pen;
    QImage m_render;
    std::vector<QImage> m_screenshots;
    int opened_step_index = 0;
    int screenshots_limit = 10;
    std::vector<QPoint> mouse_points;
    int mouse_points_limit = 2;
};