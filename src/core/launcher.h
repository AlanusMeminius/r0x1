#pragma once
#include <memory>

namespace Core {

class Launcher {
   public:
    Launcher(int argc, char *argv[]);
    static std::unique_ptr<Launcher> Create(int argc, char *argv[]);
    virtual ~Launcher() = default;
    static void initHighDpi();
    int exec();
   private:
   private:
    int _argc;
    char **_argv;
};
}// namespace Core
