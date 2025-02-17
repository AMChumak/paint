#pragma once

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

#include "RenderArea.h"

class WidthWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WidthWindow(QWidget *parent = nullptr, const int &currentWidth = 1);

signals:
    void widthChanged(const int &width);

private slots:
    void onAccept();
    void onReject();
    void onSpinBoxUpdate(int width);

private:
    QVBoxLayout *m_layout;
    QHBoxLayout *row_layout;
    QLabel *width_label;
    QSpinBox *width_spinbox;
    QDialogButtonBox *buttonBox;
    RenderArea *renderArea;
};