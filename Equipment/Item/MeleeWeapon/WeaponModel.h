#ifndef WEAPONMODEL_H
#define WEAPONMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class MeleeWeapon;
class EquipmentDb;

class WeaponModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum WeaponRoles {
        NameRole = Qt::UserRole + 1,
        SpeedRole,
        DpsRole,
        PatchRole,
        SourceRole,
        TypeRole,
        ReqLvlRole,
        ItemLvlRole,
        QualityRole,
        IconRole
    };

    WeaponModel(EquipmentDb*, QObject *parent = 0);

    Q_INVOKABLE void setPatch(const QString &patch);
    void addWeapons(const EquipmentDb *db);
    void addWeapon(MeleeWeapon *weapon);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    EquipmentDb* db;
    QList<MeleeWeapon*> melee_weapons;
};

#endif // WEAPONMODEL_H