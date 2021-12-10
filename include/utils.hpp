
#include "main.hpp"
void debug(const char *color = BOLDCYAN);
namespace ft
{
	template <typename T>
	T min(T a, T b) { return (a < b ? a : b); }

	template <typename T>
	T max(T a, T b) { return (b < a ? a : b); }
}
