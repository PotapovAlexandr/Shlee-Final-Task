#pragma once

#include <QtWidgets>
#include <QStringList>
#include <QFileInfo>

#include "ui_m_form.h"
#include "Model.h"
#include "MyListView.h"


class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* pwgt = nullptr);
    ~MainWindow();

protected:
    virtual void dragEnterEvent(QDragEnterEvent* event);
    virtual void dropEvent(QDropEvent* event);

public slots:

private:
    void SetGui()
    {
        m_ui.setupUi(this);
    }
    void LoadData()
    {}
    void SaveData()
    {}

private:
    Ui_MainWindow m_ui;
    MyListModel* m_model;
};


