add_rules("mode.debug", "mode.release")
add_requires("gtest")

target("base_test")
    set_kind("binary")
    add_includedirs("src/base")
    add_files("src/test/base_test.cpp")
    add_files("src/base/base.c")
    add_packages("gtest")
