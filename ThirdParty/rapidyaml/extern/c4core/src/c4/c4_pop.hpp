#ifdef _C4_PUSH_HPP_ // this must match the include guard from c4_push

#include "c4/unrestrict.hpp"

#ifdef C4_WIN
#   include "c4/windows_pop.hpp"
#endif

#ifdef _MSC_VER
#   pragma warning(pop)
#endif

#undef _C4_PUSH_HPP_

#endif /* _C4_PUSH_HPP_ */
