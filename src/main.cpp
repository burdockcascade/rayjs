// src/main.cpp (Updated)

#include <iostream>
#include <CLI/CLI.hpp>
#include "js_runner.hpp" // Now we include our new runner header

int main(const int argc, char** argv) {
    // 1. Initialize CLI11 App
    CLI::App app{"QuickJS CLI Runner"};

    // 2. Define the --file flag
    std::string js_filepath;
    app.add_option("-f,--file", js_filepath, "Path to the JavaScript file to execute")
        ->required()
        ->check(CLI::ExistingFile);

    // 3. Parse arguments
    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        // Handle argument parsing errors
        return app.exit(e);
    }

    // 4. Execute the JavaScript code using the new encapsulated function
    // This is now the only line of execution logic in main!
    return run_js_file(js_filepath);
}