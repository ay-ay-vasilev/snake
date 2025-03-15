# Ensure the DLL is copied after build (only for Windows)
if(WIN32)
	add_custom_command(TARGET snake_app POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"$<TARGET_FILE_DIR:SDL3::SDL3>/SDL3.dll"
			"$<TARGET_FILE_DIR:snake_app>/SDL3.dll"
	)
	add_custom_command(TARGET snake_app POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"$<TARGET_FILE_DIR:SDL3_image::SDL3_image>/SDL3_image.dll"
			"$<TARGET_FILE_DIR:snake_app>/SDL3_image.dll"
	)
endif()