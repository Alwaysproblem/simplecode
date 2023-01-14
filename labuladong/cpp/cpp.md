C++常见面试问题汇总
指针和引用的区别
堆和栈的区别
new和delete是如何实现的，new 与 malloc的异同处
C和C++的区别
C++、Java的联系与区别，包括语言特性、垃圾回收、应用场景等（java的垃圾回收机制）
Struct和class的区别
define 和const的区别（编译阶段、安全性、内存占用等）
在C++中const和static的用法（定义，用途）
const和static在类中使用的注意事项（定义、初始化和使用）
C++中的const类成员函数（用法和意义），以及和非const成员函数的区别
C++的顶层const和底层const
final和override关键字
拷贝初始化和直接初始化，初始化和赋值的区别
extern "C"的用法
模板函数和模板类的特例化
C++的STL源码（这个系列也很重要，建议侯捷老师的STL源码剖析书籍与视频），其中包括内存池机制，各种容器的底层实现机制，算法的实现原理等）
STL源码中的hashtable的实现
STL中unordered_map和map的区别和应用场景
STL中vector的实现
STL容器的几种迭代器以及对应的容器（输入迭代器，输出迭代器，前向迭代器，双向迭代器，随机访问迭代器）
顺序容器：vector,deque是随机访问迭代器；list是双向迭代器

容器适配器：stack,queue,priority_queue没有迭代器

关联容器：set,map,multiset,multimap是双向迭代器

unordered_set,unordered_map,unordered_multiset,unordered_multimap是前向迭代器

STL中的traits技法
type_traits

iterator_traits

char traits

allocator_traits

pointer_traits

array_traits

vector使用的注意点及其原因，频繁对vector调用push_back()对性能的影响和原因。
C++中的重载和重写的区别
C++内存管理，内存池技术（热门问题），与csapp中几种内存分配方式对比学习加深理解
介绍面向对象的三大特性，并且举例说明每一个
C++多态的实现
C++虚函数相关（虚函数表，虚函数指针），虚函数的实现原理（包括单一继承，多重继承等）（拓展问题：为什么基类指针指向派生类对象时可以调用派生类成员函数，基类的虚函数存放在内存的什么区，虚函数表指针vptr的初始化时间）
C++中类的数据成员和成员函数内存分布情况
this指针
析构函数一般写成虚函数的原因
构造函数、拷贝构造函数和赋值操作符的区别
构造函数：对象不存在，没用别的对象初始化

拷贝构造函数：对象不存在，用别的对象初始化

赋值运算符：对象存在，用别的对象给它赋值

构造函数声明为explicit
构造函数为什么一般不定义为虚函数
构造函数的几种关键字(default delete 0)
= default：将拷贝控制成员定义为=default显式要求编译器生成合成的版本

= delete：将拷贝构造函数和拷贝赋值运算符定义删除的函数，阻止拷贝（析构函数不能是删除的函数 C++Primer P450）

= 0：将虚函数定义为纯虚函数（纯虚函数无需定义，= 0只能出现在类内部虚函数的声明语句处；当然，也可以为纯虚函数提供定义，不过函数体必须定义在类的外部）

构造函数或者析构函数中调用虚函数会怎样
纯虚函数
静态类型和动态类型，静态绑定和动态绑定的介绍
引用是否能实现动态绑定，为什么引用可以实现
深拷贝和浅拷贝的区别（举例说明深拷贝的安全性）
对象复用的了解，零拷贝的了解
介绍C++所有的构造函数
什么情况下会调用拷贝构造函数（三种情况）
结构体内存对齐方式和为什么要进行内存对齐？
内存泄露的定义，如何检测与避免？
手写智能指针的实现（shared_ptr和weak_ptr实现的区别）
智能指针的循环引用
遇到coredump要怎么调试
内存检查工具的了解
模板的用法与适用场景
成员初始化列表的概念，为什么用成员初始化列表会快一些（性能优势）？
用过C++ 11吗，知道C++ 11哪些新特性？
C++的调用惯例（简单一点C++函数调用的压栈过程）
C++的四种强制转换
static_cast

dynamic_cast

const_cast

reinterpret_cast

C++中将临时变量作为返回值的时候的处理过程（栈上的内存分配、拷贝过程）
C++的异常处理
volatile关键字
优化程序的几种方法
public，protected和private访问权限和继承
class和struct的区别
decltype()和auto
inline和宏定义的区别
C++和C的类型安全