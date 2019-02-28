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
    MainWindow(QWidget* pwgt = nullptr):
        QMainWindow(pwgt)
      , m_model(new MyListModel)
    {
        SetGui();
        setAcceptDrops(true);

        LoadData();

        MyListView* view = m_ui.listView;

        view->setModel(m_model);


    }
    ~MainWindow()
    {
        SaveData();
    }

protected:
    virtual void dragEnterEvent(QDragEnterEvent* event)
    {
        if(event->mimeData()->hasUrls())
        {
            event->acceptProposedAction();
        }
    }
    virtual void dropEvent(QDropEvent* event)
    {
        QList<QUrl> urls = event->mimeData()->urls();
        foreach( QUrl url, urls)
        {
            QString filePath = url.toString();
            filePath = filePath.right(filePath.length() - 8);
            QFileInfo fileInf (filePath);
            if (fileInf.isFile())
            {
                m_model->addFile(fileInf);
            }
        }

    }

public slots:

private:
    void SetGui()
    {
        m_ui.setupUi(this);
    }

    void LoadData()
    {

    }

    void SaveData()
    {

    }


private:
    Ui_MainWindow m_ui;
    MyListModel* m_model;
};


