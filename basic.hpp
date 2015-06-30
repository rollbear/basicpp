//
// Originally written by BjÃrn Fahller (bjorn@fahller.se)
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

  void type_mismatch() {
    std::cout << "Type mismatch error\n";
    exit(1);
  }

  void array_out_of_bounds() {
    std::cout << "Array out of bounds error\n";
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

  class array
  {
  public:
    array(int _size)
      : elements(_size)
    {}

    variant& operator()(const variant &indexvar) {
      if (!indexvar.isnum)
        type_mismatch();

      int index = indexvar.numval - 1;
      if (index < 0 || index >= elements.size())
        array_out_of_bounds();

      return elements[index];
    }
  private:
    std::vector<variant> elements;
  };

  class printer
  {
    public:
    printer &operator,(const char *s) {
      std::cout  << s;
      return *this;
    }

    const printer &operator,(const variant &v) const {
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
#define RND(x) (double) (rand() & 0xffff);

} // namespace basic
