#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void executeScript(const std::string &interpreter, const std::string &scriptPath) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execlp(interpreter.c_str(), interpreter.c_str(), scriptPath.c_str(), nullptr);
        perror("Error executing the script");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            std::cout << "Script exited with code: " << WEXITSTATUS(status) << std::endl;
        } else {
            std::cerr << "Script terminated abnormally." << std::endl;
        }
    } else {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
}

void parseAndExecute(const std::string &scriptPath) {
    std::ifstream scriptFile(scriptPath);
    if (!scriptFile.is_open()) {
        std::cerr << "Error: Could not open script file." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string firstLine;
    std::getline(scriptFile, firstLine);

    if (firstLine.rfind("@!", 0) == 0) {
        // Extract the interpreter
        std::string interpreter = firstLine.substr(2);
        std::cout << "Using interpreter: " << interpreter << std::endl;

        executeScript(interpreter, scriptPath);
    } else {
        std::cerr << "Error: No @! directive found in the script." << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./bang_parser <script>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string scriptPath = argv[1];
    parseAndExecute(scriptPath);

    return EXIT_SUCCESS;
}
