#pragma once

#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialogButtonBox>

class ResizeWindow : public QWidget
{
    Q_OBJECT

public:
    ResizeWindow(QWidget *parent = nullptr, const QSize &currentSize = QSize{1, 1});

signals:
    void getNewSize(const QSize &size);

private slots:
    void onOKClicked();
    void onCancelClicked();

private:
    QVBoxLayout *m_layout;
    QGridLayout *grid;
    QLabel *v_size_lbl;
    QLabel *h_size_lbl;
    QSpinBox *v_size_spinbox;
    QSpinBox *h_size_spinbox;
    QDialogButtonBox *buttonBox;
};