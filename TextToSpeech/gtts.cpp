#include "./gtts.h"

namespace gtts {

GoogleTTS::GoogleTTS(string msg, string lang, string speed,string filename ,string filetype) {

    QDir dir;

    _speed += speed;
    _lang += lang;
    _filename = filename;
    _filetype = filetype;

    _out = "> "+dir.currentPath().toStdString()+"/"+_filename+"."+_filetype;
    _outv = "> "+dir.currentPath().toStdString()+"/"+_filename+"";
    _play = " "+dir.currentPath().toStdString()+"/"+_filename+"."+filetype+" 1>/dev/null";
    _cat = "cat "+dir.currentPath().toStdString()+"/"+_filename+"*."+filetype+" > "+dir.currentPath().toStdString()+"/"+_filename+"."+filetype;
    _rm = "rm "+dir.currentPath().toStdString()+"/"+_filename+"*."+filetype;

    QString qmsg = QString::fromStdString(msg).toLower();
    if(lang == "tr")
    {
        if(qmsg.contains("ş") == true)
            msg = qmsg.replace("ş","%C5%9F").toStdString();
        if(qmsg.contains("ı") == true)
            msg = qmsg.replace("ı","%C4%B1").toStdString();
        if(qmsg.contains("ö") == true)
            msg = qmsg.replace("ö","%C3%B6").toStdString();
        if(qmsg.contains("ğ") == true)
            msg = qmsg.replace("ğ","%C4%9F").toStdString();
        if(qmsg.contains("ü") == true)
            msg = qmsg.replace("ü","%C3%BC").toStdString();
        if(qmsg.contains("ç") == true)
            msg = qmsg.replace("ç","%C3%A7").toStdString();

    }


    if (msg.length() > 200) {
        std::vector<string> msgs = this->split(msg);
        this->parse(msgs);
    } else {

        _text = msg;
        this->parse();
    }
}

std::vector<string> GoogleTTS::split(string& msg) {
    std::vector<string> vec;
    std::istringstream iss(msg);
    std::vector<string> words(std::istream_iterator<string>{iss},
            std::istream_iterator<string>());
    string part = "";
    for (string s : words) {
        if(part.size()-1 + s.size() <= 200) {
            part += s + " ";
        } else {
            vec.push_back(part);
            part = s + " ";
        }
    }
    if(part != "") vec.push_back(part);

    return vec;
}

void GoogleTTS::unite() {
    system(_cat.c_str());
    system(_rm.c_str());
}

void GoogleTTS::execute() {
    if (_cmds.size() == 1) {
        std::system(_cmds[0].c_str());
    } else {
        for(string cmd : _cmds) {
            std::system(cmd.c_str());
        }
        this->unite();
    }
    _mpv += _speed + _play;
    std::system(_mpv.c_str());
}

void GoogleTTS::replace(string& text) {
    size_t start_pos = 0;
    while ((start_pos = text.find(" ", start_pos)) != string::npos) {
       text.replace(start_pos, 1, "%20");
       start_pos += 3; // Handles case where 'to' is a substring of 'from'
    }
}

void GoogleTTS::parse() {
    this->replace(_text);
    string cmd = _curl + _text + _lang + _client + "-H" + _ref + "-H";
    cmd += _agent + _out + " 2>/dev/null";
    _cmds.push_back(cmd);
}

void GoogleTTS::parse(std::vector<string>& vec) {
    string cmd = "";
    int i = 0;
    for (string msg : vec) {
        this->replace(msg);
        cmd = _curl + msg + _lang + _client + "-H" + _ref + "-H";
        cmd += _agent + _outv + std::to_string(i) + ".mp3" + " 2>/dev/null";
        _cmds.push_back(cmd);
        i++;
    }
}

void GoogleTTS::help() {
    std::cout << "gtts: plays Google Text-to-Speech speech synthesis with " <<
        "help of Google Translate voice" << std::endl;
    std::cout << "Usage: gtts [language] \"[message]\" ([speed])" << std::endl;
    std::cout << "Example: gtts us \"hello world\" 1.5" << std::endl;
    std::cout << "standard speed is 1.0" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-h\t\tshows this help" << std::endl;
    std::cout << "-v\t\tshows program version" << std::endl;
    std::cout << "-l\t\tshows all available languages" << std::endl;
    std::cout << std::endl;
    std::cout << "To speak from text files use: gtts [lang] \"$(cat file.txt)\""
       " ([speed])" << std::endl;
    std::cout << std::endl;
}

void GoogleTTS::languages() {
    std::cout << "Supported languages:" << std::endl;
    int counter = 0;
    for(std::pair<string, string> l : lang_codes) {
        std::cout << l.first  << "\t:\t"<< l.second << std::endl;
    }
    std::cout << std::endl;
}

void GoogleTTS::version() {
    std::cout << "gtts version: 0.3" << std::endl;
}

}
