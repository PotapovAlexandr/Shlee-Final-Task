#pragma once
#include <QtWidgets>
#include <QAbstractListModel>




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


struct FileData
{
    QString header;
    QPixmap preview;
    QString filePath;
    QDate creationDate;
    bool isPlayable;
};

enum FileDataRoles
{
    HeaderRole = Qt::DisplayRole,
    PreviewRole = Qt::UserRole + 1,
    FilePathRole = Qt::UserRole + 2,
    CreationDateRole = Qt::UserRole + 3,
    IsPlayableRole = Qt::UserRole + 4
};

class MyListModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MyListModel(QObject *parent = nullptr): QAbstractListModel(parent)
    {}

    void Load(const QList<FileData>& files)
    {
        for(const FileData& file: files)
        {
            m_files.append(file);
        }
    }

    void ObtainFiles(QList<FileData>& files) const
    {
        files = m_files;
    }


    QVariant data(const QModelIndex &index, int role) const
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

        default:
            return QVariant();

        }
    }

    bool setData(const QModelIndex& index, const QVariant& value, int role)
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

    Qt::ItemFlags flags(const QModelIndex& index) const
    {
        if(!index.isValid())
        {
            return Qt::NoItemFlags;
        }
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable ;
    }

    int rowCount(const QModelIndex& /*parent*/) const
    {
        return m_files.size();
    }

public slots:
    void addFile(const QFileInfo& fileInf)
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

private:
    QList<FileData> m_files;
};



