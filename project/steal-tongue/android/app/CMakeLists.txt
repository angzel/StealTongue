# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

set(ZEN_ROOT ../../../../../)

# libz
add_library(lib_zip STATIC IMPORTED)
set_target_properties(lib_zip
		PROPERTIES IMPORTED_LOCATION
		${CMAKE_SOURCE_DIR}/${ZEN_ROOT}/external/android/prebuilt/zlib/armeabi-v7a/libz-android.a)

# png

add_library(lib_png STATIC IMPORTED)
set_target_properties(lib_png
		PROPERTIES IMPORTED_LOCATION
		${CMAKE_SOURCE_DIR}/${ZEN_ROOT}/external/android/prebuilt/png/armeabi-v7a/libpng-android.a)


# jpeg

add_library(lib_jpeg STATIC IMPORTED)

set_target_properties(lib_jpeg
		PROPERTIES IMPORTED_LOCATION
		${CMAKE_SOURCE_DIR}/${ZEN_ROOT}/external/android/prebuilt/jpeg/armeabi-v7a/libjpeg-android.a)


# freetype2
add_library(lib_freetype STATIC IMPORTED)

set_target_properties(lib_freetype
		PROPERTIES IMPORTED_LOCATION
		${CMAKE_SOURCE_DIR}/${ZEN_ROOT}/external/android/prebuilt/freetype2/armeabi-v7a/libfreetype.a)


# openal
add_library(lib_openal STATIC IMPORTED)

set_target_properties(lib_openal
		PROPERTIES IMPORTED_LOCATION
		${CMAKE_SOURCE_DIR}/${ZEN_ROOT}/external/android/prebuilt/openal/armeabi-v7a/libopenal.a)

set(include_pathes
		../../source
		${ZEN_ROOT}/source/zen-core/
        ${ZEN_ROOT}/source/platfrom
        ${ZEN_ROOT}/source/platfrom/zen-android
        ${ZEN_ROOT}/source/platfrom/zen-unix
        ${ZEN_ROOT}/source/platfrom/zen-utils
        ${ZEN_ROOT}/source/platfrom/zen-utils/android
        ${ZEN_ROOT}/source/third
        ${ZEN_ROOT}/source/third/zen-jpg
        ${ZEN_ROOT}/source/third/zen-png
        ${ZEN_ROOT}/source/third/zen-mysql
        ${ZEN_ROOT}/source/third/zen-freetype
        ${ZEN_ROOT}/source/third/zen-metal
        ${ZEN_ROOT}/source/third/zen-al
        ${ZEN_ROOT}/source/third/zen-gles2
        ${ZEN_ROOT}/source/network
        ${ZEN_ROOT}/source/network/zen-http
        ${ZEN_ROOT}/source/network/zen-socket
        ${ZEN_ROOT}/source/network/zen-mail
        ${ZEN_ROOT}/source/basic
        ${ZEN_ROOT}/source/basic/zen-base
        ${ZEN_ROOT}/source/basic/zen-string
        ${ZEN_ROOT}/source/basic/zen-math
        ${ZEN_ROOT}/source/visual
        ${ZEN_ROOT}/source/visual/zen-app
        ${ZEN_ROOT}/source/visual/zen-app/android
        ${ZEN_ROOT}/source/visual/zen-vap
        ${ZEN_ROOT}/source/visual/zen-vap/3d
        ${ZEN_ROOT}/source/visual/zen-vap/model
        ${ZEN_ROOT}/source/media
        ${ZEN_ROOT}/source/media/zen-audio
        ${ZEN_ROOT}/source/media/zen-image
        ${ZEN_ROOT}/source/media/zen-player
		${ZEN_ROOT}/external/android/include
		${ZEN_ROOT}/external/android/include/freetype2
		)
# include
include_directories(
		${include_pathes}
)

# source files
file(GLOB cpp_files
		../../../source/*.cpp
        ${ZEN_ROOT}/source/zen-core/*.cpp
        ${ZEN_ROOT}/source/platfrom/*.cpp
        ${ZEN_ROOT}/source/platfrom/zen-android/*.cpp
        ${ZEN_ROOT}/source/platfrom/zen-unix/*.cpp
        ${ZEN_ROOT}/source/platfrom/zen-utils/*.cpp
        ${ZEN_ROOT}/source/platfrom/zen-utils/android/*.cpp
        ${ZEN_ROOT}/source/third/*.cpp
        ${ZEN_ROOT}/source/third/zen-jpg/*.cpp
        ${ZEN_ROOT}/source/third/zen-png/*.cpp
#        ${ZEN_ROOT}/source/third/zen-mysql/*.cpp
        ${ZEN_ROOT}/source/third/zen-freetype/*.cpp
        ${ZEN_ROOT}/source/third/zen-metal/*.cpp
        ${ZEN_ROOT}/source/third/zen-al/*.cpp
        ${ZEN_ROOT}/source/third/zen-gles2/*.cpp
        ${ZEN_ROOT}/source/network/*.cpp
        ${ZEN_ROOT}/source/network/zen-http/*.cpp
        ${ZEN_ROOT}/source/network/zen-socket/*.cpp
        ${ZEN_ROOT}/source/network/zen-mail/*.cpp
        ${ZEN_ROOT}/source/basic/*.cpp
        ${ZEN_ROOT}/source/basic/zen-base/*.cpp
        ${ZEN_ROOT}/source/basic/zen-string/*.cpp
        ${ZEN_ROOT}/source/basic/zen-math/*.cpp
        ${ZEN_ROOT}/source/visual/*.cpp
        ${ZEN_ROOT}/source/visual/zen-app/*.cpp
        ${ZEN_ROOT}/source/visual/zen-app/android/*.cpp
        ${ZEN_ROOT}/source/visual/zen-vap/*.cpp
        ${ZEN_ROOT}/source/visual/zen-vap/3d/*.cpp
        ${ZEN_ROOT}/source/visual/zen-vap/model/*.cpp
        ${ZEN_ROOT}/source/media/*.cpp
        ${ZEN_ROOT}/source/media/zen-audio/*.cpp
        ${ZEN_ROOT}/source/media/zen-image/*.cpp
        ${ZEN_ROOT}/source/media/zen-player/*.cpp
		)

add_library( # Sets the name of the library.
		native-lib
		SHARED
		${cpp_files}
		)

#find_path(GLES2_INCLUDE_DIR GLES2/gl2.h HINTS ${ANDROID_NDK})              #找到opengl头文件路径

#find_library(GLES2_LIBRARY libGLESv2.so HINTS ${GLES2_INCLUDE_DIR}/../lib)

find_library(log-lib log )

find_library(opensl-lib OpenSLES)

find_library(opengl-lib GLESv2)

target_link_libraries( # Specifies the target library.
		native-lib
		# ${GLES2_LIBRARY}
		${log-lib}
		${opensl-lib}
		${opengl-lib}
		lib_png
		lib_jpeg
		lib_openal
		lib_freetype
		lib_zip
		)

