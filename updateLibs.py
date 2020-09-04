import subprocess
import sys

def run_command(cmd):
    if sys.platform[:3] == 'win':
        startupinfo = subprocess.STARTUPINFO()
        startupinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    else:
        startupinfo = None

    # pass as the startupinfo keyword argument:
    return subprocess.Popen(cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        stdin=subprocess.PIPE,
        startupinfo=startupinfo,
        shell=True).communicate()

out, err = run_command('git -C external/bgfx pull origin master')
out, err = run_command('git -C external/bx pull origin master')
out, err = run_command('git -C external/bimg pull origin master')
