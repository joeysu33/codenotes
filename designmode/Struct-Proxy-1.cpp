/*!
 * 设计模式 代理(proxy)
 * 角色
 * 1.客户(client)
 * 2.对象接口 (isubject)
 * 3.代理 (proxy)
 * 4.被代理的类(subject)
 *    对象接口
 *      | (继承)
 *   -----------
 *   |         |
 *        (使用)
 * 被代理的---代理类
 */

#include <memory>
#include <string>
#include <cstdio>

struct Rect {
    int m_x {0}, m_y{0};
    int m_width{0}, m_height {0};
};

class Graphic {
public:
    virtual ~Graphic() {}
    virtual Rect getExtent() { return Rect(); }
    virtual void draw() = 0;
    virtual bool store() const = 0;
    virtual bool load() = 0;
};

class VeryBigImage : public Graphic{
public:
    Rect getExtent() override { return m_rect; }
    void draw() override { fprintf(stdout, "VeryBigImage::draw\n"); }
    bool store() const override { fprintf(stdout, "VeryBigImage::store\n"); }
    bool load() override { fprintf(stdout, "VeryBigImage::load\n"); }
private:
    Rect m_rect ;
};


/*!
 * 通过使用proxy可以延迟加载Image
 * 避免对象直接被加载，延迟到绘制的时候再使用
 */
class ImageProxy : public Graphic{
public:
    ~ImageProxy() { if(m_image) { delete m_image; } }
    Rect getExtent() override{ 
        /*! 这里可以预读出图片的基本属性,在此省略*/
        if(m_image)  {
            return Rect();
        }
        return m_image->getExtent(); 
    }

    void draw() override {
        /*! 在绘制的时候才进行加载*/
        if(!m_image) {
            m_image = new VeryBigImage();
            if(!load()) return ;
        }

        m_image->draw();
    }

    bool load() override {
        return m_image;
    }

    bool store() const override {
        if(!m_image) return false;
        return m_image->store();
    }

private:
    VeryBigImage *m_image { nullptr};
};

int main() {
    std::shared_ptr<Graphic> g(new ImageProxy());
    g->draw();

    return 0;
}



