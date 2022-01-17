#include <vector>
#include <iterator>
#include <algorithm>

template <typename T>
class ListVector final
{
    using Vector = std::vector<T*>;
    using VecIter = typename Vector::iterator;
public:
    class Iterator final
    {
    public:
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = value_type*;
	using reference = value_type&;

	Iterator
	() = default;
	
	Iterator
	(VecIter vec_it)
	    : _vec_it{vec_it}
	{};

	Iterator
	(Iterator const& other) noexcept
	    : _vec_it(other._vec_it)
	{
	};

	Iterator
	(Iterator && other) = delete;

	Iterator&
	operator=
	(Iterator const& other) noexcept {
	    if (this != &other) {
		_vec_it = other._vec_it;
	    }
	    return *this;
	};
	
	Iterator&
	operator=
	(Iterator && other) = delete;
	
	reference
	operator*
	() const
	{
	    return **_vec_it;
	};

	pointer
	operator->
	()
	{
	    return *_vec_it;
	};

	friend Iterator
	operator+
	(Iterator const& left,
	 difference_type right) {
	    auto temp = left;
	    temp += right;
	    return temp;
	};

	friend Iterator
	operator+
	(difference_type left,
	 Iterator const& right) {
	    return right + left;
	};
	
	Iterator&
	operator+=
	(difference_type right)
	{
	    _vec_it += right;
	    return *this;
	};
	
	Iterator&
	operator-=
	(difference_type right)
	{
	    _vec_it -= right;
	    return *this;
	};

	friend Iterator
	operator-
	(Iterator const& left, difference_type right)
	{
	    auto temp = left;
	    temp -= right;
	    return temp;

	};
	
	friend Iterator
	operator-
	(difference_type left, Iterator const& right)
	{
	    return right - left;
	};	

	friend difference_type
	operator-
	(Iterator const& left, Iterator const& right)
	{
	    return left._vec_it - right._vec_it;
	};

	reference
	operator[]
	(difference_type i) const {
	    return *(*this + i);
	};	    
	
	Iterator&
	operator++
	()
	{
	    _vec_it++;
	    return *this;
	};
	
	Iterator&
	operator++
	(int)
	{
	    auto temp = *this;
	    ++(*this);
	    return temp;
	};

	Iterator&
	operator--
	() {
	    _vec_it--;
	    return *this;
	};
	
	Iterator&
	operator--
	(int) {
	    auto temp = *this;
	    --(*this);
	    return temp;
	};

	friend bool
	operator==
	(Iterator const& a,
	 Iterator const& b)
	{
	    return *a._vec_it == *b._vec_it;
	};

	friend bool
	operator!=
	(Iterator const& a,
	 Iterator const& b)
	{
	    return !(a == b);
	};

	
	friend bool
	operator<
	(Iterator const& left,
	 Iterator const& right) {
	    return left._index < right._index;
	};

	friend bool
	operator<=
	(Iterator const& left,
	 Iterator const& right) {
	    return left._index <= right._index;
	};

	friend bool operator>
	(Iterator const& left
	 , Iterator const& right) {
	    return left._index > right._index;
	};

	friend bool
	operator>=
	(Iterator const& left,
	 Iterator const& right) {
	    return left._index >= right._index;
	};	
    private:
	VecIter _vec_it { nullptr };
};
    
    
    
    ListVector<T>() {};

    ~ListVector<T>() {
	for (auto *ptr : _data) {
	    delete ptr;
	};
    };

    ListVector
    (ListVector const& other) = delete;

    ListVector
    (ListVector && other)
	: _data(std::move(other._data))
    {	
    };

    ListVector&
    operator=
    (ListVector const& other) = delete;
    
    ListVector&
    operator=
    (ListVector && other) {
	_data = std::move(other._data);
    };

    void push_back(T const& val) {
	_data.push_back(new T(val));	
    };  

    template<class U = T,
	     class = std::enable_if_t<std::is_same_v<T,U> &&
				      std::is_move_constructible_v<U>>>
    void push_back(U && val) noexcept {
	_data.push_back(new T(std::move(val)));
    };

    void donate(T * val) noexcept {
	_data.push_back(val);
    };

    void insert_at(size_t const index, T const & val) {
	auto it = _data.begin();
	std::advance(it, index);
	_data.insert(it, new T(val));
    };

    template<class U = T,
	     class = std::enable_if_t<std::is_same_v<T,U> &&
				      std::is_move_constructible_v<U>>>
    void insert_at(size_t const index, U && val) {
	auto it = _data.begin();
	std::advance(it, index);
	_data.insert(it, new U(std::move(val)));
    };

    void donate_at(size_t const index, T * val) {
	auto it = _data.begin();
	std::advance(it, index);
	_data.insert(it, val);
    };
    
    T const& operator[](size_t index) const {
	return *_data[index];
    };
    
    void erase(size_t const index) {
	auto it = _data.begin();
	std::advance(it, index);
	delete *it;
	_data.erase(it);
    };

    bool erase(T * val) {
	auto it = std::find(
			    _data.begin(),
			    _data.end(),
			    val);
	if (it != _data.end()) {
	    delete *it;
	    _data.erase(it);
	    return true;
	}
	
	return false;
    };

    size_t size() const noexcept {
	return _data.size();
    };

    T & front() const noexcept {
	return *_data.front();
    };

    T & back() const noexcept {
	return *_data.back();
    };   

    bool reserve(size_t const num) {
	if (num > _data.size()) {
	    _data.reserve(num);
	};
	return false;
    };

    decltype(auto)
    begin
    () {
	return Iterator(_data.begin());
    }

    decltype(auto)
    end
    () {
	return Iterator(_data.end());
    };
    
private:
	std::vector<T*> _data;    
};
