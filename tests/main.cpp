#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

int main(int argc, char *argv[])
{
    return Catch::Session().run(argc, argv);
}
