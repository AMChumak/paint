#pragma once

#include <QMainWindow>
#include <QToolBar>
#include <QVBoxLayout>
#include "RenderArea.h"

#if defined MAKE_UI_LIB
#define UI_LIB_EXPORT Q_DECL_EXPORT
#else
#define UI_LIB_EXPORT Q_DECL_IMPORT
#endif

class UI_LIB_EXPORT MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);



private slots:
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void newFile();
    void open();
    void save();
    void undo();
    void redo();
    void clean();
    void resize();
    void setPen();
    void insert();
    void line();
    void fill();
    void insert4Polygon();
    void insert5Polygon();
    void insert6Polygon();
    void insert7Polygon();
    void insert8Polygon();
    void insert4Star();
    void insert5Star();
    void insert6Star();
    void insert7Star();
    void insert8Star();
    void setKcolor();
    void setRcolor();
    void setRGcolor();
    void setGcolor();
    void setGBcolor();
    void setBcolor();
    void setBRcolor();
    void setWcolor();
    void about();

    void onCanvasPressed(const QPoint &point);
    void onMouseMovedOverCanvas(const QPoint &point);

private:
    void createActions();
    void createMenus();
    void createToolBar();

private:
    enum Mode { MODE_LINE = 1, MODE_FILL = 2, MODE_POLYGON = 3, MODE_STAR = 4 };

private:
    QWidget *window;
    QVBoxLayout *m_layout;
    QMenu *fileMenu{};
    QMenu *editMenu{};
    QMenu *aboutMenu{};
    QAction *newFileAct{};
    QAction *openAct{};
    QAction *saveAct{};
    QAction *undoAct{};
    QAction *redoAct{};
    QAction *cleanAct{};
    QAction *resizeAct{};
    QAction *setPenAct{};
    QAction *insertAct{};
    QAction *lineAct{};
    QAction *fillAct{};
    QAction *insert4PolygonAct{};
    QAction *insert5PolygonAct{};
    QAction *insert6PolygonAct{};
    QAction *insert7PolygonAct{};
    QAction *insert8PolygonAct{};
    QAction *insert4StarAct{};
    QAction *insert5StarAct{};
    QAction *insert6StarAct{};
    QAction *insert7StarAct{};
    QAction *insert8StarAct{};
    QAction *setKcolorAct{};
    QAction *setRcolorAct{};
    QAction *setRGcolorAct{};
    QAction *setGcolorAct{};
    QAction *setGBcolorAct{};
    QAction *setBcolorAct{};
    QAction *setBRcolorAct{};
    QAction *setWcolorAct{};
    QAction *aboutAct{};
    QActionGroup *colorsGroup;
    QActionGroup *toolGroup;
    QToolBar *mainToolBar{};
    QScrollArea *scrollArea{};
    RenderArea *renderArea{};
    int clickCount = 0;
    enum Mode currentMode = MODE_LINE;
    int currentVerticesCount = 0;
};
