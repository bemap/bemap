#!/usr/bin/python3
import glob
import sys
import os
import shutil


def cp_file(filename, path):
    filebasename = os.path.basename(filename)
    shutil.copyfile(filename, os.path.join(path, filebasename))

def update_conf(filepath, conf={}):
    with open(filepath) as fp:
        for line in fp:
            if line[0] != '#':
                line = line.replace('\n','')
                line = line.replace('\r','')
                splited_line = line.split('=')
                if len(splited_line) > 1:
                    conf[splited_line[0]] = '='.join(splited_line[1:])

    return conf

def main(args):
    sketch_dir = os.path.abspath(args[0])
    sketch_filename = glob.glob(os.path.join(sketch_dir, '*.ino'))[0]
    base_dir = os.path.abspath(os.path.dirname(__file__))
    libs_dir = os.path.join(base_dir, 'libs')
    tmp_dir = os.path.join('/tmp/bemap', os.path.basename(sketch_dir))
    global_conf = os.path.join(base_dir, 'global.conf')
    local_conf = os.path.join(sketch_dir, 'arduino.conf')
    conf = update_conf(global_conf)
    conf = update_conf(local_conf, conf)
    conf['sketch_filename'] = os.path.join(tmp_dir, os.path.basename(sketch_filename))

    # ensure a clear tmp dir
    if not os.path.exists(tmp_dir):
        os.makedirs(tmp_dir)
    for previous_files in glob.glob(os.path.join(tmp_dir, '*')):
        os.remove(previous_files)

    print('#################################')
    print('global configuration: ', global_conf)
    print('local configuration: ', local_conf)
    print('conf: ', conf)
    print('libs: ', libs_dir)
    print('sketch dir: ', sketch_dir)
    print('base dir: ', base_dir)
    print('tmp dir: ', tmp_dir)
    print('#################################')

    # cp libs to tmp dir
    for lib_filename in glob.glob(os.path.join(libs_dir, '*')):
        cp_file(lib_filename, tmp_dir)

    # cp sketch to tmp dir
    cp_file(sketch_filename, tmp_dir)

    cmd = '%(ARDUINO_PATH)s --board %(board)s --port %(port)s  --upload %(sketch_filename)s' % conf
    print('\n', cmd, '\n')
    os.system(cmd)
    # delete tmp dir
    # shutil.rmtree(tmp_dir)

if __name__ == "__main__":
    main(sys.argv[1:])