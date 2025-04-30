/*
 *
 *  DO NOT MODIFY THIS FILE
 *
 */

#include "pch.h"
#include "test_config.h"

#include "Ailment.h"

#if TEST_AILMENT_CONSTRUCTOR
TEST(Ailment, Constructor)
{
	const std::string name = "Heart Attack";
	const int severity = 10;
	const int time_sensitivity = 1;
	const int contagiousness = 0;
	Ailment ailment(name, severity, time_sensitivity, contagiousness);

	//verify all the members where set correctly
	ASSERT_EQ(ailment.get_name(), name);
	ASSERT_EQ(ailment.get_severity(), severity);
	ASSERT_EQ(ailment.get_time_sensitivity(), time_sensitivity);
	ASSERT_EQ(ailment.get_contagiousness(), contagiousness);
}
#endif