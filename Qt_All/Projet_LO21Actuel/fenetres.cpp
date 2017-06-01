#include "fenetres.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QDockWidget>
#include <QListWidget>
#include <QWidget>
#include <QListView>


Principale::Principale()
{
    zoneCentrale = new QWidget; //on crée un widget zone centrale

    ID = new QLineEdit;      //création des widgets a remplir
    titre = new QLineEdit;
    texte = new QTextEdit;

    layout = new QFormLayout;          //layout de forme qui va être mis en zone centrale
    layout->addRow("ID de la note", ID);
    layout->addRow("Titre de la note", titre);
    layout->addRow("Texte", texte);

    zoneCentrale->setLayout(layout);

    setCentralWidget(zoneCentrale);
    //Barre de menus avec les diverses options
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");        //création de la barre de menu
    QMenu *menuEdition = menuBar()->addMenu("&Edition");
  //  QMenu *menuAffichage = menuBar()->addMenu("&Affichage");

    QAction *actionQuitter = new QAction("&Quitter", this);
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
        connect(actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
        menuFichier->addAction(actionQuitter);

        QAction *actionNouveau = new QAction("Ajouter Note",this);
            actionNouveau->setShortcut(QKeySequence("Ctrl+N"));
            connect(actionNouveau,SIGNAL(triggered()),this,SLOT(ouverture_fen_edition()));
            menuFichier->addAction(actionNouveau);

        QAction *actionEnregistrer = new QAction("&Enregistrer", this);
        actionEnregistrer->setShortcut(QKeySequence("Ctrl+S"));
        // connect(actionEnregistrer, SIGNAL(triggered()), qApp, SLOT(save()));
            menuFichier->addAction(actionEnregistrer);
//Plus nécessaire si on regroupe tout sous édition
      QAction *actionTache = new QAction("&Tâche", this);
        actionTache->setShortcut(QKeySequence("Ctrl+T"));
        connect(actionTache,SIGNAL(triggered()),this,SLOT(ouverture_edition_tache()));
        menuEdition->addAction(actionTache);

        QAction *actionImage = new QAction("&Image", this);
          actionImage->setShortcut(QKeySequence("Ctrl+I"));
          connect(actionImage,SIGNAL(triggered()),this,SLOT(ouverture_edition_image()));
          menuEdition->addAction(actionImage);

          QAction *actionAudio = new QAction("&Audio", this);
            actionAudio->setShortcut(QKeySequence("Ctrl+A"));
            connect(actionAudio,SIGNAL(triggered()),this,SLOT(ouverture_edition_audio()));
            menuEdition->addAction(actionAudio);

            QAction *actionVideo = new QAction("&Vidéo", this);
              actionVideo->setShortcut(QKeySequence("Ctrl+V"));
              connect(actionVideo,SIGNAL(triggered()),this,SLOT(ouverture_edition_video()));
              menuEdition->addAction(actionVideo);

              QAction *actionArticle = new QAction("&Article", this);
                actionArticle->setShortcut(QKeySequence("Ctrl+R"));
                connect(actionArticle,SIGNAL(triggered()),this,SLOT(ouverture_edition_article()));
                menuEdition->addAction(actionArticle);
// Plus utile puisque les Notes actives seront désormais dans une arbo

// Creation Docks
            creation_docks_Arbo();

// Arborescence


                /*QAction *actionNotesActives = new QAction("&Arborescence", this);
                        actionNotesActives->setShortcut(QKeySequence("Ctrl+A"));
                        connect(actionNotesActives,SIGNAL(triggered()),this,SLOT(view.show()));
                            menuAffichage->addAction(actionNotesActives);*/
}

void Principale:: ouverture_fen_edition() { // Méthode qui appelle l'ouverture d'une fenetre dédié aux Notes
    nouvelle = new fen_Note;
    //connect(nouvelle,SIGNAL(destroyed(QObject*)),this,SLOT(affichage_notes())); //on connecte la destruction de la fenetre de creation à l'affichage des notes
    nouvelle->show();
}
void Principale:: ouverture_edition_image() { // creer une classe pour une fenêtre spéciale d'édition

     QString type = "img";
  NoteEditeur* tmp= NoteEditeur::chooseEditeur(NULL, type);

}
void Principale:: ouverture_edition_tache() { // creer une classe pour une fenêtre spéciale d'édition

    QString type = "task";
 NoteEditeur* tmp= NoteEditeur::chooseEditeur(NULL, type);

}
void Principale:: ouverture_edition_audio() { // creer une classe pour une fenêtre spéciale d'édition

     QString type = "aud";
  NoteEditeur* tmp= NoteEditeur::chooseEditeur(NULL, type);

}
void Principale:: ouverture_edition_video() { // creer une classe pour une fenêtre spéciale d'édition

     QString type = "vid";
  NoteEditeur* tmp= NoteEditeur::chooseEditeur(NULL, type);

}
void Principale:: ouverture_edition_article() { // creer une classe pour une fenêtre spéciale d'édition

     QString type = "art";
  NoteEditeur* tmp= NoteEditeur::chooseEditeur(NULL, type);

}
//1 er Dock
void Principale::creation_docks_Arbo(){

    dock_affichage_arborescence = new QDockWidget(tr("Notes"), this);
         dock_affichage_arborescence->setAllowedAreas(Qt::LeftDockWidgetArea |
                                     Qt::RightDockWidgetArea);
        liste_Notes = new QListWidget(dock_affichage_arborescence);
         dock_affichage_arborescence->setWidget(liste_Notes);
         addDockWidget(Qt::LeftDockWidgetArea, dock_affichage_arborescence);
}

  //2nd Dock: Edition Article
void Principale::creation_docks_Edition_Article(){

                 dock_affichage_Article = new QDockWidget(tr("Edition Article"), this);
                      dock_affichage_Article->setAllowedAreas(Qt::LeftDockWidgetArea |
                                                  Qt::RightDockWidgetArea);
                     liste_Article = new QListWidget(dock_affichage_Article);
                      dock_affichage_Article->setWidget(liste_Notes);
                      addDockWidget(Qt::RightDockWidgetArea, dock_affichage_Article);



}

/*void Principale::quit(){   //Acompléter avec la fonction save qui permet d'enregistrer tout le contenu
    save();
}
*/

fen_Note::fen_Note(){

    this->setWindowModality(Qt::ApplicationModal); //pour que la fenetre parente ne soit pas utilisable quand celle ci est ouverte
    choix_layout = new QVBoxLayout; //création layout
    //Création des différents champs du formulaire
    idl = new QLineEdit("Entre l'id ",this);
    titrel = new QLineEdit("Titre ",this);
    date_creation = date_modification = QDateTime();
    date_creation = date_modification = QDateTime::currentDateTime();
    label_date_creat = new QLabel("Date de création : " + date_creation.toString("dddd dd MMMM yyyy"),this);
    label_date_modif = new QLabel("Date de dernière modif : " + date_modification.toString("dddd dd MMMM yyyy"),this);
    m_texte = new QTextEdit("texte/description/action ici",this);


    m_article = new QRadioButton("Article",this);   //Bouton spécial de sélection
        m_article->toggle();
    m_tache = new QRadioButton("Tache",this);
        m_groupe_tache = new QWidget(this);
        m_layout_tache = new QVBoxLayout;
        m_groupe_tache->setLayout(m_layout_tache);
        m_groupe_tache->setVisible(false);
        m_tache->connect(m_tache,SIGNAL(toggled(bool)),m_groupe_tache,SLOT(setVisible(bool)));

        QLabel* label_spinbox = new QLabel("Priorité, 0 si aucune priorité",this);
        m_priorite = new QSpinBox(this);
        m_case_calendrier = new QCheckBox("Echeance",this);
            m_calendrier = new QCalendarWidget(this);
            m_calendrier->setVisible(false);
            m_case_calendrier->connect(m_case_calendrier,SIGNAL(toggled(bool)),m_calendrier,SLOT(setVisible(bool)));

    m_media = new QRadioButton("Media",this);
        m_selection_fichier = new QPushButton("Parcourir...",this);
            m_selection_fichier->setVisible(false);
            m_selection_fichier->connect(m_selection_fichier,SIGNAL(clicked(bool)),this,SLOT(choisir_fichier()));
        m_media->connect(m_media,SIGNAL(toggled(bool)),m_selection_fichier,SLOT(setVisible(bool)));

    m_save = new QPushButton("Sauvegarder",this);
        m_save->connect(m_save,SIGNAL(clicked(bool)),this,SLOT(save()));
    m_quit = new QPushButton("Annuler",this);
        m_quit->connect(m_quit,SIGNAL(clicked(bool)),this,SLOT(close()));

    //Ajout des objets au layout
    choix_layout->addWidget(idl);
    choix_layout->addWidget(titrel);
    choix_layout->addWidget(label_date_creat);
    choix_layout->addWidget(label_date_modif);
    choix_layout->addWidget(m_article);
    choix_layout->addWidget(m_tache);
    choix_layout->addWidget(m_media);
    choix_layout->addWidget(m_texte);
    choix_layout->addWidget(m_selection_fichier);

    m_layout_tache->addWidget(label_spinbox);
    m_layout_tache->addWidget(m_priorite);
    m_layout_tache->addWidget(m_case_calendrier);
    m_layout_tache->addWidget(m_calendrier);

    choix_layout->addWidget(m_groupe_tache);
    choix_layout->addWidget(m_save);
    choix_layout->addWidget(m_quit);


    this->setLayout(choix_layout); //affectation du layout
    this->move(100,100); //décalage de la nouvelle fenetre par rapport à la première

}

// Arborescence
//TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent) //Enregistre l'item père et l'information pour chaque colonne
//{
//    m_parentItem = parent;
//    m_itemData = data;
//}

//TreeItem::~TreeItem() //On a un pointeur sur les enfants dans childItems (vector), il faut tous les détruire quand on fait appel au destructeur de la classe
//{
//    qDeleteAll(m_childItems);
//}
//void TreeItem::appendChild(TreeItem *item) // Fonction pour ajouter des items fils
//{
//    m_childItems.append(item); //append = ajouter
//}
//TreeItem *TreeItem::child(int row) //Retourne le fils qui correspond au row number dans la liste des fils items
//{
//    return m_childItems.value(row);
//}
//int TreeItem::childCount() const //Renvoie le nombre d'items fils
//{
//    return m_childItems.count();
//}
//int TreeItem::row() const //Détermine le nombre de row qu'il y a pour un objet parent. Retourn la localisation de l'item
//{
//    if (m_parentItem)
//        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

//    return 0;
//}
//int TreeItem::columnCount() const // Retourne le nombre de colonne de données
//{
//    return m_itemData.count();
//}
//QVariant TreeItem::data(int column) const //Retourne l'objet QVariant correspondant a la colonne de donnée
//{
//    return m_itemData.value(column);
//}

//TreeItem *TreeItem::parentItem() //Retourne le parent. O si on l'utilise depuis la racine
//{
//    return m_parentItem;
//}
//// Methodes de la classe TreeModel

//TreeModel::TreeModel(const QString &data, QObject *parent)
//    : QAbstractItemModel(parent)
//{
//    QList<QVariant> rootData;
//    rootData << "Title" << "Summary";
//    rootItem = new TreeItem(rootData);
//    setupModelData(data.split(QString("\n")), rootItem); //SetupModelData va parser un fichier text
//}
//TreeModel::~TreeModel()
//{
//    delete rootItem;
//}
//QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
//            const
//{
//    if (!hasIndex(row, column, parent))
//        return QModelIndex();

//    TreeItem *parentItem;

//    if (!parent.isValid())
//        parentItem = rootItem;
//    else
//        parentItem = static_cast<TreeItem*>(parent.internalPointer());

//    TreeItem *childItem = parentItem->child(row);
//    if (childItem)
//        return createIndex(row, column, childItem);
//    else
//        return QModelIndex();
//}
//QModelIndex TreeModel::parent(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return QModelIndex();

//    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
//    TreeItem *parentItem = childItem->parentItem();

//    if (parentItem == rootItem)
//        return QModelIndex();

//    return createIndex(parentItem->row(), 0, parentItem);
//}
//int TreeModel::rowCount(const QModelIndex &parent) const
//{
//    TreeItem *parentItem;
//    if (parent.column() > 0)
//        return 0;

//    if (!parent.isValid())
//        parentItem = rootItem;
//    else
//        parentItem = static_cast<TreeItem*>(parent.internalPointer());

//    return parentItem->childCount();
//}
//int TreeModel::columnCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
//    else
//        return rootItem->columnCount();
//}
//QVariant TreeModel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    if (role != Qt::DisplayRole)
//        return QVariant();

//    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

//    return item->data(index.column());
//}
//Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const //sert pour dire que le modele est en lecture seulement
//{
//    if (!index.isValid())
//        return 0;

//    return QAbstractItemModel::flags(index);
//}
//QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
//                               int role) const
//{
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//        return rootItem->data(section);

//    return QVariant();
//}
//void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
//{
//    QList<TreeItem*> parents;
//    QList<int> indentations;
//    parents << parent;
//    indentations << 0;

//    int number = 0;

//    while (number < lines.count()) {
//        int position = 0;
//        while (position < lines[number].length()) {
//            if (lines[number].at(position) != ' ')
//                break;
//            position++;
//        }

//        QString lineData = lines[number].mid(position).trimmed();

//        if (!lineData.isEmpty()) {
//            // Read the column data from the rest of the line.
//            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
//            QList<QVariant> columnData;
//            for (int column = 0; column < columnStrings.count(); ++column)
//                columnData << columnStrings[column];

//            if (position > indentations.last()) {
//                // The last child of the current parent is now the new parent
//                // unless the current parent has no children.

//                if (parents.last()->childCount() > 0) {
//                    parents << parents.last()->child(parents.last()->childCount()-1);
//                    indentations << position;
//                }
//            } else {
//                while (position < indentations.last() && parents.count() > 0) {
//                    parents.pop_back();
//                    indentations.pop_back();
//                }
//            }

//            // Append a new item to the current parent's list of children.
//            parents.last()->appendChild(new TreeItem(columnData, parents.last()));
//        }

//        ++number;
//    }
//}
