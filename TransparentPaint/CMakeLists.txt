cmake_minimum_required(VERSION 3.8)

project(TransparentPaint)
set(TARGET_NAME ${PROJECT_NAME})

# exeを生成
add_executable(${TARGET_NAME} WIN32 main.cpp "TransparentPaint.h")

# C++バージョン
set_target_properties(${TARGET_NAME} PROPERTIES
		CXX_STANDARD 17
		CXX_EXTENSIONS ON
		LINKER_LANGUAGE CXX
	)

message("wxWidgets_ROOT_DIR = ${wxWidgets_ROOT_DIR}")
message("wxWidgets_LIB_DIR = ${wxWidgets_LIB_DIR}")
message("wxWidgets_CONFIGURATION = ${wxWidgets_CONFIGURATION}")
message("wxWidgets_EXCLUDE_COMMON_LIBRARIES = ${wxWidgets_EXCLUDE_COMMON_LIBRARIES}")

# wxWidgetsの検索
find_package( wxWidgets REQUIRED COMPONENTS core base )
include( ${wxWidgets_USE_FILE} )
message("wxWidgets_USE_FILE = ${wxWidgets_USE_FILE}")
message("wxWidgets_DEFINITIONS = ${wxWidgets_DEFINITIONS}")
message("wxWidgets_DEFINITIONS_DEBUG = ${wxWidgets_DEFINITIONS_DEBUG}")
message("wxWidgets_CXX_FLAGS = ${wxWidgets_CXX_FLAGS}")
message("wxWidgets_INCLUDE_DIRS = ${wxWidgets_INCLUDE_DIRS}")
message("wxWidgets_LIBRARY_DIRS = ${wxWidgets_LIBRARY_DIRS}")
message("wxWidgets_LIBRARIES = ${wxWidgets_LIBRARIES}")


#wxWidgetsのリンク
target_link_libraries(${TARGET_NAME} ${wxWidgets_LIBRARIES})