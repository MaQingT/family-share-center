#include <music.h>

bool addNewMusic(QString musicName,QString artist,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",familyid);
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;

    if(db.open()){
        qDebug()<<"add music record function connect";
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `%1`.`music` (`music_name`, `artist`) VALUES ('%2', '%3');").arg(familyid).arg(musicName).arg(artist);
        if(query.exec(I)){
            qDebug()<<"add music success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add music record function disconnect";
            return true;
        }
        else {
            qDebug()<<"add music fail";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add music record function disconnect";
            return false;
        }
    }else {
        qDebug()<<"database connect fail";
        return false;
    }
}

bool addMusicRecord(Music music,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",familyid);
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;
    if(db.open()){
        qDebug()<<"add music record function connect";
        QDateTime t;
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `%1`.`music_record` (`music_id`, `user_id`, `time`) VALUES ('%2', '%3', '%4');").arg(QString::number(user.getFamilyId())).arg(QString::number(music.getId())).arg(QString::number(user.getId())).arg(t.currentDateTime().toString("yyyyMMddhhmmss"));
        if(query.exec()){
            qDebug()<<"add record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add music record function disconnect";
            return true;
        }
        else{
            qDebug()<<"add record fail";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"music add record function disconnect";
            return false;
        }
    }
    else{
        qDebug()<<"database connect fail";
        return false;
    }
}

bool ifNewMusic(QString musicName,QString artist,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",familyid);
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;

    if(db.open()){
        qDebug()<<"if music function connect";
        QString S = QString("select * from '%1'.music where user_name = '%2' and artist = '%3'").arg(familyid).arg(musicName).arg(artist);
        QSqlQuery query(db);
        if(query.exec(S) && query.next()){
            qDebug()<<"already have music";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"if music function disconnect";
            return true;
        }
        else {
            qDebug()<<"dont have music";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add music record function disconnect";
            qDebug()<<"adding music now";
            if(addNewMusic(musicName,artist,user)) return true;
            else return false;
        }
    }
    else {
        qDebug()<<"if music function fail";
        return false;
    }
}

QList<MusicRecord> syncMusicRecord(User user,int start,int numbers,int Tspecial){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",familyId);
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;
    QList<MusicRecord> records;
    if(db.open()){
        qDebug()<<"sync music record function connect";
        QString S = QString("SELECT music.music_name,members.user_name FROM `%1`.music,`%1`.music_record,`%1`.members where members.special = '%4' and music_record.music_id = music.music_id and members.user_id = music_record.user_id order by time desc limit %2,%3;")
                .arg(familyId)
                .arg(QString::number(start))
                .arg(QString::number(numbers))
                .arg(QString::number(Tspecial));
        QSqlQuery query(db);
        if(query.exec(S)){
            while(query.next()){
                MusicRecord New(query.value(1).toString(),query.value(0).toString(),query.value(2).toString());
                records<<New;
            }
            qDebug()<<"sync music record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync music record function disconnect";
            return records;
        }
        else {
            qDebug()<<"sync music record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync music record function disconnect";
            return records;
        }

    }
    else {
        qDebug()<<"connect fail";
        return records;
    }
}
