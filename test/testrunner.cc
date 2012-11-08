#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(int argc, char ** argv) {
    bool status = true;

    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
        
    if (argc > 1) {
        /// \todo should there be an 'exit early' option if a test fails?
        for (int i = 1; i < argc; i++) {
            status = runner.run(argv[i], false) && status;
        }
    } else {
        status = runner.run("", false);
    }

    return (status ? 0: 1);
}
