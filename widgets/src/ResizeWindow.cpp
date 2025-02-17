#include "ResizeWindow.h"
#include <QLabel>
#include <QPushButton>

ResizeWindow::ResizeWindow(QWidget *parent, const QSize &currentSize)
{
    setWindowTitle("Resize Image");
    setFixedSize(300, 180);
    setWindowFlag(Qt::Dialog);
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose);

    v_size_spinbox = new QSpinBox();
    v_size_spinbox->setRange(1, 5000);
    v_size_spinbox->setToolTip("from 1 to 5000");
    v_size_spinbox->setValue(currentSize.height());
    h_size_spinbox = new QSpinBox();
    h_size_spinbox->setRange(1, 5000);
    h_size_spinbox->setToolTip("from 1 to 5000");
    h_size_spinbox->setValue(currentSize.width());

    v_size_lbl = new QLabel("vertical size:");
    h_size_lbl = new QLabel("horizontal size:");

    ok_button = new QPushButton("OK");

    grid = new QGridLayout();
    grid->setSpacing(5);
    grid->addWidget(h_size_lbl, 0, 0, 1, 1);
    grid->addWidget(h_size_spinbox, 0, 1, 1, 1);
    grid->addWidget(v_size_lbl, 1, 0, 1, 1);
    grid->addWidget(v_size_spinbox, 1, 1, 1, 1);

    m_layout = new QVBoxLayout();
    m_layout->setSpacing(5);
    m_layout->addLayout(grid);
    m_layout->addWidget(ok_button);
    setLayout(m_layout);

    connect(ok_button, SIGNAL(pressed()), this, SLOT(onOKClicked()));
}
void ResizeWindow::onOKClicked()
{
    emit getNewSize(QSize{h_size_spinbox->value(), v_size_spinbox->value()});
    close();
}