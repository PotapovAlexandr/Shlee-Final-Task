#pragma once
#include <QtWidgets>
#include <QAbstractListModel>

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
    IsPlayableRole = Qt::UserRole + 4,
    IsSelectedRole = Qt::UserRole + 5
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

    void AddFile(const QFileInfo& fileInf, const QString& haeder = "");
    void DelFile(QModelIndex& index);

private:
    QList<FileData> m_files;
};



