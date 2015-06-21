//
// Originally written by BjÃrn Fahller (bjorn@fahller.se)
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

  template <typename T>
  class printer_h
  {
    using str = char const *;
  public:
    printer_h<str> operator,(str s) {
      std::cout << separator<T, str>::str() << s;
      return printer_h<str>();
    }
    template <typename U>
    printer_h<U> operator,(U const& u) const {
      std::cout << separator<T,U>::str() << u;
      return printer_h<U>();
    }
  };

  class printer
  {
    using str = char const;
  public:
    printer_h<str> operator,(str s) {
      std::cout  << s;
      return printer_h<str>();
    }
    template <typename T>
    printer_h<T> operator,(T const& t) const {
      std::cout << t;
      return printer_h<T>();
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
    template <typename T>
    input& operator,(T& t) {
      std::cin >> t;
      return *this;
    }
  };

#define INPUT basic::input(),
#define PRINT basic::printer(),
#define IF if (
#define THEN )
#define LET double
#define GOTO goto
#define FOR { double& for_loop_variable =
#define TO ;                                   \
           {                                   \
             jmp_buf for_loop_top;             \
             bool for_loop_exit = 0;           \
             while (!for_loop_exit)            \
             {                                 \
               if (setjmp(for_loop_top) == 0)  \
               {                               \
                 double for_loop_step=1;       \
                 double const for_loop_endval=
#define STEP ;              \
             for_loop_step=

#define NEXT for_loop_variable+=for_loop_step;                           \
             for_loop_exit=(  (   for_loop_step > 0                      \
                               && for_loop_variable > for_loop_endval)   \
                            ||(   for_loop_step < 0                      \
                               && for_loop_variable < for_loop_endval)); \
             longjmp(for_loop_top, 1);                                   \
             }                                                           \
           }                                                             \
         }                                                               \
       }

#define BEGIN {

#define END }

} // namespace basic
