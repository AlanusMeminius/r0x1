#pragma once
#include <memory>

namespace Core {

class Launcher {
   public:
    Launcher(int argc, char *argv[]);
    static std::unique_ptr<Launcher> Create(int argc, char *argv[]);
    int exec();
    static void initHighDpi();
    virtual ~Launcher() = default;
   private:
    int _argc;
    char **_argv;
};
}// namespace Core
