#include <vector>
#include <algorithm>

#include "utils.h"
#include "iterator.h"
#include "vector.h"

struct A : Printable<A>
{
    int a = -1;
    A() {::print("created");}
    A(int b) : a(b) { ::print("created"); }
    A(const A& other):  Printable<A>(), a(other.a) { ::print("created"); }
    A(A&& other) { a = std::move(other.a); }
    A& operator=(const A& other) { a = other.a; return *this;}
    A& operator=(A&& other) { a = std::move(other.a); return *this; }
    virtual ~A() {
        ::print<const char*>("died") << std::endl;
    };

    const auto print() const noexcept {
        return std::string()
          .append("A: [a=")
          .append(std::to_string(a))
          .append("]");
    }
};

int main()
{
    Vector<A> init {{10},  {20} };
    println(init);

    Vector<A> as;
    A a1{1};
    A a2{2};
    as.pushBack(std::move(a1));
    as.pushBack(std::move(a2));
    println(as.size());
    println(as.capacity());
    print(as) << std::endl;

    Vector<A> newv(std::move(as));
    print(newv) << std::endl;
    // newv = as;
    // newv = {{10}, {40}};
    // print(newv) << std::endl;

    return 0;
}
