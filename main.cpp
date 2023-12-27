#include <vector>
#include <algorithm>

#include "utils.h"
#include "iterator.h"
#include "vector.h"

struct A : Printable<A>
{
    int a;
    A() {}
    A(int b) : a(b) {}
    A(const A& other) : a(other.a) {}
    A(A&& other) { a = std::move(other.a); }
    A& operator=(const A& other) { a = other.a; return *this;}

    const auto print() const noexcept
    {
        return std::string()
            .append("A: [a=")
            .append(std::to_string(a))
            .append("]");
    }
};

int main()
{
    A a {10};
    println(a);

    Vector vec = {30, 20, 10, 40};
    //println(*max(vec));

    forEach(vec, [](const int& a){ print(a);});
    //print(vec);

    // println(vec);
    // vec.pushBack(std::move(0));
    // println(vec);
    // vec.pushBack(40);
    // println(vec);

    // println(vec.isEmpty());
    // println(vec.isNotEmpty());
    // println(vec.size());
    // println(vec.capacity());

    Vector<A> as = { {1}, {3} };
    print(as);

    //allOf(vec, [](const int& a) { return a > 10; });

    // Vector<int> v;
    // v.reserve(3);
    // v.pushBack(std::move(10));
    // v.pushBack(1);
    // v.pushBack(std::move(30));
    // println(v);
    // v.popBack();
    // println(v);

    // println(v[0] == v.at(0));

    // std::sort(vec.begin(), vec.end(), [](const auto& first, const auto& second){
    //     return first < second;
    // });


    // for (auto begin = vec.begin(), end = vec.end(); begin != end; begin++)
    // {
    //     println(*begin);
    // }

    // for (const auto& v : vec)
    // {
    //     println(v);
    // }

    return 0;
}
