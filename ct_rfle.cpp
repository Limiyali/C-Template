#include <iostream>
#include <set>
#include <cassert>
#include <sstream>
#include <type_traits>
#include "utils/type.h"
using namespace std;

struct AnyType {
  template <typename T> operator T();
};

// template <typename T> consteval size_t CountMember(auto &&...Args) {
//   if constexpr (!requires { T{Args...}; }) { // (1)
//     return sizeof...(Args) - 1;
//   } else {
//     return CountMember<T>(Args..., AnyType{}); // (2)
//   }
// }

template<typename T, typename = void, typename... Ts>
struct CountMember{
  const static size_t value = sizeof...(Ts) -1 ;
};

template<typename T, typename... Ts>
struct CountMember<T,std::void_t<decltype(T{Ts{} ...})>,Ts...>{
  const static size_t value = CountMember<T,void,Ts...,AnyType>::value;
};

template<typename T, typename = void, typename... Ts>
struct my_ptr{
  const static size_t value =0;
};

template<typename T, typename... Ts>
struct my_ptr<T,void,Ts...>{
  const static size_t value = 1;
};

#define REPEAT_0(func, i, arg)
#define REPEAT_1(func, i, arg)        func(i, arg)
#define REPEAT_2(func, i, arg, ...)   func(i, arg) REPEAT_1(func, i + 1, __VA_ARGS__)
#define REPEAT_3(func, i, arg, ...)   func(i, arg) REPEAT_2(func, i + 1, __VA_ARGS__)
#define REPEAT_4(func, i, arg, ...)   func(i, arg) REPEAT_3(func, i + 1, __VA_ARGS__)
#define REPEAT_5(func, i, arg, ...)   func(i, arg) REPEAT_4(func, i + 1, __VA_ARGS__)
#define REPEAT_6(func, i, arg, ...)   func(i, arg) REPEAT_5(func, i + 1, __VA_ARGS__)
#define REPEAT_7(func, i, arg, ...)   func(i, arg) REPEAT_6(func, i + 1, __VA_ARGS__)
#define REPEAT_8(func, i, arg, ...)   func(i, arg) REPEAT_7(func, i + 1, __VA_ARGS__)
#define REPEAT_9(func, i, arg, ...)   func(i, arg) REPEAT_8(func, i + 1, __VA_ARGS__)
#define REPEAT_10(func, i, arg, ...)  func(i, arg) REPEAT_9(func, i + 1, __VA_ARGS__)
#define REPEAT_11(func, i, arg, ...)  func(i, arg) REPEAT_10(func, i + 1, __VA_ARGS__)
#define REPEAT_12(func, i, arg, ...)  func(i, arg) REPEAT_11(func, i + 1, __VA_ARGS__)
#define REPEAT_13(func, i, arg, ...)  func(i, arg) REPEAT_12(func, i + 1, __VA_ARGS__)
#define REPEAT_14(func, i, arg, ...)  func(i, arg) REPEAT_13(func, i + 1, __VA_ARGS__)
#define REPEAT_15(func, i, arg, ...)  func(i, arg) REPEAT_14(func, i + 1, __VA_ARGS__)
#define REPEAT_16(func, i, arg, ...)  func(i, arg) REPEAT_15(func, i + 1, __VA_ARGS__)
#define REPEAT_17(func, i, arg, ...)  func(i, arg) REPEAT_16(func, i + 1, __VA_ARGS__)
#define REPEAT_18(func, i, arg, ...)  func(i, arg) REPEAT_17(func, i + 1, __VA_ARGS__)
#define REPEAT_19(func, i, arg, ...)  func(i, arg) REPEAT_18(func, i + 1, __VA_ARGS__)
#define REPEAT_20(func, i, arg, ...)  func(i, arg) REPEAT_19(func, i + 1, __VA_ARGS__)
#define REPEAT_21(func, i, arg, ...)  func(i, arg) REPEAT_20(func, i + 1, __VA_ARGS__)
#define REPEAT_22(func, i, arg, ...)  func(i, arg) REPEAT_21(func, i + 1, __VA_ARGS__)
#define REPEAT_23(func, i, arg, ...)  func(i, arg) REPEAT_22(func, i + 1, __VA_ARGS__)
#define REPEAT_24(func, i, arg, ...)  func(i, arg) REPEAT_23(func, i + 1, __VA_ARGS__)
#define REPEAT_25(func, i, arg, ...)  func(i, arg) REPEAT_24(func, i + 1, __VA_ARGS__)
#define REPEAT_26(func, i, arg, ...)  func(i, arg) REPEAT_25(func, i + 1, __VA_ARGS__)
#define REPEAT_27(func, i, arg, ...)  func(i, arg) REPEAT_26(func, i + 1, __VA_ARGS__)
#define REPEAT_28(func, i, arg, ...)  func(i, arg) REPEAT_27(func, i + 1, __VA_ARGS__)
#define REPEAT_29(func, i, arg, ...)  func(i, arg) REPEAT_28(func, i + 1, __VA_ARGS__)
#define REPEAT_30(func, i, arg, ...)  func(i, arg) REPEAT_29(func, i + 1, __VA_ARGS__)
#define REPEAT_31(func, i, arg, ...)  func(i, arg) REPEAT_30(func, i + 1, __VA_ARGS__)
#define REPEAT_32(func, i, arg, ...)  func(i, arg) REPEAT_31(func, i + 1, __VA_ARGS__)
#define REPEAT_33(func, i, arg, ...)  func(i, arg) REPEAT_32(func, i + 1, __VA_ARGS__)
#define REPEAT_34(func, i, arg, ...)  func(i, arg) REPEAT_33(func, i + 1, __VA_ARGS__)
#define REPEAT_35(func, i, arg, ...)  func(i, arg) REPEAT_34(func, i + 1, __VA_ARGS__)
#define REPEAT_36(func, i, arg, ...)  func(i, arg) REPEAT_35(func, i + 1, __VA_ARGS__)
#define REPEAT_37(func, i, arg, ...)  func(i, arg) REPEAT_36(func, i + 1, __VA_ARGS__)
#define REPEAT_38(func, i, arg, ...)  func(i, arg) REPEAT_37(func, i + 1, __VA_ARGS__)
#define REPEAT_39(func, i, arg, ...)  func(i, arg) REPEAT_38(func, i + 1, __VA_ARGS__)
#define REPEAT_40(func, i, arg, ...)  func(i, arg) REPEAT_39(func, i + 1, __VA_ARGS__)
#define REPEAT_41(func, i, arg, ...)  func(i, arg) REPEAT_40(func, i + 1, __VA_ARGS__)
#define REPEAT_42(func, i, arg, ...)  func(i, arg) REPEAT_41(func, i + 1, __VA_ARGS__)
#define REPEAT_43(func, i, arg, ...)  func(i, arg) REPEAT_42(func, i + 1, __VA_ARGS__)
#define REPEAT_44(func, i, arg, ...)  func(i, arg) REPEAT_43(func, i + 1, __VA_ARGS__)
#define REPEAT_45(func, i, arg, ...)  func(i, arg) REPEAT_44(func, i + 1, __VA_ARGS__)
#define REPEAT_46(func, i, arg, ...)  func(i, arg) REPEAT_45(func, i + 1, __VA_ARGS__)
#define REPEAT_47(func, i, arg, ...)  func(i, arg) REPEAT_46(func, i + 1, __VA_ARGS__)
#define REPEAT_48(func, i, arg, ...)  func(i, arg) REPEAT_47(func, i + 1, __VA_ARGS__)
#define REPEAT_49(func, i, arg, ...)  func(i, arg) REPEAT_48(func, i + 1, __VA_ARGS__)
#define REPEAT_50(func, i, arg, ...)  func(i, arg) REPEAT_49(func, i + 1, __VA_ARGS__)
#define REPEAT_51(func, i, arg, ...)  func(i, arg) REPEAT_50(func, i + 1, __VA_ARGS__)
#define REPEAT_52(func, i, arg, ...)  func(i, arg) REPEAT_51(func, i + 1, __VA_ARGS__)
#define REPEAT_53(func, i, arg, ...)  func(i, arg) REPEAT_52(func, i + 1, __VA_ARGS__)
#define REPEAT_54(func, i, arg, ...)  func(i, arg) REPEAT_53(func, i + 1, __VA_ARGS__)
#define REPEAT_55(func, i, arg, ...)  func(i, arg) REPEAT_54(func, i + 1, __VA_ARGS__)
#define REPEAT_56(func, i, arg, ...)  func(i, arg) REPEAT_55(func, i + 1, __VA_ARGS__)
#define REPEAT_57(func, i, arg, ...)  func(i, arg) REPEAT_56(func, i + 1, __VA_ARGS__)
#define REPEAT_58(func, i, arg, ...)  func(i, arg) REPEAT_57(func, i + 1, __VA_ARGS__)
#define REPEAT_59(func, i, arg, ...)  func(i, arg) REPEAT_58(func, i + 1, __VA_ARGS__)
#define REPEAT_60(func, i, arg, ...)  func(i, arg) REPEAT_59(func, i + 1, __VA_ARGS__)
#define REPEAT_61(func, i, arg, ...)  func(i, arg) REPEAT_60(func, i + 1, __VA_ARGS__)
#define REPEAT_62(func, i, arg, ...)  func(i, arg) REPEAT_61(func, i + 1, __VA_ARGS__)
#define REPEAT_63(func, i, arg, ...)  func(i, arg) REPEAT_62(func, i + 1, __VA_ARGS__)
#define REPEAT_64(func, i, arg, ...)  func(i, arg) REPEAT_63(func, i + 1, __VA_ARGS__)

#define GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,    \
                    _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24,     \
                    _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,     \
                    _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,     \
                    _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,     \
                    _58, _59, _60, _61, _62, _63, _64, n, ...)                 \
  n

#define GET_ARG_COUNT(...)                                                     \
  GET_NTH_ARG(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, \
              51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36,  \
              35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20,  \
              19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,  \
              1)

#define STR(x) #x
#define CONCATE(x, y) x ## y
#define STRING(x) STR(x)
#define PARE(...) __VA_ARGS__
#define EAT(...)
#define PAIR(x) PARE x // PAIR((int) x) => PARE(int) x => int x
#define STRIP(x) EAT x // STRIP((int) x) => EAT(int) x => x
#define PASTE(x, y) CONCATE(x, y)


#define FIELD_EACH(i, arg)                                                     \
  PAIR(arg);                                                                   \
  template <typename T> struct FIELD<T, i> {                                   \
    T &obj;                                                                    \
    FIELD(T &obj) : obj(obj) {}                                                \
    auto value() -> decltype(auto) { return (obj.STRIP(arg)); }                \
    static constexpr const char *name() { return STRING(STRIP(arg)); }         \
  };

#define DEFINE_STRUCT(st, ...)                                                \
struct st {                                                                   \
    template <typename, size_t> struct FIELD;                                 \
    static constexpr size_t _field_count_ = GET_ARG_COUNT(__VA_ARGS__);       \
    PASTE(REPEAT_, GET_ARG_COUNT(__VA_ARGS__)) (FIELD_EACH, 0, __VA_ARGS__) \
};                                                                            \

template<typename T,typename F,size_t... Is>
inline constexpr void forEach(T&&obj, F&& f,std::index_sequence<Is...>){
    using TDECAY = std::decay_t<T>;
    (void(f(typename TDECAY::template FIELD<TDECAY,Is>(obj).name(),
            typename TDECAY::template FIELD<TDECAY,Is>(obj).value())), ...);
}
template<typename T,typename F>
inline constexpr void forEach(T&& obj, F&& f){
        forEach(std::forward<T>(obj),
            std::forward<F>(f),
            std::make_index_sequence<std::decay_t<T>::_field_count_>{});
}

template<typename T>
void dumpObj(T&& obj, const char* fieldName = "", int depth = 0) {
    auto indent = [depth] {
        for (int i = 0; i < depth; ++i) {
            cout << "";
        }
    };

    if constexpr(std::is_class_v<std::decay_t<T>>) { // (1)
        indent();
        cout << fieldName << (*fieldName ? ": {" : "{") << endl;
        forEach(obj, [depth](auto&& fieldName, auto&& value) {
            dumpObj(value, fieldName, depth + 1);
        });
        indent();
        cout << "}" << (depth == 0 ? "" : ",") << endl;
    } else { // (2)
        indent();
        cout << fieldName << ":" << obj << "," << endl;
    }
}

template<typename T>
void serializeObj(std::ostream& out, T&& obj,
        const char* fieldName = "", int depth = 0) {
    auto indent = [&] {
        for (int i = 0; i < depth; ++i)
        { out << "    "; }
    };

    if constexpr(std::is_class_v<std::decay_t<T>>) {
        indent();
        out << fieldName << (*fieldName ? ": {" : "{") << std::endl;
        forEach(std::forward<T>(obj),
                [&](auto&& fieldName, auto&& value)
                { serializeObj(out, value, fieldName, depth + 1); });
        indent();
        out << "}" << std::endl;
    } else {
        indent();
        out << fieldName << ": " << obj << std::endl;
    }
}

template<typename T>
void deserializeObj(std::istream& in, T&& obj,
        const char* fieldName = "") {
    cout<<fieldName<<endl;
    if constexpr(std::is_class_v<std::decay_t<T>>) {
        std::string token;
        in >> token; // eat '{'
        if (*fieldName) {
            in >> token; // WARNING: needs check fieldName valid
        }

        forEach(std::forward<T>(obj),
                [&](auto&& fieldName, auto&& value)
                { deserializeObj(in, value, fieldName); });

        in >> token; // eat '}'
    } else {
        if (*fieldName) {
            std::string token;
            in >> token; // WARNING: needs check fieldName valid
        }
        in >> obj; // dump value
    }
}


template<typename T, typename = void>
struct IsReflected: std::false_type { };

template<typename T>
struct IsReflected<T,
    std::void_t<decltype(&T::_field_count_)>>
    : std::true_type { };

template<typename T>
constexpr static bool IsReflected_v =
    IsReflected<T>::value;

DEFINE_STRUCT(Point, (double) x, (double) y)

DEFINE_STRUCT(Rect,
        (Point) p1,
        (Point) p2,
        (uint32_t) color)

int main() {
//   struct Test {
//     int a;
//     int b;
//     int c;
//     int d;
//   };
//   printf("%zu\n", CountMember<Test>::value);
//   cout << GET_ARG_COUNT(a) << endl;
// cout<<GET_ARG_COUNT((double) x , (double)y)<<endl;
std::stringstream result;
Rect rect {
            {1.2, 3.4},
            {5.6, 7.8},
            12345678,
        };
Rect rect2;
serializeObj(result,rect);
cout<<result.str()<<endl;
deserializeObj(result,rect2);
std::stringstream result2;
serializeObj(result2,rect2);
cout<<result2.str()<<endl;
}
