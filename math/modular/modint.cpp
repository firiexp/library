#ifndef FIRIEXP_LIBRARY_UTIL_MODINT_CPP
#define FIRIEXP_LIBRARY_UTIL_MODINT_CPP

#include "modint_base.cpp"

#ifndef FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED
using mint = modint<MOD>;
#define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED
#else
static_assert(mint::get_mod() == MOD, "mint is already defined with a different modulus");
#endif

/**
 * @brief modint(固定MOD)
 */

#endif
