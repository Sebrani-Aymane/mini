Welcome to Minishell, a minimalist shell implementation project! This project aims to build a simple yet functional shell inspired by bash. The goal is to provide a deeper understanding of system-level programming, process management, and Unix/Linux shell features.
🚀 Features

Minishell replicates key functionalities of a standard shell, including:

    Prompt Display: Displays a customizable prompt to the user.
    Command Execution: Executes commands via PATH resolution and directly specified binaries.
    Built-in Commands:
        cd: Change the current directory.
        echo: Print arguments to the standard output.
        pwd: Display the current working directory.
        env: Display the current environment variables.
        export: Set or modify environment variables.
        unset: Remove environment variables.
        exit: Terminate the shell.
    Environment Handling: Fully supports environment variable management.
    Redirections: Handles input (<) and output (>, >>) redirections.
    Pipes: Supports piping (|) between commands.
    Signals:
        Handles Ctrl-C, Ctrl-D, and Ctrl-\ gracefully.
        Avoids termination on signal interruptions.
    Error Handling: Provides detailed error messages for invalid commands, syntax errors, and edge cases.
    Execution Features:
        Support for relative and absolute paths.
        Support for quoted arguments (single and double quotes).
        Wildcard handling (optional).

🛠️ Technologies Used

    C Programming Language: The core language for building the shell.
    POSIX APIs: For system calls such as fork, execve, wait, pipe, and signal handling.
    Makefile: For automated builds and dependency management.

📁 Project Structure

minishell/
├── execution/
│   ├──         # Entry point of the shell
│   ├──         # Command execution logic
│   ├──         # Built-in command implementations
│   └──         # Utility functions
├── parsing/
│   ├──         # Command parsing and syntax handling
├── include/
│   ├── minishell.h      # Main header file
└── Makefile             # Build automation

🔧 How to Build and Run

    Clone the repository:

git clone git@github.com:Sebrani-Aymane/mini.git
cd minishell

Build the project:

make

Run the shell:

./minishell

Clean the build:

    make clean

📋 Usage

    Launch the shell and interact with it using commands:

    $ ./minishell
    minishell> echo Hello, world!
    Hello, world!
    minishell> ls -l | grep minishell
    minishell.c
    minishell> exit

🧪 Testing

    Add your own test scripts in the tests/ directory for customized scenarios.

🌟 Project Goals

    Develop a deeper understanding of:
        Process and memory management.
        Shell command parsing and execution flow.
        Error handling and system interaction.
    Build a foundational project showcasing low-level programming expertise.

🤝 Contributing

Contributions are welcome! To contribute:

    Fork the repository.
    Create a feature branch:

git checkout -b feature-name

Commit your changes and push:

    git commit -m "Add feature description"
    git push origin feature-name

    Open a Pull Request.

📜 License

This project is licensed under the MIT License. You are free to use, modify, and distribute it.

🌐 Connect with us
Have questions, feedback, or ideas? Feel free to open an issue or contact us through GitHub Discussions.

Happy coding! 🚀
