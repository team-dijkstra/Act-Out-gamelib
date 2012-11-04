/* 
 * cpsc 2720 - Project - the main function for the test code
 */

#include <cppunit/ui/text/TestRunner.h>
//#include "TestTile.h"
//#include "TestBoard.h"

int main() {
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(TestPhase::suite());
	runner.run();
	return 0;
}
