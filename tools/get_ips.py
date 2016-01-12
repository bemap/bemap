#!/usr/bin/python3
import os
import re
import nmap

print('get ips')
#targeted_ips = ['192.168.1.{}'.format(index) for index in range(256)]
#print(targeted_ips)

nm = nmap.PortScanner()
nm.scan(hosts='192.168.0-1.0-255', arguments='-sn')
print(nm.all_hosts())





# #fun = lambda ip_addres: os.system("ping -c 1 " + ip_addres) == 0
# #devices = filter(fun, targeted_ips)

# #print("devices: ", list(devices))
# text = os.popen('nmap -sn 192.168.1.0-255').read()
# print(text.split('\n'))



# ips = []

# text = text.rstrip()
# #this is probably not the best way, but it works for now
# regex = re.findall(r'(?:[\d]{1,3})\.(?:[\d]{1,3})\.(?:[\d]{1,3})\.(?:[\d]{1,3})$', text)
# # if the regex is not empty and is not already in ips list append
# if regex is not None and regex not in ips:
#     ips.append(regex)

# print(ips)