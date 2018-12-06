add_library(printCodePass MODULE
	printCode.cpp
)

target_compile_features(printCodePass PRIVATE cxx_range_for cxx_auto_type)

set_target_properties(printCodePass PROPERTIES
	COMPILE_FLAGS "-fno-rtti"
)
