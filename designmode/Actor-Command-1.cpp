/*!
 * 设计模式 行为篇(命令模式)
 * 角色
 * 1.抽象Command基类
 * 2.构造子类Command (构造的时候聚合一个Receiver)
 * 3.接收处理的对象
 */

#include <cassert>
#include <algorithm>
#include <cstdio>
#include <string>
#include <memory>
#include <map>
#include <list>

using namespace std;
/*!
 * 各种处理器Receiver
 */
class SoundManager {
private:
    SoundManager() {}
    friend class Application;
private:
    SoundManager(const SoundManager& );
    SoundManager& operator=(const SoundManager&);
public:
    void playSong() const { fprintf(stdout, "Play Song\n"); }
    void pause() const { fprintf(stdout, "Pause Song\n"); }
};

class Clipboard{
public:
    Clipboard() {}
    Clipboard(int id, const string& text) :m_id(id), m_text(text) {}
    string getText() const { return m_text; }
    void setText(const string& text) { m_text = text; }
    int getID() const { return m_id; }
private:
    int m_id;
    string m_text;
};

typedef std::shared_ptr<Clipboard> ClipboardSP;

class Document {
public:
    Document() {}
    ~Document() {}
    Document(const string& text) :m_content(text) {}

    string  getContent() const { return m_content; }
    void copy(int index, int length, int toClip = -1) {
        if(index < 0 || 
            index >= m_content.size() || 
            length < 1 || 
            (index+length)>m_content.size() ) return ;
        string c = m_content.substr(index, length);
        if(toClip < 0) toClip = 0;
        auto i = m_clips.find(toClip);
        if(i == m_clips.end()) {
            m_clips[toClip] = ClipboardSP(new Clipboard(toClip, c));
        } else {
            m_clips[toClip]->setText(c);
        }
    }

    void paste(int toIndex, int fromClip = -1) {
        if(fromClip < 0) fromClip = 0;
        auto i = m_clips.find(fromClip);
        if(i == m_clips.end()) return ;
        string s = (*i).second->getText();

        if(toIndex < 0 || toIndex >= m_content.size()) {
            /*! append to it*/
            m_content += s;
        } else {
            m_content.insert(toIndex, s);
        }
    }

    void dump() const {
        fprintf(stdout, "m_content=%s\n", m_content.c_str());
    }
private:
    string m_content;
    map<int, ClipboardSP> m_clips;
};

class Application {
public:
    Application() {
        m_doc = new Document("It's a initialize text.");
    }

    ~Application() {
        if(m_doc) delete m_doc;
    }
    static SoundManager* getSoundManager()  {
        static SoundManager *sm {nullptr};

        if(sm == nullptr) {
            sm = new SoundManager();
        }
        return sm;
    }

    Document* getDocument() const { return m_doc; }
private:
    Document *m_doc {nullptr};
};

/*!
 * 抽象Command以及他们的构造类
 */
class Command {
public:
    virtual ~Command() {}
    virtual string getName() const = 0;
    virtual bool execute() = 0;
};

class CopyCommand : public Command{
public:
    CopyCommand(Document* doc):m_doc(doc) {}
    CopyCommand(Document* doc, int pos, int length=1) :
        m_doc(doc),
        m_pos(pos),
        m_length(length) {}

    void setCopyInfo(int index, int length = 1) {
        m_pos = index;
        m_length = length;
    }

    int getPos() const { return m_pos; }
    int getLength() const { return m_length;}

    bool execute() override {
        if(!m_doc) return false;
        m_doc->copy(m_pos, m_length);
        return true;
    }

    string getName() const override { return "CopyCommand"; }
private:
    Document *m_doc {nullptr};
    int m_pos{0}, m_length{0};
};

class PasteCommand : public Command {
public:
    PasteCommand(Document* doc):m_doc(doc) {}
    PasteCommand(Document* doc, int pos) :
        m_doc(doc), m_pos(pos) {}

    void setPos(int pos) { m_pos = pos; }
    int getPos() const { return m_pos; }

    bool execute() override {
        if(!m_doc) return false;
        m_doc->paste(m_pos);
        return true;
    }

    string getName() const override { return "PasteCommand"; }
private:
    Document *m_doc {nullptr};
    int m_pos {0};
};

class PlaySongCommand : public Command {
public:
    PlaySongCommand(SoundManager* sm) :m_sm(sm) {}
    bool execute() override {
        if(!m_sm) return false;
        m_sm->playSong();
        return true;
    }
    string getName() const override { return "PlaySongCommand"; }
private:
    SoundManager *m_sm{nullptr};
};

class PauseSongCommand : public Command {
public:
    PauseSongCommand(SoundManager* sm):m_sm(sm) {}
    bool execute() override {
        if(!m_sm) return false;
        m_sm->pause();
        return true;
    }
    string getName() const override { return "PauseSongCommand"; }
private:
    SoundManager *m_sm {nullptr};
};

class MarcoCommand : public Command {
public:
    ~MarcoCommand() {
        for(auto i=m_cmds.begin(); i != m_cmds.end(); ) {
            fprintf(stdout, "free:%s\n", (*i)->getName().c_str());
            delete *i;
            i = m_cmds.erase(i);
        }
    }
    void add(Command * c) {
        if(!c) return ;
        auto i = std::find(m_cmds.begin(), m_cmds.end(), c);
        if(i != m_cmds.end()) return ;
        m_cmds.push_back(c);
    }

    void remove(Command *c){
        if(!c) return ;
        auto i = std::find(m_cmds.begin(), m_cmds.end(), c);
        if(i == m_cmds.end()) return ;
        m_cmds.erase(i);
    }

    string getName() const override { return "MacroCommand"; }

    bool execute() override {
        if(m_cmds.empty()) return true;
        for(Command* c : m_cmds) {
            if(!c->execute()) {
                return false;
            }
        }

        return true;
    }
private:
    list<Command*> m_cmds;
};

int main() {
    Application app;
    Document * doc = app.getDocument();
    SoundManager *sm = Application::getSoundManager();
    assert(sm);

    doc->dump();
    MarcoCommand mc;
    mc.add(new CopyCommand(doc, 0, 2));
    mc.add(new PasteCommand(doc, 0));
    mc.add(new PlaySongCommand(sm));
    mc.add(new PauseSongCommand(sm));
    assert(mc.execute());
    doc->dump();

    return 0;
}




