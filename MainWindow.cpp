#include "MainWindow.h"
#include "MyProxiModel.h"


MainWindow::MainWindow(QWidget *pwgt):
    QMainWindow(pwgt)
  , m_proxiModel(new MyProxiModel(this))
{
    SetGui();
    setAcceptDrops(true);

    MyListModel* model = new MyListModel(this);

    LoadData(model);

    m_proxiModel->setSourceModel(model);
    MyListView* view = m_ui.listView;
    view->setModel(m_proxiModel);
    //view->setSelectionModel();

    m_proxiModel->setSortRole(HeaderRole);

}

MainWindow::~MainWindow()
{
    SaveData(dynamic_cast<MyListModel*>(m_proxiModel->sourceModel()));
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
            MyListModel* model = dynamic_cast<MyListModel*>(m_proxiModel->sourceModel());
            model->AddFile(fileInf);
        }
    }
    m_proxiModel->invalidate();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->matches(QKeySequence::Delete))
    {
        MyListModel* model = dynamic_cast<MyListModel*>(m_proxiModel->sourceModel());
        QModelIndexList indexList = m_ui.listView->SelectedIndexesList();
        for (QModelIndex& index : indexList )
        {
            model->DelFile(index);
        }
        m_proxiModel->invalidate();
    }
    else
    {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::SetGui()
{
    m_ui.setupUi(this);
}

void MainWindow::LoadData(MyListModel* model)
{
    if(model == nullptr)
    {
        return;
    }

    QFile fileDb("db");
    if(!fileDb.open(QIODevice::ReadOnly))
    {
        return;
    }
    QString header;
    QString path;
    QTextStream in(&fileDb);
    while(!in.atEnd())
    {
        header = in.readLine();
        path = in.readLine();
        QFileInfo fileInf(path);
        model->AddFile(fileInf, header);
    }
    fileDb.close();
}

void MainWindow::SaveData(MyListModel* model)
{
    if(model == nullptr)
    {
        return;
    }

    QList<FileData> files;
    model->ObtainFiles(files);

    QFile fileDb("db");
    if(!fileDb.open(QIODevice::WriteOnly))
    {
        return;
    }
    QTextStream out(&fileDb);

    for(const FileData& file : files)
    {
        out << file.header << "\n";
        out << file.filePath << "\n";
    }
    fileDb.close();
}
