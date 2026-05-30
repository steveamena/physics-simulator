from pathlib import Path
import subprocess
import shutil
import sys
import argparse
import traceback


ROOT_DIR = Path(__file__).resolve().parent
BUILD_DIR = ROOT_DIR / "build"

EXECUTABLE_NAME = "physics-simulator"

# Windows executable extension
if sys.platform.startswith("win"):
    EXECUTABLE_NAME += ".exe"

EXECUTABLE_PATH = BUILD_DIR / EXECUTABLE_NAME


def run_command(command):
    print(f"\n>> Running: {' '.join(command)}\n")
    subprocess.run(command, check=True)


def configure(build_type="Debug"):
    run_command([
        "cmake",
        "-B", str(BUILD_DIR),
        "-G", "Ninja",
        f"-DCMAKE_BUILD_TYPE={build_type}"
    ])


def build():
    run_command([
        "cmake",
        "--build",
        str(BUILD_DIR)
    ])

def clean():
    if BUILD_DIR.exists():
        print(">> Removing build directory")
        shutil.rmtree(BUILD_DIR)
    else:
        print(">> Build directory does not exist")


def run():
    if not EXECUTABLE_PATH.exists():
        print(">> Executable not found. Build the project first.")
        return

    run_command([str(EXECUTABLE_PATH)])


def rebuild(build_type="Debug"):
    clean()
    configure(build_type)
    build()


def arguments_manager():
    parser = argparse.ArgumentParser(
        description="Physics Simulator Build Tool"
    )

    parser.add_argument(
        "command",
        choices=["debug", "release", "rebuild", "run", "clean"],
        help="Build command to execute"
    )

    args = parser.parse_args()

    print(args.command)
    return args

def main():
    args = arguments_manager()
    commands = {
        "debug": lambda: (
            configure("Debug"),
            build()
        ),

        "release": lambda: (
            configure("Release"),
            build()
        ),

        "rebuild": lambda: rebuild("Debug"),

        "run": run,

        "clean": clean
    }
    try:
        commands[args.command]()
    except Exception as e:
        print(f"Exception {e} generated. Details: {traceback.format_exc()}")

if __name__ == "__main__":
    main()