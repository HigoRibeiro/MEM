#include "language.h"

Language * Language::inst = NULL;
QHash<QString, QString> Language::languageMap;

Language::Language()
{
}

Language * Language::instance()
{
    if( !inst )
        inst = new Language;
    return inst;
}

void Language::loadLanguage(QString lang)
{
    QFile fileLanguage(QCoreApplication::applicationDirPath()+"/Language/"+lang+".po");

       if (fileLanguage.open(QIODevice::ReadOnly|QIODevice::Text))
       {
          while ( !fileLanguage.atEnd() )
          {
              QString line = fileLanguage.readLine();
              line.remove("\n");

              if( line.contains("=") )
             {
                 QStringList lista = line.split("=");
                 QString key = lista.first().remove(" ");
                 QString traducao = lista.last().remove(QRegExp( "^\"|\"$"));
                 languageMap[key] = QString::fromUtf8(traducao.toStdString().c_str());
             }
          }
       }
       fileLanguage.close();
}

QString Language::language(QString key)
{
    return languageMap[key];
}
