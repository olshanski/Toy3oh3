# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("toy3oh3")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        toy3oh3

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        jni-bridge.cpp

        engine/Toy303AudioEngine.cpp
        engine/Voice.cpp
        engine/Oscillator.cpp
        engine/Envelope.cpp
        engine/CircularBuffer.cpp
        engine/EnvelopeListener.cpp
        engine/Filter.cpp
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

find_package (oboe REQUIRED CONFIG)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        toy3oh3

        oboe::oboe

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})