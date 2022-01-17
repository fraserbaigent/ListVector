#include "list_vector.hpp"
#include <iostream>
#include <string>
#include <algorithm>

class TestClass
{
public:
    TestClass
    (std::string s,
     const int n,
     const double v)
	: str(std::move(s))
	, num(n)
	, val(v) {};

    virtual
    ~TestClass
    ()
    {};

    TestClass
    (TestClass const& other)
	: str(other.str)
	, num(other.num)
	, val(other.val)
    {};

    TestClass
    (TestClass && r_value) = delete;
    
    std::string str;
    int num;
    double val;
};


auto print_all(ListVector<TestClass> const& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
	const auto &v = vec[i];
	std:: cout << v.str << " " << v.num << " " << v.val << "\n";
    };
}

int main(int, char *[])
{
    ListVector<TestClass> vec;
    //TestClass t{"first test", 1, 100.0};
    vec.push_back(TestClass{"first test", 1, 100.0});
    TestClass test_2{"second test", 2, 200.0};
    vec.push_back(test_2);
    {
	auto *test_3 = new TestClass{"third test", 3, 300.0};
	vec.donate(test_3);
    }
    
    vec.insert_at(1, TestClass{"fourth test", 4, 400.0});
    
    print_all(vec);
    
    
    std::cout <<"\n";
    
    vec.erase(2);
    print_all(vec);

    ListVector<TestClass>::Iterator it = vec.begin();
    TestClass &b = *it;
    std::cout << it->str <<"\n";


    std::sort(
	      vec.begin(),
	      vec.end(),
	      [] (auto &v, auto&n) { return v.num < n.num; });

    print_all(vec);
    
    return 0;
};
