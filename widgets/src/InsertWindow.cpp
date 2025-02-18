#include "InsertWindow.h"

InsertWindow::InsertWindow(QWidget *parent, int width, int height)
{
    setWindowTitle("Insert Figure");
    setFixedSize(300, 300);
    setWindowFlag(Qt::Dialog);
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose);

    m_layout = new QVBoxLayout(this);
    panel_layout = new QHBoxLayout();
    settings_layout = new QVBoxLayout();
    count_layout = new QHBoxLayout();
    radius_layout = new QHBoxLayout();
    rotation_layout = new QHBoxLayout();

    renderArea = new RenderArea(this);
    renderArea->resizeImage(QSize(151, 151));
    renderArea->setColor(Qt::black);
    renderArea->setPenWidth(1);
    center = QPoint(76, 76);
    offset = QPoint(0, -50);
    renderArea->drawPolygon(center, center + offset, 3);

    count_label = new QLabel("count:");
    count_spinbox = new QSpinBox();
    count_spinbox->setRange(3, 16);
    count_spinbox->setToolTip("from 3 to 16");
    count_spinbox->setValue(3);
    connect(count_spinbox, SIGNAL(valueChanged(int)), this, SLOT(onCountChanged(int)));
    count_slider = new QSlider(Qt::Horizontal);
    count_slider->setRange(3, 16);
    count_slider->setToolTip("from 3 to 16");
    count_slider->setValue(3);
    connect(count_slider, SIGNAL(valueChanged(int)), this, SLOT(onCountChanged(int)));

    radius_label = new QLabel("radius:");
    radius_spinbox = new QSpinBox();
    radius_spinbox->setRange(0, static_cast<int>(sqrt(width*width + height*height)));
    radius_spinbox->setToolTip("from 0 to " + QString::number(static_cast<int>(sqrt(width*width + height*height))));
    radius_spinbox->setValue(50);
    connect(radius_spinbox, SIGNAL(valueChanged(int)), this, SLOT(onRadiusChanged(int)));
    radius_slider = new QSlider(Qt::Horizontal);
    radius_slider->setRange(0, static_cast<int>(sqrt(width*width + height*height)));
    radius_slider->setToolTip("from 0 to " + QString::number(static_cast<int>(sqrt(width*width + height*height))));
    radius_slider->setValue(50);
    connect(radius_slider, SIGNAL(valueChanged(int)), this, SLOT(onRadiusChanged(int)));

    rotation_label = new QLabel("rotation:");
    rotation_spinbox = new QSpinBox();
    rotation_spinbox->setRange(0, 360);
    rotation_spinbox->setToolTip("from 0 to 360");
    rotation_spinbox->setValue(0);
    connect(rotation_spinbox, SIGNAL(valueChanged(int)), this, SLOT(onRotationChanged(int)));
    rotation_slider = new QSlider(Qt::Horizontal);
    rotation_slider->setRange(0, 360);
    rotation_slider->setToolTip("from 0 to 360");
    rotation_slider->setValue(0);
    connect(rotation_slider, SIGNAL(valueChanged(int)), this, SLOT(onRotationChanged(int)));

    type_combo_box = new QComboBox();
    type_combo_box->setToolTip("choose type of figure");
    type_combo_box->addItem("polygon");
    type_combo_box->addItem("star");
    type_combo_box->setCurrentIndex(0);
    type_combo_box->setEditable(false);
    connect(type_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onTypeChanged(int)));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(onAccept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(onReject()));

    panel_layout->addWidget(renderArea);

    settings_layout->addWidget(count_slider);
    count_layout->addWidget(count_label);
    count_layout->addWidget(count_spinbox);
    settings_layout->addLayout(count_layout);

    settings_layout->addWidget(radius_slider);
    radius_layout->addWidget(radius_label);
    radius_layout->addWidget(radius_spinbox);
    settings_layout->addLayout(radius_layout);

    settings_layout->addWidget(rotation_slider);
    rotation_layout->addWidget(rotation_label);
    rotation_layout->addWidget(rotation_spinbox);
    settings_layout->addLayout(rotation_layout);

    settings_layout->addWidget(type_combo_box);

    panel_layout->addLayout(settings_layout);

    m_layout->addLayout(panel_layout);
    m_layout->addWidget(buttonBox);

    setLayout(m_layout);


}
void InsertWindow::onRadiusChanged(int newRadius)
{
    if (radius_spinbox->value() != newRadius)
        radius_spinbox->setValue(newRadius);
    if (radius_slider->value() != newRadius)
        radius_slider->setValue(newRadius);
}
void InsertWindow::onRotationChanged(int newAngle)
{
    if (rotation_spinbox->value() != newAngle)
        rotation_spinbox->setValue(newAngle);
    if (rotation_slider->value() != newAngle)
        rotation_slider->setValue(newAngle);
    updateRender();
}
void InsertWindow::onCountChanged(int newCount)
{
    if (count_spinbox->value() != newCount)
        count_spinbox->setValue(newCount);
    if (count_slider->value() != newCount)
        count_slider->setValue(newCount);
    updateRender();
}
void InsertWindow::onTypeChanged(int newIndex)
{
    updateRender();
}
void InsertWindow::onAccept()
{
    QTransform rotation = QTransform().rotate(-rotation_spinbox->value());
    offset = rotation.map(QPoint(0, -radius_spinbox->value()));
    emit insertFigure(offset, count_spinbox->value(),
        static_cast<enum FigureTypes>(type_combo_box->currentIndex()));
    close();
}
void InsertWindow::onReject()
{
    close();
}

void InsertWindow::updateRender()
{
    QTransform rotation = QTransform().rotate(-rotation_spinbox->value());
    offset = rotation.map(QPoint(0, -50));

    if (type_combo_box->currentIndex() == FigureTypes::FigureTypes_POLYGON) {
        renderArea->drawPolygon(center, center + offset, count_spinbox->value());
    }
    else {
        renderArea->drawStar(center, center + offset, count_spinbox->value());
    }
}