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
# coding: utf-8
e=0
ok=0
for j in range(0,50):
    sum=0
    for i in range(0,len(a)):
        sum=sum+int(a[i][j])
    for i in range(0,len(a)):
        if ((sum/4) - int(a[i][j])) < (0.1*sum/4):
            ok=ok+1          
        else:
            e=e+1
print('errors: '+ str(e))
print('ok: '+ str(ok)) 
          
               
        
                      
