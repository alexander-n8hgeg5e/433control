#!/usr/bin/python3
# Copyright 2018 Alexander Wilhelmi
# This file is part of 433control.
# 
# 433control is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# 433control is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with 433control.  If not, see <http://www.gnu.org/licenses/>.
# 
# Diese Datei ist Teil von 433control.
# 
# 433control ist Freie Software: Sie können es unter den Bedingungen
# der GNU General Public License, wie von der Free Software Foundation,
# Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
# veröffentlichten Version, weiter verteilen und/oder modifizieren.
# 
# 433control wird in der Hoffnung, dass es nützlich sein wird, aber
# OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
# Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
# Siehe die GNU General Public License für weitere Details.
# 
# Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
# Programm erhalten haben. Wenn nicht, siehe <https://www.gnu.org/licenses/>.
# Copyright 2018 Alexander Wilhelmi
# This file is part of 433control.
# 
# 433control is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# 433control is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with 433control.  If not, see <http://www.gnu.org/licenses/>.
# 
# Diese Datei ist Teil von 433control.
# 
# 433control ist Freie Software: Sie können es unter den Bedingungen
# der GNU General Public License, wie von der Free Software Foundation,
# Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
# veröffentlichten Version, weiter verteilen und/oder modifizieren.
# 
# 433control wird in der Hoffnung, dass es nützlich sein wird, aber
# OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
# Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
# Siehe die GNU General Public License für weitere Details.
# 
# Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
# Programm erhalten haben. Wenn nicht, siehe <https://www.gnu.org/licenses/>.
import serial
from time import sleep
s = serial.Serial(port='/dev/ttyACM1', baudrate=19200,timeout=0)
datasets = []
for i in range(0,4):
    done = False
    lines = []
    results_passed = False
    savethis = False
    capturing = False
    b4 = False
    for j in range(6,0,-1):
       print('capturing in '+str(j)+' seconds.')
       sleep(1);
    while not done:
        line = s.readline().decode().strip()
        if line.find('limit') is not -1 and capturing: # done
            savethis = False
            done = True
            print('dataset '+str(i)+' captured.')
        if line.find('limit') is -1 and results_passed: # no limit keyword -> values here
            capturing = True
            savethis = True
        if line.find('results') is not -1: # the results line
            results_passed = True
            savethis = False
        if savethis:
            lines.append(line)
    datasets.append(lines)
s.close()
print(datasets)
f = open('datacapture',mode='wt')
for i in datasets:
    for j in i:
        f.writelines(j+' ')
f.close()

