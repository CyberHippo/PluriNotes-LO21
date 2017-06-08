#include "noteediteur.h"
#include <QMessageBox>
#include <QObject>
#include <QItemSelectionModel>
#include "corbeille.h"
#include "mainwindow.h"

NoteEditeur::NoteEditeur(Note* n, QWidget* parent)
{
    idLabel= new QLabel("Identificateur", this);
    titleLabel = new  QLabel("Titre", this);
    versionLabel = new QLabel("Numero Version", this);
    dcLabel = new QLabel("Date de création :", this);
    dmLabel = new QLabel("Dernière Modification :", this);

    id = new QLineEdit(this);
    title = new QLineEdit(this);
    version = new QLineEdit(this);
    date_creation = new QDateEdit(this);
    date_modif =  new QDateEdit(this);


    save = new QPushButton("Sauver",this);
    oldVersions = new QPushButton("Anciennes Versions",this);
    supp = new QPushButton("Mettre à la corbeille",this);
    close = new QPushButton("Fermer Editeur", this);

    idLayout = new QHBoxLayout;
    titleLayout = new QHBoxLayout;
    versionLayout = new QHBoxLayout;
    datesLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;


    layer = new QVBoxLayout;

    idLayout->addWidget(idLabel);
    idLayout->addWidget(id);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(title);
    versionLayout->addWidget(versionLabel);
    versionLayout->addWidget(version);
    datesLayout->addWidget(dcLabel);
    datesLayout->addWidget(date_creation);
    datesLayout->addWidget(dmLabel);
    datesLayout->addWidget(date_modif);


    buttonLayout->addWidget(save);
    buttonLayout->addWidget(oldVersions);
    buttonLayout->addWidget(supp);
    buttonLayout->addWidget(close);
    buttonLayout->setAlignment(Qt::AlignHCenter);

    //version->setMaximumWidth(100);

    layer->addLayout(idLayout);
    layer->addLayout(titleLayout);
    layer->addLayout(versionLayout);
    layer->addLayout(datesLayout);



    id->setDisabled(true);
    version->setDisabled(true);
    date_creation->setDisabled(true);
    date_modif->setDisabled(true);


}


void NoteEditeur::activerSave() {
    save->setEnabled(true);
    isSaved=false;
}

void NoteEditeur::updateNotesManager(){
    MainWindow::getInstance().updateNotesManager();
}

void NoteEditeur::updateArchivesManager(){
    MainWindow::getInstance().updateArchivesManager();
}

void NoteEditeur::updateTaskManager(){
    MainWindow::getInstance().updateTaskManager();
}

void NoteEditeur::setEmptyCentralWidget(){
    QWidget* empty = new QWidget;
    MainWindow::getInstance().setCentralWidget(empty);
}

ArticleEditeur::ArticleEditeur(Article* a, QWidget* parent) : NoteEditeur(a,parent), article (a) {
    textLabel = new QLabel("Texte", this);
    text = new QTextEdit(this);

    id->setText(QString::number(article->getId().toInt()));
    version->setText(QString::number(article->getNumVersion()));
    date_creation->setDate(article->getDateCreation());
    date_modif->setDate(article->getDateLastModif());
    title->setText(article->getTitle());
    text->setText(article->getText());


    textLayout = new QHBoxLayout;

    textLayout->addWidget(textLabel);
    textLayout->addWidget(text);

    idLayout->addWidget(id);
    titleLayout->addWidget(title);
    textLayout->addWidget(text);

    layer->addLayout(textLayout);

    /*layer->addWidget(save);
    layer->addWidget(supp);
    layer->addWidget(close);*/
    layer->addLayout(buttonLayout);

    setLayout(layer);

    QObject::connect(close, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(close, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveNote()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(updateNotesManager()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(updateTaskManager()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(toDustbin()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateArchivesManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateTaskManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateNotesManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(oldVersions, SIGNAL(clicked()), this, SLOT(showOldVersionsWindow()));
    //QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(updateNote()));
    //QObject::connect(text, SIGNAL(textChanged()), this, SLOT(updateNote()));
    QObject::connect(text, SIGNAL(textChanged()), this, SLOT(activerSave()));
    QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    save->setEnabled(false);

    if(article->getNumVersion() == 0){oldVersions->setEnabled(false);}
}

void ArticleEditeur::saveNote() {
    article->addOldVersion();
    article->incrementNumVersion();
    article->setDateLastMofid();
    article->setTitle(title->text());
    article->setText(text->toPlainText());
    QMessageBox::information(this, "Sauvegarde", "Votre article a bien été sauvé");
    save->setEnabled(false);
    isSaved=true;
}

/*void ArticleEditeur::updateNote() {
    article->setTitle(title->text());
    article->setText(text->toPlainText());
    activerSave();
}*/

void ArticleEditeur::toDustbin(){
    Note* n;
    QMessageBox msgBox;
    if (RelationsManager::getInstance().isReferenced(article) == true){
        msgBox.setText("La note a été archivée car elle est reférencée.");
        msgBox.exec();
        n = NotesManager::getInstance().getNoteWithTitle(article->getTitle());
        ArchivesManager::getInstance().addNote(n);
        NotesManager::getInstance().deleteNote(n->getId());
    }
    else {
        msgBox.setText("La note a bien été ajoutée à la corbeille.");
        msgBox.exec();
        n = NotesManager::getInstance().getNoteWithTitle(article->getTitle());
        Corbeille::getInstance().addNote(n);
        NotesManager::getInstance().deleteNote(n->getId());
    }
}

void ArticleEditeur::readOnly(){
    title->setDisabled(true);
    text->setDisabled(true);
    supp->setDisabled(true);
}

void ArticleEditeur::showOldVersionsWindow(){
    ovw = new OldVersionsWindow(article,this);
    ovw->show();
}



TaskEditeur::TaskEditeur(Task *t, QWidget *parent): NoteEditeur(t,parent), task(t) {
    //setWindowState(Qt::WindowMaximized);

    actionsLabel= new QLabel("Actions", this);
    statusLabel = new QLabel("Statut", this);
    priorityLabel = new QLabel("Priorite", this);
    deadlineLabel = new QLabel("Deadline", this);

    actions = new QTextEdit(this);
    status = new QLineEdit(this);
    priority = new QLineEdit(this);
    deadline = new QDateEdit(this);

    id->setText(task->getId());
    version->setText(QString::number(task->getNumVersion()));
    date_creation->setDate(task->getDateCreation());
    date_modif->setDate(task->getDateLastModif());
    title->setText(task->getTitle());
    actions->setText(task->getActions());
    status->setText(task->getStatus());
    priority->setText(QString::number(task->getPriority()));
    deadline->setDate(task->getDeadline());

    actionsLayout = new QHBoxLayout;
    statusLayout = new QHBoxLayout;
    priorityLayout = new QHBoxLayout;
    deadlineLayout = new QHBoxLayout;

    actionsLayout->addWidget(actionsLabel);
    actionsLayout->addWidget(actions);
    statusLayout->addWidget(statusLabel);
    statusLayout->addWidget(status);
    priorityLayout->addWidget(priorityLabel);
    priorityLayout->addWidget(priority);
    deadlineLayout->addWidget(deadlineLabel);
    deadlineLayout->addWidget(deadline);

    layer->addLayout(actionsLayout);
    layer->addLayout(statusLayout);
    layer->addLayout(priorityLayout);
    layer->addLayout(deadlineLayout);
    layer->addLayout(buttonLayout);

    setLayout(layer);

    QObject::connect(close, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(close, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveNote()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(updateNotesManager()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(updateTaskManager()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(toDustbin()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateArchivesManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateTaskManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateNotesManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(oldVersions, SIGNAL(clicked()), this, SLOT(showOldVersionsWindow()));
    QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    QObject::connect(status, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    QObject::connect(priority, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    QObject::connect(actions, SIGNAL(textChanged()), this, SLOT(activerSave()));
    QObject::connect(deadline, SIGNAL(dateChanged(QDate)), this, SLOT(activerSave()));
    save->setEnabled(false);

    if(task->getNumVersion() == 0){oldVersions->setEnabled(false);}

}

void TaskEditeur::saveNote(){
    task->addOldVersion();
    task->incrementNumVersion();
    task->setDateLastMofid();
    task->setTitle(title->text());
    task->setAction(actions->toPlainText());
    task->setPriority(priority->text().toInt());
    task->setDeadline(deadline->date());
    QMessageBox::information(this, "Sauvegarde", "Tache sauvegardé !");
    save->setDisabled(true);
}

void TaskEditeur::toDustbin(){
    Note* n;
    QMessageBox msgBox;
    if (RelationsManager::getInstance().isReferenced(task) == true){
        msgBox.setText("La note a été archivée car elle est reférencée.");
        msgBox.exec();
        n = NotesManager::getInstance().getNoteWithTitle(task->getTitle());
        ArchivesManager::getInstance().addNote(n);
        NotesManager::getInstance().deleteNote(n->getId());
    }
    else {
        msgBox.setText("La note a bien été ajoutée à la corbeille.");
        msgBox.exec();
        n = NotesManager::getInstance().getNoteWithTitle(task->getTitle());
        Corbeille::getInstance().addNote(n);
        NotesManager::getInstance().deleteNote(n->getId());
    }


}

void TaskEditeur::readOnly(){
    title->setDisabled(true);
    actions->setDisabled(true);
    status->setDisabled(true);
    deadline->setDisabled(true);
    priority->setDisabled(true);
    supp->setDisabled(true);
}

void TaskEditeur::showOldVersionsWindow(){
    ovw = new OldVersionsWindow(task,this);
    ovw->show();
}

MultimediaEditeur::MultimediaEditeur(Multimedia *m, QWidget *parent): NoteEditeur(m,parent){

    //setWindowState(Qt::WindowMaximized);

    descLabel = new QLabel("Description", this);
    filenameLabel = new QLabel("Filename", this);

    desc = new QTextEdit(this);
    filename = new QLineEdit(this);

    descLayout = new QHBoxLayout;
    filenameLayout = new QHBoxLayout;

    descLayout->addWidget(descLabel);
    descLayout->addWidget(desc);
    filenameLayout->addWidget(filenameLabel);
    filenameLayout->addWidget(filename);



    layer->addLayout(descLayout);
    layer->addLayout(filenameLayout);

    /*layer->addWidget(save);
    layer->addWidget(supp);
    layer->addWidget(close);*/
    layer->addLayout(buttonLayout);


    setLayout(layer);



}

void MultimediaEditeur::activerSave() {
    save->setEnabled(true);
    isSaved=false;
}

void MultimediaEditeur::readOnly(){
    title->setDisabled(true);
    desc->setDisabled(true);
    filename->setDisabled(true);
    supp->setDisabled(true);
}

AudioEditeur::AudioEditeur(Audio *a, QWidget *parent): MultimediaEditeur(a,parent), audio(a) {
    id->setText(audio->getId());
    version->setText(QString::number(audio->getNumVersion()));
    date_creation->setDate(audio->getDateCreation());
    date_modif->setDate(audio->getDateLastModif());
    title->setText(audio->getTitle());
    desc->setText(audio->getDescription());
    filename->setText(audio->getImageFilename());

    QObject::connect(close, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(close, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveNote()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(updateNotesManager()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(updateTaskManager()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(toDustbin()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateArchivesManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateNotesManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateTaskManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(oldVersions, SIGNAL(clicked()), this, SLOT(showOldVersionsWindow()));
    QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    QObject::connect(desc, SIGNAL(textChanged()), this, SLOT(activerSave()));
    QObject::connect(filename, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    save->setEnabled(false);

    if(audio->getNumVersion() == 0){oldVersions->setEnabled(false);}
}

void AudioEditeur::saveNote(){
    audio->addOldVersion();
    audio->incrementNumVersion();
    audio->setDateLastMofid();
    audio->setTitle(title->text());
    audio->setDescription(desc->toPlainText());
    audio->setImageFilename(filename->text());
    QMessageBox::information(this, "Sauvegarde", "Audio sauvegardé !");
    save->setDisabled(true);
}

void AudioEditeur::toDustbin(){
    Note* n;
    QMessageBox msgBox;
    if (RelationsManager::getInstance().isReferenced(audio) == true){
        msgBox.setText("La note a été archivée car elle est reférencée.");
        msgBox.exec();
        n = NotesManager::getInstance().getNoteWithTitle(audio->getTitle());
        ArchivesManager::getInstance().addNote(n);
        NotesManager::getInstance().deleteNote(n->getId());
    }
    else {
        msgBox.setText("La note a bien été ajoutée à la corbeille.");
        msgBox.exec();
        n = NotesManager::getInstance().getNoteWithTitle(audio->getTitle());
        Corbeille::getInstance().addNote(n);
        NotesManager::getInstance().deleteNote(n->getId());
    }


}

void AudioEditeur::showOldVersionsWindow(){
    ovw = new OldVersionsWindow(audio,this);
    ovw->show();
}


ImageEditeur::ImageEditeur(Image *img, QWidget *parent): MultimediaEditeur(img,parent), image(img) {
    id->setText(image->getId());
    version->setText(QString::number(image->getNumVersion()));
    date_creation->setDate(image->getDateCreation());
    date_modif->setDate(image->getDateLastModif());
    title->setText(image->getTitle());
    desc->setText(image->getDescription());
    filename->setText(image->getImageFilename());

    QObject::connect(close, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(close, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveNote()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(updateNotesManager()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(updateTaskManager()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(toDustbin()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateArchivesManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateNotesManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateTaskManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(oldVersions, SIGNAL(clicked()), this, SLOT(showOldVersionsWindow()));
    QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    QObject::connect(desc, SIGNAL(textChanged()), this, SLOT(activerSave()));
    QObject::connect(filename, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    save->setEnabled(false);

    if(image->getNumVersion() == 0){oldVersions->setEnabled(false);}
}

void ImageEditeur::saveNote(){
    image->addOldVersion();
    image->incrementNumVersion();
    image->setDateLastMofid();
    image->setTitle(title->text());
    image->setDescription(desc->toPlainText());
    image->setImageFilename(filename->text());
    QMessageBox::information(this, "Sauvegarde", "Image sauvegardé !");
    save->setDisabled(true);
}

void ImageEditeur::toDustbin(){
    Note* n;
    QMessageBox msgBox;
    if (RelationsManager::getInstance().isReferenced(image) == true){
        msgBox.setText("La note a été archivée car elle est reférencée.");
        msgBox.exec();
        n = NotesManager::getInstance().getNoteWithTitle(image->getTitle());
        ArchivesManager::getInstance().addNote(n);
        NotesManager::getInstance().deleteNote(n->getId());
    }
    else {
        msgBox.setText("La note a bien été ajoutée à la corbeille.");
        msgBox.exec();
        n = NotesManager::getInstance().getNoteWithTitle(image->getTitle());
        Corbeille::getInstance().addNote(n);
        NotesManager::getInstance().deleteNote(n->getId());
    }


}

void ImageEditeur::showOldVersionsWindow(){
    ovw = new OldVersionsWindow(image,this);
    ovw->show();
}

VideoEditeur::VideoEditeur(Video* v, QWidget *parent): MultimediaEditeur(v,parent), video(v) {
    id->setText(video->getId());
    version->setText(QString::number(video->getNumVersion()));
    date_creation->setDate(video->getDateCreation());
    date_modif->setDate(video->getDateLastModif());
    title->setText(video->getTitle());
    desc->setText(video->getDescription());
    filename->setText(video->getImageFilename());

    QObject::connect(close, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(close, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveNote()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(updateNotesManager()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(updateTaskManager()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(toDustbin()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateArchivesManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateNotesManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(updateTaskManager()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(oldVersions, SIGNAL(clicked()), this, SLOT(showOldVersionsWindow()));
    QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    QObject::connect(desc, SIGNAL(textChanged()), this, SLOT(activerSave()));
    QObject::connect(filename, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    save->setEnabled(false);

    if(video->getNumVersion() == 0){oldVersions->setEnabled(false);}

}

void VideoEditeur::saveNote(){
    video->addOldVersion();
    video->incrementNumVersion();
    video->setDateLastMofid();
    video->setTitle(title->text());
    video->setDescription(desc->toPlainText());
    video->setImageFilename(filename->text());
    QMessageBox::information(this, "Sauvegarde", "Video sauvegardé !");
    save->setDisabled(true);

}

void VideoEditeur::toDustbin(){
    Note* n;
    QMessageBox msgBox;
    if (RelationsManager::getInstance().isReferenced(video) == true){
        msgBox.setText("La note a été archivée car elle est reférencée.");
        msgBox.exec();
        n = NotesManager::getInstance().getNoteWithTitle(video->getTitle());
        ArchivesManager::getInstance().addNote(n);
        NotesManager::getInstance().deleteNote(n->getId());
    }
    else {
        msgBox.setText("La note a bien été ajoutée à la corbeille.");
        msgBox.exec();
        n = NotesManager::getInstance().getNoteWithTitle(video->getTitle());
        Corbeille::getInstance().addNote(n);
        NotesManager::getInstance().deleteNote(n->getId());
    }


}

void VideoEditeur::showOldVersionsWindow(){
    ovw = new OldVersionsWindow(video,this);
    ovw->show();
}

