/*!
 * 单体模式
 * 角色
 * 单体对象（全局仅一个对象)
 */

#include <string>
#include <cstdio>
#include <memory>

using namespace std;

class Singleton {
public:
  static Singleton* instance() {
    /*! 并非线程安全，要保证线程安全，需要考虑加锁 */
    static Singleton *s {nullptr};
    if(s == nullptr) {
      /*!延迟创建*/
      s = new Singleton();
    }

    return s;
  }

  void show() const { fprintf(stdout, "singleton:\n"); }
private:
  Singleton() {};
private:
  /*!禁用拷贝和赋值拷贝 */
  Singleton(const Singleton& other);
  Singleton& operator=(const Singleton& other);
};

int main() {
  Singleton::instance()->show();
  return 0;
}
