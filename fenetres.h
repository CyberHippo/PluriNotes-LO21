#ifndef FENETRES_H
#define FENETRES_H

#include <QtWidgets>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDockWidget>
#include <QListView>
#include "noteediteur.h"
class Principale : public QMainWindow
{
    Q_OBJECT
    friend NoteEditeur;
    public:

    Principale();

public slots:
    //Fonction qui appelle l'ouverture à d'autres fenetres
   // void ouverture_NotesActives(); //Plus utile, car on utilise l'arbo
    void ouverture_edition_image(); //ouverture d'une fenêtre de modification
    void ouverture_edition_video();
    void ouverture_edition_audio();
    void ouverture_edition_article();
    void ouverture_edition_tache();
    void ouverture_fen_edition();



//void save() const;
    //void ouverture();

private:
   void creation_docks_Arbo();
   void creation_docks_Edition_Article();


QWidget *zoneCentrale; // Création du Widget contrôlant la zone centrale
QLineEdit *titre;
QLineEdit *ID;
QTextEdit *texte;
//Dock Affichage Arbo
QDockWidget *dock_affichage_arborescence;
//Dock Edition Article
QDockWidget *dock_affichage_Article;
QWidget *liste_Article;

QListWidget *liste_Notes;
QWidget * lN;
QListView *m_treeView;
 QFormLayout *layout; //Layout

 QWidget *nouvelle; // Utiliser dans la fonction ouverture
 QWidget *liste_note;
};

class fen_Note : public QWidget
{
    Q_OBJECT
    friend Principale;
public:
    fen_Note();
public slots:
    //void choisir_fichier();
  //  void save();

protected:

    QVBoxLayout* choix_layout;
    QLineEdit* idl;
    QLineEdit* titrel;
    QDateTime date_creation, date_modification;
    QLabel *label_date_creat, *label_date_modif;
    QRadioButton *m_article, *m_tache, *m_media;
    QTextEdit* m_texte;

    ///objets qui peuvent être affichés ou non selon la case cochée
    QPushButton* m_selection_fichier;
    QString* m_fichier;
    QSpinBox* m_priorite;

    QVBoxLayout* m_layout_tache;
    QWidget* m_groupe_tache;
    QCalendarWidget* m_calendrier;
        QCheckBox* m_case_calendrier;

    //Boutons de fin
    QPushButton* m_save;
    QPushButton* m_quit;

};

// Classe pour l'arborescence.
// La structure que l'on veut utiliser est une forme d'arborescence, avec des objets TreeItem.
// Chaque TreeItem represent un item dans l'arborescence, et contient plusieurs colonnes de données
// La donnée est conservée dans le model, pour chaque objet.
// La donnée sera l'id, le titre.
// Pour le stockage, on utilisera une liste d'objets Qvariant qui stockera l'information
// QVariant permet une union de données de types différents (ici, id en integer et titre en string)
// Les objets sont liés entre eux par un tableau vector contenant un pointeur sur les items
// Chaque objet TreeItem à un parent, et plusieurs enfant.
// Seul la racine (root) n'a pas de parent et n'est pas référencé.
// Chaque objet TreeItem contient de l'information sur sa position dans l'arborescence. Il renvoie son père ainsi que son row number

// Cette classe est utilisé pour conserver
//class TreeItem
//{
//public:
//    explicit TreeItem(const QList<QVariant> &data, TreeItem *parentItem = 0);
//    ~TreeItem();

//    void appendChild(TreeItem *child);

//    TreeItem *child(int row);
//    int childCount() const;
//    int columnCount() const;
//    QVariant data(int column) const;
//    int row() const;
//    TreeItem *parentItem();

//private:
//    QList<TreeItem*> m_childItems;
//    QList<QVariant> m_itemData;
//    TreeItem *m_parentItem;
//};

//// Classe de l'arborescence
//class TreeModel : public QAbstractItemModel
//{
//    Q_OBJECT

//public:
//    explicit TreeModel(const QString &data, QObject *parent = 0);
//    ~TreeModel();

//    QVariant data(const QModelIndex &index, int role) const override;
//    Qt::ItemFlags flags(const QModelIndex &index) const override;
//    QVariant headerData(int section, Qt::Orientation orientation,
//                        int role = Qt::DisplayRole) const override;
//    QModelIndex index(int row, int column,
//                      const QModelIndex &parent = QModelIndex()) const override;
//    QModelIndex parent(const QModelIndex &index) const override;
//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

//private:
//    void setupModelData(const QStringList &lines, TreeItem *parent);

//    TreeItem *rootItem;
//};
#endif // FENETRES_H
