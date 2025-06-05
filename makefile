name=ao

path_directory_cero=../cer0
path_directory_cero_library=${path_directory_cero}/library
path_directory_include=include
path_directory_objects=objects
path_directory_output=output
path_directory_sources=sources

path_file_object_cero=${path_directory_cero_library}/cer0.o
path_file_output=${path_directory_output}/${name}

files_sources=${wildcard ${path_directory_sources}/*.c}
files_objects=${patsubst ${path_directory_sources}/%.c,${path_directory_objects}/%.o,${files_sources}}

c_opts=-O3 -I${path_directory_include} -I../cer0/include
c_opts_executable=-framework CoreAudio

cc=clang

${path_file_output}: ${files_objects} ${path_directory_output}
	${cc} ${c_opts} ${c_opts_executable} ${files_objects} ${path_file_object_cero} -o ${path_file_output}

${path_directory_objects}/%.o: ${path_directory_sources}/%.c ${path_directory_objects}
	${cc} ${c_opts} -c $< -o $@

${path_directory_objects}:
	mkdir ${path_directory_objects}

${path_directory_output}:
	mkdir ${path_directory_output}

clean:
	-rm -r ${path_directory_objects} 2> /dev/null
	-rm -r ${path_directory_output} 2> /dev/null
