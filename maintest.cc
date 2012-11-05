/* 
 * cpsc 2720 - Project - the main function for the test code
 */

#include <cppunit/ui/text/TestRunner.h>
//need to include a header file

int main() {
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(TestPhase::suite());
	runner.run();
	return 0;
}
