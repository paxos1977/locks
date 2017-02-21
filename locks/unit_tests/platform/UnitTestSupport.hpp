#pragma once

#ifdef WIN32
    #pragma warning(push)
    #pragma warning(disable : 4127 4350)
    #include <UnitTest++/UnitTest++.h>
    #pragma warning(pop)
#else
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wnewline-eof"

    // Ubuntu and Debian use lowercase directory names :/
    #if defined UBUNTU || defined DEBIAN
        #include <unittest++/UnitTest++.h>
    #else 
        #include <UnitTest++/UnitTest++.h>
    #endif
    #pragma clang diagnostic pop
#endif

// handle the case we're on an older version of UnitTest++
#ifndef REQUIRE
    #define REQUIRE
#endif
