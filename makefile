name=ao

directory_cer0=../cer0
directory_cer0_include=${directory_cer0}/include
directory_cer0_library=${directory_cer0}/library

directory_cexil=../cexil
directory_cexil_include=${directory_cexil}/include
directory_cexil_library=${directory_cexil}/library

directory_clic3=../clic3
directory_clic3_include=${directory_clic3}/include
directory_clic3_library=${directory_clic3}/library

directory_include=include
directory_objects=objects
directory_output=output
directory_sources=sources

file_object_cer0=${directory_cer0_library}/cer0.o
file_object_cexil=${directory_cexil_library}/cexil.o
file_object_clic3=${directory_clic3_library}/clic3.o

file_output=${directory_output}/${name}

files_sources=${wildcard ${directory_sources}/*.c}
files_objects=${patsubst ${directory_sources}/%.c,${directory_objects}/%.o,${files_sources}}

cc=clang

c_flags=-O3 -I${directory_include} -I${directory_cer0_include} -I${directory_cexil_include} -I${directory_clic3_include}
c_flags_executable=-framework CoreAudio

strip=strip
strip_flags=

${file_output}: ${files_objects} ${directory_output}
	${cc} ${c_flags} ${c_flags_executable} ${files_objects} ${file_object_cer0} ${file_object_cexil} ${file_object_clic3} -o ${file_output}
	${strip} ${strip_flags} ${file_output}

${directory_objects}/%.o: ${directory_sources}/%.c ${directory_objects}
	${cc} ${c_flags} -c $< -o $@

${directory_objects}:
	mkdir ${directory_objects}

${directory_output}:
	mkdir ${directory_output}

clean: clean_objects clean_output

clean_objects:
	-rm -r ${directory_objects} 2> /dev/null

clean_output:
	-rm -r ${directory_output} 2> /dev/null
