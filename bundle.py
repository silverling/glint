import os
import shutil
from typing import List
import sys

# The shared libraries that we want to bundle with the executable.
# fmt: off
LIBRARY_PREFIXES = [
    "libopencv", "libmetavision", "libglfw", "libprotobuf", "libjpeg", "libgdcm",
    "libOpenEXR", "libgdal", "liblapack", "libblas", "libdc1394", "libav", "libsw",
    "libcharls", "libIlmThread", "libIex", "libx26", "libodbc", "libodbcinst",
    "libblosc", "libarmadillo", "libqhull_r", "libxerces-c-3.2", "libgeotiff",
    "libaec", "libpoppler", "libnetcdf", "libcfitsio", "libhdf5_serial", "libpq",
    "libkmlbase", "libkmldom", "libkmlengine", "libfyba", "libspatialite",
    "libmysqlclient", "libfreexl", "libogdi", "libgeos_c", "libproj", "libdfalt",
    "libmfhdfalt", "libjxl", "libjxl_threads", "libshine", "libSvtAv1Enc", "libbz2",
    "libsrt-gnutls", "libssh-gcrypt", "libarpack", "libsuperlu", "libcurl-gnutls",
    "libsz", "libminizip", "libfyut", "libfygm", "librttopo", "libgeos", "librtmp",
    "libcurl", "libicu"
]
# fmt: on

DIST_DIR = "dist"


def main() -> None:
    # Make sure the script is run from the directory where it is located
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    if len(sys.argv) < 2:
        print("Usage: python bundle.py <executable>")
        sys.exit(1)

    executable = sys.argv[1]
    if not os.path.isfile(executable):
        print(f"Error: {executable} is not a valid file.")
        sys.exit(1)

    bundle_executable(executable, DIST_DIR)
    print("Bundling complete.")


def bundle_executable(exe: str, dist_dir: str) -> None:
    """Bundle the executable and its dependencies into a distribution directory.
    Args:
        exe (str): Path to the executable to bundle.
        dist_dir (str): Directory where the bundled files will be placed.
    """

    # Clear previous distribution directory if it exists
    if os.path.exists(dist_dir):
        shutil.rmtree(dist_dir)
    os.makedirs(dist_dir, exist_ok=True)

    lib_dir = f"{DIST_DIR}/lib"
    os.makedirs(lib_dir, exist_ok=True)
    print(f"Created distribution directory: {dist_dir}")

    # Copy and patch the executable
    patch_rpath(
        shutil.copy2(exe, dist_dir, follow_symlinks=True),
        rpath=f"$ORIGIN/{os.path.relpath(lib_dir, dist_dir)}",
    )

    # For each dependency, check and copy if it matches the criteria
    # Also patch the RPATH for .so files, so it can find its dependencies
    all_deps = get_shared_deps(exe)
    for dep in all_deps:
        if not os.path.exists(dep):
            print(f"Dependency {dep} does not exist, skipping.")
            continue
        if not os.path.isfile(dep):
            print(f"{dep} is not a file, skipping.")
            continue

        filename = os.path.basename(dep)
        if any(filename.startswith(prefix) for prefix in LIBRARY_PREFIXES):
            dst = shutil.copy2(dep, lib_dir, follow_symlinks=True)
            patch_rpath(dst)
            print(f"Copied {dep} to {dst}")


def run_command(cmd: str) -> str:
    """
    Run a shell command and return the output.
    """
    result = os.popen(cmd).read()
    return result.strip()


def get_shared_deps(exe: str) -> List[str]:
    """
    Get all dependencies of the executable.
    """
    deps = []
    cmd = f"ldd {exe} | grep -v 'not a dynamic executable' | awk '{{print $3}}' | grep -v '^\\s*$'"
    output = run_command(cmd)
    if output:
        deps = output.split("\n")
    return deps


def patch_rpath(exe: str, rpath: str = "$ORIGIN") -> None:
    """
    Patch the RPATH of the executable to include the current directory.
    """
    cmd = f"patchelf --set-rpath '{rpath}' {exe}"
    run_command(cmd)


if __name__ == "__main__":
    main()
