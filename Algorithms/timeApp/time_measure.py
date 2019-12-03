import os_call

cmp_prg = input('Digite o nome do binário de seu programa: ')
input_folder = input ('Digite o nome do diretorio dos casos de entrada: ')

exec_times = os_call.os_time_measure(input_folder,cmp_prg)

print('Tempos obtidos: ')

for time in exec_times:
    print(time)

