
# Check if examples are enabled
if(NOT OPTION_BUILD_EXAMPLES)
    return()
endif()

# Example applications
add_subdirectory(logging)
add_subdirectory(properties)
add_subdirectory(propertyeditors)
add_subdirectory(propertygui)
add_subdirectory(script)
add_subdirectory(variant)
add_subdirectory(type)
add_subdirectory(widget)
