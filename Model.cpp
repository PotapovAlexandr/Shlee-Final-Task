#include "Model.h"


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
        m_files[index.row()].header = value.toString();
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

void MyListModel::addFile(const QFileInfo &fileInf)
{
    QString header = fileInf.fileName();
    QPixmap preview;
    bool isPlayable = false;
    GetMiniature(fileInf, preview, isPlayable);
    QDate creationDate = fileInf.birthTime().date();

    FileData file{header
                , preview
                , fileInf.filePath()
                , creationDate
                , isPlayable
                 };

    m_files.append(file);


    emit dataChanged(QModelIndex(), QModelIndex());
}
