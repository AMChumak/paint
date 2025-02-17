#include "WidthWindow.h"


WidthWindow::WidthWindow(QWidget *parent, const int &currentWidth)
    : QWidget(parent)
{
    setWindowTitle("Set Pen Width");
    setFixedSize(300, 180);
    setWindowFlag(Qt::Dialog);
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose);

    m_layout = new QVBoxLayout(this);

    renderArea = new RenderArea(this);
    renderArea->resizeImage(QSize(200,80));
    renderArea->setColor(Qt::black);
    renderArea->setPenWidth(currentWidth);
    renderArea->drawLine(QPoint{0, 40}, QPoint{200, 40});

    m_layout->addWidget(renderArea);

    width_label = new QLabel("width:");

    width_spinbox = new QSpinBox();
    width_spinbox->setRange(1, 50);
    width_spinbox->setValue(currentWidth);
    width_spinbox->setToolTip("from 1 to 50");

    row_layout = new QHBoxLayout();
    row_layout->addWidget(width_label);
    row_layout->addWidget(width_spinbox);

    m_layout->addLayout(row_layout);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    m_layout->addWidget(buttonBox);

    setLayout(m_layout);

    connect(width_spinbox, &QSpinBox::valueChanged, this, &WidthWindow::onSpinBoxUpdate);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(onAccept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(onReject()));
}
void WidthWindow::onAccept()
{
    emit widthChanged(width_spinbox->value());
    close();
}
void WidthWindow::onReject()
{
    close();
}
void WidthWindow::onSpinBoxUpdate(int width)
{
    renderArea->setPenWidth(width);
    renderArea->drawLine(QPoint{0, 40}, QPoint{200, 40});
}