function(MAKE_LIBRARY LIB_NAME)
	set(library_name "${LIB_NAME}")
	set(dependencies ${ARGN})
	message("Adding Library '${library_name}'")
	
	file( GLOB public_interface RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
		*.h 
		*.hpp
	)

	file( GLOB protected_interface RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
		internal/*.h 
		internal/*.hpp
	)

	file( GLOB implementation RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
		src/*.h 
		src/*.hpp 
		src/*.c 
		src/*.cpp
	)

	add_library(${library_name} STATIC
		${public_interface} 
		${protected_interface} 
		${implementation}
	)

	if(${dependencies})
		add_dependencies(${library_name} ${dependencies})
	endif()

	# build a testing library that holds mocks and test dummies
	set(testing_lib "") 
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/testing/")
		set(testing_lib "${library_name}-Testing")	
		message("Adding Library '${testing_lib}'")

		file( GLOB testing_interface RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
			testing/*.h 
			testing/*.hpp
		)

		file( GLOB testing_impl RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
			testing/*.c 
			testing/*.cpp
		)

		add_library(${testing_lib}
			${testing_interface} 
			${testing_impl}
		)

		add_dependencies(${testing_lib} ${library_name})
	endif()


	# build a unit test executable
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/")
        find_package(UnitTest++ REQUIRED)
        include_directories(${UNITTEST++_INCLUDE_DIRS})

		set(executable_name "${library_name}-UT")
		message("Adding Executable '${executable_name}'")

		file( GLOB ut_interface ${CMAKE_CURRENT_SOURCE_DIR} 
			unit_tests/*.h 
			unit_tests/*.hpp
		)

		file( GLOB ut_implementation ${CMAKE_CURRENT_SOURCE_DIR}
			unit_tests/*.c
			unit_tests/*.cpp
		)

		add_executable("${executable_name}" 
			${ut_interface} 
			${ut_implementation}
		)

		add_dependencies("${executable_name}" 
			${library_name} 
			${testing_library}
		)

		target_link_libraries("${executable_name}"
			 ${library_name}
			 ${testing_lib}
			 ${ARGN}
			 ${UNITTEST++_LIBRARIES}
		)

		# run the UT as a post build event
        if(WIN32)
		    add_custom_command(TARGET "${executable_name}" POST_BUILD COMMAND @echo off)
        endif()
		add_custom_command(TARGET "${executable_name}" POST_BUILD COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${executable_name}")
	endif()
endfunction()
