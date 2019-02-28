#include "MainWindow.h"


MainWindow::MainWindow(QWidget *pwgt):
    QMainWindow(pwgt)
  , m_model(new MyListModel)
{
    SetGui();
    setAcceptDrops(true);
    LoadData();

    MyListView* view = m_ui.listView;
    view->setModel(m_model);
}

MainWindow::~MainWindow()
{
    SaveData();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    foreach( QUrl url, urls)
    {
        QString filePath = url.toString();
        filePath = filePath.right(filePath.length() - 8); //delete "file:///". TODO add checking.
        QFileInfo fileInf (filePath);
        if (fileInf.isFile())
        {
            m_model->addFile(fileInf);
        }
    }

}
