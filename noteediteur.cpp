#include "noteediteur.h"
#include <QMessageBox>
#include <QObject>
#include <QItemSelectionModel>
#include "corbeille.h"

NoteEditeur::NoteEditeur(Note* n, QWidget* parent)
{
    idLabel= new QLabel("Identificateur", this);
    titleLabel = new  QLabel("Titre", this);
    versionLabel = new QLabel("Numero Version", this);

    id = new QLineEdit(this);
    title = new QLineEdit(this);
    version = new QLineEdit(this);

    save = new QPushButton("Sauver",this);
    supp = new QPushButton("Mettre à la corbeille",this);

    idLayout = new QHBoxLayout;
    titleLayout = new QHBoxLayout;
    versionLayout = new QHBoxLayout;

    saveLayout = new QHBoxLayout;
    suppLayout = new QHBoxLayout;

    layer = new QVBoxLayout;

    idLayout->addWidget(idLabel);
    idLayout->addWidget(id);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(title);
    versionLayout->addWidget(versionLabel);
    versionLayout->addWidget(version);

    saveLayout->addWidget(save);
    suppLayout->addWidget(supp);
    //version->setMaximumWidth(100);

    layer->addLayout(idLayout);
    layer->addLayout(titleLayout);
    layer->addLayout(versionLayout);


    id->setDisabled(true);
    version->setDisabled(true);


}

/*NoteEditeur* NoteEditeur::chooseEditeur(Note* n, QString& type){
    if(type==(QString) "art") {ArticleEditeur* fact = new ArticleEditeur(dynamic_cast<Article*>(n)); return fact;}
    else if(type==(QString) "task") {TaskEditeur* fact = new TaskEditeur(dynamic_cast<Task*>(n)); return fact;}
    else if(type==(QString) "img") {ImageEditeur* fact = new ImageEditeur(dynamic_cast<Image*>(n)); return fact;}
    else if(type==(QString) "aud") {AudioEditeur* fact = new AudioEditeur(dynamic_cast<Audio*>(n)); return fact;}
    else if(type==(QString) "vid") {VideoEditeur* fact = new VideoEditeur(dynamic_cast<Video*>(n)); return fact;}
    else {throw NotesException("Mauvais type..");}

}*/

void NoteEditeur::activerSave() {
    save->setEnabled(true);
    isSaved=false;
}

void NoteEditeur::toDustbin(Note* n){
    Corbeille::getInstance().addNote(n);
    NotesManager::getInstance().deleteNote(n->getId());

}


ArticleEditeur::ArticleEditeur(Article* a, QWidget* parent) : NoteEditeur(a,parent), article (a) {
    //article = dynamic_cast<Article*>(a);
    //setWindowState(Qt::WindowMaximized);

    textLabel = new QLabel("Texte", this);

    text = new QTextEdit(this);

    id->setText(QString::number(article->getId().toInt()));
    version->setText(QString::number(article->getNumVersion()));
    title->setText(article->getTitle());
    text->setText(article->getText());


    textLayout = new QHBoxLayout;

    textLayout->addWidget(textLabel);
    textLayout->addWidget(text);

    idLayout->addWidget(id);
    titleLayout->addWidget(title);
    textLayout->addWidget(text);

    layer->addLayout(textLayout);

    layer->addWidget(save);
    layer->addWidget(supp);

    setLayout(layer);

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveNote()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(toDustbin(this->article)));
    //QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(updateNote()));
    //QObject::connect(text, SIGNAL(textChanged()), this, SLOT(updateNote()));
    QObject::connect(text, SIGNAL(textChanged()), this, SLOT(activerSave()));
    QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    save->setEnabled(false);
}

void ArticleEditeur::saveNote() {
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









TaskEditeur::TaskEditeur(Task *t, QWidget *parent): NoteEditeur(t,parent), task(t) {
    //setWindowState(Qt::WindowMaximized);

    statusLabel = new QLabel("Statut", this);
    priorityLabel = new QLabel("Priorite", this);
    deadlineLabel = new QLabel("Deadline", this);

    status = new QLineEdit(this);
    priority = new QLineEdit(this);
    deadline = new QLineEdit(this);

    id->setText(task->getId());
    version->setText(QString::number(task->getNumVersion()));
    title->setText(task->getTitle());
    status->setText(task->getStatus());
    priority->setText(QString::number(task->getPriority()));
    deadline->setText(task->getDeadline().toString());

    statusLayout = new QHBoxLayout;
    priorityLayout = new QHBoxLayout;
    deadlineLayout = new QHBoxLayout;

    statusLayout->addWidget(statusLabel);
    statusLayout->addWidget(status);
    priorityLayout->addWidget(priorityLabel);
    priorityLayout->addWidget(priority);
    deadlineLayout->addWidget(deadlineLabel);
    deadlineLayout->addWidget(deadline);


    layer->addLayout(statusLayout);
    layer->addLayout(priorityLayout);
    layer->addLayout(deadlineLayout);

    layer->addWidget(save);
    layer->addWidget(supp);

    setLayout(layer);

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveNote()));
    QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    QObject::connect(status, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    QObject::connect(priority, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    QObject::connect(deadline, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    save->setEnabled(false);

}

void TaskEditeur::saveNote(){
    task->setTitle(title->text());
    task->setPriority(priority->text().toInt());
    task->setDeadline(QDate::fromString(deadline->text()));
    QMessageBox::information(this, "Sauvegarde", "Tache sauvegardé !");
    save->setDisabled(true);
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

    layer->addWidget(save);
    layer->addWidget(supp);


    setLayout(layer);



}

void MultimediaEditeur::activerSave() {
    save->setEnabled(true);
    isSaved=false;
}

AudioEditeur::AudioEditeur(Audio *a, QWidget *parent): MultimediaEditeur(a,parent), audio(a) {
    id->setText(audio->getId());
    version->setText(QString::number(audio->getNumVersion()));
    title->setText(audio->getTitle());
    desc->setText(audio->getDescription());
    filename->setText(audio->getImageFilename());

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveNote()));
    QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    QObject::connect(desc, SIGNAL(textChanged()), this, SLOT(activerSave()));
    QObject::connect(filename, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    save->setEnabled(false);
}

void AudioEditeur::saveNote(){
    audio->setTitle(title->text());
    audio->setDescription(desc->toPlainText());
    audio->setImageFilename(filename->text());
    QMessageBox::information(this, "Sauvegarde", "Audio sauvegardé !");
    save->setDisabled(true);
}


ImageEditeur::ImageEditeur(Image *img, QWidget *parent): MultimediaEditeur(img,parent), image(img) {
    id->setText(image->getId());
    version->setText(QString::number(image->getNumVersion()));
    title->setText(image->getTitle());
    desc->setText(image->getDescription());
    filename->setText(image->getImageFilename());

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveNote()));
    QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    QObject::connect(desc, SIGNAL(textChanged()), this, SLOT(activerSave()));
    QObject::connect(filename, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    save->setEnabled(false);
}

void ImageEditeur::saveNote(){
    image->setTitle(title->text());
    image->setDescription(desc->toPlainText());
    image->setImageFilename(filename->text());
    QMessageBox::information(this, "Sauvegarde", "Image sauvegardé !");
    save->setDisabled(true);
}

VideoEditeur::VideoEditeur(Video* v, QWidget *parent): MultimediaEditeur(v,parent), video(v) {
    id->setText(video->getId());
    version->setText(QString::number(video->getNumVersion()));
    title->setText(video->getTitle());
    desc->setText(video->getDescription());
    filename->setText(video->getImageFilename());

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveNote()));
    QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    QObject::connect(desc, SIGNAL(textChanged()), this, SLOT(activerSave()));
    QObject::connect(filename, SIGNAL(textEdited(QString)), this, SLOT(activerSave()));
    save->setEnabled(false);

}

void VideoEditeur::saveNote(){
    video->setTitle(title->text());
    video->setDescription(desc->toPlainText());
    video->setImageFilename(filename->text());
    QMessageBox::information(this, "Sauvegarde", "Video sauvegardé !");
    save->setDisabled(true);

}

