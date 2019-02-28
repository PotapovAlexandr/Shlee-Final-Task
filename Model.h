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
    void Load(const QList<FileData>& files);
    void ObtainFiles(QList<FileData>& files) const;

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual int rowCount(const QModelIndex& /*parent*/) const override;

public slots:
    void addFile(const QFileInfo& fileInf);

private:
    QList<FileData> m_files;
};



