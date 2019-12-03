import os
import time

def os_time_measure(input_dir, comp_prg):
    exec_times = []

    for r, d, f in os.walk(input_dir):
        for file in f:
            start = time.perf_counter()

            os.system(comp_prg + ' < ' + os.path.join(r,file))

            end = time.perf_counter()

            exec_times.append(end-start) 

    return exec_times
