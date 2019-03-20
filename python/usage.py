import sys
from getopt import getopt

def usage():
    """
    Usage: python_usage.py [-v|--version] [-h|--help]
    Description:
        -v, --version   Display ...  version
        -h, --help      Display help information.
    """
    pass

if __name__ == '__main__':
    try:
        options, args = getopt(sys.argv[1:], "uv", [ "version", "help"])
    except Exception as e:
        print(e)
        print(usage.__doc__)
        exit(1)

    for option, _ in options:
        if option in ("-v", "--version"):
            pass
            break
        elif option in ("-h", "--version"):
            break
    print(usage.__doc__)