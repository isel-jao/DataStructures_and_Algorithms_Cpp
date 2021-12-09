
#include "main.hpp"

void debug(const char *color = BOLDCYAN);
namespace ft
{
	template <typename T>
	T min(T a, T b) { return (a < b ? a : b); }

	template <typename T, typename... Ts>
	T min(T val1, T val2, Ts &&...vs)
	{
		return val1 < val2 ? min(val1, std::forward<Ts>(vs)...) : min(val2, std::forward<Ts>(vs)...);
	}

	template <typename T>
	T max(T a, T b) { return (b < a ? a : b); }
}
