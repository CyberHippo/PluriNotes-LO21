#include "noteediteur.h"
#include <QMessageBox>
#include <QObject>
#include <QItemSelectionModel>

NoteEditeur::NoteEditeur(Note* n, QWidget* parent)
{
    id = new QLineEdit(n->getId());
    title = new QLineEdit(n->getTitle());
    save = new QPushButton("Sauver");
    supp = new QPushButton("Mettre à la corbeille");
    idLayout = new QHBoxLayout;
    titleLayout = new QHBoxLayout;
    layout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(save);
    buttonLayout->addWidget(supp);
}

ArticleEditeur::ArticleEditeur(Note* a, QWidget* parent) : NoteEditeur(a) {
    article = dynamic_cast<Article*>(a);
    setWindowState(Qt::WindowMaximized);

    text = new QTextEdit;
    text->setText(article->getText());

    idLayout->addWidget(id);
    titleLayout->addWidget(title);
    layout->addWidget(text);
    layout->addLayout(buttonLayout);
    title->setText(a->getTitle());

    setLayout(layout);

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveNote()));
    QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(updateNote()));
    QObject::connect(text, SIGNAL(textChanged()), this, SLOT(updateNote()));
    QObject::connect(text, SIGNAL(textChanged()), this, SLOT(activerSave()));
    QObject::connect(title, SIGNAL(textEdited(QString)), this, SLOT(activerSave(QString)));
    save->setEnabled(false);
}

void ArticleEditeur::saveNote() {
    article->setTitle(title->text());
    article->setText(text->toPlainText());
    NotesManager::getInstance().saveNote(*article);
    QMessageBox::information(this, "Sauvegarde", "Votre article a bien été sauvé");
    save->setEnabled(false);
    isSaved=true;
}

void ArticleEditeur::updateNote() {
    article->setTitle(title->text());
    article->setText(text->toPlainText());
    activerSave();
}

void ArticleEditeur::activerSave() {
    save->setEnabled(true);
    isSaved=false;
}

Article* ArticleEditeur::getNote() const {
    return article;
}
