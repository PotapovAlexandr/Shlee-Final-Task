#pragma once

#include <QtWidgets>
#include <QStringList>
#include <QFileInfo>

#include "ui_m_form.h"
#include "Model.h"
#include "MyListView.h"

class MyProxiModel;

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* pwgt = nullptr);
    ~MainWindow();

protected:
    virtual void dragEnterEvent(QDragEnterEvent* event);
    virtual void dropEvent(QDropEvent* event);
    virtual void keyPressEvent(QKeyEvent *event);

public slots:

private:
    void SetGui();
    void LoadData(MyListModel* model);
    void SaveData(MyListModel* model);

private:
    Ui_MainWindow m_ui;
    MyProxiModel* m_proxiModel;
};


