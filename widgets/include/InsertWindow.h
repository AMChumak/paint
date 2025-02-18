#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QSpinBox>
#include <QSlider>
#include <QWidget>
#include "RenderArea.h"
#include <QComboBox>
#include <QDialogButtonBox>

class InsertWindow : public QWidget
{
    Q_OBJECT

public:

    enum FigureTypes
    {
        FigureTypes_POLYGON = 0,
        FigureTypes_STAR = 1,
    };

    explicit InsertWindow(QWidget *parent = nullptr, int width = 0, int height = 0);

signals:
    void insertFigure(const QPoint &offset, const int &count, enum FigureTypes type);

public slots:
    void onRadiusChanged(int newRadius);
    void onRotationChanged(int newAngle);
    void onCountChanged(int newCount);
    void onTypeChanged(int newIndex);
    void onAccept();
    void onReject();

private:
    void updateRender();

private:
    QVBoxLayout *m_layout;
    QHBoxLayout *panel_layout;
    QVBoxLayout *settings_layout;
    QHBoxLayout *count_layout;
    QHBoxLayout *radius_layout;
    QHBoxLayout *rotation_layout;

    QDialogButtonBox *buttonBox;
    RenderArea *renderArea;

    QLabel *radius_label;
    QSlider *radius_slider;
    QSpinBox *radius_spinbox;

    QLabel *rotation_label;
    QSlider *rotation_slider;
    QSpinBox *rotation_spinbox;

    QLabel *count_label;
    QSlider *count_slider;
    QSpinBox *count_spinbox;

    QComboBox *type_combo_box;

    QPoint offset;
    QPoint center;
};