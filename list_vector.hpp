#include <vector>
#include <algorithm>

template <typename T>
class ListVector final
{
public:
    ListVector<T>() {};

    ~ListVector<T>() {
	for (auto *ptr : _data) {
	    delete ptr;
	};
    };

    void push_back(T const& val) {
	_data.push_back(new T(val));	
    };

    void push_back(T && val) noexcept {
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

    void insert_at(size_t const index, T && val) {
	auto it = _data.begin();
	std::advance(it, index);
	_data.insert(it, new T(std::move(val)));
    };

    void donate_at(size_t const index, T * val) {
	auto it = _data.begin();
	std::advance(it, index);
	_data.insert(it, val);
    };
    
    T& operator[](size_t index) {
	return *_data[index];
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
    
private:
	std::vector<T*> _data;    
};
