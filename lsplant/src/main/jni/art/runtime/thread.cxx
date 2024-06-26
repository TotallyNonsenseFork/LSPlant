module;

#include "utils/hook_helper.hpp"

export module thread;

namespace lsplant::art {
export class Thread {
    CREATE_FUNC_SYMBOL_ENTRY(Thread *, CurrentFromGdb) {
        if (CurrentFromGdbSym) [[likely]]
            return CurrentFromGdbSym();
        else
            return nullptr;
    }

public:
    static Thread *Current() { return CurrentFromGdb(); }

    static bool Init(const HookHandler &handler) {
        if (!RETRIEVE_FUNC_SYMBOL(CurrentFromGdb, "_ZN3art6Thread14CurrentFromGdbEv"))
            [[unlikely]] {
            return false;
        }
        return true;
    }
};
}  // namespace lsplant::art
