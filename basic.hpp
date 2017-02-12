//
// Originally written by Björn Fahller (bjorn@fahller.se)
// Modified by Jeff Bush
//
// No rights claimed. The sources are released to the public domain
//
// For license information, please refer to <http://unlicense.org>
//

#include <setjmp.h>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include <forward_list>
#include <vector>
#include <algorithm>
#include <numeric>

namespace basic {
  struct stack_frame { jmp_buf buf; };
  std::forward_list<stack_frame> stack;

#define GOSUB                                                           \
  if (!(setjmp((basic::stack.emplace_front(),basic::stack.front().buf)) \
        && (basic::stack.pop_front(),true)))                            \
    goto

#define RETURN if (basic::stack.empty()) return 0; longjmp(basic::stack.front().buf, 1)

  template <typename T, typename U>
  struct separator
  {
    static char const *str() { return ""; }
  };

  template <typename T>
  struct separator<T,T>
  {
    static char const *str() { return ","; }
  };

  inline void type_mismatch() {
    std::cout << "Type mismatch error\n";
    exit(1);
  }

  inline void array_out_of_bounds() {
    std::cout << "Array out of bounds error\n";
    exit(1);
  }

  inline void dimension_error() {
    std::cout << "Array Dimension error\n";
    exit(1);
  }

  inline void illegal_quantity_error() {
    std::cout << "Illegal quantity error\n";
    exit(1);
  }

  class variant
  {
  public:
    variant()
      : isnum(true),
        numval(0)
    {}

    variant(double _numval)
      : isnum(true),
        numval(_numval)
    {}

    variant(int _numval)
      : isnum(true),
        numval(_numval)
    {}

    variant(const std::string _strval)
      : isnum(false),
        strval(_strval)
    {}

    variant(const char *_strval)
      : isnum(false),
        strval(_strval)
    {}

    double numeric() const {
      if (!isnum)
        type_mismatch();
      return numval;
    }

    std::string string() const {
      if (isnum)
        type_mismatch();
      return strval;
    }
    variant toString() const {
      if (isnum)
        return variant(std::to_string(numval));
      else
        return *this;
    }

    variant toNum() const {
      if (!isnum)
        return variant(stod(strval));
      else
        return *this;
    }
    variant &operator=(const variant &copyfrom) {
      isnum = copyfrom.isnum;
      numval = copyfrom.numval;
      strval = copyfrom.strval;
      return *this;
    }

    // Note that strings in BASIC are 1 based, so subtract 1 from the left
    // index
    variant midStr(const variant &left, const variant &right) const {
      if (isnum || !left.isnum || !right.isnum)
        type_mismatch();

      return variant(strval.substr(int(left.numval) - 1, (int(right.numval) - int(left.numval) + 1)));
    }

    variant leftStr(const variant &count) const {
      if (isnum)
        type_mismatch();

      return variant(strval.substr(0, int(count.numval)));
    }

    variant rightStr(const variant &count) const {
      if (isnum)
        type_mismatch();

      return variant(strval.substr(strval.length() - int(count.numval) - 1, int(count.numval)));
    }

    variant strlen() const {
      if (isnum)
        type_mismatch();

      return variant((int)strval.length());
    }

    variant operator+(const variant op) const {
      if (isnum != op.isnum)
        type_mismatch();

      if (isnum)
        return variant(numval + op.numval);
      else
        return variant(strval + op.strval);
    }

    variant operator-(const variant op) const {
      if (!isnum || !op.isnum)
        type_mismatch();

      return variant(numval - op.numval);
    }

    variant operator*(const variant op) const {
      if (!isnum || !op.isnum)
        type_mismatch();

      return variant(numval * op.numval);
    }

    variant operator/(const variant op) const {
      if (!isnum || !op.isnum)
        type_mismatch();

      return variant(numval / op.numval);
    }

    bool operator>(const variant op) const {
      if (isnum != op.isnum)
        type_mismatch();

      if (isnum)
        return numval > op.numval;
      else
        return strval > op.strval;
    }

    bool operator>=(const variant op) const {
      if (isnum != op.isnum)
        type_mismatch();

      if (isnum)
        return numval >= op.numval;
      else
        return strval >= op.strval;
    }

    bool operator<(const variant op) const {
      if (isnum != op.isnum)
        type_mismatch();

      if (isnum)
        return numval < op.numval;
      else
        return strval < op.strval;
    }

    bool operator<=(const variant op) const {
      if (isnum != op.isnum)
        type_mismatch();

      if (isnum)
        return numval <= op.numval;
      else
        return strval <= op.strval;
    }

    bool operator!=(const variant op) const {
      if (isnum != op.isnum)
        type_mismatch();

      if (isnum)
        return numval != op.numval;
      else
        return strval != op.strval;
    }

    bool operator==(const variant op) const {
      if (isnum != op.isnum)
        type_mismatch();

      if (isnum)
        return numval == op.numval;
      else
        return strval == op.strval;
    }

    bool isnum;
    double numval;
    std::string strval;
  };

  template <typename T>
  typename std::enable_if<std::is_constructible<variant, T>::value && !std::is_same<typename std::decay<T>::type, variant>::value, variant>::type
  operator+(T&& t, variant const& p)
  {
    return variant(std::forward<T>(t)) + p;
  }

  template <typename T>
  typename std::enable_if<std::is_constructible<variant, T>::value && !std::is_same<typename std::decay<T>::type, variant>::value, variant>::type
  operator-(T&& t, variant const& p)
  {
    return variant(std::forward<T>(t)) - p;
  }

  template <typename T>
  typename std::enable_if<std::is_constructible<variant, T>::value && !std::is_same<typename std::decay<T>::type, variant>::value, variant>::type
  operator*(T&& t, variant const& p)
  {
    return variant(std::forward<T>(t)) * p;
  }

  template <typename T>
  typename std::enable_if<std::is_constructible<variant, T>::value && !std::is_same<typename std::decay<T>::type, variant>::value, variant>::type
  operator/(T&& t, variant const& p)
  {
    return variant(std::forward<T>(t)) / p;
  }

  template <typename T>
  typename std::enable_if<std::is_constructible<variant, T>::value && !std::is_same<typename std::decay<T>::type, variant>::value, bool>::type
  operator==(T&& t, variant const& p)
  {
    return variant(std::forward<T>(t)) == p;
  }

  template <typename T>
  struct is_dimmable
  {
    using DT = typename std::decay<T>::type;
    static constexpr bool value = std::is_integral<DT>::value || std::is_same<DT, variant>::value;
  };

  template <template <typename> class pred, typename ... T>
  struct all_are
  {
    static constexpr bool value = true;
  };

  template <template <typename> class pred, typename H, typename ... T>
  struct all_are<pred, H, T...>
  {
    static constexpr bool value = pred<H>::value && all_are<pred, T...>::value;
  };

  template <typename T>
  T numeric_value(T t) { return t; }

  inline
  long numeric_value(const variant& v) { return long(v.numeric()); }

  class array
  {
  public:
    template <typename ... T, typename = typename std::enable_if<all_are<is_dimmable, T...>::value>::type>
    array(T const & ... t)
      : dimensions{1LU+numeric_value(t)..., 1LU},
        elements(std::accumulate(std::begin(dimensions),
                                 std::end(dimensions),
                                 1U,
                                 [](std::size_t i, std::size_t j){ return i*j;}))
    {}

    template <typename ... T>
    typename std::enable_if<all_are<is_dimmable, T...>::value, variant&>::type
    operator()(T const& ... t) {
      if (sizeof...(t) != dimensions.size() - 1)
        dimension_error();

      long indexes[] { long(numeric_value(t))... };

      auto i = sizeof...(t);
      size_t mul = 1U;
      size_t idx = 0U;
      while (i--)
      {
        if (indexes[i] < 0 || indexes[i] >= dimensions[i])
          array_out_of_bounds();
        idx += indexes[i]*mul;
        mul = dimensions[i];
      }

      return elements[idx];
    }
  private:
    std::vector<std::size_t> dimensions;
    std::vector<variant> elements;
  };

  class printer
  {
    public:
    printer &operator,(const char *s) {
      std::cout  << s;
      return *this;
    }

    printer &operator,(const variant &v) {
      if (v.isnum)
        std::cout << v.numval;
      else
        std::cout << v.strval;

      return *this;
    }

    ~printer() { std::cout << std::endl; }
  };

  class input
  {
  public:
    input& operator,(char const *s) {
      std::cout << s << std::flush;
      return *this;
    }

    input& operator,(variant& v) {
      if (v.isnum)
        std::cin >> v.numval;
      else
        std::cin >> v.strval;

      return *this;
    }
  };

  template <typename T>
  variant to_char_str(T const& t)
  {
    auto n = numeric_value(t);
    char a[] = { char(n), '\0' };
    return variant{a};
  }

  template <std::size_t N>
  inline variant to_asc_val(char const (&a)[N])
  {
    if (N < 2) illegal_quantity_error();
    return variant(double(a[0]));
  }

  inline variant to_asc_val(variant const& v)
  {
    auto s = v.string();
    if (s.empty()) illegal_quantity_error();
    return variant(double(s[0]));
  }

#define INPUT basic::input(),
#define PRINT basic::printer(),
#define IF if (
#define THEN )
#define LET basic::variant
#define GOTO goto
#define FOR { basic::variant& for_loop_variable =
#define TO ;                                   \
           {                                   \
             jmp_buf for_loop_top;             \
             bool for_loop_exit = false;           \
             while (!for_loop_exit)            \
             {                                 \
               if (setjmp(for_loop_top) == 0)  \
               {                               \
                 basic::variant for_loop_step=1;       \
                 basic::variant const for_loop_endval=
#define STEP ;              \
             for_loop_step=

#define NEXT for_loop_variable=for_loop_variable+for_loop_step;                           \
             for_loop_exit=(  (   for_loop_step > 0                      \
                               && for_loop_variable > for_loop_endval)   \
                            ||(   for_loop_step < 0                      \
                               && for_loop_variable < for_loop_endval)); \
             longjmp(for_loop_top, 1);                                   \
             }                                                           \
           }                                                             \
         }                                                               \
       }

#define END exit(0)
#define VAL(x) x.toNum()
#define STR(x) x.toString()
#define MID$(str, left, right) str.midStr(left, right)
#define LEFT$(str, count) str.leftStr(count)
#define RIGHT$(str, count) str.rightStr(count)
#define LEN(str) str.strlen()
#define DIM basic::array
#define RND(x) ((rand() & 0xffff)/65535.0)
#define INT(x) static_cast<int>(basic::numeric_value(x))
#define CHR$(num) basic::to_char_str(num)
#define ASC(str) basic::to_asc_val(str)
} // namespace basic
