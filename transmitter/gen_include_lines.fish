for l in (fish gen_cscope_files.fish|grep '.h$')
echo '#include <'(basename $l)'>'
end
