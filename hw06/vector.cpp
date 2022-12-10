#include "vector.h"

#include <iterator>


namespace linalg {
auto operator<<(std::ostream& ostr, const Vector& x) -> std::ostream&
{
    ostr << "[ ";
    std::copy(x.begin(), x.end(), std::ostream_iterator<float>(ostr, " "));
    ostr << "]";
    return ostr;
}

auto min(const Vector& x) -> float
{
    if (x.size() == 0) {
        throw std::invalid_argument("invalid arguments");
    }
    return *min_element(x.begin(), x.end());
}
auto max(const Vector& x) -> float
{
    if (x.size() == 0) {
        throw std::invalid_argument("invalid arguments");
    }
    return *max_element(x.begin(), x.end());
}
auto argmin(const Vector& x) -> std::size_t
{
    if (x.size() == 0) {
        throw std::invalid_argument("invalid arguments");
    }
    return min_element(x.begin(), x.end()) - x.begin();
}
auto argmax(const Vector& x) -> std::size_t
{
    if (x.size() == 0) {
        throw std::invalid_argument("invalid arguments");
    }
    return max_element(x.begin(), x.end()) - x.begin();
}

auto non_zeros(const Vector& x) -> std::size_t
{
    return x.size() - std::count(x.begin(), x.end(), 0);
}
auto sum(const Vector& x) -> float
{
    float result = 0;
    for (auto tmp : x) {
        result += tmp;
    }
    return result;
}
auto prod(const Vector& x) -> float
{
    float result = 1;
    for (auto tmp : x) {
        result *= tmp;
    }
    return result;
}
auto dot(const Vector& x, const Vector& y) -> float
{
    if (x.size() != y.size()) {
        throw std::invalid_argument("invalid arguments");
    }
    float result = 0;
    for (auto i = 0; i < x.size(); i++) {
        result += x[i] * y[i];
    }
    return result;
}
auto norm(const Vector& x) -> float
{
    float result = 0;
    for (auto i = 0; i < x.size(); i++) {
        result += x[i] * x[i];
    }
    return result;
}
auto normalize(Vector& x) -> void
{
    float tmp = std::sqrt(norm(x));
    x /= tmp;
}
auto normalized(const Vector& x) -> Vector
{
    float  tmp  = std::sqrt(norm(x));
    size_t size = x.size();
    Vector ans(size);
    for (std::size_t i = 0; i < x.size(); ++i) {
        ans[i] = x[i];
    }
    return ans /= tmp;
}
auto floor(const Vector& x) -> Vector
{
    size_t size = x.size();
    Vector ans(size);
    for (auto i = 0; i < size; i++) {
        ans[i] = std::floor(x[i]);
    }
    return ans;
}
auto ceil(const Vector& x) -> Vector
{
    size_t size = x.size();
    Vector ans(size);
    for (auto i = 0; i < size; i++) {
        ans[i] = std::ceil(x[i]);
    }
    return ans;
}
auto operator+(const Vector& x) -> Vector
{
    return x;
}
auto operator-(const Vector& x) -> Vector
{
    return -x;
}
auto operator+(const Vector& x, const Vector& y) -> Vector
{
    Vector ans(x.size());
    for (std::size_t i = 0; i < x.size(); ++i) {
        ans[i] = x[i] + y[i];
    }
    return ans;
}
auto operator-(const Vector& x, const Vector& y) -> Vector
{
    Vector ans(x.size());
    for (std::size_t i = 0; i < x.size(); ++i) {
        ans[i] = x[i] - y[i];
    }
    return ans;
}
auto operator+(const Vector& x, float val) -> Vector
{
    Vector ans(x.size());
    for (std::size_t i = 0; i < x.size(); ++i) {
        ans[i] = x[i] + val;
    }
    return ans;
}
auto operator-(const Vector& x, float val) -> Vector
{
    Vector ans(x.size());
    for (std::size_t i = 0; i < x.size(); ++i) {
        ans[i] = x[i] - val;
    }
    return ans;
}
auto operator*(const Vector& x, float val) -> Vector
{
    Vector ans(x.size());
    for (std::size_t i = 0; i < x.size(); ++i) {
        ans[i] = x[i] * val;
    }
    return ans;
}
auto operator/(const Vector& x, float val) -> Vector
{
    Vector ans(x.size());
    for (std::size_t i = 0; i < x.size(); ++i) {
        ans[i] = x[i] / val;
    }
    return ans;
}
auto operator+(float val, const Vector& x) -> Vector
{
    Vector ans(x.size());
    for (std::size_t i = 0; i < x.size(); ++i) {
        ans[i] = x[i] + val;
    }
    return ans;
}
auto operator-(float val, const Vector& x) -> Vector
{
    Vector ans(x.size());
    for (std::size_t i = 0; i < x.size(); ++i) {
        ans[i] = val - x[i];
    }
    return ans;
}
auto operator*(float val, const Vector& x) -> Vector
{
    Vector ans(x.size());
    for (std::size_t i = 0; i < x.size(); ++i) {
        ans[i] = x[i] * val;
    }
    return ans;
}
// Define the Vector Functions

// 默认构造函数不用构造

Vector::Vector(std::size_t n)
{
    data_ = std::vector<float>(n);
}

Vector::Vector(std::size_t n, float val)
{
    data_ = std::vector<float>(n, val);
}
auto Vector::operator=(float val) -> Vector&
{
    for (auto i = 0; i < data_.size(); i++) {
        data_[i] = val;
    }
    return *this;
}
Vector::Vector(std::initializer_list<float> list)
{
    for (float tmp : list) {
        data_.push_back(tmp);
    }
}

auto Vector::assign(float val) -> void
{
    // TODO: 确认引用的问题
    // for (float& tmp : data_) {
    //     tmp = val;
    // }
    for (auto i = 0; i < this->data_.size(); i++) {
        data_[i] = val;
    }
}

// 需要输入 void 返回类型
auto Vector::assign(Vector v) -> void
{
    for (auto i = 0; i < this->data_.size(); i++) {
        data_[i] = v[i];
    }
}

auto Vector::size() const -> std::size_t
{
    return data_.size();
}

// 内部定义的返回类型需要 Vector::
auto Vector::begin() -> iterator
{
    return data_.begin();
}

auto Vector::end() -> iterator
{
    return data_.end();
}

auto Vector::begin() const -> const_iterator
{
    return data_.begin();
}

auto Vector::end() const -> const_iterator
{
    return data_.end();
}

auto Vector::cbegin() const -> const_iterator
{
    return data_.begin();
}

auto Vector::cend() const -> const_iterator
{
    return data_.end();
}

auto Vector::operator[](int idx) -> float&
{
    std::size_t size = this->size();
    if (idx < size) {
        idx += size;
    }
    return data_[idx];
}

auto Vector::operator[](int idx) const -> const float&
{
    std::size_t size = this->size();
    return data_[idx % size];
}

auto Vector::coeff(int idx) -> float&
{
    std::size_t size = this->size();
    if (idx < 0 || idx >= size) {
        throw std::out_of_range("out_of_range");
    }
    return data_[idx % size];
}

auto Vector::coeff(int idx) const -> const float&
{
    std::size_t size = this->size();
    if (idx < 0 || idx >= size) {
        throw std::out_of_range("out_of_range");
    }
    return data_[idx % size];
}

auto Vector::operator+=(float val) -> Vector&
{
    for (auto i = 0; i < this->size(); i++) {
        data_[i] += val;
    }
    return *this;
}


auto Vector::operator-=(float val) -> Vector&
{
    for (auto i = 0; i < this->size(); i++) {
        data_[i] -= val;
    }
    return *this;
}

auto Vector::operator*=(float val) -> Vector&
{
    for (auto i = 0; i < this->size(); i++) {
        data_[i] *= val;
    }
    return *this;
}

auto Vector::operator/=(float val) -> Vector&
{
    for (auto i = 0; i < this->size(); i++) {
        data_[i] /= val;
    }
    return *this;
}

auto Vector::operator+=(const Vector& y) -> Vector&
{
    for (auto i = 0; i < this->size(); i++) {
        data_[i] += y[i];
    }
    return *this;
}

auto Vector::operator-=(const Vector& y) -> Vector&
{
    for (auto i = 0; i < this->size(); i++) {
        data_[i] -= y[i];
    }
    return *this;
}



}   // namespace linalg