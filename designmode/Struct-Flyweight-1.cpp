/*!
 * 设计模式 享元(flyweight)
 * 外部显示和内部状态分别独立，外部显示需要使用内部状态
 * 解决大量细粒度对象存储的方法
 * 角色
 * 1.flyweight 描述一个接口，通过这个接口可以接受并作用于外部状态
 * 2.concreateflyweight 实现flyweight接口（concreateflyweight是可共享的)
 * 3.unsharedflyweight 非共享的flyweight
 * 4.flyweightfactory 共享的工厂对象（用来创建内部对象)
 */

#include <cstdio>
#include <string>
#include <cassert>

#define NMAXCHAR 128

using namespace std;
struct Font {
    int m_fontFamily;
    int m_fontSize;
    float m_fontPoint;
};

struct Color {
    /*! rgb */
    unsigned char m_red, m_green, m_blue, m_alpha;
};

/*! 构建一个链表来查询对应索引字符的上下文，可以构建一个btree */
struct GlyphContext {
    Font  m_font;
    Color m_color;
};

class Glyph {
public:
    virtual ~Glyph() {}
    virtual void draw(GlyphContext *gc) = 0;
protected:
    Glyph() {}
};

class Character : public Glyph{
public:
    Character(char c): m_char(c){}
    void draw(GlyphContext *gc) override {
        fprintf(stdout,"draw %c, with font-family:%d font-size:%d font-point=%f font-color:rgb(%d,%d,%d)"
                ,m_char, gc->m_font.m_fontFamily, gc->m_font.m_fontSize, gc->m_font.m_fontPoint,
                gc->m_color.m_red, gc->m_color.m_green, gc->m_color.m_blue);
    }
private:
    char m_char;
};

class CharacterFactory {
public:
    CharacterFactory() {
        for(int i=0; i<NMAXCHAR; ++i) m_chars[i] = nullptr;
    }
    ~CharacterFactory() {
        for(int i=0; i<NMAXCHAR; ++i) {
            if(m_chars[i]) delete m_chars[i];
        }
    }
    Character* create(char c) {
        if(!m_chars[c]) {
            m_chars[c] = new Character(c);
        }

        return m_chars[c];
    }
private:
    /*! character 享元*/
    Character *m_chars[NMAXCHAR];
};

int main() {
    CharacterFactory fac;
    Character * c = fac.create('a');
    return 0;
}


