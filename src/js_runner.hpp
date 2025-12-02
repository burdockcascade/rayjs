#pragma once

#include <string>

/**
 * @brief Reads the content of a file and executes it as JavaScript code using QuickJS.
 * * @param filepath The path to the JavaScript file.
 * @return 0 on successful execution, 1 on failure (file read error or JS exception).
 */
int run_js_file(const std::string& filepath);