set_description("RayJS")
set_version("0.1.0") -- x-release-please-version
set_languages("cxx20")

add_requires("cli11 2.6.1")
add_requires("raylib 5.5.0")
add_requires("quickjs-ng 0.11.0")

add_rules("mode.debug", "mode.release")

target("rayjs")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("cli11", "raylib", "quickjs-ng")
