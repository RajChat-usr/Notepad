import os
import sys
import subprocess

def parse_and_execute(script_path):
    with open(script_path, 'r') as script:
        first_line = script.readline().strip()
        if first_line.startswith("@!"):
            # Extract interpreter path
            interpreter = first_line[2:].strip()
            # Pass the script to the interpreter
            subprocess.run([interpreter, script_path])
        else:
            print("Error: No @! directive found.")
            sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python run_bang.py <script>")
    else:
        parse_and_execute(sys.argv[1])
