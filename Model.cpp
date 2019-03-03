#include "Model.h"

namespace
{
    void GetMiniature(const QFileInfo& file, QPixmap& image, bool& isPlayable)
    {
        QString fileSuffix = file.suffix();
        isPlayable = true;

        if (fileSuffix == "jpeg" || fileSuffix == "jpg")
        {
            image.load(file.filePath());
        }
        else if (fileSuffix == "avi")
        {
            image.load("C:\\Users\\potapov.alexander\\Documents\\SleeQtFinalTask\\video.jpg");
        }
        else
        {
            image.load("C:\\Users\\potapov.alexander\\Documents\\SleeQtFinalTask\\file.jpeg");
            isPlayable = false;
        }
    }
}

void MyListModel::Load(const QList<FileData> &files)
{
    for(const FileData& file: files)
    {
        m_files.append(file);
    }
}

void MyListModel::ObtainFiles(QList<FileData> &files) const
{
    files = m_files;
}

QVariant MyListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    const FileData fileData = m_files[index.row()];
    switch (role)
    {
    case HeaderRole:
        return fileData.header;
    case PreviewRole:
        return fileData.preview;
    case FilePathRole:
        return fileData.filePath;
    case CreationDateRole:
        return fileData.creationDate;
    case IsPlayableRole:
        return fileData.isPlayable;
    default:
        return QVariant();
    }
}

bool MyListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }
    if (role == Qt::EditRole)
    {
        if(value.toString().isEmpty())
        {
           QString fileName =  QFileInfo (m_files[index.row()].filePath).fileName();
           m_files[index.row()].header = fileName;
        }
        else
        {
            m_files[index.row()].header = value.toString();
        }
    }
    return true;
}

Qt::ItemFlags MyListModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable ;
}

int MyListModel::rowCount(const QModelIndex &) const
{
    return m_files.size();
}

void MyListModel::AddFile(const QFileInfo &fileInf, const QString& haeder)
{
    QPixmap preview;
    bool isPlayable = false;
    GetMiniature(fileInf, preview, isPlayable);

    FileData file{haeder.isEmpty()? fileInf.fileName() : haeder
                , preview
                , fileInf.filePath()
                , fileInf.birthTime().date()
                , isPlayable
                 };

    m_files.append(file);

    emit dataChanged(QModelIndex(), QModelIndex());
}

void MyListModel::DelFile(QModelIndex &index)
{
    m_files.removeAt(index.row());
}
