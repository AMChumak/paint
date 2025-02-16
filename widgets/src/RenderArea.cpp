#include "RenderArea.h"
#include <QSize>
#include <QTransform>

#include <qevent.h>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    for (int i = 0; i != mouse_points_limit; ++i) {
        mouse_points.emplace_back(-1, -1);
    }
    m_render = QImage(400, 400, QImage::Format_ARGB32);
    m_render.fill(Qt::white);
    m_screenshots.push_back(m_render);
    setMouseTracking(true);
    update();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(0, 0);
}
QSize RenderArea::sizeHint() const
{
    return QSize(402, 402);
}
QPoint RenderArea::getLastPressed() const
{
    return mouse_points.front();
}
QPoint RenderArea::getCurrentPressed() const
{
    return mouse_points.back();
}
void RenderArea::mousePressEvent(QMouseEvent *event)
{
    while (mouse_points.size() > mouse_points_limit - 1) {
        mouse_points.erase(mouse_points.begin());
    }
    mouse_points.push_back(event->position().toPoint());
    emit mousePressed(mouse_points.back());
    QWidget::mousePressEvent(event);
}
void RenderArea::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event->position().toPoint());
    QWidget::mouseMoveEvent(event);
}

void RenderArea::resizeImage(const QSize &size)
{
    m_render = m_screenshots[opened_step_index].scaled(size, Qt::KeepAspectRatio, Qt::FastTransformation);
    resize(m_render.width()+2, m_render.height()+2);
    update();
}
void RenderArea::setColor(const QColor &color)
{
    m_pen.setColor(color);
    update();
}
void RenderArea::setPenWidth(const int &width)
{
    m_pen.setWidth(width);
    update();
}

inline void bresenhamAlgorithm(
    QImage &image, const QColor &color, const QPoint &begin, const QPoint &end)
{
    std::vector<QPoint> result;
    int x_q = 1; //coefficient of transofrm
    int y_q = 1;
    bool is_swap = false;
    //get normal form of line, save transformation
    int x_dif = end.x() - begin.x();
    int y_dif = end.y() - begin.y();

    if (x_dif != 0) { // line y = ax + b
        if (abs(y_dif) > abs(x_dif)) {
            is_swap = true;
        }
    } else { //vertical line
        if (y_dif > 0) {
            is_swap = true;
        } else if (y_dif < 0) {
            is_swap = true;
            x_q = -1;
        } else { // point
            image.setPixelColor(begin.x(), begin.y(), color);
            return;
        }
    }
    if (x_dif != 0) {
        x_q = x_dif / abs(x_dif);
        x_dif *= x_q;
    }
    if (y_dif != 0) {
        y_q =  y_dif / abs(y_dif);
        y_dif *= y_q;
    }
    if (is_swap) {
        const int tmp = x_dif;
        x_dif = y_dif;
        y_dif = tmp;
    }

    //main part of algorithm
    result.push_back(begin);
    int current_x = begin.x();
    int current_y = begin.y();
    int err = -x_dif;

    for (int i = 0; i < x_dif; ++i) {
        if (is_swap) {
            current_y += y_q;
        } else {
            current_x += x_q;
        }

        err += 2 * y_dif;
        if (err > 0) {
            err -= 2 * x_dif;
            if (is_swap) {
                current_x += x_q;
            } else {
                current_y += y_q;
            }
        }
        image.setPixelColor(current_x, current_y, color);
    }
}

void RenderArea::drawLine(const QPoint &begin, const QPoint &end)
{
    m_render = m_screenshots[opened_step_index];
    if (m_pen.width() == 1) { // Bresenham algorithm
        bresenhamAlgorithm(m_render, m_pen.color(), begin, end);
    } else {
        QPainter painter(&m_render);
        painter.begin(&m_render);
        painter.setPen(m_pen);
        painter.drawLine(begin.x(), begin.y(), end.x(), end.y());
        painter.end();
    }
    update();
}
void RenderArea::drawPolygon(const QPoint &center, const QPoint &vertex, const int &vertexCount)
{
    m_render = m_screenshots[opened_step_index];
    //calculate points
    float angle = 360.0F / vertexCount;
    QTransform rotation = QTransform()
                              .translate(center.x(), center.y())
                              .rotate(-angle)
                              .translate(-center.x(), -center.y());

    QPoint last = vertex;
    for (int i = 0; i < vertexCount; ++i) {
        QPoint next = rotation.map(last);
        bresenhamAlgorithm(m_render, m_pen.color(), last, next);
        last = next;
    }
    update();
}
void RenderArea::drawStar(const QPoint &center, const QPoint &vertex, const int &limbCount)
{
    m_render = m_screenshots[opened_step_index];
    //calculate points
    float angle = 360 / limbCount;

    QTransform rotation = QTransform()
                              .translate(center.x(), center.y())
                              .rotate(-angle)
                              .translate(-center.x(), -center.y());

    QTransform half_rotation = QTransform()
                                   .translate(center.x(), center.y())
                                   .rotate(-angle / 2)
                                   .translate(-center.x(), -center.y());

    QPoint inner_point = half_rotation.map(center + (vertex - center) / 3);

    QPoint last = vertex;
    for (int i = 0; i < limbCount; ++i) {
        QPoint next = rotation.map(last);
        bresenhamAlgorithm(m_render, m_pen.color(), last, inner_point);
        bresenhamAlgorithm(m_render, m_pen.color(), inner_point, next);

        last = next;
        inner_point = rotation.map(inner_point);
    }
    update();
}

void scanSpan(
    const QImage &image,
    const QColor color,
    const QPoint &begin,
    const QPoint &end,
    std::vector<QPoint> &stack)
{
    bool couldAddSpan = true;
    for (QPoint i = begin; i != end; i.setX(i.x() + 1)) {
        if (image.pixelColor(i) != color) {
            couldAddSpan = true;
        } else if (couldAddSpan) {
            stack.push_back(i);
            couldAddSpan = false;
        }
    }
}

void RenderArea::fillArea(const QPoint &seed) //span algorithm
{
    m_render = m_screenshots[opened_step_index];
    QColor inside_color = m_render.pixelColor(seed);
    std::vector<QPoint> stack;
    stack.push_back(seed);
    while (!stack.empty()) {
        QPoint right = stack.back();
        stack.pop_back();
        QPoint left = right + QPoint(-1, 0);
        while (m_render.pixelColor(left) == inside_color) {
            m_render.setPixelColor(left, m_pen.color());
            left += QPoint(-1, 0);
        }
        left += QPoint(1, 0);
        while (m_render.pixelColor(right) == inside_color) {
            m_render.setPixelColor(right, m_pen.color());
            right = right + QPoint(1, 0);
        }
        scanSpan(m_render, inside_color, left + QPoint(0, 1), right + QPoint(0, 1), stack);
        scanSpan(m_render, inside_color, left + QPoint(0, -1), right + QPoint(0, -1), stack);
    }
    update();
}

void RenderArea::make_screenshot()
{
    ++opened_step_index;
    if (opened_step_index < m_screenshots.size()) { // create new memory branch
        m_screenshots.erase(m_screenshots.begin() + opened_step_index, m_screenshots.end());
    }
    if (m_screenshots.size() > screenshots_limit) { // check that screenshots vector is not overflow
        m_screenshots.erase(m_screenshots.begin());
    }
    m_screenshots.push_back(m_render);
}
void RenderArea::undo()
{
    ++opened_step_index;
    m_render = m_screenshots[opened_step_index];
    update();
}
void RenderArea::redo()
{
    ++opened_step_index;
    m_render = m_screenshots[opened_step_index];
    update();
}
void RenderArea::clean()
{
    m_render = m_screenshots[opened_step_index];
    m_render.fill(Qt::white);
    make_screenshot();
    update();
}
void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1,Qt::SolidLine));
    painter.drawLine(QPoint(0, 0), QPoint(m_render.width() + 1, 0));
    painter.drawLine(QPoint(m_render.width() + 1, 0), QPoint(m_render.width() + 1, m_render.height() + 1));
    painter.drawLine(QPoint(m_render.width() + 1, m_render.height() + 1), QPoint(0, m_render.height() + 1));
    painter.drawLine(QPoint(0, m_render.height() + 1), QPoint(0, 0));
    painter.drawImage(QRect(1, 1, m_render.width(), m_render.height()), m_render);
}