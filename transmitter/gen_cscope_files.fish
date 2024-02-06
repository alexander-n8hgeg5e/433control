for i in (find -name '*c.d' -o -name '*cpp.d')
for j in (cat $i|grep -E '\S*[.](c(pp)?|h)'|grep -Ev '\S*[.](c(pp)?|h)[.][o]'|grep -Eo '\S*[.](c(pp)?|h)')
 echo $j
end
end|sort -u
