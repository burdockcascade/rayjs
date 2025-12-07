// src/main.cpp (Updated)

#include <iostream>
#include <CLI/CLI.hpp>
#include "js_runner.hpp"

int main(const int argc, char** argv) {

    // Initialize CLI11 App
    CLI::App app{"QuickJS CLI Runner"};

    // Define the --file flag
    std::string js_filepath;
    app.add_option("-f,--file", js_filepath, "Path to the JavaScript file to execute")
        ->required()
        ->check(CLI::ExistingFile);

    // Parse arguments
    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        // Handle argument parsing errors
        return app.exit(e);
    }

    // Execute the JavaScript code using the new encapsulated function
    return run_js_file(js_filepath);

}