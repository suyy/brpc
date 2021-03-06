// Copyright (c) 2014 Baidu, Inc.

#include <sys/resource.h>
#include <gtest/gtest.h>
#include <gflags/gflags.h>
#include "butil/base_switches.h"
#include "butil/at_exit.h"
#include "test/multiprocess_func_list.h"

// Disable coredumps by default to avoid generating a lot of coredumps
// after running death tests.
DEFINE_bool(disable_coredump, true, "Never core dump");

int main(int argc, char** argv) {
    butil::AtExitManager at_exit;
    testing::InitGoogleTest(&argc, argv);
    
    google::ParseCommandLineFlags(&argc, &argv, true);
    if (FLAGS_disable_coredump) {
        rlimit core_limit;
        core_limit.rlim_cur = 0;
        core_limit.rlim_max = 0;
        setrlimit(RLIMIT_CORE, &core_limit);
    }
#if !BRPC_WITH_GLOG
    CHECK(!google::SetCommandLineOption("crash_on_fatal_log", "true").empty());
#endif
    return RUN_ALL_TESTS();
}
